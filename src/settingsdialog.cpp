#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    setDialogState(0);
}

int SettingsDialog::getDialogState() const
{
    return dialogState;
}

void SettingsDialog::setDialogState(const int newState)
{
   dialogState = (newState == 1) ? 1 : 0;
}

void SettingsDialog::showDialog()
{
    if (getDialogState() == 1)
    {
        this->raise();
        this->activateWindow();
    }
    else
    {
        //TODO : set correct values of settings
        this->show();
        this->raise();
        this->activateWindow();
    }
}

void SettingsDialog::closeDialog()
{
    setDialogState(0);
    this->close();
}

void SettingsDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
    this->setDialogState(0);
}

