#include "visualtranslator.h"

VisualTranslator::VisualTranslator(QWidget *parent) : QWidget(parent)
{
   tray = new Tray;
   recognizer = new Recognizer(this);
   screenArea = new ScreenArea;
   hotkey = new QHotkey(QKeySequence("ctrl+alt+Q"), true, this);
   translator = new Translator;

   QObject::connect(hotkey, SIGNAL(activated()), screenArea, SLOT(show()));
   QObject::connect(screenArea, SIGNAL(selected(QPixmap)), recognizer, SLOT(start(QPixmap)));
   QObject::connect(recognizer, SIGNAL(recognized(QString)), translator, SLOT(translate(QString)));
   QObject::connect(translator, SIGNAL(translated(QString, QString)), tray, SLOT(showMessage(QString,QString)));
}
