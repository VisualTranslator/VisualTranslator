#ifndef TRAY_H
#define TRAY_H

#include <QtWidgets>
#include "app.h"
#include "language.h"
#include "settingsform.h"
#include <languageqcombobox.h>
#include <translationresultform.h>
#include <ui_translationresultform.h>

class Tray : public QWidget
{
    Q_OBJECT
private:
    void addLanguageToMenu(QString name);
    QAction *startTranslation;
    QSystemTrayIcon *trayIcon;
    QMenu *menu;
    SettingsForm *settingsForm;
    QWidgetAction *actionFrom;
    QWidgetAction *actionTo;
    TranslationResultForm *translationResultForm;
    LanguageQComboBox *comboBoxFrom;
    LanguageQComboBox *comboBoxTo;
public:
    explicit Tray(QWidget *parent = 0);

public slots:
    void showMessage(const QString &original, const QString &translation);
    void chooseFromLang(QString name);
    void chooseToLang(QString name);
    void showMenu();
    void shortcutChange(QString shortcut);

signals:
    void shortcutChanged(QString shortcut);
    void startRecognitionPressed();
};

#endif // TRAY_H
