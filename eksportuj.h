#ifndef EKSPORTUJ_H
#define EKSPORTUJ_H

#include <QWidget>
#include <QMainWindow>
#include <QLocale>
#include <QTranslator>
#include <direct.h>
#include <QFileInfo>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QList>
#include <QFileDialog>
#include <windows.h>
#include <iostream>
#include <direct.h>
#include <QTextStream>
#include <QTextCodec>


namespace Ui {
class Eksportuj;
}

class Eksportuj : public QWidget
{
    Q_OBJECT
    
public:
    explicit Eksportuj(QWidget *parent = 0);
    ~Eksportuj();
    void Eksportuj_all();
    void Eksportuj_current();
    
private slots:
    void on_pushButton_GetPath_clicked();

    void on_pushButton_Eksport_clicked();

    void on_pushButton_Anuluj_clicked();

private:
    Ui::Eksportuj *ui;
};

#endif // EKSPORTUJ_H
