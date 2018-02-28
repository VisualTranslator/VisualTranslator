#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>
#include <QtWidgets>
#include "app.h"
#include "shortcutsetupform.h"

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = 0);
    ~SettingsForm();

protected:
    bool eventFilter(QObject *obj, QEvent *ev);

public slots:
    void showForm();
    void shortcutChanged(QString shortcut);
    virtual void closeEvent(QCloseEvent *event);

private slots:
    void on_btnCancel_clicked();
    void on_btnSaveChanges_clicked();

private:
    Ui::SettingsForm *ui;
    ShortcutSetupForm *shortcutSetupForm;
};

#endif // SETTINGSFORM_H
