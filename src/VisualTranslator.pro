#-------------------------------------------------
#
# Project created by QtCreator 2017-04-28T09:30:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisualTranslator
TEMPLATE = app

SOURCES += main.cpp \
    visualtranslator.cpp \
    tray.cpp

HEADERS  += \
    visualtranslator.h \
    tray.h

FORMS    +=
include(qhotkey.pri)


RESOURCES += \
    resources.qrc

DISTFILES +=
