#include <QCoreApplication>
#include <QDebug>
#include "jsonrpcresult.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    JsonRPCResult r(8);

    qDebug()<<r.id()<<r.jsonrpcV();
    return a.exec();
}
