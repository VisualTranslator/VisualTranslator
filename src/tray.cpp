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

    QDir tessdataFolder(qApp->applicationDirPath() + "/tessdata");
    QStringList tessFiles = tessdataFolder.entryList();

    addLangMenuItem("from", "Arabic", QVariant("ar"), QIcon(":/resources/lang_icons/sa.png"), tessFiles.contains("ara.traineddata"));
    addLangMenuItem("from", "English", QVariant("en"), QIcon(":/resources/lang_icons/us.png"), tessFiles.contains("eng.traineddata"));
    addLangMenuItem("from", "French", QVariant("fr"), QIcon(":/resources/lang_icons/fr.png"), tessFiles.contains("fra.traineddata"));
    addLangMenuItem("from", "German", QVariant("de"), QIcon(":/resources/lang_icons/de.png"), tessFiles.contains("fra.traineddata"));
    addLangMenuItem("from", "Italian", QVariant("it"), QIcon(":/resources/lang_icons/it.png"), tessFiles.contains("ita.traineddata"));
    addLangMenuItem("from", "Japanese", QVariant("ja"), QIcon(":/resources/lang_icons/jp.png"), tessFiles.contains(("jpn.traineddata")));
    addLangMenuItem("from", "Korean", QVariant("ko"), QIcon(":/resources/lang_icons/kr.png"), tessFiles.contains(("kor.traineddata")));
    addLangMenuItem("from", "Portuguese", QVariant("pt"), QIcon(":/resources/lang_icons/pt.png"), tessFiles.contains(("por.traineddata")));
    addLangMenuItem("from", "Russian", QVariant("ru"), QIcon(":/resources/lang_icons/ru.png"), tessFiles.contains("rus.traineddata"));
    addLangMenuItem("from", "Spanish", QVariant("es"), QIcon(":/resources/lang_icons/es.png"), tessFiles.contains("spa.traineddata"));
    addLangMenuItem("from", "Ukrainian", QVariant("uk"), QIcon(":/resources/lang_icons/ua.png"), tessFiles.contains("ukr.traineddata"));

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
    langFromMenu->addSeparator();
    QAction *downloadLangs = new QAction("Load more languages");
    langFromMenu->addAction(downloadLangs);

    menu->addMenu(langToMenu);
    menu->addSeparator();
    menu->addAction("Exit", qApp, SLOT(quit()));

    trayIcon->setContextMenu(menu);
}

void Tray::showMessage(const QString &message)
{
    // TODO fix issue with the visible message limit
    trayIcon->showMessage(QString("VisualTranslator"), message);
}

void Tray::chooseFromLang()
{
    QAction *action = qobject_cast<QAction*>(sender());
    App::theApp()->settings()->setValue("/Settings/Languages/from", action->data().toString());
}

void Tray::chooseToLang()
{
    QAction *action = qobject_cast<QAction*>(sender());
    App::theApp()->settings()->setValue("/Settings/Languages/to", action->data().toString());
}

void Tray::addLangMenuItem(QString type, QString title, QVariant data , QIcon icon, bool langDownloaded)
{
    QString settingsLangFrom = App::theApp()->settings()->value("/Settings/Languages/from", "en").toString();
    QString settingsLangTo = App::theApp()->settings()->value("/Settings/Languages/to", "en").toString();

    QAction *item = new QAction(title);
    item->setCheckable(true);
    item->setData(data);
    item->setIcon(icon);

    if (langDownloaded && type == "from") {
       langFromMenu->addAction(item);
       if (data.toString() == settingsLangFrom) item->setChecked(true);
       QObject::connect(item, SIGNAL(triggered()), this, SLOT(chooseFromLang()));
       menuLangFromGroup->addAction(item);
    }

    if (type == "to") {
        langToMenu->addAction(item);
        if (data.toString() == settingsLangTo) item->setChecked(true);
        QObject::connect(item, SIGNAL(triggered()), this, SLOT(chooseToLang()));
        menuLangToGroup->addAction(item);
    }
}
