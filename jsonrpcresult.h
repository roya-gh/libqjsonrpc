#ifndef JSONRPCRESULT_H
#define JSONRPCRESULT_H
#include "jsonrpcresponse.h"
#include <QJsonObject>

class JsonRPCResult : public JsonRPCResponse
{
public:
    JsonRPCResult(int id = 0,const QJsonObject& result = QJsonObject(),
                  const QString& jsonrpcV = "2");
    ~JsonRPCResult()=default;
    const QJsonObject& result();
    void setResult(const QJsonObject&);

private:
    QJsonObject m_result;

};

#endif // JSONRPCRESULT_H
