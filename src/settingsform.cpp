#include "settingsform.h"
#include "ui_settingsform.h"

SettingsForm::SettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);
    ui->lineEdit->installEventFilter(this);
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    QString shortcut = App::theApp()->settings()->value("/Settings/Shortcut/Recognition", "Ctrl+Alt+Q").toString();
    ui->lineEdit->setText(shortcut);

    // If Autorun/Flag do not set - it's means that it's a first app run
    // add to the autorun
    if (App::theApp()->settings()->value("/Settings/Autorun/Flag").toString() == "")
    {
        App::theApp()->settings()->setValue("/Settings/Autorun/Flag", QString("1"));

        QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        settings.setValue("VisualTranslator", QCoreApplication::applicationFilePath().replace('/', '\\'));
    }

    if (App::theApp()->settings()->value("/Settings/Autorun/Flag", "0").toString() == QString("0"))
    {
        ui->checkBox->setChecked(false);
    }
    else
    {
       ui->checkBox->setChecked(true);
    }
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

bool SettingsForm::eventFilter(QObject* object, QEvent* event)
{
    if(object == ui->lineEdit && event->type() == QEvent::MouseButtonPress) {
        shortcutSetupForm = new ShortcutSetupForm();
        connect(shortcutSetupForm, SIGNAL(shortcutChanged(QString)), this, SLOT(shortcutChange(QString)));
        shortcutSetupForm->show();
        return false; // lets the event continue to the edit
    }
    return false;
}

void SettingsForm::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}

void SettingsForm::on_btnCancel_clicked()
{
    this->hide();
}

void SettingsForm::on_btnSaveChanges_clicked()
{
    if (ui->checkBox->isChecked())
    {
        App::theApp()->settings()->setValue("/Settings/Autorun/Flag", QString("1"));

        QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        settings.setValue("VisualTranslator", QCoreApplication::applicationFilePath().replace('/', '\\'));
    }
    else
    {
        App::theApp()->settings()->setValue("/Settings/Autorun/Flag", QString("0"));

        QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        settings.remove("VisualTranslator");
    }

    App::theApp()->settings()->setValue("/Settings/Shortcut/Recognition", ui->lineEdit->text());

    this->hide();
}

void SettingsForm::shortcutChange(QString shortcut)
{
    ui->lineEdit->setText(shortcut);
    emit shortcutChanged(shortcut);
}
