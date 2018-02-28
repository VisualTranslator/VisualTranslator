#include "tray.h"

Tray::Tray(QWidget *parent) : QWidget(parent)
{
    // Setup the tray icon
    trayIcon = new QSystemTrayIcon(QIcon(":/resources/tray.png"));
    trayIcon->setToolTip(QString("Visual Translator"));
    trayIcon->show();

    // Setup all forms
    settingsForm = new SettingsForm(parent);
    connect(settingsForm, SIGNAL(shortcutChanged(QString)), this, SLOT(shortcutChange(QString)));

    translationResultForm = new TranslationResultForm(parent);
    translationResultForm->setWindowFlag(Qt::Popup);

    // Create a menus
    menu = new QMenu(this);
    langFromMenu = new QMenu("Translate from", menu);
    langToMenu = new QMenu("Translate to", menu);

    QString shortcut = App::theApp()->settings()->value("/Settings/Shortcut/Recognition", "Ctrl+Alt+Q").toString();
    startTranslation = new QAction(tr("&Start translation"), this);
    startTranslation->setShortcut(QKeySequence(shortcut));
    connect(startTranslation, SIGNAL(triggered(bool)), this, SIGNAL(startRecognitionPressed()));

    menu->addAction(startTranslation);

    // used to simulate toggle effect when choose some language
    menuLangFromGroup = new QActionGroup(this);
    menuLangToGroup = new QActionGroup(this);

    menu->addMenu(langFromMenu);
    menu->addMenu(langToMenu);

    menu->addSeparator();
    menu->addAction("Settings...", settingsForm, SLOT(showForm()));

    menu->addSeparator();
    menu->addAction("Exit", qApp, SLOT(quit()));

    // Fill a menu with all available languages
    foreach (Lang language, Language::languages) {
        addLanguageToMenu(language.name);
    }

    trayIcon->setContextMenu(menu);

    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showMenu()));
}

void Tray::shortcutChange(QString shortcut)
{
    startTranslation->setShortcut(QKeySequence(shortcut));
    emit shortcutChanged(shortcut);
}

void Tray::showMessage(const QString &original, const QString &translation)
{
    translationResultForm->ui->originalTextEdit->setText(original);
    translationResultForm->ui->translatedTextEdit->setText(translation);

    // search for the correct position for the translationResultForm
    int screenWidth = QApplication::desktop()->screenGeometry().width();
    int screenHeight = QApplication::desktop()->screenGeometry().height();
    QRect trayIconGeometry = trayIcon->geometry();
    QPoint formPosition = QPoint(trayIconGeometry.x(), trayIconGeometry.y());

    // TODO check with non-default dock position (left, right, top)
    if (formPosition.x() + translationResultForm->width() > screenWidth - 100) {
        formPosition.setX(screenWidth - translationResultForm->width());
    }

    if (formPosition.y() + translationResultForm->height() > screenHeight - 100) {
        formPosition.setY(screenHeight - translationResultForm->height() - trayIconGeometry.height());
    }

    translationResultForm->move(formPosition);
    translationResultForm->show();
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

void Tray::addLanguageToMenu(QString name)
{
    // receive saved settings
    QString settingsLangFrom = App::theApp()->settings()->value("/Settings/Languages/from", "English").toString();
    QString settingsLangTo = App::theApp()->settings()->value("/Settings/Languages/to", "English").toString();

    // add item to the `Translate from` menu
    QAction *actionFrom = new QAction(Language::getOriginalName(name));
    actionFrom->setCheckable(true);
    actionFrom->setData(QVariant(name));
    actionFrom->setIcon(QIcon(Language::getIconPath(name)));
    actionFrom->setChecked(name == settingsLangFrom);

    langFromMenu->addAction(actionFrom);
    menuLangFromGroup->addAction(actionFrom);
    QObject::connect(actionFrom, SIGNAL(triggered()), this, SLOT(chooseFromLang()));

    // add item to the `Translate to` menu
    QAction *actionTo = new QAction(Language::getOriginalName(name));
    actionTo->setCheckable(true);
    actionTo->setData(QVariant(name));
    actionTo->setIcon(QIcon(Language::getIconPath(name)));
    actionTo->setChecked(name == settingsLangTo);

    langToMenu->addAction(actionTo);
    menuLangToGroup->addAction(actionTo);
    QObject::connect(actionTo, SIGNAL(triggered()), this, SLOT(chooseToLang()));
}

void Tray::showMenu()
{
    trayIcon->contextMenu()->exec(QCursor::pos());
}
