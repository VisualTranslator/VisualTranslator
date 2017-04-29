#include "tray.h"

Tray::Tray(QWidget *parent) : QWidget(parent)
{
    trayIcon = new QSystemTrayIcon(QIcon(":/tray.png"));
    trayIcon->setToolTip(QString("Visual Translator"));
    trayIcon->show();
    generateMenu();
}

void Tray::generateMenu()
{
    menu = new QMenu(this);
    menu->addAction("Exit", qApp, SLOT(quit()));
    trayIcon->setContextMenu(menu);
}

void Tray::showMessage()
{
     trayIcon->showMessage(QString("Message"), QString("Test message"));
}
