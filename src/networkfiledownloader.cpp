#include "networkfiledownloader.h"

NetworkFileDownloader::NetworkFileDownloader(QObject *parent) : QObject(parent)
{
}

void NetworkFileDownloader::download(QString url)
{
    this->url = url;

    QStringList filePathList = url.split('/');
    QString fileName = filePathList.at(filePathList.count() - 1);
    QString saveFilePath = QString(qApp->applicationDirPath() + "/tessdata/" + fileName);

    QNetworkRequest request;
    manager = new QNetworkAccessManager;
    request.setUrl(QUrl(url));
    reply = manager->get(request);

    file = new QFile;
    file->setFileName(saveFilePath);
    file->open(QIODevice::WriteOnly);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this, SLOT(onDownloadFinished(QNetworkReply*)));
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this, SLOT(onDownloadProgress(qint64,qint64)));
    connect(reply,SIGNAL(readyRead()),this, SLOT(onReadyRead()));
    connect(reply,SIGNAL(finished()), this, SLOT(onReplyFinished()));
}

void NetworkFileDownloader::onDownloadProgress(qint64 bytesRead, qint64 bytesTotal)
{
    emit downloadProgress(bytesRead, bytesTotal);
}

void NetworkFileDownloader::onDownloadFinished(QNetworkReply* reply)
{
    emit downloadFinished(reply, this->url);
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
