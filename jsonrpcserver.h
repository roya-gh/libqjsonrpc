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

class LIBQJSONRPCSHARED_EXPORT JSonRPCServer : public QObject
{
    Q_OBJECT
public:
    explicit JSonRPCServer(RequestHandlerFactory *r, quint16 port, QObject *parent = nullptr);
    ~JSonRPCServer();

signals:

public slots:
    void handleNewHttpRequest(QHttpRequest *req, QHttpResponse *resp);

private :
    QHttpServer* server;
    RequestHandlerFactory* factory;
    QQueue<RequestHandler*> q;
};

#endif // JSONRPCSERVER_H
