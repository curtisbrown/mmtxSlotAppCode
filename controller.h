#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "utilities.h"
#include "settings.h"
#include "communicationgui.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QStringList arguments = QStringList(), QString name = QString(), QObject *parent = nullptr);

    Settings *settings();

signals:

public slots:

private:
    Utilities m_utilities;
    Settings m_acSettings;
    CommunicationGui m_commsGui;
};

#endif // CONTROLLER_H
