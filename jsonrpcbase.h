#ifndef JDONRPCDATA_H
#define JDONRPCDATA_H

#include <QObject>
#include <QJsonObject>
class JsonRPCBase : public QObject
{
    Q_OBJECT
public:
     JsonRPCBase(const QString& methodName=QString()
                         ,QObject *parent = nullptr);
     JsonRPCBase(const JsonRPCBase* base);
const QJsonObject& data();

signals:

public slots:
    void setMethodName(const QString&);
protected:
    QJsonObject m_data;


};

#endif // JDONRPCDATA_H
