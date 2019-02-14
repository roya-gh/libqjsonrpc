#include <QString>
#include <QtTest>
#include <QDebug>
#include <jsonrpcserver.h>
#include <jsonrpcclient.h>
#include <jsonrpcresponse.h>
#include <QMap>
#include <QPair>
#include <QRandomGenerator>

class Handler : public RequestHandler {
public:
    Handler(QHttpRequest* req, QHttpResponse* resp): RequestHandler{req, resp} {
    }

    JsonRPCResponse determineRPCResult(QString n, QJsonObject r) override {
        JsonRPCResponse res;
        if(n == "sum") {
            if(!(r["x"] == QJsonValue::Undefined) && !(r["y"] == QJsonValue::Undefined)
                    && r["x"].isDouble() && r["y"].isDouble()) {
                int i = r["x"].toDouble();
                int j = r["y"].toDouble();
                double  temp = i + j;
                res.setResult(temp);
            } else {
                res.setErrorCode(-32602);
                res.setErrorMessage("Invalid method parameter(s).");
            }
        } else if(n == "sub") {
            int i = r["x"].toInt();
            int j = r["y"].toInt();
            int temp = i - j;
            res.setResult(temp);
        } else if(n == "toUpper") {
            QString i = r["str"].toString();
            QString temp = i.toUpper();
            res.setResult(temp);
        }
        //TODO: handle error
        else {
            res.setErrorCode(-32601);
            res.setErrorMessage("Method not found");
        }
        return res;
    }
};

class HandlerFactory : public RequestHandlerFactory {
public:
    RequestHandler* createHandler(QHttpRequest* req, QHttpResponse* resp)const override {
        return new Handler{req, resp};
    }
};

QMap<int, QPair<int, int>> test_data;

class testClientData: public QObject {
    Q_OBJECT
public:
    testClientData() = default;
public slots:
    void clientDataReady(const JsonRPCResponse& r) {
        qDebug() << "received result is " << r.id() << r.jsonrpcV() << r.result() <<
                 r.errorCode() << r.errorData() << r.errorMessage();
        int expected = test_data[r.id()].first + test_data[r.id()].second;
        if(r.id() <= 1000) {
            QCOMPARE(expected, r.result().toInt());
        }

    }

};

class JsonRPCServerTest : public QObject {
    Q_OBJECT

public:
    JsonRPCServerTest(QObject* parent = nullptr);
    ~JsonRPCServerTest();

private Q_SLOTS:
    void initTestCase();
    void client();
    void cleanupTestCase();
private :
    JSonRPCServer m_server;
    JsonRPCClient m_client;
    quint16 m_portNumber;
    HandlerFactory m_handlerFactory;
    testClientData m_testClientData;
};


JsonRPCServerTest::JsonRPCServerTest(QObject* parent):
    QObject(parent), m_portNumber{8383} {
}

JsonRPCServerTest::~JsonRPCServerTest() {
}

void JsonRPCServerTest::initTestCase() {

    for(int i = 1 ; i <= 1000 ; ++i) {
        int n1 = QRandomGenerator::global()->generate() % 1000 + 1;
        int n2 = QRandomGenerator::global()->generate() % 1000 + 1;
        test_data.insert(i, QPair<int, int>(n1, n2));
    }

    m_server.setFactory(&m_handlerFactory);
    QVERIFY(m_server.listen(m_portNumber));
}

void JsonRPCServerTest::client() {
    m_client.setUrl("http://127.0.0.1:" + QString::number(m_portNumber));
    connect(&m_client, SIGNAL(ResultRecieved(JsonRPCResponse)),
            &m_testClientData, SLOT(clientDataReady(const JsonRPCResponse)));

    for(int i = 1; i <= 1000; ++i) {
        QJsonObject jobj;
        jobj["x"] = test_data[i].first ;
        jobj["y"] = test_data[i].second;
        JsonRPCRequest req{i, "sum", jobj};
        //        qDebug() << "Dispatching " << req.data();
        m_client.dispatch(req);
    }

    QJsonObject o;
    o["str"] = "hello";
    JsonRPCRequest req{1500, "toUpper", o};
    m_client.dispatch(req);

    QTest::qWait(10000);
}

void JsonRPCServerTest::cleanupTestCase() {
    m_server.close();
    QTest::qWait(10000);
}

QTEST_GUILESS_MAIN(JsonRPCServerTest)

#include "tst_jsonrpcserver.moc"
