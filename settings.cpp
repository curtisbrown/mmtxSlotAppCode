#include "settings.h"

#include <QDebug>
#include <QDataStream>
#include <iostream>
#include <cstdlib>
#include "definitions.h"

Settings::Settings(QObject *parent, Utilities *utilities)
    : QObject(parent)
    , m_customer(Enums::CUSTOMER_UNSET)
    , m_platform(Enums::PLATFORM_UNSET)
    , m_modelToTest(Enums::UUT_NONE)
    , m_utilities(utilities)
    , m_ipNetwork("")
    , m_guiRevision("")
    , m_testerName("")
    , m_guiIp("")
    , m_slotNo(0)
{
}

bool Settings::readArgs(QStringList &arguments)
{
    bool argsStatus = false;
    bool platformSet = false;
    bool guiIpSet = false;
    int argsCount = 0;

    if (arguments.isEmpty()) {
        m_utilities->debugLogMessage("ERROR: NO args passed at runtime, exiting...");
        exit(EXIT_FAILURE);
    } else {
        argsCount = arguments.count() / 2;     // Count is "/ 2" because there is a option followed by value
    }

    for (int i = 0; i < argsCount; i++) {
        QString option = arguments.first();
        QString argument;

        if (option.startsWith("-h") || option.startsWith("--help")) {
            std::cout << help().toStdString() << std::endl;
            exit(EXIT_SUCCESS);
        } else if (option.startsWith("-p") || option.startsWith("--platform")) {
            argument = removeOptionTakeArgument(option, arguments);
            platformSet = readPlatformArgument(argument);
        } else if (option.startsWith("-c") || option.startsWith("--customer")) {
            argument = removeOptionTakeArgument(option, arguments);
        } else if (option.startsWith("-g") || option.startsWith("--gui")) {
            argument = removeOptionTakeArgument(option, arguments);
            guiIpSet = readGuiIp(argument);
        } else if (option.startsWith("-n") || option.startsWith("--name")) {
            argument = removeOptionTakeArgument(option, arguments);
            readName(argument);
        } else if (option.startsWith("-v") || option.startsWith("--version")) {
            std::cout << "AppCode version: " << REV << std::endl;
            exit(EXIT_SUCCESS);
        } else {
            m_utilities->debugLogMessage(QString("Unknown command: %1").arg(option));
        }
    }

#ifdef QT_DEBUG
    if (!platformSet)
        setPlatform(Enums::PLATFORM_CMTX3);

    if (!guiIpSet)
        setGuiIp("192.168.9.10");

    argsStatus = true;
#else
    if (platformSet && guiIpSet) {
        m_utilities->debugLogMessage("Required arguments set to proceed");
        argsStatus = true;
    }
#endif

    return argsStatus;
}

Enums::Customer Settings::customer() const
{
    return m_customer;
}

void Settings::setCustomer(const Enums::Customer &customer)
{
    if (customer != m_customer) {
        m_utilities->debugLogMessage(QString("Customer set to %1").arg(customerEnumToString(customer)));
        m_customer = customer;
        setIpNetwork();
        setIpRegex();
        emit customerChanged();
    }
}

