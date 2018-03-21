#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QtWidgets>
#include <QNetworkAccessManager>
#include <QNetworkConfigurationManager>
#include <QNetworkReply>
#include <QSslError>
#include "app.h"
#include <language.h>

class Translator : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager *qNetwork;
    QString original;

public:
    explicit Translator(QObject *parent = 0);

signals:
    void translated(QString original, QString result);
    void error(QString message);

public slots:
    void translate(QString text);
    void handleNetworkData(QNetworkReply *reply);
};

#endif // TRANSLATOR_H
