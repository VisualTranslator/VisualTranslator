#ifndef VISUALTRANSLATOR_H
#define VISUALTRANSLATOR_H

#include <QtWidgets>
#include <QHotkey>
#include <tray.h>
#include <recognizer.h>
#include <screenarea.h>
#include <translator.h>

class VisualTranslator : public QObject
{
    Q_OBJECT
private:
    QHotkey *hotkey;
    Recognizer *recognizer;
    ScreenArea *screenArea;
    Translator *translator;
    Tray *trayForm;

public:
    explicit VisualTranslator();
    bool willBeUpdated();

public slots:
    void changeShortcut(QString shortcut);
};


#endif // VISUALTRANSLATOR_H
