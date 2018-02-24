#ifndef SCREENAREA_H
#define SCREENAREA_H

#include <QtWidgets>
#include "allheaders.h"

class ScreenArea: public QLabel
{
    Q_OBJECT
private:
    QPixmap screenshot, cropped;
    QPoint start, end;
    QRubberBand *rubberBand;
    bool isActive;
    Pix* qImage2PIX(QImage& qImage);
    void translate(char *text, char *lang);
    void replyFinished();
protected:
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    virtual void mouseMoveEvent(QMouseEvent *ev);
    virtual void paintEvent(QPaintEvent *ev);

public:
    ScreenArea(QWidget *parent = 0);

public slots:
    void show();

signals:
    void selected(const QPixmap &img);
};

#endif // SCREENAREA_H
