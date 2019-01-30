#ifndef JSONRPCRESPONSE_H
#define JSONRPCRESPONSE_H
#include <QString>
#include <QVariant>
#include <QJsonObject>

class JsonRPCResponse {
public:
    JsonRPCResponse(int id = 0, const QVariant& result = QJsonObject(),
                    const QString& jsonrpcV = "2");
    JsonRPCResponse(
        int id = 0,
        int errorCode = 0,
        const QString& errorMessage = QString(),
        const QJsonObject& errorData = QJsonObject(),
        const QString& jsonrpcV = "2");

    ~JsonRPCResponse() = default;
    int id();
    const QString& jsonrpcV();
    int errorCode();
    const QString& errorMessage();
    const QJsonObject& errorData();
    const QVariant& result();

public slots:
    void setJsonrpcV(const QString&);
    void setId(int);
    void setErrorCode(int);
    void setErrorMessage(const QString&);
    void setErrorData(const QJsonObject&);
    void setResult(const QJsonObject&);

private :
    int m_id;
    QString m_jsonrpcV;
    int m_errorCode;
    QString m_errorMessage;
    QJsonObject m_errorData;
    QVariant m_result;
};

#endif // JSONRPCRESPONSE_H
