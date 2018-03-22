#include "screenarea.h"

ScreenArea::ScreenArea(QWidget *parent): QLabel(parent), isActive(false)
{
    this->setCursor(QPixmap(":/resources/cursor.png"));
}

void ScreenArea::show()
{
    screenshot = QPixmap::grabWindow(QApplication::desktop()->winId());
    showFullScreen();
    isActive = false;
}

void ScreenArea::mousePressEvent(QMouseEvent *ev)
{
    start = ev->pos();
    isActive = true;
}

void ScreenArea::mouseReleaseEvent(QMouseEvent *ev)
{
    end = ev->pos();
    QRect rect;

    if(start.x()<end.x())
    {
        rect.setLeft(start.x());
        rect.setRight(end.x());
    }
    else
    {
        rect.setLeft(end.x());
        rect.setRight(start.x());
    }
    if(start.y()<end.y())
    {
        rect.setTop(start.y());
        rect.setBottom(end.y());
    }
    else
    {
        rect.setTop(end.y());
        rect.setBottom(start.y());
    }
    cropped =  screenshot.copy(rect);
    this->hide();
    emit selected(cropped);
}

void ScreenArea::mouseMoveEvent(QMouseEvent *ev)
{
    end = ev->pos();
    update();
}

void ScreenArea::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);

    QPainter painter(this);
    painter.drawPixmap(0, 0, screenshot);
    painter.setPen(QPen(QColor(11, 164, 236), 2, Qt::DashLine));
    if (isActive) painter.drawRect(QRect(start, end));
}

void ScreenArea::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Escape)
    {
        this->hide();
    }
}
