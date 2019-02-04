#ifndef JSONRPCSERVER_H
#define JSONRPCSERVER_H
#include <QObject>
#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>
#include "requesthandler.h"
#include "requesthandlerfactory.h"
#include <QQueue>

class JSonRPCServer : public QObject
{
    Q_OBJECT
public:
    explicit JSonRPCServer(RequestHandlerFactory *r, QObject *parent = nullptr);
    ~JSonRPCServer()=default;

signals:

public slots:
    void handle(QHttpRequest *req, QHttpResponse *resp);
//    void parseJsonData(const QByteArray&);
private :
    QHttpServer* server;
    RequestHandlerFactory* factory;
    QQueue<RequestHandler*> q;
};

#endif // JSONRPCSERVER_H
