#include "translator.h"

Translator::Translator(QObject *parent) : QObject(parent)
{
    qNetwork = new QNetworkAccessManager;
    connect(qNetwork, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleNetworkData(QNetworkReply*)));
}

void Translator::start(char *&text)
{
    QString langFrom = App::theApp()->settings()->value("Settings/Languages/from").toString();
    QString langTo = App::theApp()->settings()->value("Settings/Languages/to").toString();

    QString url = QString("http://translate.googleapis.com/translate_a/single?client=gtx&sl=%1&tl=%2&dt=t&q=%3").arg(langFrom).arg(langTo).arg(*&text);
    QNetworkRequest request(url);
    qNetwork->get(request);
}

void Translator::handleNetworkData(QNetworkReply *reply)
{
    // receive raw responce from Google Translator
    QString strReply = (QString)reply->readAll();

    // parse the string with RegExp to receive only needed part
    QRegExp rx("\"([^\"]*)\"");
    rx.indexIn(strReply);
    QString result = rx.capturedTexts()[1];

    emit showResult(result);
    reply->deleteLater();
}
