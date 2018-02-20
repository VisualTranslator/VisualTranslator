#ifndef DOWNLOADLANGUAGEFORM_H
#define DOWNLOADLANGUAGEFORM_H

#include <QWidget>
#include "downloadlanguageitem.h"
#include <language.h>
#include "ui_downloadlanguageform.h"
#include "ui_downloadlanguageitem.h"

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
    void onDownloadFinished();

private:
    Ui::DownloadLanguageForm *ui;
    void addLanguage(QString name, QString iconPath, bool isDownloaded);
};

#endif // DOWNLOADLANGUAGEFORM_H
