#include "qtjsonrpc.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QPoint>
#include <QSize>
#include <QLine>
#include <QJsonDocument>
#include <QDebug>
#include <QNetworkReply>

//JsonRPCClient::JsonRPCClient(QObject *parent) :
//    QObject(parent)
//{

//}

JsonRPCClient::JsonRPCClient(bool notification, int id,
                             const QString& methodName, const QVariant& params, const QUrl& url, QObject* parent):
    QObject(parent), m_isNotification(notification), m_data(), m_response()
    , m_errorCode(), m_errorString(), httpManager(), httpRequest() {

    m_data["jsonrpc"] = "2.0";
    if(!m_isNotification) {
        setId(id);
        setParams(params);
    }
    setMethodName(methodName);
    setUrl(url);
    qDebug() << m_data["jsonrpc"] << m_data["method"] << m_data["params"] << m_data["id"];
}

JsonRPCClient::JsonRPCClient(bool notification, int id, const QString& methodName, const QJsonObject params, const QUrl& url,
                             QObject* parent)
    :    QObject(parent), m_isNotification(notification), m_data(), m_response()
    , m_errorCode(), m_errorString(), httpManager(), httpRequest() {
    m_data["jsonrpc"] = "2.0";
    if(!m_isNotification) {
        setId(id);
        m_data["params"] = params;
    }
    setMethodName(methodName);
    setUrl(url);
    qDebug() << m_data["jsonrpc"] << m_data["method"] << m_data["params"] << m_data["id"];
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
    m_data["id"] = int(id);
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

void JsonRPCClient::dispatch() {
    httpRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //    connect(httpReply, SIGNAL(error(QNetworkReply::NetworkError)),
    //            this, SLOT(httpError(QNetworkReply::NetworkError)));
    //    connect(httpReply, SIGNAL(sslErrors(QList<QSslError>)),
    //            this, SLOT(sslerrors(QList<QSslError>)));
    //    connect(httpReply, SIGNAL(finished()),
    //            this, SLOT(httpFinished()));
    //    httpRequest.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    connect(&httpManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(httpFinished(QNetworkReply*)));

    QJsonDocument doc(m_data);
    QByteArray bytes = doc.toJson(QJsonDocument::JsonFormat::Compact);
    //    qDebug() << bytes;
    httpManager.post(httpRequest, bytes);

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

void JsonRPCClient::httpFinished(QNetworkReply* rep) {
    qDebug() << "network finish";
    if(rep->error() == QNetworkReply::NoError) {
        qDebug() << "no error";
        QByteArray r = rep->readAll();
        qDebug() << r.size();
        QJsonDocument j = QJsonDocument::fromJson(r);
        QJsonObject rootObject = j.object();
        qDebug() << rootObject.value("result").toString();
        for(QJsonObject::iterator i = rootObject.begin(); i != rootObject.end();
                i++) {
            qDebug() << i.key() << i.value();
        }
        //        for(const QString& key: rootObject.keys()) {
        //            QJsonValue value = rootObject.value(key);
        //            qDebug() << "Key = " << key << ", Value = " << value.toString();
        //        }

    } else {
        qDebug() << rep->error() << rep->errorString();
    }
    rep->deleteLater();
}

void JsonRPCClient::httpError(QNetworkReply::NetworkError err) {
    qDebug() << "network error " << err;
}

void JsonRPCClient::sslerrors(QList<QSslError>) {
    qDebug() << "sslerror";
}
