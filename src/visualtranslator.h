#ifndef VISUALTRANSLATOR_H
#define VISUALTRANSLATOR_H

#include <QtWidgets>
#include <QHotkey>
#include <tray.h>
#include <recognizer.h>
#include <screenarea.h>

class VisualTranslator : public QWidget
{
    Q_OBJECT
private:
    QHotkey *hotkey;
    Tray *tray;
    Recognizer *recognizer;
    ScreenArea *screenArea;

protected:

public:
    explicit VisualTranslator(QWidget *parent = 0);

signals:

public slots:
    void start();
};

#endif // VISUALTRANSLATOR_H
