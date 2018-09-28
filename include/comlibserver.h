#ifndef COMLIB_SERVER_H
#define COMLIB_SERVER_H

#include <QObject>
#include <QTcpServer>

class TcpClient;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

    void setPort(int port);
    int port() const;

    QHostAddress serverAddress() const;
    void setServerAddress(const QHostAddress &serverAddress);

public slots:
    void openSession();

signals:
    void newConnection(QSharedPointer<TcpClient>);
    void sessionOpened();
    void debug(QString);

private:
    void incomingConnection(qintptr socketDescriptor);
    int m_port;
    QHostAddress m_serverAddress;
};

#endif // SERVER_H
