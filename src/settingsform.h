#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = 0);
    ~SettingsForm();

public slots:
    void showForm();
    virtual void closeEvent(QCloseEvent *event);

private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
