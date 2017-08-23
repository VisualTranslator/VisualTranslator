#-------------------------------------------------
#
# Project created by QtCreator 2017-04-28T09:30:02
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisualTranslator
TEMPLATE = app


SOURCES += main.cpp \
    visualtranslator.cpp \
    tray.cpp \
    app.cpp \
    screenarea.cpp \
    recognizer.cpp \
    translator.cpp

HEADERS  += \
    visualtranslator.h \
    tray.h \
    app.h \
    screenarea.h \
    recognizer.h \
    translator.h

FORMS    +=
include(qhotkey.pri)


RESOURCES += \
    resources.qrc

DISTFILES +=

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../MinGW/lib/ -llept
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../MinGW/lib/ -llept
#else:unix: LIBS += -L$$PWD/../../../../../MinGW/lib/ -llept

#INCLUDEPATH += $$PWD/../../../../../MinGW/include/leptonica
#DEPENDPATH += $$PWD/../../../../../MinGW/include/leptonica

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../MinGW/lib/ -ltesseract
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../MinGW/lib/ -ltesseract
#else:unix: LIBS += -L$$PWD/../../../../../MinGW/lib/ -ltesseract

#INCLUDEPATH += $$PWD/../../../../../MinGW/include/tesseract
#DEPENDPATH += $$PWD/../../../../../MinGW/include/tesseract

unix|win32: LIBS += -L$$PWD/Leptonica/lib/ -llept

INCLUDEPATH += $$PWD/Leptonica/include
DEPENDPATH += $$PWD/Leptonica/include

unix|win32: LIBS += -L$$PWD/Tesseract/lib/ -ltesseract

INCLUDEPATH += $$PWD/Tesseract/include
DEPENDPATH += $$PWD/Tesseract/include
