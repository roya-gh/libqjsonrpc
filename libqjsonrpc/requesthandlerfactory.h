#ifndef REQUESTHANDLERFACTORY_H
#define REQUESTHANDLERFACTORY_H

#include "requesthandler.h"
#include "libqjsonrpc_global.h"


class LIBQJSONRPCSHARED_EXPORT RequestHandlerFactory {
public:
    explicit RequestHandlerFactory();
    ~RequestHandlerFactory();
    virtual RequestHandler* createHandler(QHttpRequest* req, QHttpResponse* resp) const = 0;
};

#endif // REQUESTHANDLERFACTORY_H
