#ifndef TRAYFORM_H
#define TRAYFORM_H

#include <QWidget>
#include <QtWidgets>
#include "app.h"
#include "language.h"
#include "settingsform.h"
#include <languageqcombobox.h>
#include <translationresultform.h>
#include <ui_translationresultform.h>

namespace Ui {
class TrayForm;
}

class TrayForm : public QWidget
{
    Q_OBJECT

public:
    explicit TrayForm(QWidget *parent = 0);
    ~TrayForm();

private:
    LanguageQComboBox *comboBoxFrom;
    LanguageQComboBox *comboBoxTo;
    QAction *startTranslation;
    QMenu *menu;
    QSystemTrayIcon *trayIcon;
    QWidgetAction *actionFrom;
    QWidgetAction *actionTo;
    SettingsForm *settingsForm;
    TranslationResultForm *translationResultForm;
    Ui::TrayForm *ui;
protected:
    void focusOutEvent(QFocusEvent * event)
        {
            Q_UNUSED(event);
            close();
        }

public slots:
    void shortcutChange(QString shortcut);
    void showError(QString);
    void showMenu();
    void showMessage(const QString &original, const QString &translation);

signals:
    void shortcutChanged(QString shortcut);
    void startRecognitionPressed();
private slots:
    void on_ExitButton_clicked();
    void on_SettingsButton_clicked();
    void on_startButton_clicked();
    void on_translateFrom_activated(const QString &name);
    void on_translateTo_activated(const QString &name);
};

#endif // TRAYFORM_H
