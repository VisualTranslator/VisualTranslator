#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <QObject>
#include <QtWidgets>
#include <app.h>
#include <allheaders.h>
#include <baseapi.h>
#include <language.h>

class Recognizer : public QObject
{
    Q_OBJECT

private:
    Pix* qImage2PIX(QImage& qImage);
public:
    explicit Recognizer(QObject *parent = 0);

signals:
    void recognized(QString text);

public slots:
    void start(const QPixmap &img);
};

#endif // RECOGNIZER_H
