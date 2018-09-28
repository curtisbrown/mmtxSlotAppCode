#ifndef TCPCLIENTTHREADED_H
#define TCPCLIENTTHREADED_H

#include <QObject>
#include <QThread>
#include <QBuffer>
#include <QSharedPointer>
#include "client.h"

/*!
 * \brief The TcpClientThreaded class
 * Behaves more or less like a TcpClient except that all of what the TcpClient do is now threaded
 * This is useful to have a connection that will always send and received data even if the thread instantiating
 * the object is busy.
 * This avoids having to use a polling behavior with waitForBytesWritten and similar.
 */
class TcpClientThreaded : public Client
{
    Q_OBJECT
public:
    explicit TcpClientThreaded(QObject *parent = 0);
    ~TcpClientThreaded();

    QBuffer &ioDevice();

    bool isConnected();
    bool open(); // TODO: Causes run-time error messages when used, but it works.

signals:
    void setHostname(const QString &hostname);
    void setPort(qint16 port);
    void setSocketDescriptor(qintptr id);
    void openRequest();
    void close();

    void debug(QString, bool);
    void debug(QString);
    void debugWarning(QString);
    void connectedChanged();
    void connectionError();
    void connected();
    void disconnected();

    void writeToThread(QSharedPointer<QByteArray> data);

public slots:
    qint64 write(const char *data, qint64 maxSize);

private slots:
    void fillBuffer(const QByteArray &array);

private:
    void setConnected(bool state);
    void setBlocking(bool blocking) { Q_UNUSED(blocking); } // Non blockable

    QThread m_tcpClientThread;
    QBuffer m_readBuffer;
    QByteArray m_readArray; //!< Filled with incomming data
    bool m_connected;
};

#endif // TCPCLIENTTHREADED_H
