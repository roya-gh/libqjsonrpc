#ifndef JSONRPCERROR_H
#define JSONRPCERROR_H
#include "jsonrpcresponse.h"

class JsonRPCError : public JsonRPCResponse
{
public:
    JsonRPCError(
        int id = 0,
        int errorCode = 0,
        const QString& errorMessage = QString(),
       const QJsonObject& errorData = QJsonObject(),
       const QString& jsonrpcV = "2");

    ~JsonRPCError() = default;

    int errorCode();
    const QString& errorMessage();
    const QJsonObject& errorData();
    void setErrorCode(int );
    void setErrorMessage(const QString&);
    void setErrorData(const QJsonObject&);



private :
    int m_errorCode;
    QString m_errorMessage;
    QJsonObject m_errorData;
};

#endif // JSONRPCERROR_H
