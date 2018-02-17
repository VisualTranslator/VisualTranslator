#ifndef DOWNLOADLANGUAGEFORM_H
#define DOWNLOADLANGUAGEFORM_H

#include <QWidget>
#include "downloadlanguageitem.h"

namespace Ui {
class DownloadLanguageForm;
}

class DownloadLanguageForm : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadLanguageForm(QWidget *parent = 0);
    ~DownloadLanguageForm();

public slots:
    void showForm();
    virtual void closeEvent(QCloseEvent *event);
    void downloadStart();
    void onDownloadProgress(qint64 bytesRead, qint64 bytesTotal);

private:
    Ui::DownloadLanguageForm *ui;
    void addLanguage(QString name, QString iconPath);
};

#endif // DOWNLOADLANGUAGEFORM_H
