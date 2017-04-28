#ifndef TRAY_H
#define TRAY_H

#include <QtWidgets>

class Tray
{
public:
    Tray();
    void showMessage();
    QSystemTrayIcon *trayIcon;
};

#endif // TRAY_H
