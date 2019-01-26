#include "jsonrpcresult.h"
#include "jsonrpcresponse.h"

JsonRPCResult::JsonRPCResult(int id, const QJsonObject& result,
                             const QString& jsonrpcV):
    JsonRPCResponse(id,jsonrpcV),m_result(result)
{

}
void JsonRPCResult::setResult(const QJsonObject & result)
{
    m_result = result;
}

const QJsonObject& JsonRPCResult::result() {
    return m_result;
}
