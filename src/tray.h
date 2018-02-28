#ifndef TRAY_H
#define TRAY_H

#include <QtWidgets>
#include "app.h"
#include "language.h"
#include "settingsform.h"
#include <translationresultform.h>
#include <ui_translationresultform.h>

class Tray : public QWidget
{
    Q_OBJECT
private:
    void addLanguageToMenu(QString name);
    QActionGroup *menuLangToGroup;
    QActionGroup *menuLangFromGroup;
    QSystemTrayIcon *trayIcon;
    QMenu *menu;
    QMenu *langToMenu;
    QMenu *langFromMenu;
    SettingsForm *settingsForm;
    TranslationResultForm *translationResultForm;
public:
    explicit Tray(QWidget *parent = 0);

public slots:
    void showMessage(const QString &original, const QString &translation);
    void chooseFromLang();
    void chooseToLang();
    void showMenu();

signals:
    void shortcutChanged(QString name);
};

#endif // TRAY_H
