#include "drukuj.h"
#include "ui_drukuj.h"

#include "film_ftbl_class.h"
#include "Unmngd.h"

Ftbl flm_d;

Drukuj::Drukuj(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Drukuj)
{
    ui->setupUi(this);
}

Drukuj::~Drukuj()
{
    delete ui;
}

void Drukuj::on_pushButton_Print_clicked()
{
	if (ui->radioButton_Akt->isChecked == true)
	{
		QFile fn_exp(QString("wydruk.html");
		fn_exp.open(QFile::Append | QFile::Text);
		QTextStream fnout(&fn_exp);

		fnout << QString::fromWCharArray(L"<!DOCTYPE HTML><html><head><title>Biblioteka Filmów - Wydruk danych z bazy - http://mkalat.pl</title><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"><style type=\"text/css\">p {font-family: Verdana, Arial, Helvetica, sans-serif;font-size: 12px;line-height : 1%;}</style></head><body><h1>").toLocal8Bit() << "\n";
		fnout << QString::fromWCharArray(flm_d.film_tbl.tytul);
		fnout << QString::fromWCharArray(L"</h1><table ><tr><td><img src=\"").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.skan_przod_path);
		fnout << QString::fromWCharArray(L"\" alt=\"\"></td></tr><tr><td><p>Oryginalny tytu³ : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.oryginalny_tytul);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Gatunek : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.gatunek_filmu);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Rok produkcji : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_rok_produkcji);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data premiery : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_data_premiery);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Czas projekcji : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_czas_trwania);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Jêzyk lektora : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_jezyk_lektora);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Jêzyk napisów : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_jezyk_napisow);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Format wyœwietlania : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_format_wysw);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>System kodowania obrazu : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_system_kodowania_obrazu);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kraj produkcji filmu : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_kraj_produkcji_filmu);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Cena : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_cena);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Wartoœæ aktualna : </p></td><td><p>").toLocal8Bit;
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_wartosc_akt);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data zakupu : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_data_zakupu);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data utraty : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_data_utraty);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data skatalogowania : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_data_skatalogowania);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Noœnik : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_rodzaj_nosnika);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Muzyka : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.WOF_sciezka_dz);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Obsada : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.WOF_obsada);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Zdjêcia : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.WOF_zdjecia);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Wartoœæ artystyczna : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.WOF_w_art);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Ca³oœæ : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.WOF_calosc);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Nr Kat : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_Nr_kat);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>W³aœciciel - Imiê : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_WKF_imie);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>W³aœciciel - Nazwisko : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_WKF_nazwisko);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>W³aœciciel - Adres : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_WKF_adres);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Nazwa : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_nazwa);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Adres : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_adres);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Telefon : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_telefon);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - email : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_email);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - WWW : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_www);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Fax : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_fax);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek wideo - Nazwa : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_KODEK_nazwa);
		fbout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek wideo - typ : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_KODEK_typ);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek wideo - wersja : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_KODEK_wersja);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Zabezpieczenia - Nazwa : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_ZABEZP_nazwa);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Zabezpieczenia - typ : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_ZABEZP_typ);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Zabezpieczenia - wersja : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_ZABEZP_wersja);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek audio - Nazwa : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_DZWIEK_nazwa);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek audio - typ : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_DZWIEK_typ);
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek audio - wersja : </p></td><td><p>").toLocal8Bit();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_DZWIEK_wersja);
		fnout << QString::fromWCharArray(L"</p></td></tr></table>").toLocal8Bit();


	}
	else if (ui->radioButton_All->isChecked == true)
	{
		
	}
}

void Drukuj::on_pushButton_Cancel_clicked()
{
	this->close();
}
