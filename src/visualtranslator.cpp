#include "visualtranslator.h"

VisualTranslator::VisualTranslator(QWidget *parent) : QWidget(parent)
{
    // Initialize related modules
    hotkey = new QHotkey(QKeySequence("ctrl+alt+Q"), true, this);
    screenArea = new ScreenArea;
    recognizer = new Recognizer(this);
    translator = new Translator;
    tray = new Tray;

    // Setup connection between the modules in order of execution
    QObject::connect(hotkey, SIGNAL(activated()), screenArea, SLOT(show()));
    QObject::connect(screenArea, SIGNAL(selected(QPixmap)), recognizer, SLOT(start(QPixmap)));
    QObject::connect(recognizer, SIGNAL(recognized(QString)), translator, SLOT(translate(QString)));
    QObject::connect(translator, SIGNAL(translated(QString, QString)), tray, SLOT(showMessage(QString,QString)));
}
