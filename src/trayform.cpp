#include "trayform.h"
#include "ui_trayform.h"

TrayForm::TrayForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrayForm)
{
    // Setup initial UI state
    ui->setupUi(this);
    this->setWindowFlags(Qt::Popup);

    QString shortcut = App::theApp()->settings()->value("/Settings/Shortcut/Recognition", "Ctrl+Alt+Q").toString();
    ui->shortcut->setText("or press " + shortcut);

    // Setup the tray icon
    trayIcon = new QSystemTrayIcon(QIcon(":/resources/tray.png"));
    trayIcon->setToolTip(QString("Visual Translator"));
    trayIcon->show();
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showMenu()));

    // Setup all forms
    settingsForm = new SettingsForm();
    connect(settingsForm, SIGNAL(shortcutChanged(QString)), this, SLOT(shortcutChange(QString)));

    translationResultForm = new TranslationResultForm(parent);
    translationResultForm->setWindowFlag(Qt::Popup);

    // Fill a combo boxes with with all available languages
    foreach (Lang language, Language::languages) {
        ui->translateFrom->addItem(QIcon(Language::getIconPath(language.name)), language.name, QVariant(language.name));

        // do not add Auto item to `Translate to` menu
        if (language.name == "Auto") continue;
        ui->translateTo->addItem(QIcon(Language::getIconPath(language.name)), language.name, QVariant(language.name));
    }

    // choose the correct value from saved settings
    QString settingsLangFrom = App::theApp()->settings()->value("/Settings/Languages/from", "Auto").toString();
    QString settingsLangTo = App::theApp()->settings()->value("/Settings/Languages/to", "English").toString();
    ui->translateFrom->setCurrentText(settingsLangFrom);
    ui->translateTo->setCurrentText(settingsLangTo);

    //connect(ui->translateFrom, SIGNAL(highlighted(QString)));
}

TrayForm::~TrayForm()
{
    delete ui;
}

void TrayForm::showMenu()
{
    // search for the correct position
    int screenWidth = QApplication::desktop()->screenGeometry().width();
    int screenHeight = QApplication::desktop()->screenGeometry().height();
    QRect trayIconGeometry = trayIcon->geometry();
    QPoint formPosition = QPoint(trayIconGeometry.x(), trayIconGeometry.y());

    // TODO check with non-default dock position (left, right, top)

    if (formPosition.x() + this->width() > screenWidth) {
        formPosition.setX(screenWidth - this->width());
    }

    if (formPosition.y() + this->height() > screenHeight) {
        formPosition.setY(screenHeight - this->height() - trayIconGeometry.height());
    }

    this->move(formPosition);
    this->show();
}

void TrayForm::on_SettingsButton_clicked()
{
    settingsForm->show();
}

void TrayForm::on_startButton_clicked()
{
    this->hide();
    emit startRecognitionPressed();
}

void TrayForm::on_translateFrom_activated(const QString &name)
{
    App::theApp()->settings()->setValue("/Settings/Languages/from", name);
}


void TrayForm::on_translateTo_activated(const QString &name)
{
    App::theApp()->settings()->setValue("/Settings/Languages/to", name);
}

void TrayForm::shortcutChange(QString shortcut)
{
    ui->shortcut->setText("or press " + shortcut);
    emit shortcutChanged(shortcut);
}

void TrayForm::showMessage(const QString &original, const QString &translation)
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

void TrayForm::on_ExitButton_clicked()
{
    qApp->exit();
}
