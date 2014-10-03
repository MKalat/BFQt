#include "ImpBFNETWiz.h"
#include "ui_ImpBFNETWiz.h"

#include "film_ftbl_class.h"

#include <windows.h>
#include <iostream>
#include <direct.h>

Ftbl flm_impbf;

ImpBFNETWiz::ImpBFNETWiz(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::ImpBFNETWiz)
{
    ui->setupUi(this);
}

ImpBFNETWiz::~ImpBFNETWiz()
{
	delete ui;
}

void ImpBFNETWiz::BTN_IMP_CLICKED()
{
    if (QFile::exists(ui->lineEdit_csv_BFNET->text()))
    {
        QFile file(ui->lineEdit_csv_BFNET->text());
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            emit clearCTRLS(true);
            QString line = file.readLine();
            line = file.readLine();
            line = file.readLine();
            line = file.readLine();
            line = file.readLine();
            while (!file.atEnd())
            {
                line = file.readLine();
                QStringList strings = line.split(",");
                wchar_t buff;
                QString cur_s_id; // set the Id from csv
                strings.value(0).toWCharArray(&buff); // skopiuj zawartość rekordu film z csv fo film_table
                wcscpy(flm_impbf.film_tbl.tytul,&buff);
                strings.value(2).toWCharArray(&buff);
                wcscpy(flm_impbf.film_tbl.gatunek_filmu,&buff);

                int new_db_id;
                emit add_new_film_rec(&new_db_id); // dodaj rekord fil i pobierz nowe id przydzielone do tego filmu
                if (ui->checkBox_Obsada->isChecked())
                {


                }
                if (ui->checkBox_Ocena->isChecked())
                {


                }
                if (ui->checkBox_Dyst->isChecked())
                {


                }
                if (ui->checkBox_Prod->isChecked())
                {


                }
                if (ui->checkBox_LZ->isChecked())
                {
                    processSubTable("LZ", new_db_id, cur_s_id);

                }
                if (ui->checkBox_Wyp->isChecked())
                {

                }

            }
            file.close();
            Ftbl::add_new_oc = true;
            Ftbl::add_new_lz = true;
            Ftbl::add_new_ob = true;
            Ftbl::add_new_pd = true;
            Ftbl::add_new_pp = true;
            Ftbl::add_new_wi = true;
            Ftbl::add_new_wo = true;
            unsigned int zad_pos_film;
            emit SearchLastFilmPos(&zad_pos_film);
            emit SetZadanaPozPliku(zad_pos_film);
            emit save_full_F();
        }


    }


}
void ImpBFNETWiz::BTN_CANCEL_CLICKED()
{
	this->close();
}
void ImpBFNETWiz::BTN_SEL_PATH_CLICKED()
{
	QFileDialog fdlg(this);
	fdlg.setFileMode(QFileDialog::AnyFile);
    fdlg.setViewMode(QFileDialog::Detail);
    fdlg.setNameFilter(tr("Comma Separated Values file (*.csv )"));
	fdlg.setAcceptMode(QFileDialog::AcceptOpen);
    if (fdlg.exec())
    {
        QString dir_path = fdlg.selectedFiles().at(0);
		ui->lineEdit_csv_BFNET->setText(dir_path);
    }

}
void ImpBFNETWiz::processSubTable(QString sb_tbl, int new_id, QString csv_id)
{
    QFile file_sb(ui->lineEdit_csv_BFNET->text());
    if (file_sb.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        if (sb_tbl == "LZ")
        {
            flm_impbf.lz_arr.clear();
            while (!file_sb.atEnd())
            {
                bool set_pos = false;
                QString line_sb = file_sb.readLine();
                if (line_sb == "Dane Tabeli Lokalizacje Zdjęciowe :")
                {
                    set_pos = true;
                }
                if (set_pos)
                {
                    if (line_sb.contains(csv_id))
                    {
                        QStringList strings_sb = line_sb.split(",");
                        int lz_new_id;
                        emit get_hi_LZ_id(&lz_new_id);
                        flm_impbf.lz.ID = lz_new_id;
                        flm_impbf.lz.IDPDB = new_id;
                        wchar_t *buff;
                        strings_sb.value(3).toWCharArray(buff);
                        wcscpy(flm_impbf.lz.nazwa_obiektu,buff);
                        strings_sb.value(4).toWCharArray(buff);
                        wcscpy(flm_impbf.lz.kraj,buff);
                        strings_sb.value(5).toWCharArray(buff);
                        wcscpy(flm_impbf.lz.miejscowosc,buff);
                        strings_sb.value(6).toWCharArray(buff);
                        wcscpy(flm_impbf.lz.region,buff);
                        strings_sb.value(7).toWCharArray(buff);
                        wcscpy(flm_impbf.lz.pora_roku,buff);
                        strings_sb.value(8).toWCharArray(buff);
                        wcscpy(flm_impbf.lz.data,buff);

                        flm_impbf.lz_arr.append(flm_impbf.lz);

                    }
                }
            }
        }
        else if (sb_tbl == "OC")
        {

        }
        else if (sb_tbl == "OB")
        {

        }
        else if (sb_tbl == "WI")
        {

        }
        else if (sb_tbl == "WO")
        {

        }
        else if (sb_tbl == "PP")
        {

        }
        else if (sb_tbl == "PD")
        {

        }
    }
}

