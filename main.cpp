#include <QCoreApplication>
#include <QDebug>
#include "jsonrpcresult.h"
#include "qtjsonrpc.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    JsonRPCResult r(8);

    qDebug()<<r.id()<<r.jsonrpcV();
    JsonRPCClient cl(false,int(123),"guru.test","[\"Guru\"]",QUrl("https://gurujsonrpc.appspot.com/guru"));
    cl.dispatch();
    return a.exec();
}
