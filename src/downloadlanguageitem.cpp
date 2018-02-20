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
    QString url;

    if (name == "Arabic") {
        url = "https://dl.dropboxusercontent.com/s/7qujorvi4op3tej/ara.traineddata";
    }

    if (name == "English") {
        url = "https://dl.dropboxusercontent.com/s/r5qmsfonx7mluc4/eng.traineddata";
    }

    if (name == "French") {
        url = "https://dl.dropboxusercontent.com/s/ak8pnk2eup3w6e7/fra.traineddata";
    }

    if (name == "German") {
        url = "https://dl.dropboxusercontent.com/s/l3083m8285ouhtr/deu.traineddata";
    }

    if (name == "Italian") {
        url = "https://dl.dropboxusercontent.com/s/opr15y55o01cm4b/ita.traineddata";
    }

    if (name == "Japanese") {
        url = "https://dl.dropboxusercontent.com/s/orsqcy09ohnd8ry/jpn.traineddata";
    }

    if (name == "Korean") {
        url = "https://dl.dropboxusercontent.com/s/rkg0vev3jzcgdur/kor.traineddata";
    }

    if (name == "Portuguese") {
        url = "https://dl.dropboxusercontent.com/s/tmoion1c26qbx6b/por.traineddata";
    }

    if (name == "Russian") {
        url = "https://dl.dropboxusercontent.com/s/3msbg4slhgm6gaq/rus.traineddata";
    }

    if (name == "Spanish") {
        url = "https://dl.dropboxusercontent.com/s/pba3sen7o8e3nhf/spa.traineddata";
    }

    if (name == "Ukrainian") {
        url = "https://dl.dropboxusercontent.com/s/17at42rlq50cy1z/ukr.traineddata";
    }

    NetworkFileDownloader *networkFileDownloader = new NetworkFileDownloader();
    networkFileDownloader->download(url);

    emit downloadStart();
    connect(networkFileDownloader->reply,SIGNAL(downloadProgress(qint64,qint64)),this, SIGNAL(downloadProgress(qint64, qint64)));
}

void DownloadLanguageItem::removeButtonClicked()
{
    QDir tessdataFolder(qApp->applicationDirPath() + "/tessdata");

    QString fileName;

    if (name == "Arabic") {
        fileName = "ara.traineddata";
    }

    if (name == "English") {
        fileName = "eng.traineddata";
    }

    if (name == "French") {
        fileName = "fra.traineddata";
    }

    if (name == "German") {
        fileName = "deu.traineddata";
    }

    if (name == "Italian") {
        fileName = "ita.traineddata";
    }

    if (name == "Japanese") {
        fileName = "jpn.traineddata";
    }

    if (name == "Korean") {
        fileName = "kor.traineddata";
    }

    if (name == "Portuguese") {
        fileName = "por.traineddata";
    }

    if (name == "Russian") {
        fileName = "rus.traineddata";
    }

    if (name == "Spanish") {
        fileName = "spa.traineddata";
    }

    if (name == "Ukrainian") {
        fileName = "ukr.traineddata";
    }

    tessdataFolder.remove(fileName);
}
