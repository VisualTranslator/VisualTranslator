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
    QSystemTrayIcon *trayIcon;
    void addLanguageToMenu(QString name);
    QAction *startTranslation;
    QMenu *menu;
    SettingsForm *settingsForm;
    QWidgetAction *actionFrom;
    QWidgetAction *actionTo;
    TranslationResultForm *translationResultForm;
    LanguageQComboBox *comboBoxFrom;
    LanguageQComboBox *comboBoxTo;

public slots:
    void showMenu();
    //void showMessage(const QString &original, const QString &translation);
    //void chooseFromLang(QString name);
    //void chooseToLang(QString name);
    //void shortcutChange(QString shortcut);

signals:
    void shortcutChanged(QString shortcut);
    void startRecognitionPressed();
};

#endif // TRAYFORM_H
