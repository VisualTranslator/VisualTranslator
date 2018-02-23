#ifndef NETWORKFILEDOWNLOADER_H
#define NETWORKFILEDOWNLOADER_H

#include <QObject>
#include <QtWidgets>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

class NetworkFileDownloader : public QObject
{
    Q_OBJECT
public:
    explicit NetworkFileDownloader(QObject *parent = nullptr);
    void download(QString url);
    QNetworkReply *reply;

private:
    QFile *file;
    QString url;
    bool isDownloading;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;

signals:
    void downloadFinished(QNetworkReply*, QString);
    void downloadProgress(qint64 bytesRead, qint64 bytesTotal);

public slots:

private slots:
    void onReadyRead();
    void onReplyFinished();
    void onDownloadFinished(QNetworkReply *reply);
    void onDownloadProgress(qint64 bytesRead, qint64 bytesTotal);
};

#endif // NETWORKFILEDOWNLOADER_H
