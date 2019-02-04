#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <QObject>
#include <qhttprequest.h>
#include <qhttpresponse.h>
#include <QJsonValue>
#include "jsonrpcresponse.h"

class RequestHandler : public QObject
{
    Q_OBJECT
public:
    RequestHandler(QHttpRequest *req,
                   QHttpResponse *resp, QObject *parent = nullptr);

    ~RequestHandler()=default;

signals:

public slots:
    void dataReceived(const QByteArray &data);
    void parseData();
private :
    QHttpRequest *m_req;
    QHttpResponse *m_resp;
    QByteArray m_data;
    virtual JsonRPCResponse rpcResult(QString , QJsonObject)=0;
};

#endif // REQUESTHANDLER_H
