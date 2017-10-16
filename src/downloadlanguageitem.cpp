#include "downloadlanguageitem.h"
#include "ui_downloadlanguageitem.h"

DownloadLanguageItem::DownloadLanguageItem(QString name, QString iconPath, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadLanguageItem)
{
    ui->setupUi(this);

    ui->label->setText(name);
    ui->langIcon->setPixmap(QPixmap::fromImage(QImage(iconPath)));
}

DownloadLanguageItem::~DownloadLanguageItem()
{
    delete ui;
}
