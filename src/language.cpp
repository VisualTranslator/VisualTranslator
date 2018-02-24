#include "language.h"

Language::Language(QObject *parent) : QObject(parent)
{

}

Lang Language::find(QString name) {
    foreach (Lang language, Language::languages) {
        if (language.name == name) return language;
    }

    // return the default language (English) with id 1
    return Language::languages[1];
}

QString Language::getFileName(QString name)
{
    return Language::find(name).shortName + ".traineddata";
}

QString Language::getShortName(QString name)
{
    return Language::find(name).shortName;
}

QString Language::getGoogleName(QString name)
{
    return Language::find(name).googleName;
}

QList<Lang> Language::languages = QList<Lang>(
    {
        {
            "Arabic",
            "ara",
            "ar",
        },
        {
            "English",
            "eng",
            "en",
        },
        {
            "French",
            "fra",
            "fr",
        },
        {
            "German",
            "deu",
            "de",
        },
        {
            "Italian",
            "ita",
            "it",
        },
        {
            "Japanese",
            "jpn",
            "ja",
        },
        {
            "Korean",
            "kor",
            "ko",
        },
        {
            "Portuguese",
            "por",
            "pt",
        },
        {
            "Russian",
            "rus",
            "ru",
        },
        {
            "Spanish",
            "spa",
            "es",
        },
        {
            "Ukrainian",
            "ukr",
            "uk",
        },
    }
);
