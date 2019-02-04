#include "requesthandler.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

RequestHandler::RequestHandler(QHttpRequest *req, QHttpResponse *resp, QObject *parent):
    QObject(parent),m_req(req),m_resp(resp)
{
    connect(m_req, SIGNAL(data(QByteArray)),this , SLOT(dataReceived(QByteArray)));
    connect(m_req, SIGNAL(end()),this , SLOT(handleRPCRequest()));
}

RequestHandler::~RequestHandler()
{
    m_req->deleteLater();
    m_resp->deleteLater();
}

void RequestHandler::dataReceived(const QByteArray &data)
{
    m_data.append(data);
}

void RequestHandler::handleRPCRequest()
{
    QJsonDocument j = QJsonDocument::fromJson(m_data);
    QJsonObject rootObject = j.object();
    qDebug()<<rootObject["jsonrpc"]<<rootObject["method"]<<rootObject["id"]
            <<rootObject["params"].type();

    JsonRPCResponse result= determineRPCResult(rootObject["method"].toString(),
            rootObject["params"].toObject());

    QJsonDocument doc(result.data());
    QByteArray bytes = doc.toJson(QJsonDocument::JsonFormat::Compact);

    m_resp->setHeader("Content-Length", QString::number(bytes.size()));
    m_resp->writeHead(200); // everything is OK
    m_resp->write(bytes);
    m_resp->end();
}

