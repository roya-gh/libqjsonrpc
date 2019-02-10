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
    QObject(parent), m_url(url) {
}

void JsonRPCClient::setUrl(const QUrl& url) {
    m_url = url;
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
        if(rootObject.contains("error")) {
            JsonRPCResponse err(
                rootObject["id"].toInt(),
                rootObject["error"].toObject()["code"].toInt(),
                rootObject["error"].toObject()["message"].toString(),
                rootObject["error"].toObject()["data"].toObject(),
                rootObject["jsonrpc"].toString());
            emit ResultRecieved(err);
        } else {
            if(rootObject["id"] != QJsonValue::Null) {
                JsonRPCResponse res(
                    rootObject["id"].toInt(),
                    rootObject["result"].toVariant(),
                    rootObject["jsonrpc"].toString()
                );
                emit ResultRecieved(res);
            } else {
                JsonRPCResponse res(
                    rootObject["result"].toVariant(),
                    rootObject["jsonrpc"].toString()
                );
                emit ResultRecieved(res);
            }
        }
    } else {
        JsonRPCResponse err(0, rep->error(), rep->errorString());
        emit ResultRecieved(err);
    }
    rep->deleteLater();
}

void JsonRPCClient::sslerrors(QList<QSslError>) {
    qDebug() << "sslerror";
}
