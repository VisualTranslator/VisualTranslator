#include "app.h"

App::App(int& argc, char** argv, const QString& strOrg, const QString& strAppName): QApplication(argc, argv), pSettings(0)
{
    setOrganizationName(strOrg);
    setApplicationName(strAppName);
    pSettings = new QSettings(strOrg, strAppName, this);
}

App* App::theApp()
{
    return (App*)qApp;
}

QSettings* App::settings()
{
    return pSettings;
}
