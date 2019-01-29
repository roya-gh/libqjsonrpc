#ifndef JSONRPCRESULT_H
#define JSONRPCRESULT_H
#include "jsonrpcresponse.h"
#include <QJsonObject>

class JsonRPCResult : public JsonRPCResponse
{
public:
    JsonRPCResult(int id = 0,const QVariant& result = QJsonObject(),
                  const QString& jsonrpcV = "2");
    ~JsonRPCResult()=default;
    const QVariant &result();
    void setResult(const QJsonObject&);

private:
    QVariant m_result;

};

#endif // JSONRPCRESULT_H
