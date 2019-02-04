#include "jsonrpcresponse.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QDate>
#include <QDateTime>
#include <QUrl>

JsonRPCResponse::JsonRPCResponse(int errorCode, const QString& errorMessage,
                                 const QJsonObject& errorData, int id, const QString& jsonrpcV)
    :  m_id(id), m_jsonrpcV(jsonrpcV), m_errorCode(errorCode),
       m_errorMessage(errorMessage), m_errorData(errorData) {

}
JsonRPCResponse::JsonRPCResponse(const QVariant& result, int id,
                                 const QString& jsonrpcV):
    m_id(id), m_jsonrpcV(jsonrpcV), m_result(result),
    m_errorCode(), m_errorMessage() {

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

QJsonObject JsonRPCResponse::data() {
    QJsonObject d;
    d["id"] = id();
    d["jsonrpc"] = jsonrpcV();
    if(errorCode() == 0 && errorMessage().isEmpty()) {
        d["result"] = toJsonValue(result());
        return d;
    } else {
        QJsonObject errobj;
        errobj["code"] = errorCode();
        errobj["message"] = errorMessage();
        //for error data do sth
        d["error"] = errobj;
        return d;
    }
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

QJsonValue JsonRPCResponse::toJsonValue(const QVariant& input) {
    switch(input.type()) {
        case QMetaType::Int:
            return input.toInt();
            break;
        case QMetaType::Bool:
            return input.toBool();
            break;
        case QMetaType::QChar:
            return input.toString();
            break;
        case QMetaType::Double:
            return input.toDouble();
            break;
        case QMetaType::QString:
            return input.toString();
            break;
        case QMetaType::QDate:
            return input.toDate().toString("yyyy-MM-dd");
            break;
        case QMetaType::QDateTime:
            return input.toDateTime().toString("yyyy-MM-ddThh:mm:ss.zzzZ");
            break;
        case QMetaType::QTime:
            return input.toTime().toString("hh:mm:ss.zzzZ");
            break;
        case QMetaType::QUrl:
            return input.toUrl().toString();
            break;
        case QMetaType::QVariantList: {
            QList<QVariant> list = input.toList();
            QJsonArray output;
            for(const QVariant& item : list) {
                output.push_back(toJsonValue(item));
            }
            return output;
        }
        break;
        case QMetaType::QStringList: {
            QStringList list = input.toStringList();
            QJsonArray output;
            for(const QString& item : list) {
                output.push_back(item);
            }
            return output;
        }
        break;
        case QMetaType::QJsonValue:
            return input.toJsonValue();
            break;
        case QMetaType::QJsonObject:
            return input.toJsonObject();
            break;
        case QMetaType::QJsonArray:
            return input.toJsonArray();
            break;

        default:
            return QJsonValue();
            break;
    }
}
