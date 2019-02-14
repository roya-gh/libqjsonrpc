#include "requesthandler.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

RequestHandler::RequestHandler(QHttpRequest* req, QHttpResponse* resp, QObject* parent):
    QObject{parent}, m_req{req}, m_resp{resp}, m_done{false} {

    connect(m_req, SIGNAL(data(QByteArray)), this, SLOT(dataReceived(QByteArray)));
    connect(m_req, SIGNAL(end()), this, SLOT(handleRPCRequest()));
    connect(m_resp, SIGNAL(done()), this, SLOT(setDone()));
}

RequestHandler::~RequestHandler() {
}

bool RequestHandler::isDone() {
    return m_done;
}

void RequestHandler::dataReceived(const QByteArray& data) {
    m_data.append(data);
}

void RequestHandler::handleRPCRequest() {
    QJsonDocument j = QJsonDocument::fromJson(m_data);
    QJsonObject rootObject = j.object();

    JsonRPCResponse result = determineRPCResult(rootObject["method"].toString(),
                             rootObject["params"].toObject());

    m_resp->writeHead(200); // everything is OK
    //only send a rpc response if it was not a notification
    if(rootObject["id"] != QJsonValue::Null) {
        result.setId(rootObject["id"].toInt());
        QJsonDocument doc{result.data()};
        QByteArray bytes = doc.toJson(QJsonDocument::JsonFormat::Compact);
        m_resp->setHeader("Content-Length", QString::number(bytes.size()));
        m_resp->write(bytes);
    }
    m_resp->end();
}

void RequestHandler::setDone() {
    m_done = true;
}

