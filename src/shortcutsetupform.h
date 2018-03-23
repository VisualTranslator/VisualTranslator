#ifndef SHORTCUTSETUPFORM_H
#define SHORTCUTSETUPFORM_H

#include <QWidget>
#include <QtWidgets>

namespace Ui {
class ShortcutSetupForm;
}

class ShortcutSetupForm : public QWidget
{
    Q_OBJECT

public:
    explicit ShortcutSetupForm(QWidget *parent = 0);
    ~ShortcutSetupForm();

signals:
    void shortcutChanged(QString shortcut);

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_cancelButton_clicked();
    void on_saveButton_clicked();

private:
    QString shortcut;
    Ui::ShortcutSetupForm *ui;
};

#endif // SHORTCUTSETUPFORM_H
