#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QSharedPointer>

#define COMMLIB_VER "2.8.0"				// Version of the library

class QIODevice;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

    virtual bool open() = 0;

    bool waitForReadyRead(int msecs);
    bool waitForBytesWritten(int msecs);
    virtual QByteArray waitForInputAndRead(int timeoutMs);

public slots:
    virtual QByteArray read(qint64 maxLength);
    virtual QByteArray read(qint64 bytes, int timeoutMs);
    virtual qint64 read(char *data, qint64 maxSize, int timeoutMs);
    virtual qint64 read(char *data, qint64 maxSize);
    virtual QByteArray readAll();

    virtual qint64 write(QSharedPointer<QByteArray> data);
    virtual qint64 write(const QByteArray &data);
    virtual qint64 write(const char *data, qint64 maxSize);
    virtual qint64 write(const char *data);
    qint64 write(QString string);

public:
    bool sendReturn();
    virtual void close() = 0;
    virtual bool isConnected() = 0;
    virtual void reset();
    /*!
     * \brief ioDevice Is used by the Client function to perform IO actions
     * \return A reference to the current IO device
     */
    virtual QIODevice &ioDevice() = 0;
signals:
    /*!
     * \brief debug
     * Simply define it as a signal in your class,
     * there is nothing else to do.
     *
     * The second argument determines if the timestamp should be displayed or not
     */
    void debug(QString, bool);
    void debug(QString);
    void debugWarning(QString);
    void allRead(const QByteArray &array); //!< Emitted when readAll() has been called

public:
    int readUntil(QStringList strings, int timeoutMs, QString &buffer, Qt::CaseSensitivity cs = Qt::CaseSensitive);
    int readUntil(QStringList strings, int timeoutMs, Qt::CaseSensitivity cs = Qt::CaseSensitive);
    bool readUntil(QString string, int timeoutMs, QString &buffer, Qt::CaseSensitivity cs = Qt::CaseSensitive);
    bool readUntil(QString string, int timeoutMs, Qt::CaseSensitivity cs = Qt::CaseSensitive);

    /*!
     * \brief Reads a line and save it in the buffer.
     * \param buffer Line's content will be written into the buffer
     * \param timeoutMs Time in milliseconds to wait until the end of a line.
     */
    bool readUntilLine(QString &buffer, int timeoutMs);

    bool login(int timeoutMs);

    QString username() const;
    void setUsername(const QString &username);

    QString password() const;
    void setPassword(const QString &password);

    QString readyUsername() const;
    void setReadyUsername(const QString &readyUsername);

    QString readyPassword() const;
    void setReadyPassword(const QString &readyPassword);

    bool blocking() const;
    void setBlocking(bool blocking);

    int defaultTimeout() const;
    void setDefaultTimeout(int defaultTimeout);

    bool verbose() const;
    void setVerbose(bool verbose);

private:
    QString m_username;
    QString m_password;
    QString m_readyUsername;
    QString m_readyPassword;

    bool m_blocking; //!< Determines if a blocking behavior is required or not for some functionalities
    int m_defaultTimeout;
    bool m_verbose; //!< Will display extra debug messages if true
};

#endif // CLIENT_H
