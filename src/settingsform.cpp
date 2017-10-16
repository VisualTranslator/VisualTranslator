#include "settingsform.h"
#include "ui_settingsform.h"
#include <QtWidgets>

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
    this->show();
}

void SettingsForm::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}
