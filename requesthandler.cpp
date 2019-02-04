#include "requesthandler.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

RequestHandler::RequestHandler(QHttpRequest *req, QHttpResponse *resp, QObject *parent):
    QObject(parent),m_req(req),m_resp(resp)
{
    connect(m_req, SIGNAL(data(QByteArray)),this , SLOT(dataReceived(QByteArray)));
    connect(m_req, SIGNAL(end()),this , SLOT(parseData()));
}

void RequestHandler::dataReceived(const QByteArray &data)
{
    m_data.append(data);
}

void RequestHandler::parseData()
{
    qDebug()<<m_data.size();
    QJsonDocument j = QJsonDocument::fromJson(m_data);
    QJsonObject rootObject = j.object();
    qDebug()<<rootObject["jsonrpc"]<<rootObject["method"]<<rootObject["id"]
            <<rootObject["params"].type();

   JsonRPCResponse result= rpcResult(rootObject["method"].toString(),
           rootObject["params"].toObject());

   QJsonDocument doc(result.data());
   QByteArray bytes = doc.toJson(QJsonDocument::JsonFormat::Compact);

    qDebug() << "in request handler";
    m_resp->setHeader("Content-Length", QString::number(bytes.size()));
    m_resp->writeHead(200); // everything is OK
    m_resp->write(bytes);
    m_resp->end();
}

