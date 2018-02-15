#include "networkfiledownloader.h"

NetworkFileDownloader::NetworkFileDownloader(QObject *parent) : QObject(parent)
{
    this->manager = new QNetworkAccessManager;
}

void NetworkFileDownloader::download(QString url)
{
    QStringList filePathList = url.split('/');
    QString fileName = filePathList.at(filePathList.count() - 1);
    QString saveFilePath = QString(qApp->applicationDirPath() + "/tessdata/" + fileName);

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    reply = manager->get(request);

    file = new QFile;
    file->setFileName(saveFilePath);
    file->open(QIODevice::WriteOnly);

    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(onDownloadProgress(qint64,qint64)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinished(QNetworkReply*)));
    connect(reply,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    connect(reply,SIGNAL(finished()),this,SLOT(onReplyFinished()));
}


void NetworkFileDownloader::onDownloadProgress(qint64 bytesRead,qint64 bytesTotal)
{
    qDebug(QString::number(bytesRead).toLatin1() +" - "+ QString::number(bytesTotal).toLatin1());
}

void NetworkFileDownloader::onFinished(QNetworkReply * reply)
{
    switch(reply->error())
    {
        case QNetworkReply::NoError:
        {
            qDebug("file is downloaded successfully.");
        }break;
        default:{
            qDebug(reply->errorString().toLatin1());
        };
    }

    if(file->isOpen())
    {
        file->close();
        file->deleteLater();
    }
}

void NetworkFileDownloader::onReadyRead()
{
    file->write(reply->readAll());
}

void NetworkFileDownloader::onReplyFinished()
{
    if(file->isOpen())
    {
        file->close();
        file->deleteLater();
    }
}
