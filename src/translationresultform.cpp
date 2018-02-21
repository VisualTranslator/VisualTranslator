#include "translationresultform.h"
#include "ui_translationresultform.h"

TranslationResultForm::TranslationResultForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TranslationResultForm)
{
    ui->setupUi(this);
}

TranslationResultForm::~TranslationResultForm()
{
    delete ui;
}
