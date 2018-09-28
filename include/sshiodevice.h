#ifndef SSHIODEVICE_H
#define SSHIODEVICE_H

#include <QObject>
#include <QIODevice>

namespace ssh {
    class Channel;
    class Session;
}

class SshIODevice : public QIODevice
{
public:
    SshIODevice() = delete;
    SshIODevice(ssh::Channel &channel);
    bool open(OpenMode mode);
    void close();
    qint64 bytesAvailable() const;

protected:
    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

private:
    ssh::Channel &m_channel;
};

#endif // SSHIODEVICE_H
