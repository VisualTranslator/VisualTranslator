#include "visualtranslator.h"

VisualTranslator::VisualTranslator(QWidget *parent) : QWidget(parent)
{
    QString shortcut = App::theApp()->settings()->value("/Settings/Shortcut/Recognition", "Ctrl+Alt+Q").toString();

    // Initialize related modules
    hotkey = new QHotkey(QKeySequence(shortcut), true, this);
    screenArea = new ScreenArea;
    recognizer = new Recognizer(this);
    translator = new Translator;
    tray = new Tray;

    // Setup connection between the modules in order of execution
    QObject::connect(hotkey, SIGNAL(activated()), screenArea, SLOT(show()));
    QObject::connect(screenArea, SIGNAL(selected(QPixmap)), recognizer, SLOT(start(QPixmap)));
    QObject::connect(recognizer, SIGNAL(recognized(QString)), translator, SLOT(translate(QString)));
    QObject::connect(translator, SIGNAL(translated(QString, QString)), tray, SLOT(showMessage(QString,QString)));

    QObject::connect(tray, SIGNAL(shortcutChanged(QString)), this, SLOT(changeShortcut(QString)));
}

void VisualTranslator::changeShortcut(QString shortcut)
{
    // disconnect a previous connection
    hotkey->disconnect();

    // create a new hotkey
    hotkey = new QHotkey(QKeySequence(shortcut), true, this);
    QObject::connect(hotkey, SIGNAL(activated()), screenArea, SLOT(show()));
}
