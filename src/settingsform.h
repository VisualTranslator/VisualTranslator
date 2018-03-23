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
    void shortcutChange(QString shortcut);

private slots:
    virtual void closeEvent(QCloseEvent *event);
    void on_btnCancel_clicked();
    void on_btnSaveChanges_clicked();

signals:
    void shortcutChanged(QString shortcut);

private:
    ShortcutSetupForm *shortcutSetupForm;
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
