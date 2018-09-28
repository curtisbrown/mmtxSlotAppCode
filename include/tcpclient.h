#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include "client.h"

class TcpClient : public Client
{
    Q_OBJECT
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY connectedChanged)

public:
    explicit TcpClient(QObject *parent = 0);

    bool openBlocking(int timeoutMs = 30000);
    bool isConnected();
    void reset();

    QString hostname() const;

    qint16 port() const;

    QTcpSocket &ioDevice();

public slots:
    void setHostname(const QString &hostname);
    void setPort(qint16 port);
    bool setSocketDescriptor(qintptr id);
    bool open();
    void close();

signals:
    void connectedChanged();
    void connectionError(QAbstractSocket::SocketError);
    void connected();
    void disconnected();

private slots:
    void error(QAbstractSocket::SocketError error);
    void stateChange(QAbstractSocket::SocketState state);

private:
    QTcpSocket m_socket;
    QString m_hostname;
    qint16 m_port;
};

#endif // TCPCLIENT_H
