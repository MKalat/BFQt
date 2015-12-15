#include "mainwindow.h"
#include <QtWidgets>
#include <QtWidgets/QApplication>
#include <QTranslator>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1250"));
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
    QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    myappTranslator.load("bf_" + QLocale::system().name());
    a.installTranslator(&myappTranslator);
    MainWindow w;
    w.show();
    
    return a.exec();
}
