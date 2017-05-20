#include "translator.h"

Translator::Translator(QObject *parent) : QObject(parent)
{
    qNetwork = new QNetworkAccessManager;
    connect(qNetwork, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleNetworkData(QNetworkReply*)));
}

void Translator::start(char *&text)
{
    QJsonObject  obj;
    obj.insert("to", QJsonValue::fromVariant("ru"));
    obj.insert("text", QJsonValue::fromVariant(text));

    QJsonDocument doc(obj);
    QByteArray bytes = doc.toJson();

    //connect(qNetwork,SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(handleSSLErrors(QNetworkReply*)));
    QByteArray postDataSize = QByteArray::number(bytes.size());
    QUrl serviceURL("http://www.transltr.org/api/translate");
    QNetworkRequest request(serviceURL);

    request.setRawHeader("User-Agent", "My app name v0.1");
    request.setRawHeader("X-Custom-User-Agent", "My app name v0.1");
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);

    qNetwork->post(request, bytes);
}

void Translator::handleNetworkData(QNetworkReply *reply)
{
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    qDebug() << jsonObject["translationText"].toString();
    emit showResult(jsonObject["translationText"].toString());
    reply->deleteLater();
}
