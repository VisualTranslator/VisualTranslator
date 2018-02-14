#include <QDebug>
#include "downloadlanguageitem.h"
#include "ui_downloadlanguageitem.h"

DownloadLanguageItem::DownloadLanguageItem(QString name, QString iconPath, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadLanguageItem)
{
    this->name = name;
    ui->setupUi(this);

    ui->label->setText(name);
    ui->langIcon->setPixmap(QPixmap::fromImage(QImage(iconPath)));
}

DownloadLanguageItem::~DownloadLanguageItem()
{
    delete ui;
}

void DownloadLanguageItem::on_pushButton_clicked()
{
    //TODO add links for all languages
    //TODO rewrite external links with self-hosted
    QString url;
    QString fileName;
    if (name == "French") {
        url = "https://dl.dropboxusercontent.com/s/a0cdoulz5mldkbq/6.%20The%20Sleep%20Solution%20by%20W.%20Chris%20Winter.epub?dl=0";
        fileName = "fra.traineddata";
    }

    if (!url.isEmpty()) {
        NetworkFileDownloader *networkFileDownloader = new NetworkFileDownloader;
        networkFileDownloader->download(url, fileName);
    }
}
