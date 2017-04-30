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
    static App* theApp();
    QSettings* settings();
};

#endif // APP_H
