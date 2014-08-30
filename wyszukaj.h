#ifndef WYSZUKAJ_H
#define WYSZUKAJ_H

#include <QWidget>
#include <QLocale>
#include <QTranslator>
#include <direct.h>
#include <QFileInfo>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QList>
#include <QFileDialog>



namespace Ui {
class Wyszukaj;
}

class Wyszukaj : public QWidget
{
    Q_OBJECT
    
public:
    explicit Wyszukaj(QWidget *parent = 0);
    ~Wyszukaj();

    void Fill_details(unsigned int pos);
signals :
    void ustaw_rec(unsigned int);
    
private slots:


    void on_pushButton_Search_clicked();

    void on_pushButton_Cancel_clicked();

    void on_tableWidget_Wyniki_cellClicked(int row, int column);

private:
    Ui::Wyszukaj *ui;
};

#endif // WYSZUKAJ_H
