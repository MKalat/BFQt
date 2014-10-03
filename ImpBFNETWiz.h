#ifndef IMPBFNETWIZHP1164_H
#define IMPBFNETWIZHP1164_H

#include <QDialog>
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
class ImpBFNETWiz;
}

class ImpBFNETWiz : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImpBFNETWiz(QDialog *parent = 0);
    ~ImpBFNETWiz();
    void processSubTable(QString sb_tbl, int new_id, QString csv_id);
signals :
    void save_full_F();
    void add_new_film_rec(int *new_id);
    void get_hi_LZ_id(int *new_id);
    void get_hi_OC_id(int *new_id);
    void get_hi_OB_id(int *new_id);
    void get_hi_PP_id(int *new_id);
    void get_hi_PD_id(int *new_id);
    void get_hi_WI_id(int *new_id);
    void get_hi_WO_id(int *new_id);
    void new_rec_F();
    void new_rec_LZ();
    void new_rec_OC();
    void new_rec_OB();
    void new_rec_PP();
    void new_rec_PD();
    void new_rec_WI();
    void new_rec_WO();
    void clearCTRLS(bool all);
    void SetZadanaPozPliku(unsigned int pos);
    void SearchLastFilmPos(unsigned int *pos);

public slots:
	void BTN_IMP_CLICKED();
	void BTN_CANCEL_CLICKED();
	void BTN_SEL_PATH_CLICKED();


private:
    Ui::ImpBFNETWiz *ui;
};

#endif // IMPBFNETWIZHP1164_H
