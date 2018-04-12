#include "screenarea.h"

ScreenArea::ScreenArea(QWidget *parent): QLabel(parent), isActive(false)
{
    this->setCursor(QPixmap(":/resources/cursor.png"));
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void ScreenArea::show()
{
    screenshot = QPixmap::grabWindow(QApplication::desktop()->winId());
    this->showFullScreen();
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
    painter.setPen(QPen(QColor(66, 134, 244), 2, Qt::SolidLine));
    if (isActive) {
        painter.drawRect(QRect(start, end));
        painter.fillRect(QRect(start, end), QBrush(QColor(66, 134, 244, 50)));

    }
}

void ScreenArea::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Escape)
    {
        this->hide();
    }
}
