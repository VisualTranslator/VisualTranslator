#ifndef VISUALTRANSLATOR_H
#define VISUALTRANSLATOR_H

#include <QtWidgets>
#include <QHotkey>

class VisualTranslator : public QWidget
{
    Q_OBJECT
private:
    QSystemTrayIcon *trayIcon;
    QHotkey *hotkey;
protected:

public:
    explicit VisualTranslator(QWidget *parent = 0);

signals:

public slots:
    void start();
};

#endif // VISUALTRANSLATOR_H
