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

class Tray : public QWidget
{
    Q_OBJECT

public:
    explicit Tray(QWidget *parent = 0);
    ~Tray();

private:
    LanguageQComboBox *comboBoxFrom;
    LanguageQComboBox *comboBoxTo;
    QAction *startTranslation;
    QMenu *menu;
    QSystemTrayIcon *trayIcon;
    SettingsForm *settingsForm;
    TranslationResultForm *translationResultForm;
    Ui::TrayForm *ui;
    QActionGroup *menuLangToGroup;
    QActionGroup *menuLangFromGroup;
    QMenu *langToMenu;
    QMenu *langFromMenu;

public slots:
    void shortcutChange(QString shortcut);
    void showError(QString);
    void showMessage(const QString &original, const QString &translation);

signals:
    void shortcutChanged(QString shortcut);
    void startRecognitionPressed();
private slots:
    void on_SettingsButton_clicked();
    void on_startButton_clicked();
    void chooseLanguageFrom();
    void chooseLanguageTo();
};

#endif // TRAYFORM_H
