#ifndef TRAY_H
#define TRAY_H

#include <QtWidgets>

class Tray : public QWidget
{
    Q_OBJECT
private:
    virtual void generateMenu();
public:
    explicit Tray(QWidget *parent = 0);
    void showMessage();
    QSystemTrayIcon *trayIcon;
    QMenu *menu;
signals:

public slots:
};

#endif // TRAY_H
