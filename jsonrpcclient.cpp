#include "jsonrpcclient.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QPoint>
#include <QSize>
#include <QLine>
#include <QJsonDocument>
#include <QDebug>
#include <QNetworkReply>
#include "jsonrpcresponse.h"


JsonRPCClient::JsonRPCClient(const QUrl& url, QObject* parent):
    QObject(parent), httpManager(), m_url(url) {
}

void JsonRPCClient::setUrl(const QUrl& url) {
    m_url = url;
}

void JsonRPCClient::setHost(const QString& host) {
    m_url.setHost(host);
}

void JsonRPCClient::setPort(int port) {
    m_url.setPort(port);
}

void JsonRPCClient::dispatch(const JsonRPCRequest& jrequest) {
    QNetworkRequest httpRequest(m_url);
    httpRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(&httpManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(httpFinished(QNetworkReply*)));

    QJsonDocument doc(jrequest.data());
    QByteArray bytes = doc.toJson(QJsonDocument::JsonFormat::Compact);
    httpManager.post(httpRequest, bytes);
}

void JsonRPCClient::httpFinished(QNetworkReply* rep) {
    if(rep->error() == QNetworkReply::NoError) {
        QByteArray r = rep->readAll();
        QJsonDocument j = QJsonDocument::fromJson(r);
        QJsonObject rootObject = j.object();
        qDebug() << "finished ?!";
        if(rootObject.contains("error")) {
            JsonRPCResponse err(
                rootObject["id"].toInt(),
                rootObject["error"].toObject()["code"].toInt(),
                rootObject["error"].toObject()["message"].toString(),
                rootObject["error"].toObject()["data"].toObject(),
                rootObject["jsonrpc"].toString());
            qDebug() << err.id() << err.errorCode() << err.errorMessage() << err.jsonrpcV();
            emit ResultRecieved(err);
        } else {
            if(rootObject["id"] != QJsonValue::Null) {
                JsonRPCResponse res(
                    rootObject["id"].toInt(),
                    rootObject["result"].toVariant(),
                    rootObject["jsonrpc"].toString()
                );
                emit ResultRecieved(res);
                qDebug() << res.id() << res.result().toString() << res.jsonrpcV();
            } else {
                JsonRPCResponse res(
                    rootObject["result"].toVariant(),
                    rootObject["jsonrpc"].toString()
                );
                emit ResultRecieved(res);
                qDebug() << res.result().toString() << res.jsonrpcV();
            }
        }
    } else {
        qDebug() << rep->error() << rep->errorString();
        JsonRPCResponse err(0, rep->error(), rep->errorString());
        emit ResultRecieved(err);
    }
    rep->deleteLater();
}

void JsonRPCClient::sslerrors(QList<QSslError>) {
    qDebug() << "sslerror";
}
