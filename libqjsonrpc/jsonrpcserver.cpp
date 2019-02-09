#include "jsonrpcserver.h"
#include <QDebug>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

JSonRPCServer::JSonRPCServer(QObject* parent):
    QHttpServer(parent) {
    connect(this, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
            this, SLOT(handleNewHttpRequest(QHttpRequest*, QHttpResponse*)));
}

void JSonRPCServer::setFactory(RequestHandlerFactory* f) {
    factory = f;
}

void JSonRPCServer::handleNewHttpRequest(QHttpRequest* req, QHttpResponse* resp) {
    q.push_back(factory->createHandler(req, resp));
}

