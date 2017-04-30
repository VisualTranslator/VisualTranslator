#include "visualtranslator.h"
#include "tray.h"

VisualTranslator::VisualTranslator(QWidget *parent) : QWidget(parent)
{
   tray = new Tray;

   hotkey = new QHotkey(QKeySequence("ctrl+alt+Q"), true, this);
   QObject::connect(hotkey, SIGNAL(activated()), this, SLOT(start()));
}

void VisualTranslator::start()
{
    //TODO : paint screenshot
}
