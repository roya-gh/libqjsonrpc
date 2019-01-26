#ifndef QTJSONRPC_H
#define QTJSONRPC_H

#include <QJsonObject>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "jsonrpcresult.h"
#include "jsonrpcerror.h"

class JsonRPCClient : QObject
{
    Q_OBJECT
public:
    JsonRPCClient(QObject* parent = nullptr,
                  bool notification=false, int id=0,const QString &methodName=QString(),
                  const QVariant& params=QVariant(),
                  const QUrl& url=QUrl(""));


    ~JsonRPCClient() = default;

public slots:
    void setNotification(bool);
    void setMethodName(const QString&);
    void setParams(const QVariant& );
    void setId(int);
//    void setId(QString);

    void setUrl(const QUrl&);
    void setHost(const QString&);
    void setPort(int);
    void dispatch();

    int errorCode();
    QString errorString();
    void isNotification();
    QVariant getResult();


private :
    bool m_isNotification;
    QJsonObject m_data;
    QJsonObject m_response;
    int m_errorCode;
    QString m_errorString;

    QNetworkAccessManager httpManager;
    QNetworkRequest httpRequest;
    QNetworkReply *httpReply;

    QJsonValue toJsonValue(const QVariant&);

//private slots:
//    void httpFinished();
//    void httpError(QNetworkReply::NetworkError);

// signals:
    void finished(const JsonRPCResult&);
    void error(const JsonRPCError&);
};

#endif // QTJSONRPC_H
