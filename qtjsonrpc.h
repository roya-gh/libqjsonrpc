#ifndef QTJSONRPC_H
#define QTJSONRPC_H

#include <QJsonObject>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "jsonrpcresult.h"
#include "jsonrpcerror.h"
#include "jsonrpcrequest.h"

class JsonRPCClient : QObject
{
    Q_OBJECT
public:
    JsonRPCClient(const QUrl& url=QUrl(""), QObject* parent = nullptr);
    ~JsonRPCClient() = default;
    void setUrl(const QUrl&);
    void setHost(const QString&);
    void setPort(int);
    void dispatch(const JsonRPCNotification&);
    void dispatch(const JsonRPCRequest&);

//    int errorCode();
//    QString errorString();
//    void isNotification();
//    QVariant getResult();

private :
    QNetworkAccessManager httpManager;
    QNetworkRequest httpRequest;
//    QNetworkReply *httpReply;

private slots:
    void httpFinished(QNetworkReply *r);
//    void httpError(QNetworkReply::NetworkError);
    void sslerrors(QList<QSslError>);

 signals:
    void ResultRecieved(const JsonRPCResult&);
    void errorRecieved(const JsonRPCError&);
//    void networkError(const int ECode,const QString& EString);
};

#endif // QTJSONRPC_H
