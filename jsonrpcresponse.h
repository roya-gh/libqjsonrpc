#ifndef JSONRPCRESPONSE_H
#define JSONRPCRESPONSE_H
#include <QString>
#include <QVariant>
#include <QJsonObject>

class JsonRPCResponse {
public:
    JsonRPCResponse(int id = 0,
       const QString& jsonrpcV = "2");
    ~JsonRPCResponse() = default;

    const QString& jsonrpcV();
    int id();


    void setJsonrpcV(const QString& );
    void setId(int );


private:
    int m_id;
    QString m_jsonrpcV;




};

#endif // JSONRPCRESPONSE_H
