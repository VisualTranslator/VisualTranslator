#-------------------------------------------------
#
# Project created by QtCreator 2017-04-28T09:30:02
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets \
                                        network

TARGET = VisualTranslator
TEMPLATE = app


SOURCES += main.cpp \
    visualtranslator.cpp \
    app.cpp \
    screenarea.cpp \
    recognizer.cpp \
    translator.cpp \
    settingsform.cpp \
    language.cpp \
    translationresultform.cpp \
    shortcutsetupform.cpp \
    languageqcombobox.cpp \
    trayform.cpp

HEADERS  += \
    visualtranslator.h \
    app.h \
    screenarea.h \
    recognizer.h \
    translator.h \
    settingsform.h \
    language.h \
    translationresultform.h \
    shortcutsetupform.h \
    languageqcombobox.h \
    trayform.h

FORMS    += \
    settingsform.ui \
    translationresultform.ui \
    shortcutsetupform.ui \
    trayform.ui

include(vendor/vendor.pri)

RESOURCES += \
    resources.qrc

DISTFILES +=

unix|win32: LIBS += -L$$PWD/'../vendor/lib/' -lleptonica-1.74.4
unix|win32: LIBS += -L$$PWD/'../vendor/lib/' -ltesseract400

INCLUDEPATH += $$PWD/'../vendor/include/leptonica'
INCLUDEPATH += $$PWD/'../vendor/include/tesseract'

DEPENDPATH += $$PWD/'../include/leptonica'
DEPENDPATH += $$PWD/'../include/tesseract'

CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/../VisualTranslatorDebug
} else {
    DESTDIR = $$OUT_PWD/../VisualTranslatorRelease
}

# Copies the given files to the destination directory
defineTest(copyToDestdir) {
    files = $$1
    DDIR = $$DESTDIR/$$2

    for(FILE, files) {
        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}

win32 {
    # Run windeployqt to copy all additional dependencies
    QMAKE_POST_LINK += $$(QTDIR)/bin/windeployqt $$OUT_PWD/../VisualTranslatorDebug $$escape_expand(\\n\\t)

    # Copy all the dll's files
    copyToDestdir($$files($$PWD/../vendor/dll/*), "")

    # Create tessdata directory and copy all tessdata files
    QMAKE_POST_LINK += $${QMAKE_MKDIR} $$shell_path($${DESTDIR}/tessdata) $$escape_expand(\\n\\t)
    copyToDestdir($$files($$PWD/tessdata/*), "tessdata/")    # Run windeployqt to add all additional dependencies
}


