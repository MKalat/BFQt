#include "wyszukaj.h"
#include "ui_wyszukaj.h"

#include "film_ftbl_class.h"


Ftbl flm_wysz;
QList<unsigned int> ids_wynik;

Wyszukaj::Wyszukaj(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wyszukaj)
{

    ui->setupUi(this);

}

Wyszukaj::~Wyszukaj()
{
    delete ui;
}



void Wyszukaj::on_pushButton_Search_clicked()
{
        int poz;
        poz = ui->comboBox_Pole->currentIndex();
        wchar_t szf[501];
        wcscpy(szf, (wchar_t *) ui->lineEdit_Fraza->text().utf16());
        ui->tableWidget_Wyniki->setRowCount(0);


        wchar_t *pdest;

        QFile plik(QString::fromWCharArray(flm_wysz.pths.BF_PDB));
        plik.open(QFile::ReadOnly);
        unsigned int stop;
        unsigned int x;
        stop = plik.size();

        switch (poz)
        {
        case 0:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.tytul,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 1:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.oryginalny_tytul,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 2:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.gatunek_filmu,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 3:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.WOF_sciezka_dz,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 4:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.WOF_zdjecia,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 5:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.WOF_obsada,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 6:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.WOF_w_art,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 7:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.WOF_calosc,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 8:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.O_rezyser_imie_nazw,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 9:
        for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.O_rezyser_narod,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 10:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.O_operator_imie_nazw,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 11:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.O_operator_narod,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 12:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.O_muzyka_imie_nazw,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 13:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.O_muzyka_narod,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 14:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.O_scenariusz_imie_nazw,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 15:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.O_scenariusz_narod,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 16:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_WKF_imie,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 17:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_WKF_nazwisko,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 18:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_WKF_adres,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 19:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_MN_nazwa,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 20:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_MN_adres,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 21:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_MN_telefon,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 22:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_MN_fax,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 23:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_MN_email,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 24:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_MN_www,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 25:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_cena,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 26:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_data_zakupu,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 27:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_data_skatalogowania,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 28:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_wartosc_akt,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 29:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_data_utraty,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 30:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_Nr_kat,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 31:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.DOE_rodzaj_nosnika,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 32:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_rok_produkcji,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 33:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_data_premiery,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 34:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_czas_trwania,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 35:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_format_wysw,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 36:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_system_kodowania_obrazu,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 37:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_jezyk_lektora,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 38:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_jezyk_napisow,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 39:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_KODEK_nazwa,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 40:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_KODEK_typ,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 41:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_KODEK_wersja,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 42:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_DZWIEK_nazwa,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 43:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_DZWIEK_typ,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 44:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_DZWIEK_wersja,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 45:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_ZABEZP_nazwa,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 46:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_ZABEZP_typ,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 47:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_ZABEZP_wersja,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;
        case 48:
            for (x=0;x<stop; )
            {
                plik.seek(x);
                plik.read(reinterpret_cast<char *>(&flm_wysz.film_tbl),sizeof(struct Film));
                pdest = wcsstr(flm_wysz.film_tbl.IOF_kraj_produkcji_filmu,szf);
                if (pdest != NULL)
                {
                    Fill_details(x);
                }
                x = x + (sizeof(struct Film));
            }
            break;


        }
        plik.close();

}

void Wyszukaj::on_pushButton_Cancel_clicked()
{
    this->close();
}

void Wyszukaj::on_tableWidget_Wyniki_cellClicked(int row, int column)
{
    emit ustaw_rec(ids_wynik[row]);
}
void Wyszukaj::Fill_details(unsigned int pos)
{
    ui->tableWidget_Wyniki->insertRow(ui->tableWidget_Wyniki->rowCount());
    ids_wynik.append(pos);

    QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromWCharArray(flm_wysz.film_tbl.tytul));
    ui->tableWidget_Wyniki->setItem(ui->tableWidget_Wyniki->rowCount()-1,0,item1);

    QTableWidgetItem *item2 = new QTableWidgetItem(QString::fromWCharArray(flm_wysz.film_tbl.gatunek_filmu));
    ui->tableWidget_Wyniki->setItem(ui->tableWidget_Wyniki->rowCount()-1,1,item2);

    QTableWidgetItem *item3 = new QTableWidgetItem(QString::fromWCharArray(flm_wysz.film_tbl.IOF_data_premiery));
    ui->tableWidget_Wyniki->setItem(ui->tableWidget_Wyniki->rowCount()-1,2,item3);


}
