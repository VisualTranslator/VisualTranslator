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
    tray.cpp \
    app.cpp \
    screenarea.cpp \
    recognizer.cpp \
    translator.cpp \
    settingsform.cpp \
    downloadlanguageform.cpp \
    downloadlanguageitem.cpp \
    networkfiledownloader.cpp \
    language.cpp \
    translationresultform.cpp

HEADERS  += \
    visualtranslator.h \
    tray.h \
    app.h \
    screenarea.h \
    recognizer.h \
    translator.h \
    settingsform.h \
    downloadlanguageform.h \
    downloadlanguageitem.h \
    networkfiledownloader.h \
    language.h \
    translationresultform.h

FORMS    += \
    settingsform.ui \
    downloadlanguageform.ui \
    downloadlanguageitem.ui \
    translationresultform.ui
include(qhotkey.pri)


RESOURCES += \
    resources.qrc

DISTFILES +=

unix|win32: LIBS += -L$$PWD/'Leptonica/lib/' -lleptonica-1.74.4
unix|win32: LIBS += -L$$PWD/'Tesseract/lib/' -ltesseract400

INCLUDEPATH += $$PWD/'Leptonica/include/'
INCLUDEPATH += $$PWD/'Tesseract/include/'

DEPENDPATH += $$PWD/'Leptonica/include/'
DEPENDPATH += $$PWD/'Tesseract/include/'
