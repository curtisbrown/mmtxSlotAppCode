#include "utilities.h"

#include <QTextStream>
#include <QDebug>
#include <QDateTime>

Utilities::Utilities(QObject *parent) :
    QObject(parent),
    m_debugLog("debugLog.txt")
{
    initialiseLogFile();
}

void Utilities::initialiseLogFile()
{
    if (m_debugLog.exists()) {
        // Check if previous exists also
        QFile previousDebugLog("debugLogOld.txt");
        if (previousDebugLog.exists()) {
            previousDebugLog.remove();
        }
        if (m_debugLog.copy("debugLogOld.txt")) {
            m_debugLog.remove();
        }
    }
}

void Utilities::debugLogMessage(QString string)
{
    qDebug() << string;
    if (m_debugLog.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        QTextStream out(&m_debugLog);
        out << endl
            << "[ "
            << QDateTime::currentDateTime().toString(Qt::ISODate)
            << " ] "
            << string;
        m_debugLog.close();
    } else {
        qWarning() << Q_FUNC_INFO << ", could not open the file " << m_debugLog.fileName();
    }
}

bool Utilities::checkFileExists(QString filename)
{
    QFile fileToCheck(filename);

    return fileToCheck.exists();
}

bool Utilities::deleteFile(QString filename)
{
    bool status = false;

    if (checkFileExists(filename)) {
        QFile file(filename);
        if (file.remove()) {
            status = true;
        }
    } else {
        return true;
    }

    return status;
}
