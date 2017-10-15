#include <QtWidgets>
#include "visualtranslator.h"
#include "app.h"

int main(int argc, char *argv[])
{
    App a(argc, argv, "Organization", "VisualTranslator");
    VisualTranslator *pVisualTranslator = new VisualTranslator;

    QFile file(":/resources/stylesheet.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString style(file.readAll());
        a.setStyleSheet(style);
        file.close();
    }
    return a.exec();
}
