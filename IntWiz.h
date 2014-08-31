#ifndef INTWIZ_H
#define INTWIZ_H

#include <QDialog>
#include <QMainWindow>
#include <QLocale>
#include <QTranslator>
#include <direct.h>
#include <QMessageBox>
#include <windows.h>
#include <iostream>



namespace Ui {
class IntWiz;
}

class IntWiz : public QDialog
{
    Q_OBJECT
    
public:
    explicit IntWiz(QWidget *parent = 0);
    ~IntWiz();
    
private slots:
    void on_pushButton_GetData_clicked();
    void on_pushButton_Search_clicked();


private:
    Ui::IntWiz *ui;
};

#endif // INTWIZ_H
