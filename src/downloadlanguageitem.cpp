#include <QDebug>
#include "downloadlanguageitem.h"
#include "ui_downloadlanguageitem.h"

DownloadLanguageItem::DownloadLanguageItem(QString name, QString iconPath, bool isDownloaded, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadLanguageItem)
{
    this->name = name;
    ui->setupUi(this);

    if (isDownloaded) {
        ui->pushButton->setText("Remove");
    }

    ui->label->setText(name);
    ui->langIcon->setPixmap(QPixmap::fromImage(QImage(iconPath)));
}

DownloadLanguageItem::~DownloadLanguageItem()
{
    delete ui;
}

void DownloadLanguageItem::on_pushButton_clicked()
{
    if (ui->pushButton->text() == "Download") {
        downloadButtonClicked();
    } else if (ui->pushButton->text() == "Remove") {
        removeButtonClicked();
    }
}

void DownloadLanguageItem::downloadButtonClicked()
{
    QString url = Language::getUrl(name);
    NetworkFileDownloader *networkFileDownloader = new NetworkFileDownloader();

    networkFileDownloader->download(url);

    emit downloadStart();
    connect(networkFileDownloader->reply,SIGNAL(downloadProgress(qint64,qint64)),this, SIGNAL(downloadProgress(qint64, qint64)));
}

void DownloadLanguageItem::removeButtonClicked()
{
    QString fileName = Language::getFileName(name);
    QDir tessdataFolder(qApp->applicationDirPath() + "/tessdata");

    bool isRemoved = tessdataFolder.remove(fileName);

    if (isRemoved) {
        ui->pushButton->setText("Download");
    }
}
