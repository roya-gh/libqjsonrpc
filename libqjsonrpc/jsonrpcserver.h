#ifndef JSONRPCSERVER_H
#define JSONRPCSERVER_H
#include <QObject>
#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>
#include "requesthandler.h"
#include "requesthandlerfactory.h"
#include <QQueue>
#include "libqjsonrpc_global.h"

class LIBQJSONRPCSHARED_EXPORT JSonRPCServer : public QHttpServer
{
    Q_OBJECT
public:
    explicit JSonRPCServer(QObject *parent = nullptr);
    ~JSonRPCServer()=default;
    void setFactory(RequestHandlerFactory*);

signals:

public slots:
    void handleNewHttpRequest(QHttpRequest *req, QHttpResponse *resp);

private :
//    QHttpServer* server;
    RequestHandlerFactory* factory;
    QQueue<RequestHandler*> q;
};

#endif // JSONRPCSERVER_H
