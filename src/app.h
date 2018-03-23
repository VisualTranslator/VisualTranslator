#ifndef APP_H
#define APP_H

#include <QtWidgets>

class App : public QApplication
{
    Q_OBJECT
private:
    QSettings *pSettings;
public:
    App(int& argc, char** argv, const QString& strOrg, const QString& strAppName);
    QSettings* settings();
    static App* theApp();
};

#endif // APP_H
