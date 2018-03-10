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

unix|win32: LIBS += -L$$PWD/'Leptonica/lib/' -lleptonica-1.74.4
unix|win32: LIBS += -L$$PWD/'Tesseract/lib/' -ltesseract400

INCLUDEPATH += $$PWD/'Leptonica/include/'
INCLUDEPATH += $$PWD/'Tesseract/include/'

DEPENDPATH += $$PWD/'Leptonica/include/'
DEPENDPATH += $$PWD/'Tesseract/include/'
