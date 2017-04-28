#include <QtWidgets>
#include "tray.h"

Tray::Tray()
{
    trayIcon = new QSystemTrayIcon(QIcon(":/tray.png"));
    trayIcon->setToolTip(QString("Visual Translator"));
    trayIcon->show();
}

void Tray::showMessage()
{
     trayIcon->showMessage(QString("Message"), QString("Test message"));
}
