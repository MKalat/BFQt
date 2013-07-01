#-------------------------------------------------
#
# Project created by QtCreator 2013-06-05T06:57:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BFQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    eksportuj.cpp

HEADERS  += mainwindow.h \
    film_ftbl_class.h \
    Unmngd.h \
    eksportuj.h

FORMS    += mainwindow.ui \
    eksportuj.ui

RESOURCES += \
    res.qrc
