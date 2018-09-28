#ifndef COMMUNICATIONGUI_H
#define COMMUNICATIONGUI_H

#include <QObject>

#include "tcpclient.h"
#include "utilities.h"

class CommunicationGui : public TcpClient
{
    Q_OBJECT
public:
    explicit CommunicationGui(Utilities *utilities = nullptr);

signals:

public slots:
    bool guiConnect(QString Ip, qint16 portNumber);
    void readAllDataFromGui();

private:
    Utilities *m_utilities;
    TcpClient m_tcpGuiConnection;
};

#endif // COMMUNICATIONGUI_H
