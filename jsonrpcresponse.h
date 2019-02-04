#ifndef JSONRPCRESPONSE_H
#define JSONRPCRESPONSE_H
#include <QString>
#include <QVariant>
#include <QJsonObject>

class JsonRPCResponse {
public:
    JsonRPCResponse(int id, const QVariant& result = QVariant(),
                    const QString& jsonrpcV = "2");
    JsonRPCResponse(const QVariant& result = QVariant(),
                    const QString& jsonrpcV = "2");
    JsonRPCResponse(int id,
                    int errorCode = 0,
                    const QString& errorMessage = QString(),
                    const QJsonObject& errorData = QJsonObject(),
                    const QString& jsonrpcV = "2");
    JsonRPCResponse(
        int errorCode = 0,
        const QString& errorMessage = QString(),
        const QJsonObject& errorData = QJsonObject(),
        const QString& jsonrpcV = "2");

    ~JsonRPCResponse() = default;
    int id();
    const QString jsonrpcV();
    int errorCode();
    const QString errorMessage();
    const QJsonObject errorData();
    const QVariant result();
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
