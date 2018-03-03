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
