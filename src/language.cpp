#include "language.h"

Language::Language(QObject *parent) : QObject(parent)
{

}

Lang Language::find(QString name) {
    foreach (Lang language, Language::languages) {
        if (language.name == name) return language;
    }

    // return the default language (English) with id 2
    return Language::languages[2];
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

QString Language::getIconPath(QString name)
{
    return ":resources/lang_icons/" + Language::find(name).shortName + ".png";
}

QString Language::getOriginalName(QString name)
{
    return Language::find(name).originalName;
}

QList<Lang> Language::languages = QList<Lang>(
{
                {
                    "Auto",
                    "auto",
                    "auto",
                    "Auto",
                },
                {
                    "Arabic",
                    "ara",
                    "ar",
                    "العربية",
                },
                {
                    "English",
                    "eng",
                    "en",
                    "English",
                },
                {
                    "French",
                    "fra",
                    "fr",
                    "Français",
                },
                {
                    "German",
                    "deu",
                    "de",
                    "Deutsch",
                },
                {
                    "Italian",
                    "ita",
                    "it",
                    "Italiano",
                },
                {
                    "Japanese",
                    "jpn",
                    "ja",
                    "日本語",
                },
                {
                    "Korean",
                    "kor",
                    "ko",
                    "한국어",
                },
                {
                    "Portuguese",
                    "por",
                    "pt",
                    "Português",
                },
                {
                    "Russian",
                    "rus",
                    "ru",
                    "Русский",
                },
                {
                    "Spanish",
                    "spa",
                    "es",
                    "Español",
                },
                {
                    "Ukrainian",
                    "ukr",
                    "uk",
                    "Українська",
                },
            }
            );
