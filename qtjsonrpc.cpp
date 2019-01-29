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


JsonRPCClient::JsonRPCClient(const JsonRPCBase *request, const QUrl& url, QObject* parent ):
    QObject(parent), m_request(request),m_response(),httpManager(), httpRequest() {
    setUrl(url);
}



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

    connect(&httpManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(httpFinished(QNetworkReply*)));

    QJsonDocument doc(m_request->data());
    QByteArray bytes = doc.toJson(QJsonDocument::JsonFormat::Compact);
    //    qDebug() << bytes;
    httpManager.post(httpRequest, bytes);

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
