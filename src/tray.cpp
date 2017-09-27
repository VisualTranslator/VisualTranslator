#include "tray.h"

Tray::Tray(QWidget *parent) : QWidget(parent)
{
    trayIcon = new QSystemTrayIcon(QIcon(":/resources/tray.png"));
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

    addLangMenuItem("from", "Autodetect", QVariant("auto"), QIcon(":/resources/lang_icons/auto.png"));
    addLangMenuItem("from", "Arabic", QVariant("ar"), QIcon(":/resources/lang_icons/sa.png"));
    addLangMenuItem("from", "English", QVariant("en"), QIcon(":/resources/lang_icons/us.png"));
    addLangMenuItem("from", "French", QVariant("fr"), QIcon(":/resources/lang_icons/fr.png"));
    addLangMenuItem("from", "German", QVariant("de"), QIcon(":/resources/lang_icons/de.png"));
    addLangMenuItem("from", "Italian", QVariant("it"), QIcon(":/resources/lang_icons/it.png"));
    addLangMenuItem("from", "Japanese", QVariant("ja"), QIcon(":/resources/lang_icons/jp.png"));
    addLangMenuItem("from", "Korean", QVariant("ko"), QIcon(":/resources/lang_icons/kr.png"));
    addLangMenuItem("from", "Portuguese", QVariant("pt"), QIcon(":/resources/lang_icons/pt.png"));
    addLangMenuItem("from", "Russian", QVariant("ru"), QIcon(":/resources/lang_icons/ru.png"));
    addLangMenuItem("from", "Spanish", QVariant("es"), QIcon(":/resources/lang_icons/es.png"));
    addLangMenuItem("from", "Ukrainian", QVariant("uk"), QIcon(":/resources/lang_icons/ua.png"));

    addLangMenuItem("to", "Arabic", QVariant("ar"), QIcon(":/resources/lang_icons/sa.png"));
    addLangMenuItem("to", "English", QVariant("en"), QIcon(":/resources/lang_icons/us.png"));
    addLangMenuItem("to", "French", QVariant("fr"), QIcon(":/resources/lang_icons/fr.png"));
    addLangMenuItem("to", "German", QVariant("de"), QIcon(":/resources/lang_icons/de.png"));
    addLangMenuItem("to", "Italian", QVariant("it"), QIcon(":/resources/lang_icons/it.png"));
    addLangMenuItem("to", "Japanese", QVariant("ja"), QIcon(":/resources/lang_icons/jp.png"));
    addLangMenuItem("to", "Korean", QVariant("ko"), QIcon(":/resources/lang_icons/kr.png"));
    addLangMenuItem("to", "Portuguese", QVariant("pt"), QIcon(":/resources/lang_icons/pt.png"));
    addLangMenuItem("to", "Russian", QVariant("ru"), QIcon(":/resources/lang_icons/ru.png"));
    addLangMenuItem("to", "Spanish", QVariant("es"), QIcon(":/resources/lang_icons/es.png"));
    addLangMenuItem("to", "Ukrainian", QVariant("uk"), QIcon(":/resources/lang_icons/ua.png"));

    menu->addMenu(langFromMenu);
    menu->addMenu(langToMenu);
    menu->addSeparator();
    menu->addAction("Exit", qApp, SLOT(quit()));

    trayIcon->setContextMenu(menu);
}

void Tray::showMessage(const QString &message)
{
     trayIcon->showMessage(QString("VisualTranslator"), message);
}

void Tray::chooseFromLang()
{
    QAction *action = qobject_cast<QAction*>(sender());
    QSettings *tmpSettings = App::theApp()->settings();

    tmpSettings->beginGroup("/Settings");
        tmpSettings->beginGroup("/Languages");
            tmpSettings->setValue("/from", action->data().toString());
        tmpSettings->endGroup();
    tmpSettings->endGroup();
}

void Tray::chooseToLang()
{
    QAction *action = qobject_cast<QAction*>(sender());
    QSettings *tmpSettings = App::theApp()->settings();
    tmpSettings->beginGroup("/Settings");
        tmpSettings->beginGroup("/Languages");
            tmpSettings->setValue("/to", action->data().toString());
        tmpSettings->endGroup();
    tmpSettings->endGroup();
}

void Tray::addLangMenuItem(QString type, QString title, QVariant data , QIcon icon)
{
    QAction *item = new QAction(title);
    item->setCheckable(true);
    item->setData(data);
    item->setIcon(icon);

    QSettings *tmpSettings = App::theApp()->settings();
    // uncomment line below if you want to clear previous stored settings (needed only when settings structure has changed)
    //tmpSettings->clear();
    tmpSettings->beginGroup("/Settings");
        tmpSettings->beginGroup("/Languages");
            QString settingsLangFrom = tmpSettings->value("/from", "auto").toString();
            QString settingsLangTo = tmpSettings->value("/to", "en").toString();
        tmpSettings->endGroup();
    tmpSettings->endGroup();

    if (type == "from") {
       langFromMenu->addAction(item);
       if (data.toString() == settingsLangFrom) item->setChecked(true);
       QObject::connect(item, SIGNAL(triggered()), this, SLOT(chooseFromLang()));
       menuLangFromGroup->addAction(item);
    } else {
        langToMenu->addAction(item);
        if (data.toString() == settingsLangTo) item->setChecked(true);
        QObject::connect(item, SIGNAL(triggered()), this, SLOT(chooseToLang()));
        menuLangToGroup->addAction(item);
    }
}
