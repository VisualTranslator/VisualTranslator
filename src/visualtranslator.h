#ifndef VISUALTRANSLATOR_H
#define VISUALTRANSLATOR_H

#include <QtWidgets>
#include <QHotkey>
#include <tray.h>
#include <recognizer.h>
#include <screenarea.h>
#include <translator.h>

class VisualTranslator : public QWidget
{
    Q_OBJECT
private:
    QHotkey *hotkey;
    Tray *tray;
    Recognizer *recognizer;
    ScreenArea *screenArea;
    Translator *translator;

public:
    explicit VisualTranslator(QWidget *parent = 0);

public slots:
    void changeShortcut(QString shortcut);
};


#endif // VISUALTRANSLATOR_H
