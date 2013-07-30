#-------------------------------------------------
#
# Project created by QtCreator 2013-06-05T06:57:18
#
#-------------------------------------------------

QT       += core gui
QT += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BF
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    eksportuj.cpp \
    wyszukaj.cpp \
    oprog.cpp \
    drukuj.cpp

HEADERS  += mainwindow.h \
    film_ftbl_class.h \
    Unmngd.h \
    eksportuj.h \
    version.h \
    wyszukaj.h \
    oprog.h \
    drukuj.h

FORMS    += mainwindow.ui \
    eksportuj.ui \
    wyszukaj.ui \
    oprog.ui \
    drukuj.ui

RESOURCES += \
    res.qrc

RC_FILE += \
    bf.rc
