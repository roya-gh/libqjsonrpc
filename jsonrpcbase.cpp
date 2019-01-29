#include "jsonrpcbase.h"

JsonRPCBase::JsonRPCBase(const QString &methodName, QObject *parent) : QObject(parent)
{
    m_data["jsonrpc"] = "2.0";
    setMethodName(methodName);
}

JsonRPCBase::JsonRPCBase(const JsonRPCBase *base):m_data(base->data())
{
}

const QJsonObject &JsonRPCBase::data()
{
    return m_data;
}

void JsonRPCBase::setMethodName(const QString& method) {
    m_data["method"] = method;
}
