#include <QString>
#include <QtTest>
#include <jsonrpcserver.h>

class JsonRPCServerTest : public QObject {
    Q_OBJECT

public:
    JsonRPCServerTest();

private Q_SLOTS:
    void serve();
};

JsonRPCServerTest::JsonRPCServerTest() {
}

void JsonRPCServerTest::serve() {
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(JsonRPCServerTest)

#include "tst_jsonrpcserver.moc"
