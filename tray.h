#ifndef TRAY_H
#define TRAY_H

#include <QtWidgets>

class Tray : public QWidget
{
    Q_OBJECT
private:
    QActionGroup *menuLangToGroup;
    QActionGroup *menuLangFromGroup;
    virtual void generateMenu();
    void addLangMenuItem(QString type, QString title, QVariant data , QIcon icon = QIcon());
public:
    explicit Tray(QWidget *parent = 0);
    void showMessage();
    QSystemTrayIcon *trayIcon;
    QMenu *menu;
    QMenu *langToMenu;
    QMenu *langFromMenu;
signals:

public slots:
    void chooseFromLang();
    void chooseToLang();
};

#endif // TRAY_H
