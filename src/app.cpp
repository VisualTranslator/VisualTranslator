#include "app.h"

App::App(int& argc, char** argv, const QString& strOrg, const QString& strAppName): QApplication(argc, argv), pSettings(0)
{
    // Do not quit app when close last window
    // needed for macOS
    this->setQuitOnLastWindowClosed(false);

    setOrganizationName(strOrg);
    setApplicationName(strAppName);
    pSettings = new QSettings(strOrg, strAppName, this);

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
}

App* App::theApp()
{
    return (App*)qApp;
}

QSettings* App::settings()
{
    return pSettings;
}
