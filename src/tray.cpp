#include "tray.h"

Tray::Tray()
{
    // Setup the tray icon
    trayIcon = new QSystemTrayIcon(QIcon(":/resources/logo_256_256.png"));
    trayIcon->setToolTip(QString("Visual Translator"));
    trayIcon->show();

    // Setup all forms
    settingsForm = new SettingsForm();
    connect(settingsForm, SIGNAL(shortcutChanged(QString)), this, SLOT(shortcutChange(QString)));

    translationResultForm = new TranslationResultForm();
    translationResultForm->setWindowFlag(Qt::Popup);

    // Create a menu
    menu = new QMenu();
    langFromMenu = new QMenu("Translate from", menu);
    langToMenu = new QMenu("Translate to", menu);

    startTranslation = new QAction(tr("&Start translation"), this);
    QString shortcut = App::theApp()->settings()->value("/Settings/Shortcut/Recognition", "Ctrl+Alt+Q").toString();
    startTranslation->setShortcut(QKeySequence(shortcut));
    connect(startTranslation, SIGNAL(triggered(bool)), this, SIGNAL(startRecognitionPressed()));
    menu->addAction(startTranslation);

    // used to simulate toggle effect when choose some language
    menuLangFromGroup = new QActionGroup(this);
    menuLangToGroup = new QActionGroup(this);

    menu->addMenu(langFromMenu);
    menu->addMenu(langToMenu);

    menu->addSeparator();
    menu->addAction("Settings...", this, SLOT(on_SettingsButton_clicked()));

    menu->addSeparator();
    menu->addAction("Exit", qApp, SLOT(quit()));

    // Fill a combo boxes with with all available languages
    foreach (Lang language, Language::languages) {
        // receive saved settings
        QString settingsLangFrom = App::theApp()->settings()->value("/Settings/Languages/from", "English").toString();
        QString settingsLangTo = App::theApp()->settings()->value("/Settings/Languages/to", "English").toString();

        // add item to the `Translate from` menu
        QAction *actionFrom = new QAction(Language::getOriginalName(language.name));
        actionFrom->setCheckable(true);
        actionFrom->setData(QVariant(language.name));
        actionFrom->setIcon(QIcon(Language::getIconPath(language.name)));
        actionFrom->setChecked(language.name == settingsLangFrom);

        langFromMenu->addAction(actionFrom);
        menuLangFromGroup->addAction(actionFrom);
        QObject::connect(actionFrom, SIGNAL(triggered()), this, SLOT(chooseLanguageFrom()));

        // do not add Auto item to `Translate to` menu
        if (language.name == "Auto") continue;

        // add item to the `Translate to` menu
        QAction *actionTo = new QAction(Language::getOriginalName(language.name));
        actionTo->setCheckable(true);
        actionTo->setData(QVariant(language.name));
        actionTo->setIcon(QIcon(Language::getIconPath(language.name)));
        actionTo->setChecked(language.name == settingsLangTo);

        langToMenu->addAction(actionTo);
        menuLangToGroup->addAction(actionTo);
        QObject::connect(actionTo, SIGNAL(triggered()), this, SLOT(chooseLanguageTo()));
    }

    trayIcon->setContextMenu(menu);
}

void Tray::on_SettingsButton_clicked()
{
    settingsForm->show();
}

void Tray::chooseLanguageFrom()
{
    QAction *action = qobject_cast<QAction*>(sender());
    App::theApp()->settings()->setValue("/Settings/Languages/from", action->data().toString());
}

void Tray::chooseLanguageTo()
{
    QAction *action = qobject_cast<QAction*>(sender());
    App::theApp()->settings()->setValue("/Settings/Languages/to", action->data().toString());
}

void Tray::shortcutChange(QString shortcut)
{
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

    if (formPosition.x() + translationResultForm->width() > screenWidth - 100) {
        formPosition.setX(screenWidth - translationResultForm->width());
    }

    if (formPosition.y() + translationResultForm->height() > screenHeight - 100) {
        formPosition.setY(screenHeight - translationResultForm->height() - trayIconGeometry.height());
    }

    translationResultForm->move(formPosition);
    translationResultForm->show();
}

void Tray::showError(QString message)
{
    trayIcon->showMessage("VisualTranslator Error", message);
}
