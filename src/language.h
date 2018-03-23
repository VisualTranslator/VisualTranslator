#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QObject>
#include <QtWidgets>

struct Lang
{
  QString name;
  QString shortName;
  QString googleName;
  QString originalName;
};

class Language : public QObject
{
public:
    explicit Language(QObject *parent = nullptr);
    static QList<Lang> languages;

    // Helper methods
    static QString getFileName(QString name);
    static QString getGoogleName(QString name);
    static QString getIconPath(QString name);
    static QString getNameByUrl(QString url);
    static QString getOriginalName(QString name);
    static QString getShortName(QString name);
    static QString getUrl(QString name);

private:
    static Lang find(QString name);
};

#endif // LANGUAGE_H
