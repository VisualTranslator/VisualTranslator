#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <QObject>
#include <QtWidgets>
#include <allheaders.h>
#include <baseapi.h>
#include "translator.h"

class Recognizer : public QObject
{
    Q_OBJECT

private:
    Pix* qImage2PIX(QImage& qImage);
    Translator *translator;
public:
    explicit Recognizer(QObject *parent = 0);

signals:
    void translate(char *&text);
    void signalShowResult(const QString &result);
public slots:
    void start(const QPixmap &img);
    void showResult(const QString &result);
};

#endif // RECOGNIZER_H
