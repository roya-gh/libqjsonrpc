#include "jsonrpcresponse.h"

JsonRPCResponse::JsonRPCResponse(int id, int errorCode, const QString& errorMessage,
                                 const QJsonObject& errorData, const QString& jsonrpcV)
    :  m_id(id), m_jsonrpcV(jsonrpcV), m_errorCode(errorCode),
       m_errorMessage(errorMessage), m_errorData(errorData) {

}
JsonRPCResponse::JsonRPCResponse(int id, const QVariant& result,
                                 const QString& jsonrpcV):
    m_id(id), m_jsonrpcV(jsonrpcV), m_result(result) {

}
void JsonRPCResponse::setJsonrpcV(const QString& jsonrpcv) {
    m_jsonrpcV = jsonrpcv;
}

void JsonRPCResponse::setId(int id) {
    m_id = id;
}

void JsonRPCResponse::setResult(const QJsonObject& result) {
    m_result = result;
}

void JsonRPCResponse::setErrorCode(int errorCode) {
    m_errorCode = errorCode;
}

void JsonRPCResponse::setErrorMessage(const QString& errorMessage) {
    m_errorMessage = errorMessage;
}

void JsonRPCResponse::setErrorData(const QJsonObject& errorData) {
    m_errorData = errorData;
}

const QVariant& JsonRPCResponse::result() {
    return m_result;
}

int JsonRPCResponse::errorCode() {
    return m_errorCode;
}

const QString& JsonRPCResponse::errorMessage() {
    return m_errorMessage;
}

const QJsonObject& JsonRPCResponse::errorData() {
    return m_errorData;
}
const QString& JsonRPCResponse::jsonrpcV() {
    return m_jsonrpcV;
}

int JsonRPCResponse::id() {
    return m_id;
}
