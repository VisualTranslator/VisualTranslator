#ifndef TRANSLATIONRESULTFORM_H
#define TRANSLATIONRESULTFORM_H

#include <QWidget>

namespace Ui {
class TranslationResultForm;
}

class TranslationResultForm : public QWidget
{
    Q_OBJECT

public:
    explicit TranslationResultForm(QWidget *parent = 0);
    ~TranslationResultForm();
    Ui::TranslationResultForm *ui;

private:
};

#endif // TRANSLATIONRESULTFORM_H
