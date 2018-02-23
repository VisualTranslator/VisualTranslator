#ifndef TRAY_H
#define TRAY_H

#include <QtWidgets>
#include "app.h"
#include "settingsform.h"
#include "downloadlanguageform.h"
#include <translationresultform.h>
#include <ui_translationresultform.h>

class Tray : public QWidget
{
    Q_OBJECT
private:
    void addLanguageToMenu(QString type, QString name);
    void removeLanguageFromMenu(QString name);
    QActionGroup *menuLangToGroup;
    QActionGroup *menuLangFromGroup;
    QSystemTrayIcon *trayIcon;
    QMenu *menu;
    QMenu *langToMenu;
    QMenu *langFromMenu;
    SettingsForm *settingsForm;
    DownloadLanguageForm *downloadLanguagesForm;
    TranslationResultForm *translationResultForm;
public:
    explicit Tray(QWidget *parent = 0);
signals:

public slots:
    void showMessage(const QString &message);
    void chooseFromLang();
    void chooseToLang();
    void showMenu();
    void languageRemoved(QString name);
    void languageAdded(QString name);
};

#endif // TRAY_H
