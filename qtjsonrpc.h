#ifndef QTJSONRPC_H
#define QTJSONRPC_H

#include <QJsonObject>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "jsonrpcresponse.h"
#include "jsonrpcrequest.h"

class JsonRPCClient : QObject {
    Q_OBJECT
public:
    JsonRPCClient(const QUrl& url = QUrl(""), QObject* parent = nullptr);
    ~JsonRPCClient() = default;
    void setUrl(const QUrl&);
    void setHost(const QString&);
    void setPort(int);
    void dispatch(const JsonRPCRequest&);

private :
    QNetworkAccessManager httpManager;
    QUrl m_url;

private slots:
    void httpFinished(QNetworkReply* r);
    void sslerrors(QList<QSslError>);

signals:
    void ResultRecieved(const JsonRPCResponse&);
    void errorRecieved(const JsonRPCResponse&);
};

#endif // QTJSONRPC_H
