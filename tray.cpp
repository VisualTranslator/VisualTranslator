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
    langFromMenu = new QMenu("Translate from", menu);
    langToMenu = new QMenu("Translate to", menu);
    menuLangFromGroup = new QActionGroup(this);
    menuLangToGroup = new QActionGroup(this);

    addLangMenuItem("from", "Autodetect", QVariant("auto"));
    addLangMenuItem("to", "Ukrainian", QVariant("ua"), QIcon(":/lang-icons/ua.png"));

    menu->addMenu(langFromMenu);
    menu->addMenu(langToMenu);
    menu->addSeparator();
    menu->addAction("Exit", qApp, SLOT(quit()));

    trayIcon->setContextMenu(menu);
}

void Tray::showMessage()
{
     trayIcon->showMessage(QString("Message"), QString("Test message"));
}

void Tray::chooseFromLang()
{
    QAction *action = qobject_cast<QAction*>(sender());
    qDebug()<<action->data().toString();
}

void Tray::chooseToLang()
{
    QAction *action = qobject_cast<QAction*>(sender());
    qDebug()<<action->data().toString();
}

void Tray::addLangMenuItem(QString type, QString title, QVariant data , QIcon icon)
{
    QAction *item = new QAction(title);
    item->setCheckable(true);
    item->setData(data);
    item->setIcon(icon);

    if (type == "from") {
       langFromMenu->addAction(item);
       QObject::connect(item, SIGNAL(triggered()), this, SLOT(chooseFromLang()));
       menuLangFromGroup->addAction(item);
    } else {
        langToMenu->addAction(item);
        QObject::connect(item, SIGNAL(triggered()), this, SLOT(chooseToLang()));
        menuLangToGroup->addAction(item);
    }
}
