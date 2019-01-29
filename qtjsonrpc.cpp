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


JsonRPCClient::JsonRPCClient(const QUrl& url, QObject* parent):
    QObject(parent), httpManager(), httpRequest() {
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

void JsonRPCClient::dispatch(const JsonRPCNotification& jrequest) {
    httpRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(&httpManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(httpFinished(QNetworkReply*)));

    QJsonDocument doc(jrequest.data());
    QByteArray bytes = doc.toJson(QJsonDocument::JsonFormat::Compact);
    //    qDebug() << bytes;
    httpManager.post(httpRequest, bytes);

}

void JsonRPCClient::dispatch(const JsonRPCRequest& jrequest) {
    httpRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(&httpManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(httpFinished(QNetworkReply*)));

    QJsonDocument doc(jrequest.data());
    QByteArray bytes = doc.toJson(QJsonDocument::JsonFormat::Compact);
    //    qDebug() << bytes;
    httpManager.post(httpRequest, bytes);
}




void JsonRPCClient::httpFinished(QNetworkReply* rep) {
    if(rep->error() == QNetworkReply::NoError) {
        QByteArray r = rep->readAll();
//        qDebug() << r.size();
        QJsonDocument j = QJsonDocument::fromJson(r);
        QJsonObject rootObject = j.object();
//        qDebug() << rootObject.value("result").toString();
//        for(const QString& key: rootObject.keys()) {
//               QJsonValue value = rootObject.value(key);
//               qDebug() << "Key = " << key << ", Value = " << value.toString();
//           }

        if(rootObject.contains("error")) {
            JsonRPCError err(rootObject["id"].toInt(),
                             rootObject["error"].toObject()["code"].toInt(),
                             rootObject["error"].toObject()["message"].toString(),
                             rootObject["error"].toObject()["data"].toObject(),
                             rootObject["jsonrpc"].toString());
//            qDebug() << err.id() << err.errorCode() << err.errorMessage() << err.jsonrpcV();
            emit errorRecieved(err);
        } else {
            JsonRPCResult res(rootObject["id"].toInt(),
                              rootObject["result"].toVariant(),
                              rootObject["jsonrpc"].toString());
            qDebug() << res.id() << res.result().toString() << res.jsonrpcV();
//            for(const QString& key: res.result().keys()) {
//                   QJsonValue value = res.result().value(key);
//                   qDebug() << "Key = " << key << ", Value = " << value.toString();
//               }
            emit ResultRecieved(res);
        }
    } else {
//        qDebug() << rep->error() << rep->errorString();
        JsonRPCError err(0, rep->error(), rep->errorString());
        emit errorRecieved(err);
    }
    rep->deleteLater();
}

void JsonRPCClient::sslerrors(QList<QSslError>) {
    qDebug() << "sslerror";
}
