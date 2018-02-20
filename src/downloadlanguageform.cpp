#include "downloadlanguageform.h"
#include "ui_downloadlanguageform.h"
#include <QtWidgets>

DownloadLanguageForm::DownloadLanguageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadLanguageForm)
{
    ui->setupUi(this);

    // TODO rewrite to store list of all languages (with their options) as global settings
    addLanguage("Arabic", ":/resources/lang_icons/sa.png");
    addLanguage("English", ":/resources/lang_icons/us.png");
    addLanguage("French", ":/resources/lang_icons/fr.png");
    addLanguage("German", ":/resources/lang_icons/de.png");
    addLanguage("Italian", ":/resources/lang_icons/it.png");
    addLanguage("Japanese", ":/resources/lang_icons/jp.png");
    addLanguage("Korean", ":/resources/lang_icons/kr.png");
    addLanguage("Portuguese", ":/resources/lang_icons/pt.png");
    addLanguage("Russian", ":/resources/lang_icons/ru.png");
    addLanguage("Spanish", ":/resources/lang_icons/es.png");
    addLanguage("Ukrainian", ":/resources/lang_icons/ua.png");
}

DownloadLanguageForm::~DownloadLanguageForm()
{
    delete ui;
}

void DownloadLanguageForm::showForm()
{
    this->show();
}

void DownloadLanguageForm::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}

void DownloadLanguageForm::addLanguage(QString name, QString iconPath)
{
    DownloadLanguageItem *downloadLanguageItem = new DownloadLanguageItem(name, iconPath);
    connect(downloadLanguageItem, SIGNAL(downloadStart()), this, SLOT(downloadStart()));
    connect(downloadLanguageItem, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(onDownloadProgress(qint64,qint64)));

    QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);

    ui->listWidget->addItem(listItem);
    ui->listWidget->setItemWidget(listItem, downloadLanguageItem );

    listItem->setSizeHint(QSize(downloadLanguageItem->width(),downloadLanguageItem->height()));
}

void DownloadLanguageForm::downloadStart()
{
    ui->progressBar->reset();
    ui->progressBar->setFormat("Downloaded: %p%");
}


void DownloadLanguageForm::onDownloadProgress(qint64 bytesRead,qint64 bytesTotal) {
    ui->progressBar->setValue(static_cast<int>(100.0 * bytesRead / bytesTotal));
    //qDebug(QString::number(bytesRead).toLatin1() +" - "+ QString::number(bytesTotal).toLatin1());
}
