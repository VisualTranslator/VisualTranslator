#include "languageqcombobox.h"
#include <QStylePainter>

LanguageQComboBox::LanguageQComboBox(QString direction, QWidget *parent): QComboBox(parent)
{
    this->direction = direction;
}

void LanguageQComboBox::paintEvent(QPaintEvent *ev)
{
    QStylePainter painter(this);
    painter.setPen(palette().color(QPalette::Text));

    // draw the combobox frame, focusrect and selected etc.
    QStyleOptionComboBox opt;
    initStyleOption(&opt);
    opt.currentText = QString(direction + ": " + this->currentText());
    painter.drawComplexControl(QStyle::CC_ComboBox, opt);

    // draw the icon and text
    painter.drawControl(QStyle::CE_ComboBoxLabel, opt);
}
