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
    Ui::TrayForm *ui;
    SettingsForm *settingsForm;
    QSystemTrayIcon *trayIcon;
    QAction *startTranslation;
    QMenu *menu;
    QWidgetAction *actionFrom;
    QWidgetAction *actionTo;
    TranslationResultForm *translationResultForm;
    LanguageQComboBox *comboBoxFrom;
    LanguageQComboBox *comboBoxTo;
protected:
    void focusOutEvent(QFocusEvent * event)
        {
            close();
        }

public slots:
    void showMenu();
    void shortcutChange(QString shortcut);
    void showMessage(const QString &original, const QString &translation);

signals:
    void shortcutChanged(QString shortcut);
    void startRecognitionPressed();
private slots:
    void on_SettingsButton_clicked();
    void on_startButton_clicked();
    void on_translateFrom_activated(const QString &name);
    void on_translateTo_activated(const QString &name);
    void on_ExitButton_clicked();
};

#endif // TRAYFORM_H
