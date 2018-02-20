#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QtWidgets>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslError>
#include "app.h"
#include <language.h>

class Translator : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager *qNetwork;

public:
    explicit Translator(QObject *parent = 0);

signals:
    void showResult(const QString &result);

public slots:
    void start(char *&text);
    void handleNetworkData(QNetworkReply *reply);
};

#endif // TRANSLATOR_H
