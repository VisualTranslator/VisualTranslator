#include "translator.h"

Translator::Translator(QObject *parent) : QObject(parent)
{
    qNetwork = new QNetworkAccessManager;
    connect(qNetwork, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleNetworkData(QNetworkReply*)));
}

void Translator::start(char *&text)
{
    //TODO allow to change sl (from lang) and dt(to lang)
    QString url = QString("http://translate.googleapis.com/translate_a/single?client=gtx&sl=en&tl=uk&dt=t&q=%1").arg(*&text);
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