QString Settings::customerEnumToString(const Enums::Customer &customer)
{
    switch (customer) {
    case Enums::CUSTOMER_VIRGIN:
        return "Virgin";
        break;
    case Enums::CUSTOMER_BT:
        return "BT";
        break;
    case Enums::CUSTOMER_MAGYAR_TELEKOM:
        return "Magyar Telekom";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}

Enums::UutModel Settings::modelToTest() const
{
    return m_modelToTest;
}

void Settings::setModelToTest(const Enums::UutModel &modelToTest)
{
    if (modelToTest != m_modelToTest) {
        m_utilities->debugLogMessage(QString("Setting model to %1").arg(modelToTest));
        m_modelToTest = modelToTest;
        emit modelTestedChanged(modelToTest);
    }
}

QString Settings::removeOptionTakeArgument(QString option, QStringList &arguments)
{
    QString argument;
    int index = arguments.indexOf(option);

    if (index + 1 < arguments.size())
        argument = arguments.takeAt(index + 1);

    arguments.removeAt(index);

    return argument;
}

bool Settings::readPlatformArgument(QString argument)
{
    bool status = false;

    QMap<QString, Enums::Platform> platformMap;
    platformMap["cmtx3"] = Enums::PLATFORM_CMTX3;
    platformMap["cmtx5"] = Enums::PLATFORM_CMTX5;

    argument = argument.toLower();
    if (platformMap.keys().contains(argument)) {
        setPlatform(platformMap[argument]);
        status = true;
    } else {
        qWarning() << "Wrong platform argument:" << argument;
        exit(EXIT_FAILURE);
    }

    return status;
}

bool Settings::readCustomerArgument(QString argument)
{
    bool status = false;
    Enums::Customer customerTemp = Enums::CUSTOMER_UNSET;

    argument = argument.toLower();
    if (argument == "virgin") {
        customerTemp = Enums::CUSTOMER_VIRGIN;
    } else if (argument == "bt") {
        customerTemp = Enums::CUSTOMER_BT;
    } else if (argument == "mt") {
        customerTemp = Enums::CUSTOMER_MAGYAR_TELEKOM;
    } else {
        customerTemp = Enums::CUSTOMER_UNSET;
    }

    if (customerTemp == Enums::CUSTOMER_UNSET) {
        qWarning() << "Wrong customer argument:" << argument;
        exit(EXIT_FAILURE);
    } else {
        setCustomer(customerTemp);
        status = true;
    }

    return status;
}

int Settings::slotNo() const
{
    return m_slotNo;
}

void Settings::setSlotNo(int slotNo)
{
    m_utilities->debugLogMessage(QString("Setting Slot Number to %1").arg(slotNo));
    m_slotNo = slotNo;
}

QString Settings::guiRevision() const
{
    return m_guiRevision;
}

void Settings::setGuiRevision(const QString &guiRevision)
{
    if (guiRevision != m_guiRevision) {
        m_utilities->debugLogMessage(QString("Setting GUI Rev to %1").arg(guiRevision));
        m_guiRevision = guiRevision;
    }
}

QString Settings::ipRegex() const
{
    return m_ipRegex;
}

void Settings::setIpRegex()
{
    switch (m_customer) {
    case Enums::CUSTOMER_VIRGIN:
    default:
        m_ipRegex = "\\b172.168.1.([2-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-4])\\b";
        break;
    }
    emit ipDetailsChanged();
}

QString Settings::ipNetwork() const
{
    return m_ipNetwork;
}

void Settings::setIpNetwork()
{
    switch (m_customer) {
    case Enums::CUSTOMER_VIRGIN:
    default:
        m_ipNetwork = "172.168.1.0";
        break;
    }
    emit ipDetailsChanged();
}

Enums::Platform Settings::platform() const
{
    return m_platform;
}

void Settings::setPlatform(const Enums::Platform &platform)
{
    if (platform != m_platform) {
        switch (platform) {
        case Enums::PLATFORM_CMTX3:
            m_utilities->debugLogMessage("Setting platform to CMTx3");
            m_platform = Enums::PLATFORM_CMTX3;
            break;
        case Enums::PLATFORM_CMTX5:
            m_utilities->debugLogMessage("Setting platform to CMTx5");
            m_platform = Enums::PLATFORM_CMTX5;
            break;
        default:
            m_utilities->debugLogMessage("Unknown platform type, setting to UNKNOWN");
            m_platform = Enums::PLATFORM_UNSET;
            break;
        }
        emit platformChanged(platform);
    }
}

QString Settings::guiIp() const
{
    return m_guiIp;
}

void Settings::setGuiIp(const QString &guiIp)
{
    if (guiIp != m_guiIp) {
        m_utilities->debugLogMessage(QString("set GUI IP to %1").arg(guiIp));
        m_guiIp = guiIp;
        emit guiIpChanged(m_guiIp);
    }
}

bool Settings::readGuiIp(QString argument)
{
    bool result = true;
    if (!StringProcessing::extractIp(argument).isEmpty())
        setGuiIp(StringProcessing::extractIp(argument));
    else
        result = false;
    return result;
}

bool Settings::readName(QString argument)
{
    setTesterName(argument);
    QStringList list = argument.split("SLOT");
    if (!list.isEmpty()) {
        setSlotNo(QString(list.at(1)).toInt());
        return true;
    } else {
        return false;
    }
}

QString Settings::testerName() const
{
    return m_testerName;
}

void Settings::setTesterName(const QString &name)
{
    if (name != m_testerName) {
        m_utilities->debugLogMessage(QString("set Tester name to %1").arg(name));
        m_testerName = name;
        emit nameChanged(m_testerName);
    }
}

/*!
 * \brief Settings::help
 * Display help on available commands
 */
QString Settings::help() const
{
    QStringList output;
    output << "option.startsWith(S"
           << "-h, --help" << "\tdisplay help dialog"
           << "-p, --platform NAME" << "\tset platform name"
           << "-c, --customer NAME" << "\tset customer name"
           << "-g, --gui" << "\tset GUI IP address"
           << "-n, --name NAME" << "\tset tester name"
           << "-v, --version" << "\tdisplay version of the AppCode and quits";

    return output.join('\n');
}

QDataStream &operator<<(QDataStream &in, const Settings &settings)
{
    in << static_cast<qint32>(settings.customer());
    in << static_cast<qint32>(settings.platform());
    in << static_cast<qint32>(settings.modelToTest());
    in << settings.guiRevision();
    return in;
}

QDataStream &operator>>(QDataStream &out, Settings &settings)
{
    qint32 tmp;
    out >> tmp;
    settings.setCustomer(static_cast<Enums::Customer>(tmp));
    out >> tmp;
    settings.setPlatform(static_cast<Enums::Platform>(tmp));
    out >> tmp;
    settings.setModelToTest(static_cast<Enums::UutModel>(tmp));
    out >> tmp;

    QString tmpString;
    out >> tmpString;
    settings.setGuiRevision(tmpString);
    return out;
}
