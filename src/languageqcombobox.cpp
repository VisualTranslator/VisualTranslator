#include "languageqcombobox.h"
#include <QStylePainter>

LanguageQComboBox::LanguageQComboBox(QWidget *parent): QComboBox(parent)
{
}

void LanguageQComboBox::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);

    QStylePainter painter(this);
    painter.setPen(palette().color(QPalette::Text));

    // draw the combobox frame, focusrect and selected etc.
    QStyleOptionComboBox opt;
    initStyleOption(&opt);

    if (this->objectName() == "translateFrom")
        opt.currentText = QString("From: " + this->currentText());
    else
        opt.currentText = QString("To: " + this->currentText());
    painter.drawComplexControl(QStyle::CC_ComboBox, opt);

    // draw the icon and text
    painter.drawControl(QStyle::CE_ComboBoxLabel, opt);
}
