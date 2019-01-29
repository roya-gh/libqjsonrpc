#ifndef JSONRPCREQUEST_H
#define JSONRPCREQUEST_H
#include "jsonrpcbase.h"
#include <QVariant>
#include <QJsonObject>
class JsonRPCRequest:public JsonRPCBase
{
public:

    JsonRPCRequest(int id=0, const QString &methodName=QString(),
                  const QVariant& params=QVariant(),
                  QObject* parent = nullptr);
    JsonRPCRequest(int id=0, const QString &methodName=QString(),
                  const QJsonObject params=QJsonObject(),
                  QObject* parent = nullptr);
public slots:
    void setParams(const QVariant& params);
    void setId(int id);
private :
    QJsonValue toJsonValue(const QVariant& input);

};

#endif // JSONRPCREQUEST_H
