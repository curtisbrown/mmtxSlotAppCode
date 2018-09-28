#include "communicationgui.h"

CommunicationGui::CommunicationGui(Utilities *utilities)
    : m_utilities(utilities)
{
}

bool CommunicationGui::guiConnect(QString Ip, qint16 portNumber)
{
    m_utilities->debugLogMessage(Q_FUNC_INFO);

    m_tcpGuiConnection.setHostname(Ip);
    m_tcpGuiConnection.setPort(portNumber);

    if (m_tcpGuiConnection.openBlocking(60000)) {
        m_utilities->debugLogMessage("Connected");
        connect(&m_tcpGuiConnection.ioDevice(), &QIODevice::readyRead, this, &CommunicationGui::readAllDataFromGui);
        m_tcpGuiConnection.write("Hello server, this is the client");
        return true;
    } else {
        m_utilities->debugLogMessage("ERROR: Unable to connect");
        return false;
    }
}

void CommunicationGui::readAllDataFromGui()
{
    m_utilities->debugLogMessage(Q_FUNC_INFO);

    QByteArray ba = m_tcpGuiConnection.readAll();
    this->m_utilities->debugLogMessage(ba);
}

