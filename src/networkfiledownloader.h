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

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QFile *file;

signals:

public slots:

private slots:
    void onDownloadProgress(qint64,qint64);
    void onFinished(QNetworkReply*);
    void onReadyRead();
    void onReplyFinished();
};

#endif // NETWORKFILEDOWNLOADER_H
