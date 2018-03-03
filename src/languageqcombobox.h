#ifndef LANGUAGEQCOMBOBOX_H
#define LANGUAGEQCOMBOBOX_H

#include <QObject>
#include <QComboBox>

class LanguageQComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit LanguageQComboBox(QWidget *parent = 0);

protected:
    virtual void paintEvent(QPaintEvent *ev);
};

#endif // LANGUAGEQCOMBOBOX_H
