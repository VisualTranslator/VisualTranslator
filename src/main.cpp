#include <QtWidgets>
#include "visualtranslator.h"
#include "app.h"

// Entry point for the app
int main(int argc, char *argv[])
{
    App a(argc, argv, "Organization", "VisualTranslator");
    VisualTranslator *pVisualTranslator = new VisualTranslator;

    return a.exec();
}
