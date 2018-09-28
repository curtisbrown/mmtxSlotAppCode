#include <QCoreApplication>
#include <QStandardPaths>

#include "controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString name = "";

#ifndef QT_DEBUG
    QFile testerId(QString("%1/testerID.txt").arg(QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory)));
    if (testerId.open(QIODevice::ReadOnly)) {
        name = QLatin1String(testerId.readAll());
        name.remove('\n');
        testerId.close();
    }
#else
    name = "999Tester1";
#endif

    QStringList arguments;
    for (int i = 1; i < argc; i++)
        arguments << argv[i];

    Controller controller(arguments);

    return a.exec();
}
