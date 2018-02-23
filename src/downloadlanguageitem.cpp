#include "downloadlanguageitem.h"

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
    // TODO find an alternative way to identify different types of buttons, not by `text()`
    if (ui->pushButton->text() == "Download") {
        downloadButtonClicked();
    } else if (ui->pushButton->text() == "Remove") {
        removeButtonClicked();
    }
}

void DownloadLanguageItem::downloadButtonClicked()
{
    emit downloadStart(name);
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
