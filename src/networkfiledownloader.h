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
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

private:
    QFile *file;
    bool isDownloading;

signals:

public slots:

private slots:
    void onReadyRead();
    void onReplyFinished();
};

#endif // NETWORKFILEDOWNLOADER_H
