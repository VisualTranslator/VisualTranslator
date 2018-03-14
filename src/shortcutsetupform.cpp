#include "shortcutsetupform.h"
#include "ui_shortcutsetupform.h"
#include <QRegularExpression>

ShortcutSetupForm::ShortcutSetupForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShortcutSetupForm)
{
    ui->setupUi(this);
}

ShortcutSetupForm::~ShortcutSetupForm()
{
    delete ui;
}

void ShortcutSetupForm::keyPressEvent(QKeyEvent *event)
{
    shortcut = QKeySequence(event->modifiers() + event->nativeVirtualKey()).toString().toLatin1();
    ui->lineEdit->setText(shortcut);
}

void ShortcutSetupForm::on_cancelButton_clicked()
{
    this->close();
    this->deleteLater();
}

void ShortcutSetupForm::on_saveButton_clicked()
{
    emit shortcutChanged(shortcut);
    this->close();
    this->deleteLater();
}
