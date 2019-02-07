#include "jsonrpcserver.h"
#include <QDebug>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

JSonRPCServer::JSonRPCServer(RequestHandlerFactory* r,quint16 port, QObject* parent): QObject(parent), factory(r), q() {
    server = new QHttpServer;
    server->listen(QHostAddress::Any, port);
    connect(server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
            this, SLOT(handleNewHttpRequest(QHttpRequest*, QHttpResponse*)));
}

JSonRPCServer::~JSonRPCServer()
{
    server->deleteLater();
}

void JSonRPCServer::handleNewHttpRequest(QHttpRequest* req, QHttpResponse* resp) {
    q.push_back(factory->createHandler(req, resp));
}

