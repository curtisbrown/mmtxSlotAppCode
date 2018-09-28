#ifndef SERIALCLIENT_H
#define SERIALCLIENT_H

#include "client.h"
#include <QFile>

#ifndef Q_OS_ANDROID

#include <QSerialPort>

class SerialClient : public Client
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)
public:
    explicit SerialClient(QObject *parent = 0);

    bool open();
    void close();
    bool isConnected();

    QString portName() const;
    void setPortName(const QString &name);

    qint32 baudRate() const;
    void setBaudRate(qint32 rate);

    QSerialPort &ioDevice();

signals:
    void connectedChanged();

private slots:
    void error(QSerialPort::SerialPortError error);

private:
    QSerialPort m_serialPort;
};

#else

// hack for tricking the meta object compiler
namespace QSerialPort {
    enum SerialPortError {};
}

class SerialClient : public Client
{
    Q_OBJECT
public:
    explicit SerialClient(QObject *parent = 0) :
        Client(parent)
    {}

    bool open() { return true;}
    void close() {}
    bool isConnected() { return true; }

    QString portName() const { return QString(); }
    void setPortName(const QString &name) { Q_UNUSED(name); }

    qint32 baudRate() const { return 0; }
    void setBaudRate(qint32 rate) { Q_UNUSED(rate); }

    QIODevice &ioDevice() { return m_serialPort; }

signals:
    void connectedChanged();

private slots:
    void error(QSerialPort::SerialPortError error);

private:
    QFile m_serialPort;
};

#endif

#endif // SERIALCLIENT_H
