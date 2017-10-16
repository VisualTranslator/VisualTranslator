#ifndef DOWNLOADLANGUAGEITEM_H
#define DOWNLOADLANGUAGEITEM_H

#include <QWidget>

namespace Ui {
class DownloadLanguageItem;
}

class DownloadLanguageItem : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadLanguageItem(QString name, QString iconPath, QWidget *parent = 0);
    ~DownloadLanguageItem();

private:
    Ui::DownloadLanguageItem *ui;
};

#endif // DOWNLOADLANGUAGEITEM_H
