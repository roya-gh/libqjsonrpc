#include <QCoreApplication>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<int> i;
    i.push_back(2);
    i.push_back(3);
    QJsonObject j;
    j.insert("vals",QJsonArray(i));
    return a.exec();
}
