#include "visualtranslator.h"

VisualTranslator::VisualTranslator(QWidget *parent) : QWidget(parent)
{
    // Setup the main stylesheet
    QFile file(":/resources/stylesheet.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString style(file.readAll());
        this->setStyleSheet(style);
        file.close();
    }

    // Setup the main font
    QFontDatabase::addApplicationFont(":/resources/fonts/OpenSans-Regular.ttf");
    QFont OpenSans("OpenSans", 10, QFont::Normal);
    this->setFont(OpenSans);

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
