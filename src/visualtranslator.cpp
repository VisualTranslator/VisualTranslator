#include "visualtranslator.h"

VisualTranslator::VisualTranslator(QWidget *parent) : QWidget(parent)
{
   tray = new Tray;
   recognizer = new Recognizer(this);
   screenArea = new ScreenArea;
   hotkey = new QHotkey(QKeySequence("ctrl+alt+Q"), true, this);

   QObject::connect(recognizer, SIGNAL(signalShowResult(QString)), tray, SLOT(showMessage(QString)));
   QObject::connect(hotkey, SIGNAL(activated()), this, SLOT(start()));
   QObject::connect(screenArea, SIGNAL(recognize(QPixmap)), recognizer, SLOT(start(QPixmap)));
}

void VisualTranslator::start()
{
    screenArea->showArea();
}
