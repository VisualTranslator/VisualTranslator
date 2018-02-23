#ifndef DOWNLOADLANGUAGEITEM_H
#define DOWNLOADLANGUAGEITEM_H

#include <QWidget>
#include <language.h>
#include <networkfiledownloader.h>
#include "ui_downloadlanguageitem.h"

namespace Ui {
class DownloadLanguageItem;
}

class DownloadLanguageItem : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadLanguageItem(QString name, QString iconPath, bool isDownloaded, QWidget *parent = 0);
    ~DownloadLanguageItem();
    Ui::DownloadLanguageItem *ui;
    QString name;

private slots:
    void on_pushButton_clicked();

private:
    void downloadButtonClicked();
    void removeButtonClicked();

signals:
    void downloadStart(QString name);
    void languageRemoved(QString name);
};

#endif // DOWNLOADLANGUAGEITEM_H
