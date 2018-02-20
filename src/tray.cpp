#include "tray.h"

Tray::Tray(QWidget *parent) : QWidget(parent)
{
    trayIcon = new QSystemTrayIcon(QIcon(":/resources/tray.png"));
    trayIcon->setToolTip(QString("Visual Translator"));
    settingsForm = new SettingsForm(parent);
    downloadLanguagesForm = new DownloadLanguageForm(parent);
    trayIcon->show();
    generateMenu();
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showMenu()));
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

    foreach (Lang language, Language::languages) {
        addLangMenuItem("from", language.name, QVariant(Language::getShortName(language.name)), QIcon(":/resources/lang_icons/"+ language.shortName +".png"), Language::isDownloaded(language.name));
        addLangMenuItem("to", language.name, QVariant(Language::getShortName(language.name)), QIcon(":/resources/lang_icons/"+ language.shortName +".png"));
    }

    menu->addMenu(langFromMenu);
    langFromMenu->addSeparator();
    langFromMenu->addAction("Download more languages", downloadLanguagesForm, SLOT(showForm()));

    menu->addMenu(langToMenu);
    menu->addSeparator();
    menu->addAction("Settings...", settingsForm, SLOT(showForm()));

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

void Tray::showMenu()
{
    trayIcon->contextMenu()->exec(QCursor::pos());
}
