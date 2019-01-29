#include "jsonrpcrequest.h"
#include <QDebug>
#include <QDate>
#include <QDateTime>
#include <QJsonArray>
#include <QUrl>

JsonRPCRequest::JsonRPCRequest(int id,
                               const QString& methodName, const QVariant& params, QObject* parent):
    JsonRPCBase(methodName,parent){

    setId(id);
    setParams(params);
    qDebug() << m_data["jsonrpc"] << m_data["method"] << m_data["params"] << m_data["id"];
}

JsonRPCRequest::JsonRPCRequest(int id, const QString& methodName, const QJsonObject params,
                               QObject* parent):
    JsonRPCBase(methodName,parent){
    setId(id);
    m_data["params"] = params;
    qDebug() << m_data["jsonrpc"] << m_data["method"] << m_data["params"] << m_data["id"];
}

void JsonRPCRequest::setParams(const QVariant& params) {
    m_data["params"] = toJsonValue(params);
}

void JsonRPCRequest::setId(int id) {
    m_data["id"] = int(id);
}



QJsonValue JsonRPCRequest::toJsonValue(const QVariant& input) {
    switch(input.type()) {
        case QVariant::Int:
            return input.toInt();
            break;
        case QVariant::Bool:
            return input.toBool();
            break;
        case QVariant::Char:
            return input.toString();
            break;
        case QVariant::Double:
            return input.toDouble();
            break;
        case QVariant::String:
            return input.toString();
            break;
        case QVariant::Date:
            return input.toDate().toString("yyyy-MM-dd");
            break;
        case QVariant::DateTime:
            return input.toDateTime().toString("yyyy-MM-ddThh:mm:ss.zzzZ");
            break;
        case QVariant::Time:
            return input.toTime().toString("hh:mm:ss.zzzZ");
            break;
        case QVariant::Url:
            return input.toUrl().toString();
            break;
        case QVariant::List: {
            QList<QVariant> list = input.toList();
            QJsonArray output;
            for(const QVariant& item : list) {
                output.push_back(toJsonValue(item));
            }
            return output;
        }
        break;
        case QVariant::StringList: {
            QStringList list = input.toStringList();
            QJsonArray output;
            for(const QString& item : list) {
                output.push_back(item);
            }
            return output;
        }
        break;
        default:
            return QJsonValue();
            break;
    }
}
