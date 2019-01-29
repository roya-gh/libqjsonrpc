#include <QCoreApplication>
#include <QDebug>
#include "jsonrpcresult.h"
#include "qtjsonrpc.h"
#include <QJsonArray>
#include "jsonrpcrequest.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    JsonRPCResult r(8);

    qDebug()<<r.id()<<r.jsonrpcV();
    QJsonObject params;

    params["name"]="dor";
    JsonRPCRequest i(1,"sayHello",params);
    JsonRPCClient cl(QUrl("http://127.0.0.1:8383"));
//    JsonRPCClient cl(false,2,"sayHello",params,QUrl("http://127.0.0.1:8383"));
//        JsonRPCClient cl(true,int(123),"notifyServer","",QUrl("http://127.0.0.1:8383"));


    cl.dispatch(i);
    JsonRPCNotification n("notifyServer");
    cl.dispatch(n);

    return a.exec();
}
