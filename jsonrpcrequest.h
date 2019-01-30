#ifndef JSONRPCREQUEST_H
#define JSONRPCREQUEST_H
#include <QVariant>
#include <QJsonObject>
#include <QObject>
class JsonRPCRequest: public QObject {
public:
    JsonRPCRequest(int id,
                   const QString& methodName = QString(),
                   const QVariant& params = QVariant(),
                   const QString jrpc = "2.0",
                   QObject* parent = nullptr);

    JsonRPCRequest(const QString& methodName = QString(),
                   const QVariant& params = QVariant(),
                   const QString jrpc = "2.0",
                   QObject* parent = nullptr);

    ~JsonRPCRequest() = default;
    const QJsonObject& data() const;

public slots :
    void setParams(const QVariant& params);
    void setId(int id);
    void setMethodName(const QString&);
    void deleteId();
private :
    QJsonValue toJsonValue(const QVariant& input);
    QJsonObject m_data;
};

#endif // JSONRPCREQUEST_H
