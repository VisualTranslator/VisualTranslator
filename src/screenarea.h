#ifndef SCREENAREA_H
#define SCREENAREA_H

#include <QtWidgets>

class ScreenArea: public QLabel
{
    Q_OBJECT
private:
    QPixmap screenshot, cropped;
    QPoint start, end;
    QRubberBand *rubberBand;
protected:
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    virtual void mouseMoveEvent(QMouseEvent *ev);

public:
    ScreenArea(QWidget *parent = 0);
    void showArea();
};

#endif // SCREENAREA_H
