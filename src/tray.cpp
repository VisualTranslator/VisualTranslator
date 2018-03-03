#include "tray.h"

Tray::Tray(QWidget *parent) : QWidget(parent)
{
    // Setup all forms
    settingsForm = new SettingsForm(parent);
    connect(settingsForm, SIGNAL(shortcutChanged(QString)), this, SLOT(shortcutChange(QString)));

    translationResultForm = new TranslationResultForm(parent);
    translationResultForm->setWindowFlag(Qt::Popup);

    // create button to start recognition process
    QString shortcut = App::theApp()->settings()->value("/Settings/Shortcut/Recognition", "Ctrl+Alt+Q").toString();
    startTranslation = new QAction(tr("&Start translation"), this);
    startTranslation->setShortcut(QKeySequence(shortcut));
    menu->addAction(startTranslation);
    connect(startTranslation, SIGNAL(triggered(bool)), this, SIGNAL(startRecognitionPressed()));

    // Create custom QComboBox'es for language selection
    comboBoxFrom = new LanguageQComboBox("From", this);
    comboBoxTo = new LanguageQComboBox("To", this);
    connect(comboBoxFrom, SIGNAL(activated(QString)), this, SLOT(chooseFromLang(QString)));
    connect(comboBoxTo, SIGNAL(activated(QString)), this, SLOT(chooseToLang(QString)));

    // Fill a combo boxes with with all available languages
    foreach (Lang language, Language::languages) {
        addLanguageToMenu(language.name);
    }

    // choose the correct value from saved settings
    QString settingsLangFrom = App::theApp()->settings()->value("/Settings/Languages/from", "Auto").toString();
    QString settingsLangTo = App::theApp()->settings()->value("/Settings/Languages/to", "English").toString();
    comboBoxFrom->setCurrentText(settingsLangFrom);
    comboBoxTo->setCurrentText(settingsLangTo);

    actionFrom = new QWidgetAction(0);
    actionTo = new QWidgetAction(0);
    actionFrom->setDefaultWidget(comboBoxFrom);
    actionTo->setDefaultWidget(comboBoxTo);
    menu->addAction(actionFrom);
    menu->addAction(actionTo);

    // Add Settings menu item
    menu->addAction("Settings...", settingsForm, SLOT(showForm()));

    // Add Exit menu item
    menu->addAction("Exit", qApp, SLOT(quit()));
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

void Tray::chooseFromLang(QString name)
{
    App::theApp()->settings()->setValue("/Settings/Languages/from", name);
}

void Tray::chooseToLang(QString name)
{
    App::theApp()->settings()->setValue("/Settings/Languages/to", name) ;
}

void Tray::addLanguageToMenu(QString name)
{
    comboBoxFrom->addItem(QIcon(Language::getIconPath(name)), name, QVariant(name));

    // do not add Auto item to `Translate to` menu
    if (name == "Auto") return;
    comboBoxTo->addItem(QIcon(Language::getIconPath(name)), name, QVariant(name));
}
