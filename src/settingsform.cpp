#include "settingsform.h"

SettingsForm::SettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::showForm()
{
    if (App::theApp()->settings()->value("/Settings/Autorun/Flag", "0").toString() == QString("0"))
    {
        ui->checkBox->setChecked(false);
    }
    else
    {
       ui->checkBox->setChecked(true);
    }
    this->show();
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
    this->hide();
    if (ui->checkBox->isChecked())
    {
        App::theApp()->settings()->setValue("/Settings/Autorun/Flag", QString("1"));
    }
    else
    {
        App::theApp()->settings()->setValue("/Settings/Autorun/Flag", QString("0"));
    }
}
