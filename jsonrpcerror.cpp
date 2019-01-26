#include "jsonrpcerror.h"

JsonRPCError::JsonRPCError(int id, int errorCode, const QString& errorMessage,
                           const QJsonObject& errorData, const QString& jsonrpcV)
    : JsonRPCResponse(id, jsonrpcV), m_errorCode(errorCode),
      m_errorMessage(errorMessage), m_errorData(errorData) {

}

int JsonRPCError::errorCode() {
    return m_errorCode;
}
const QString& JsonRPCError::errorMessage() {
    return m_errorMessage;
}
const QJsonObject& JsonRPCError::errorData() {
    return m_errorData;
}

void JsonRPCError::setErrorCode(int errorCode) {
    m_errorCode = errorCode;
}

void JsonRPCError::setErrorMessage(const QString& errorMessage) {
    m_errorMessage = errorMessage;
}

void JsonRPCError::setErrorData(const QJsonObject& errorData) {
    m_errorData = errorData;
}



