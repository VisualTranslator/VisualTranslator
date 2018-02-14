#ifndef DOWNLOADLANGUAGEITEM_H
#define DOWNLOADLANGUAGEITEM_H

#include <QWidget>
#include <networkfiledownloader.h>

namespace Ui {
class DownloadLanguageItem;
}

class DownloadLanguageItem : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadLanguageItem(QString name, QString iconPath, QWidget *parent = 0);
    ~DownloadLanguageItem();

private slots:
    void on_pushButton_clicked();

private:
    QString name;
    Ui::DownloadLanguageItem *ui;
};

#endif // DOWNLOADLANGUAGEITEM_H
