#ifndef SSHCLIENT_H
#define SSHCLIENT_H

#include "client.h"
#include "sshiodevice.h"
#include "libsshpp.hpp"

#define MAXSSHBUFFERSIZE = 2048

class SshClient : public Client
{
    Q_OBJECT

public:
    enum KeyExhangeMethod {
        SSH_CLIENT_KEYEXHANGE_ECDH_SHA2_NISTP256,
        SSH_CLIENT_KEYEXHANGE_DIFFIE_HELLMAN_GROUP14_SHA1,
        SSH_CLIENT_KEYEXHANGE_DIFFIE_HELLMAN_GROUP1_SHA1
    };

    explicit SshClient(QObject *parent = 0);

    bool isConnected();
    void reset();

    QString hostname() const;

    qint16 port() const;

    SshIODevice &ioDevice();

public slots:
    bool setHostname(const QString &hostname);
    bool setPort(qint16 port);
    bool setKeyExhangeMethod(KeyExhangeMethod method);
    int authPassword(QString password);
    int authKey(QString filepath, QString passphrase);
    bool open();
    bool openChannel();
    void close();

signals:
    void connected();
    void disconnected();

private slots:

private:
    int sshAuthError(int errorCode);
    ssh::Session m_session;
    ssh::Channel m_channel;
    SshIODevice m_iodevice;
    QString m_hostname;
    qint16 m_port;
    bool sessionOpen;

    static QStringList m_keyExchangeStrings;
};

#endif // SSHCLIENT_H
