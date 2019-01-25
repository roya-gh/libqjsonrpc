#include <QCoreApplication>
#include <QSize>
#include <QDebug>
#include <QJsonObject>
#include <QPair>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSize d(5,6);

    QJsonObject ob;

    ob["d"]=QJsonObject{{"h",d.height()},{"w",d.width()}};

//    qDebug()<<d.toString();
    return a.exec();
}
