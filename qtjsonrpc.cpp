#include "qtjsonrpc.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QPoint>
#include <QSize>
#include <QLine>

//JsonRPCClient::JsonRPCClient(QObject *parent) :
//    QObject(parent)
//{

//}

JsonRPCClient::JsonRPCClient(QObject* parent, bool notification, int id,
                             const QString& methodName, const QVariant& params, const QUrl& url):
    QObject(parent), m_isNotification(notification), m_data(), m_response()
    , m_errorCode(), m_errorString(), httpManager(), httpRequest(), httpReply() {
    setId(id);
    setMethodName(methodName);
    setParams(params);
    setUrl(url);
    m_data.insert("jsonrpc", 2);
}


void JsonRPCClient::setNotification(bool notification) {
    m_isNotification = notification;
}

void JsonRPCClient::setMethodName(const QString& method) {
    m_data["method"] = method;
}

void JsonRPCClient::setParams(const QVariant& params) {
    m_data["params"] = toJsonValue(params);
}

void JsonRPCClient::setId(int id) {
    m_data["id"] = id;
}


//void JsonRPCClient::setId(QString id)
//{
//    auto it=m_data.find("id");
//    if(it==m_data.end())
//        m_data.insert("id",id);
//    else
//    {
//        it.value() = id;
//    }
//}


void JsonRPCClient::setUrl(const QUrl& url) {
    httpRequest.setUrl(url);
}

void JsonRPCClient::setHost(const QString& host) {
    httpRequest.url().setHost(host);
}

void JsonRPCClient::setPort(int port) {
    httpRequest.url().setPort(port);
}

void JsonRPCClient::dispatch()
{

}

QJsonValue JsonRPCClient::toJsonValue(const QVariant& input) {
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
