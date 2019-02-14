#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <QObject>
#include <qhttprequest.h>
#include <qhttpresponse.h>
#include <QJsonValue>
#include "jsonrpcresponse.h"

class RequestHandler : public QObject {
    Q_OBJECT
public:
    RequestHandler(QHttpRequest* req,
                   QHttpResponse* resp, QObject* parent = nullptr);

    ~RequestHandler();
    bool isDone();

signals:

public slots:
    void dataReceived(const QByteArray& data);
private slots:
    void handleRPCRequest();
    void setDone();
private :
    QHttpRequest* m_req;
    QHttpResponse* m_resp;
    QByteArray m_data;
    bool m_done;
    virtual JsonRPCResponse determineRPCResult(QString methodName, QJsonObject params) = 0;
};

#endif // REQUESTHANDLER_H
