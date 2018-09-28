#ifndef SNMPCLIENT_H
#define SNMPCLIENT_H

#include <QObject>
#include <QStringList>

#ifdef SNMP_BUILD
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#endif

class SnmpClient : public QObject
{
    Q_OBJECT
public:
    explicit SnmpClient(QObject *parent = 0);
    ~SnmpClient();
    enum DataType {
        DATA_TYPE_INTEGER,
        DATA_TYPE_GAUGE,
        DATA_TYPE_STRING,
        DATA_TYPE_OCTET_STRING
    };
#ifdef SNMP_BUILD
    struct OidStr {
        OidStr();
        ~OidStr();
        QString string;
        oid values[MAX_OID_LEN];
        size_t length;
        netsnmp_pdu *response;
        bool setOid(QString oid);
        bool hasNext();
        void setNextOid();
    };
#endif

    static void open();
    static void close();

signals:
    void debug(const QString &);
    void debugWarning(QString);
    void getAnswered(const QString &);

public slots:
    QString get(const QString &hostname, const QString &oid);
    void set(const QString &hostname, const QString &oid, const QString& value, DataType type);
    QStringList walk(const QString &hostname, const QString &oid);

private:
    char getType(DataType dataType);
#ifdef SNMP_BUILD
    void openSession(snmp_session &session, const char *community, QString hostname);
    bool initialiseOid(OidStr &oid, QString oidString);
    bool sendSetOid(OidStr& oid, QString value, DataType type);
    bool sendGetOid(OidStr& oid);
    bool sendWalkOid(OidStr& oid);
    bool sendOid(OidStr& oid, netsnmp_pdu *pdu);
    QString readAnswer(netsnmp_pdu *response);
#endif
    char *m_errstr;
    void *m_sessp;  /* <-- an opaque pointer, not a struct pointer */
    static int m_opened; //!< Number of Snmp object currently used
};

#endif // SNMPCLIENT_H
