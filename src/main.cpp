#include <QtWidgets>
#include "visualtranslator.h"
#include "app.h"

// Entry point for the app
int main(int argc, char *argv[])
{
    App a(argc, argv, "VisualTranslator", "VisualTranslator");

    VisualTranslator *pVisualTranslator = new VisualTranslator;

    // Run the program only if it not will be updated
    if (!pVisualTranslator->willBeUpdated()) {
        return a.exec();
    }
}
