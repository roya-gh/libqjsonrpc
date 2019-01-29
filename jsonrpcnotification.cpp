#include "jsonrpcnotification.h"

JsonRPCNotification::JsonRPCNotification(const QString& methodName, QObject* parent) :
    QObject(parent) {
    m_data["jsonrpc"] = "2.0";
    setMethodName(methodName);
}

const QJsonObject& JsonRPCNotification::data()const {
    return m_data;
}

void JsonRPCNotification::setMethodName(const QString& method) {
    m_data["method"] = method;
}
