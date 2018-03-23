#ifndef VISUALTRANSLATOR_H
#define VISUALTRANSLATOR_H

#include <QtWidgets>
#include <QHotkey>
#include <trayform.h>
#include <recognizer.h>
#include <screenarea.h>
#include <translator.h>

class VisualTranslator : public QWidget
{
    Q_OBJECT
private:
    QHotkey *hotkey;
    Recognizer *recognizer;
    ScreenArea *screenArea;
    Translator *translator;
    TrayForm *trayForm;

public:
    explicit VisualTranslator(QWidget *parent = 0);
    bool willBeUpdated();

public slots:
    void changeShortcut(QString shortcut);
};


#endif // VISUALTRANSLATOR_H
