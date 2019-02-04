#include "jsonrpcserver.h"
#include <QDebug>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

JSonRPCServer::JSonRPCServer(RequestHandlerFactory *r,QObject* parent):QObject(parent),factory(r),q() {
    server = new QHttpServer;
    server->listen(QHostAddress::Any, 8383);
    connect(server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
            this, SLOT(handle(QHttpRequest*, QHttpResponse*)));
}

void JSonRPCServer::handle(QHttpRequest* req, QHttpResponse* resp) {

    //    connect(req, SIGNAL(data(const QByteArray&)),
    //            this, SLOT(parseJsonData(const QByteArray&)));
    q.push_back(factory->createHandler(req,resp));
}

//void JSonRPCServer::parseJsonData(const QByteArray& r)
//{

//}
