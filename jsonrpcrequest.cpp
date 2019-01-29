#include "jsonrpcrequest.h"
#include <QDebug>
#include <QDate>
#include <QDateTime>
#include <QJsonArray>
#include <QUrl>

JsonRPCRequest::JsonRPCRequest(int id, const QString& methodName,
                               const QVariant& params, QObject* parent):
    JsonRPCNotification(methodName, parent) {
    setId(id);
    setParams(params);
    //    qDebug() << m_data["jsonrpc"] << m_data["method"] << m_data["params"] << m_data["id"];
}

void JsonRPCRequest::setParams(const QVariant& params) {
    m_data["params"] = toJsonValue(params);
}

void JsonRPCRequest::setId(int id) {
    m_data["id"] = int(id);
}

QJsonValue JsonRPCRequest::toJsonValue(const QVariant& input) {
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
