#include "screenarea.h"

ScreenArea::ScreenArea(QWidget *parent): QLabel(parent)
{
    rubberBand = new QRubberBand(QRubberBand::Rectangle, parent);
}

void ScreenArea::showArea()
{
    screenshot = QPixmap::grabWindow(QApplication::desktop()->winId());
    setPixmap(screenshot);
    showFullScreen();
}

void ScreenArea::mousePressEvent(QMouseEvent *ev)
{
    start = ev->pos();
    rubberBand->setGeometry(QRect(start, QSize()));
    rubberBand->show();
}

void ScreenArea::mouseReleaseEvent(QMouseEvent *ev)
{
    end = ev->pos();
    cropped =  screenshot.copy(QRect(start,end));
    rubberBand->hide();
    this->hide();
}

void ScreenArea::mouseMoveEvent(QMouseEvent *ev)
{
    end = ev->pos();
    rubberBand->setGeometry(QRect(start, end).normalized());
}
