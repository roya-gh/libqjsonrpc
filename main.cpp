#include <QCoreApplication>
#include <QDebug>
#include "jsonrpcresult.h"
#include "qtjsonrpc.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    JsonRPCResult r(8);

    qDebug()<<r.id()<<r.jsonrpcV();
    JsonRPCClient cl(false,int(123),"sayHello","{\"name\":\"dori\"}",QUrl("http://127.0.0.1:8383"));
//        JsonRPCClient cl(true,int(123),"notifyServer","",QUrl("http://127.0.0.1:8383"));

    cl.dispatch();
    return a.exec();
}
