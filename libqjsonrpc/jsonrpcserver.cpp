#include "jsonrpcserver.h"
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

JSonRPCServer::JSonRPCServer(QObject* parent):
    QHttpServer(parent) {
    connect(this, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
            this, SLOT(handleNewHttpRequest(QHttpRequest*, QHttpResponse*)));
}

void JSonRPCServer::setFactory(RequestHandlerFactory* f) {
    m_factory = f;
}

void JSonRPCServer::handleNewHttpRequest(QHttpRequest* req, QHttpResponse* resp) {
    deleteDoneHandlers();
    m_handlerQueue.push_back(m_factory->createHandler(req, resp));
}

void JSonRPCServer::deleteDoneHandlers() {
    for(QList<RequestHandler*>::iterator i = m_handlerQueue.begin(); i != m_handlerQueue.end();) {
        if((*i)->isDone()) {
            delete *i;
            i = m_handlerQueue.erase(i);
        } else {
            ++i;
        }
    }
}

