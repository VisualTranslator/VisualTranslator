#include "visualtranslator.h"
#include "app.h"

VisualTranslator::VisualTranslator()
{
    QString shortcut = App::theApp()->settings()->value("/Settings/Shortcut/Recognition", "Ctrl+Alt+Q").toString();

    // Initialize related modules
    hotkey = new QHotkey(QKeySequence(shortcut), true, this);
    screenArea = new ScreenArea;
    recognizer = new Recognizer(this);
    translator = new Translator;
    trayForm = new Tray;

    // Setup connection between the modules in order of execution
    QObject::connect(hotkey, SIGNAL(activated()), screenArea, SLOT(show()));
    QObject::connect(trayForm, SIGNAL(startRecognitionPressed()), screenArea, SLOT(show()));

    QObject::connect(screenArea, SIGNAL(selected(QPixmap)), recognizer, SLOT(start(QPixmap)));
    QObject::connect(recognizer, SIGNAL(recognized(QString)), translator, SLOT(translate(QString)));
    QObject::connect(translator, SIGNAL(translated(QString, QString)), trayForm, SLOT(showMessage(QString,QString)));
    QObject::connect(trayForm, SIGNAL(shortcutChanged(QString)), this, SLOT(changeShortcut(QString)));

    // Errors
    QObject::connect(translator, SIGNAL(error(QString)), trayForm, SLOT(showError(QString)));
}

void VisualTranslator::changeShortcut(QString shortcut)
{
    // disconnect a previous connection
    hotkey->disconnect();

    // create a new hotkey
    hotkey = new QHotkey(QKeySequence(shortcut), true, this);// it may cause memory lick
    QObject::connect(hotkey, SIGNAL(activated()), screenArea, SLOT(show()));
}

bool VisualTranslator::willBeUpdated()
{
    // Check for updates only in a release mode
    if (!QLibraryInfo::isDebugBuild()) {
        int exitCode = QProcess::execute("maintenancetool", QStringList("--checkupdates"));

        // updates found
        if (exitCode == 0) {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(0, "VisualTranslator Update", "An update for VisualTranslator is available. Do you wish to install it now?",
                                          QMessageBox::Yes|QMessageBox::No);

            // return true only if user want to update the program
            if (reply == QMessageBox::Yes) {
                QProcess::execute("maintenancetool", QStringList("--updater"));
                return true;
            }
        }
    }
    return false;
}
