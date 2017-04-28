#include <QtWidgets>
#include "visualtranslator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VisualTranslator *pVisualTranslator = new VisualTranslator;

    pVisualTranslator->show();

    return a.exec();
}
