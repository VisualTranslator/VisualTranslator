#include "visualtranslator.h"

VisualTranslator::VisualTranslator(QWidget *parent) : QWidget(parent)
{
   trayIcon = new QSystemTrayIcon(QIcon(":/tray.png"), this);
   trayIcon->show();
   hotkey = new QHotkey(QKeySequence("ctrl+alt+Q"), true, this);
   QObject::connect(hotkey, SIGNAL(activated()), this, SLOT(start()));
}

void VisualTranslator::start()
{
    trayIcon->showMessage(QString("Message"), QString("Test message"));
}
