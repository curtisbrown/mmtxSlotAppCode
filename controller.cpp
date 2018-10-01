#include "controller.h"

Controller::Controller(QStringList arguments, QString name, QObject *parent)
    : QObject(parent)
    , m_utilities(this)
    , m_acSettings(this, &m_utilities)
    , m_commsGui(&m_utilities)
{
    // Set Slot number and read arguments for initial configuration
    if (m_acSettings.readName(name) && m_acSettings.readArgs(arguments)) {
        // Connect to GUI
        m_commsGui.guiConnect(m_acSettings.guiIp(), (8000 + m_acSettings.slotNo()));
    } else {
        m_utilities.debugLogMessage("Required Arguments not set, exiting...");
        exit(EXIT_FAILURE);
    }
}

Settings *Controller::settings()
{
    return &m_acSettings;
}
