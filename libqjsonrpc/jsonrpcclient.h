#ifndef JSONRPCCLIENT_H
#define JSONRPCCLIENT_H

#include <QJsonObject>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "jsonrpcresponse.h"
#include "jsonrpcrequest.h"

#include "libqjsonrpc_global.h"

class LIBQJSONRPCSHARED_EXPORT JsonRPCClient : public QObject {
    Q_OBJECT
public:
    JsonRPCClient(const QUrl& url = QUrl{""}, QObject* parent = nullptr);
    ~JsonRPCClient() = default;
    void setUrl(const QUrl&);
    void dispatch(const JsonRPCRequest&);

private :
    QNetworkAccessManager httpManager;
    QUrl m_url;

private slots:
    void httpFinished(QNetworkReply* r);
    void sslerrors(QList<QSslError>);

signals:
    void ResultRecieved(const JsonRPCResponse&);
    //    void errorRecieved(const JsonRPCResponse&);
};

#endif // JSONRPCCLIENT_H
