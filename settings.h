#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QTranslator>

#include "utilities.h"
#include "enumerations.h"
#include "stringprocessing.h"

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Enums::Customer customer READ customer WRITE setCustomer NOTIFY customerChanged)
    Q_PROPERTY(Enums::Platform platform READ platform WRITE setPlatform NOTIFY platformChanged)
    Q_PROPERTY(Enums::UutModel modelToTest READ modelToTest WRITE setModelToTest NOTIFY modelTestedChanged)

public:
    explicit Settings(QObject *parent = 0, Utilities *utilities = nullptr);

    bool readArgs(QStringList &arguments);
    QString help() const;

    // Accessors
    Enums::Customer customer() const;
    void setCustomer(const Enums::Customer &customer);
    QString customerEnumToString(const Enums::Customer &customer);

    Enums::Platform platform() const;
    void setPlatform(const Enums::Platform &platform);

    Enums::UutModel modelToTest() const;
    void setModelToTest(const Enums::UutModel &modelToTest);

    QString ipNetwork() const;
    void setIpNetwork();

    QString ipRegex() const;
    void setIpRegex();

    QString guiRevision() const;
    void setGuiRevision(const QString &guiRevision);

    QString guiIp() const;
    void setGuiIp(const QString &guiIp);
    bool readGuiIp(QString argument);

    QString testerName() const;
    void setTesterName(const QString &testerName);
    void readName(QString argument);

signals:
    void customerChanged();
    void platformChanged(Enums::Platform);
    void modelTestedChanged(const Enums::UutModel &model);
    void ipDetailsChanged();
    void guiIpChanged(QString);
    void nameChanged(QString);

protected:
    QString removeOptionTakeArgument(QString option, QStringList &arguments);

private:
    bool readPlatformArgument(QString argument);
    bool readCustomerArgument(QString argument);
    bool readModelArgument(QString argument);

    Enums::Customer m_customer;                  // Uut brand selected
    Enums::Platform m_platform;                 // Current platform
    Enums::UutModel m_modelToTest;              // Main model tested
    Utilities *m_utilities;
    QString m_ipNetwork;
    QString m_ipRegex;
    QString m_guiRevision;
    QString m_testerName;
    QString m_guiIp;

};

QDataStream &operator<<(QDataStream &in, const Settings &settings);
QDataStream &operator>>(QDataStream &out, Settings &settings);

#endif // SETTINGS_H
