#include <QString>
#include <QtTest>
#include <QDebug>
#include <jsonrpcserver.h>
#include <jsonrpcclient.h>

class Handler : public RequestHandler {
public:
    Handler(QHttpRequest* req, QHttpResponse* resp): RequestHandler(req, resp) {
    }

    JsonRPCResponse determineRPCResult(QString n, QJsonObject r) override {
        int temp = 0;
        qDebug() << r;
        if(n == "sum") {
            int i = r["x"].toInt();
            int j = r["y"].toInt();
            temp = i + j;
        } else   if(n == "sub") {
            int i = r["x"].toInt();
            int j = r["y"].toInt();
            temp = i - j;
        }
        //TODO: handle error
        JsonRPCResponse res(temp);
        return res;
    }
};

class HandlerFactory : public RequestHandlerFactory {
public:
    RequestHandler* createHandler(QHttpRequest* req, QHttpResponse* resp)const override {
        return new Handler(req, resp);
    }
};

class testClientData: public QObject {
    Q_OBJECT
public:
    testClientData() = default;
public slots:
    void clientDataReady(const JsonRPCResponse& r) {
        qDebug() << "received result is " << r.id() << r.jsonrpcV() << r.result() <<
                 r.errorCode() << r.errorData() << r.errorMessage();
        QCOMPARE(2, r.result().toInt());
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
    QObject(parent), m_portNumber(8383) {
}

JsonRPCServerTest::~JsonRPCServerTest() {
}

void JsonRPCServerTest::initTestCase() {
    m_server.setFactory(&m_handlerFactory);
    QVERIFY(m_server.listen(m_portNumber));
}

void JsonRPCServerTest::client() {
    m_client.setUrl("http://127.0.0.1:" + QString::number(m_portNumber));
    int i = 1;
    //    for(int i = 0; i < 2; ++i) {
    QJsonObject jobj;
    jobj["x"] = i;
    jobj["y"] = i;
    JsonRPCRequest req(1, "sum", jobj);
    qDebug() << "Dispatching " << req.data();

    connect(&m_client, SIGNAL(ResultRecieved(JsonRPCResponse)),
            &m_testClientData, SLOT(clientDataReady(const JsonRPCResponse)));
    m_client.dispatch(req);
    QTest::qWait(10000);
}

void JsonRPCServerTest::cleanupTestCase() {
    m_server.close();
    QTest::qWait(1000);
}

QTEST_GUILESS_MAIN(JsonRPCServerTest)

#include "tst_jsonrpcserver.moc"
