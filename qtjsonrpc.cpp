#include "qtjsonrpc.h"

//JsonRPCClient::JsonRPCClient(QObject *parent) :
//    QObject(parent)
//{

//}

JsonRPCClient::JsonRPCClient(QObject *parent, bool notification, int id,
                             const QString &methodName,const QVariant &params, const QUrl &url):
    QObject(parent), m_isNotification(notification),m_data(),m_response()
  ,m_errorCode(),m_errorString(),httpManager(),httpRequest(),httpReply()
{
    setId(id);
    setMethodName(methodName);
    setParams(params);
    setUrl(url);
    m_data.insert("jsonrpc",2);
}


void JsonRPCClient::setNotification(bool notification)
{
    m_isNotification=notification;
}

void JsonRPCClient::setMethodName(const QString &method)
{
    m_data["method"] = method;
}

void JsonRPCClient::setParams(const QVariant &params)
{

        switch (params.type()) {
        case QVariant::Type::Bool :
            m_data["params"] = params.toBool();
            break;
        case QVariant::Type::Int :
            m_data["params"] = params.toInt();
            break;
//        case QVariant::Type::UInt :
//            m_data["params"] = params.toUInt();
        case QVariant::Type::LongLong :
            m_data["params"] = params.toLongLong();
            break;
//        case QVariant::Type::ULongLong :
//            m_data["params"] = params.toULongLong();
            break;
        case QVariant::Type::Char :
            m_data["params"] = params.toString();
            break;
        case QVariant::Type::Double :
            m_data["params"] = params.toDouble();
            break;
        case QVariant::Type::String :
            m_data["params"] = params.toString();
            break;
        case QVariant::Type::Url :
            m_data["params"] = params.toUrl().toString();
            break;



        default:
            break;
        }
}

void JsonRPCClient::setId(int id)
{
    m_data["id"] = id;
}


//void JsonRPCClient::setId(QString id)
//{
//    auto it=m_data.find("id");
//    if(it==m_data.end())
//        m_data.insert("id",id);
//    else
//    {
//        it.value() = id;
//    }
//}


void JsonRPCClient::setUrl(const QUrl &url)
{
    httpRequest.setUrl(url);
}

void JsonRPCClient::setHost(const QString &host)
{
    httpRequest.url().setHost(host);
}

void JsonRPCClient::setPort(int port)
{
    httpRequest.url().setPort(port);
}
