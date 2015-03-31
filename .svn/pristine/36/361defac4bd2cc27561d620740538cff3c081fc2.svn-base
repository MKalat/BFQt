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
    void Eksportuj_data_MAIN(struct Film* flm_ptr, bool head_wrttn, bool html_end);
    void Eksportuj_data_WON(struct Wypozycz_Od_Innych* wo_ptr, bool head_wrttn, bool html_end);
	void Eksportuj_data_WIN(struct Wypozycz_Innym* wi_ptr, bool head_wrttn, bool html_end);
	void Eksportuj_data_LZ(struct Lok_zdjeciowe* lz_ptr, bool head_wrttn, bool html_end);
	void Eksportuj_data_PD(struct Dystrybutor* pd_ptr, bool head_wrttn, bool html_end);
	void Eksportuj_data_PP(struct Producent* pp_ptr, bool head_wrttn, bool html_end);
	void Eksportuj_data_OB(struct Obsada* ob_ptr, bool head_wrttn, bool html_end);
	void Eksportuj_data_OC(struct Ocena* oc_ptr, bool head_wrttn, bool html_end);


    
private slots:
    void on_pushButton_GetPath_clicked();

    void on_pushButton_Eksport_clicked();

    void on_pushButton_Anuluj_clicked();

private:
    Ui::Eksportuj *ui;
};

#endif // EKSPORTUJ_H
