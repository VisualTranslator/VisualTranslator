#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QtWidgets>

class SettingsDialog : public QDialog
{
    Q_OBJECT
private:
    int dialogState; // 0 - not active, 1 - active

public:
    SettingsDialog(QWidget *parent = 0);
    int getDialogState() const;
    void setDialogState(const int newState);

public slots:
    void showDialog();
    void closeDialog();
    virtual void closeEvent(QCloseEvent *event);
};

#endif // SETTINGSDIALOG_H
