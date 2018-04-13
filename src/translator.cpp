#include "translator.h"

Translator::Translator(QObject *parent) : QObject(parent)
{
    qNetwork = new QNetworkAccessManager;
    connect(qNetwork, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleNetworkData(QNetworkReply*)));
}

void Translator::translate(QString text)
{
    QNetworkConfigurationManager *configManager = new QNetworkConfigurationManager();
    if (!configManager->isOnline()) {
        emit error("No Internet connection");
    } else {
        QString langFrom = Language::getGoogleName(App::theApp()->settings()->value("Settings/Languages/from", "Auto").toString());
        QString langTo = Language::getGoogleName(App::theApp()->settings()->value("Settings/Languages/to", "English").toString());
        original = text;
        QString encodedText = QString(QUrl(text).toEncoded()).remove("&");

        QString url = QString("http://translate.googleapis.com/translate_a/single?client=gtx&sl=%1&tl=%2&dt=t&q=%3").arg(langFrom).arg(langTo).arg(encodedText);
        QNetworkRequest request(url);
        qNetwork->get(request);
    }
}

void Translator::handleNetworkData(QNetworkReply *reply)
{
    // receive raw response from Google Translator
    QString strReply = (QString)reply->readAll();

    // parse translated strings from json response
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonArray rows = jsonResponse.array()[0].toArray();
    QString result;

    for (int i = 0; i < rows.size(); i++) {
        result += rows[i].toArray()[0].toString();
    }

    emit translated(original, result);
    reply->deleteLater();
}
