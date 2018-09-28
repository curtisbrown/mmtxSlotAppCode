#include "controller.h"

Controller::Controller(QStringList arguments, QObject *parent)
    : QObject(parent)
    , m_utilities(this)
    , m_acSettings(this, &m_utilities)
    , m_commsGui(&m_utilities)
{
    // Read arguments for initial configuration
    m_acSettings.readArgs(arguments);

    // Connect to GUI
    m_commsGui.guiConnect("192.168.9.10", 8001);
}

Settings *Controller::settings()
{
    return &m_acSettings;
}
