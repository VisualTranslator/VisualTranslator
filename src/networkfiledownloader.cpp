#include "networkfiledownloader.h"

NetworkFileDownloader::NetworkFileDownloader(QObject *parent) : QObject(parent)
{
    this->manager = new QNetworkAccessManager;
}

void NetworkFileDownloader::download(QString url)
{
    qDebug() << QSslSocket::supportsSsl();
    QStringList filePathList = url.split('/');
    QString fileName = filePathList.at(filePathList.count() - 1);
    QString saveFilePath = QString(qApp->applicationDirPath() + "/tessdata/" + fileName);

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    reply = manager->get(request);

    file = new QFile;
    file->setFileName(saveFilePath);
    file->open(QIODevice::WriteOnly);

    connect(reply,SIGNAL(readyRead()),this, SLOT(onReadyRead()));
    connect(reply,SIGNAL(finished()), this, SLOT(onReplyFinished()));
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
