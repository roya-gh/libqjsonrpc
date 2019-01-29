#ifndef JDONRPCDATA_H
#define JDONRPCDATA_H

#include <QObject>
#include <QJsonObject>
class JsonRPCNotification : public QObject {
    Q_OBJECT
public:
    JsonRPCNotification(const QString& methodName = QString()
                        , QObject* parent = nullptr);
    JsonRPCNotification(const JsonRPCNotification* base);
    ~JsonRPCNotification() = default;

    const QJsonObject& data() const;

public slots:
    void setMethodName(const QString&);
protected:
    QJsonObject m_data;


};

#endif // JDONRPCDATA_H
