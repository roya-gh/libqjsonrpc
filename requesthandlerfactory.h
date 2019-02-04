#ifndef REQUESTHANDLERFACTORY_H
#define REQUESTHANDLERFACTORY_H

#include "requesthandler.h"



class RequestHandlerFactory
{
public:
    explicit RequestHandlerFactory();
    virtual RequestHandler* createHandler(QHttpRequest* req, QHttpResponse* resp) const = 0;
};

#endif // REQUESTHANDLERFACTORY_H
