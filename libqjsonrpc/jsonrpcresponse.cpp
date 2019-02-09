#include "jsonrpcresponse.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QDate>
#include <QDateTime>
#include <QUrl>

JsonRPCResponse::JsonRPCResponse(int id, int errorCode, const QString& errorMessage,
                                 const QJsonObject& errorData, const QString& jsonrpcV) {
    setId(id);
    setJsonrpcV(jsonrpcV);
    setErrorCode(errorCode);
    setErrorMessage(errorMessage);
    if(!errorData.empty()) {
        setErrorData(errorData);
    }
}
JsonRPCResponse::JsonRPCResponse(int id, const QVariant& result,
                                 const QString& jsonrpcV) {
    setId(id);
    setResult(result);
    setJsonrpcV(jsonrpcV);
}


JsonRPCResponse::JsonRPCResponse(int errorCode, const QString& errorMessage,
                                 const QJsonObject& errorData, const QString& jsonrpcV) {
    setJsonrpcV(jsonrpcV);
    setErrorCode(errorCode);
    setErrorMessage(errorMessage);
    if(errorData.empty()) {
        setErrorData(errorData);
    }
    noId =true;
}
JsonRPCResponse::JsonRPCResponse(const QVariant& result,
                                 const QString& jsonrpcV) {
    setResult(result);
    setJsonrpcV(jsonrpcV);
    noId = true;
}
void JsonRPCResponse::setJsonrpcV(const QString& jsonrpcv) {
    m_data["jsonrpc"] = jsonrpcv;
}

void JsonRPCResponse::setId(int id) {
    noId =false;
    m_data["id"] = id;
}

void JsonRPCResponse::setResult(const QVariant& result) {
    m_data["result"] = toJsonValue(result);
}

void JsonRPCResponse::setErrorCode(int errorCode) {
    m_data["error"].toObject()["code"] = errorCode;
}

void JsonRPCResponse::setErrorMessage(const QString& errorMessage) {
    m_data["error"].toObject()["message"] = errorMessage;
}

void JsonRPCResponse::setErrorData(const QJsonObject& errorData) {
    m_data["error"].toObject()["data"] = errorData;
}

const QVariant JsonRPCResponse::result()const {
    return m_data["result"].toVariant();
}

const QJsonObject JsonRPCResponse::data() {
    //    QJsonObject d;
    //    d["id"] = id();
    //    d["jsonrpc"] = jsonrpcV();
    //    if(errorCode() == 0 && errorMessage().isEmpty()) {
    //        d["result"] = toJsonValue(result());
    //        return d;
    //    } else {
    //        QJsonObject errobj;
    //        errobj["code"] = errorCode();
    //        errobj["message"] = errorMessage();
    //        //for error data do sth
    //        d["error"] = errobj;
    //        return d;
    //    }
    if(noId)
        m_data.remove("id");
    return m_data;
}

int JsonRPCResponse::errorCode()const {
    return m_data["error"].toObject()["code"].toInt();
}

const QString JsonRPCResponse::errorMessage()const {
    return m_data["error"].toObject()["message"].toString();
}

const QJsonObject JsonRPCResponse::errorData()const {
    return m_data["error"].toObject()["data"].toObject();
}
const QString JsonRPCResponse::jsonrpcV()const {
    return m_data["jsonrpc"].toString();
}

int JsonRPCResponse::id()const {
    return m_data["id"].toInt();
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
