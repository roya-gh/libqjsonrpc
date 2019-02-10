#ifndef JSONRPCRESPONSE_H
#define JSONRPCRESPONSE_H
#include <QString>
#include <QVariant>
#include <QJsonObject>
#include "libqjsonrpc_global.h"

class LIBQJSONRPCSHARED_EXPORT JsonRPCResponse {
public:
    JsonRPCResponse();
    JsonRPCResponse(int id, const QVariant& result,
                    const QString& jsonrpcV = "2");
    JsonRPCResponse(const QVariant& result ,
                    const QString& jsonrpcV = "2");
    JsonRPCResponse(int id,
                    int errorCode ,
                    const QString& errorMessage ,
                    const QJsonObject& errorData = QJsonObject(),
                    const QString& jsonrpcV = "2");
    JsonRPCResponse(
        int errorCode,
        const QString& errorMessage ,
        const QJsonObject& errorData = QJsonObject(),
        const QString& jsonrpcV = "2");

    ~JsonRPCResponse() = default;
    int id() const;
    const QString jsonrpcV()const;
    int errorCode()const;
    const QString errorMessage() const;
    const QJsonObject errorData() const;
    const QVariant result()const;
    const QJsonObject data();

public slots:
    void setJsonrpcV(const QString&);
    void setId(int);
    void setErrorCode(int);
    void setErrorMessage(const QString&);
    void setErrorData(const QJsonObject&);
    void setResult(const QVariant &);

private :
    QJsonObject m_data;
    QJsonValue toJsonValue(const QVariant& input);
    bool noId;
};

#endif // JSONRPCRESPONSE_H
