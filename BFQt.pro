#-------------------------------------------------
#
# Project created by QtCreator 2013-06-05T06:57:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BF
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    eksportuj.cpp \
    wyszukaj.cpp \
    oprog.cpp

HEADERS  += mainwindow.h \
    film_ftbl_class.h \
    Unmngd.h \
    eksportuj.h \
    version.h \
    wyszukaj.h \
    oprog.h

FORMS    += mainwindow.ui \
    eksportuj.ui \
    wyszukaj.ui \
    oprog.ui

RESOURCES += \
    res.qrc

RC_FILE += \
    bf.rc
