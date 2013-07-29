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
	if (ui->radioButton_Akt->isChecked() == true)
	{
		QFile fn_exp(QString::fromWCharArray(L"wydruk.html"));
		fn_exp.open(QFile::WriteOnly | QFile::Text);
		QTextStream fnout(&fn_exp);

		fnout << QString::fromWCharArray(L"<!DOCTYPE HTML><html><head><title>Biblioteka Filmów - Wydruk danych z bazy - http://mkalat.pl</title><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"><style type=\"text/css\">p {font-family: Verdana, Arial, Helvetica, sans-serif;font-size: 12px;line-height : 1%;}</style></head><body><h1>").toUtf8() << "\n";
		fnout << QString::fromWCharArray(flm_d.film_tbl.tytul).toUtf8();
		fnout << QString::fromWCharArray(L"</h1><table ><tr><td><img src=\"").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.skan_przod_path).toUtf8();
		fnout << QString::fromWCharArray(L"\" alt=\"\"></td></tr><tr><td><p>Oryginalny tytu³ : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.oryginalny_tytul).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Gatunek : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.gatunek_filmu).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Rok produkcji : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_rok_produkcji).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data premiery : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_data_premiery).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Czas projekcji : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_czas_trwania).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Jêzyk lektora : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_jezyk_lektora).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Jêzyk napisów : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_jezyk_napisow).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Format wyœwietlania : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_format_wysw).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>System kodowania obrazu : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_system_kodowania_obrazu).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kraj produkcji filmu : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_kraj_produkcji_filmu).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Cena : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_cena).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Wartoœæ aktualna : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_wartosc_akt).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data zakupu : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_data_zakupu).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data utraty : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_data_utraty).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data skatalogowania : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_data_skatalogowania).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Noœnik : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_rodzaj_nosnika).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Muzyka : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.WOF_sciezka_dz).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Obsada : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.WOF_obsada).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Zdjêcia : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.WOF_zdjecia).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Wartoœæ artystyczna : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.WOF_w_art).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Ca³oœæ : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.WOF_calosc).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Nr Kat : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_Nr_kat).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>W³aœciciel - Imiê : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_WKF_imie).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>W³aœciciel - Nazwisko : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_WKF_nazwisko).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>W³aœciciel - Adres : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_WKF_adres).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Nazwa : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_nazwa).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Adres : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_adres).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Telefon : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_telefon).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - email : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_email).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - WWW : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_www).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Fax : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_fax).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek wideo - Nazwa : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_KODEK_nazwa).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek wideo - typ : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_KODEK_typ).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek wideo - wersja : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_KODEK_wersja).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Zabezpieczenia - Nazwa : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_ZABEZP_nazwa).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Zabezpieczenia - typ : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_ZABEZP_typ).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Zabezpieczenia - wersja : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_ZABEZP_wersja).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek audio - Nazwa : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_DZWIEK_nazwa).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek audio - typ : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_DZWIEK_typ).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek audio - wersja : </p></td><td><p>").toUtf8();
		fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_DZWIEK_wersja).toUtf8();
		fnout << QString::fromWCharArray(L"</p></td></tr></table>").toUtf8() << "\n";
		
		
		if (ui->checkBox_OB->isChecked() == true)
		{
			fnout << QString::fromWCharArray(L"<h1>Tabela Obsada</h1><table >").toUtf8() << "\n";
			struct Obsada ob_buff;
			QFile fn_ob(QString::fromWCharArray(flm_d.pths.BF_OB));
			fn_ob.open(QFile::ReadOnly);
			unsigned int stop = fn_ob.size();
			for (unsigned int i = 0; i < stop; )
			{
				fn_ob.seek(i);
				fn_ob.read(reinterpret_cast<char *>(&ob_buff),sizeof(ob_buff));
				if (ob_buff.IDPDB == flm_d.film_tbl.ID)
				{
					fnout << QString::fromWCharArray(L"<tr><td><p>Imiê i Nazwisko : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(ob_buff.imie_nazw).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Rola : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(ob_buff.rola).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr>").toUtf8();
				}
				i = i + sizeof(ob_buff);
			}
			fn_ob.close();
			fnout << QString::fromWCharArray(L"</table>").toUtf8() << "\n"; 
		}
		if (ui->checkBox_OC->isChecked() == true)
		{
			fnout << QString::fromWCharArray(L"<h1>Tabela Ocena</h1><table >").toUtf8() << "\n";
			struct Ocena oc_buff;
			QFile fn_oc(QString::fromWCharArray(flm_d.pths.BF_OC));
			fn_oc.open(QFile::ReadOnly);
			unsigned int stop = fn_oc.size();
			for (unsigned int i = 0; i < stop; )
			{
				fn_oc.seek(i);
				fn_oc.read(reinterpret_cast<char *>(&oc_buff),sizeof(oc_buff));
				if (oc_buff.IDPDB == flm_d.film_tbl.ID)
				{
					fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(oc_buff.nazwa).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Tytu³ tekstu : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(oc_buff.tytul_tekstu).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Autor tekstu : </p></td/><td><p>").toUtf8();
					fnout << QString::fromWCharArray(oc_buff.autor_tekstu).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Strona WWW : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(oc_buff.strona_www).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena krytyka : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(oc_buff.ocena_krytyka).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr>").toUtf8();

				}
				i = i + sizeof(oc_buff);
				
			}
			fn_oc.close();
			fnout << QString::fromWCharArray(L"</table>").toUtf8() << "\n"; 
		}
		if (ui->checkBox_PROD->isChecked() == true)
		{
			fnout << QString::fromWCharArray(L"<h1>Tabela Produkcja</h1><table >").toUtf8() << "\n";
			struct Producent p_buff;
			QFile fn_p(QString::fromWCharArray(flm_d.pths.BF_PRP));
			fn_p.open(QFile::ReadOnly);
			unsigned int stop = fn_p.size();
			for (unsigned int i = 0; i < stop; )
			{
				fn_p.seek(i);
				fn_p.read(reinterpret_cast<char *>(&p_buff),sizeof(p_buff));
				if (p_buff.IDPDB == flm_d.film_tbl.ID)
				{
					fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa firmy : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(p_buff.nazwa_firmy).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Adres : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(p_buff.adres).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Telefon : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(p_buff.telefon).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Fax : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(p_buff.fax).toUtf8();
					fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>E - mail : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(p_buff.email).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Strona WWW : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(p_buff.strona_www).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Nrodowoœæ : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(p_buff.narodowosc).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr>").toUtf8();
				}
				i = i + sizeof(p_buff);
			}
			fn_p.close();
			fnout << QString::fromWCharArray(L"</table>").toUtf8() << "\n"; 

		}
		if (ui->checkBox_DYSTR->isChecked() == true)
		{
			fnout << QString::fromWCharArray(L"<h1>Tabela Dystrybucja</h1><table >").toUtf8() << "\n";
			struct Dystrybutor d_buff;
			QFile fn_d(QString::fromWCharArray(flm_d.pths.BF_PRD));
			fn_d.open(QFile::ReadOnly);
			unsigned int stop = fn_d.size();
			for (unsigned int i = 0; i < stop; )
			{
				fn_d.seek(i);
				fn_d.read(reinterpret_cast<char *>(&d_buff),sizeof(d_buff));
				if (d_buff.IDPDB == flm_d.film_tbl.ID)
				{
					fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa firmy : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(d_buff.nazwa_firmy).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Adres : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(d_buff.adres).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Telefon : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(d_buff.telefon).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Fax : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(d_buff.fax).toUtf8();
					fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>E - mail : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(d_buff.email).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Strona WWW : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(d_buff.strona_www).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Nrodowoœæ : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(d_buff.narodowosc).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr>").toUtf8();
				}
				i = i + sizeof(d_buff);
			}
			fn_d.close();
			fnout << QString::fromWCharArray(L"</table>").toUtf8() << "\n"; 

		}
		if (ui->checkBox_LZ->isChecked() == true)
		{
			fnout << QString::fromWCharArray(L"<h1>Tabela Lokalizacje zdjêciowe</h1><table >").toUtf8() << "\n";
			struct Lok_zdjeciowe z_buff;
			QFile fn_z(QString::fromWCharArray(flm_d.pths.BF_LZ));
			fn_z.open(QFile::ReadOnly);
			unsigned int stop = fn_z.size();
			for (unsigned int i = 0; i < stop; )
			{
				fn_z.seek(i);
				fn_z.read(reinterpret_cast<char *>(&z_buff),sizeof(z_buff));
				if (z_buff.IDPDB == flm_d.film_tbl.ID)
				{
					fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa obiektu : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(z_buff.nazwa_obiektu).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kraj : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(z_buff.kraj).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Miejscowoœæ : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(z_buff.miejscowosc).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Region : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(z_buff.region).toUtf8();
					fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>Pora roku : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(z_buff.pora_roku).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(z_buff.data).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr>").toUtf8();
				}
				i = i + sizeof(z_buff);
			}
			fn_z.close();
			fnout << QString::fromWCharArray(L"</table>").toUtf8() << "\n"; 
		}
		if (ui->checkBox_WYPIN->isChecked() == true)
		{
			fnout << QString::fromWCharArray(L"<h1>Tabela Wypo¿yczenia innym osobom</h1><table >").toUtf8() << "\n";
			struct Wypozycz_Innym wi_buff;
			QFile fn_wi(QString::fromWCharArray(flm_d.pths.BF_WI));
			fn_wi.open(QFile::ReadOnly);
			unsigned int stop = fn_wi.size();
			for (unsigned int i = 0; i < stop; )
			{
				fn_wi.seek(i);
				fn_wi.read(reinterpret_cast<char *>(&wi_buff),sizeof(wi_buff));
				if (wi_buff.IDPDB == flm_d.film_tbl.ID)
				{
					fnout << QString::fromWCharArray(L"<tr><td><p>Data wypo¿yczenia : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(wi_buff.data_wypozyczenia).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data oddania : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(wi_buff.data_oddania).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan przed wypo¿yczeniem : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(wi_buff.stan_przed_wypozycz).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan po oddaniu : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(wi_buff.stan_po_oddaniu).toUtf8();
					fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>Osoba : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(wi_buff.osoba).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr>").toUtf8();
				}
				i = i + sizeof(wi_buff);
			}
			fn_wi.close();
			fnout << QString::fromWCharArray(L"</table>").toUtf8() << "\n"; 
		}
		if (ui->checkBox_WYPODIN->isChecked() == true)
		{
			fnout << QString::fromWCharArray(L"<h1>Tabela Wypo¿yczenia od innych osób</h1><table >").toUtf8() << "\n";
			struct Wypozycz_Od_Innych wo_buff;
			QFile fn_wo(QString::fromWCharArray(flm_d.pths.BF_WO));
			fn_wo.open(QFile::ReadOnly);
			unsigned int stop = fn_wo.size();
			for (unsigned int i = 0; i < stop; )
			{
				fn_wo.seek(i);
				fn_wo.read(reinterpret_cast<char *>(&wo_buff),sizeof(wo_buff));
				if (wo_buff.IDPDB == flm_d.film_tbl.ID)
				{
					fnout << QString::fromWCharArray(L"<tr><td><p>Data wypo¿yczenia : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(wo_buff.data_wypozyczenia).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data oddania : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(wo_buff.data_oddania).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan przed wypo¿yczeniem : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(wo_buff.stan_przed_wypozycz).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan po oddaniu : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(wo_buff.stan_po_oddaniu).toUtf8();
					fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>Osoba : </p></td><td><p>").toUtf8();
					fnout << QString::fromWCharArray(wo_buff.osoba).toUtf8();
					fnout << QString::fromWCharArray(L"</p></td></tr>").toUtf8();
				}
				i = i + sizeof(wo_buff);
			}
			fn_wo.close();
			fnout << QString::fromWCharArray(L"</table>").toUtf8() << "\n"; 
		}
		fnout << QString::fromWCharArray(L"</body></html>").toUtf8();
		fn_exp.close();
		print_doc();

	}
	else if (ui->radioButton_All->isChecked() == true)
	{
		QFile fn_exp(QString::fromWCharArray(L"wydruk.html"));
		fn_exp.open(QFile::WriteOnly | QFile::Text);
		QTextStream fnout(&fn_exp);

		fnout << QString::fromWCharArray(L"<!DOCTYPE HTML><html><head><title>Biblioteka Filmów - Wydruk danych z bazy - http://mkalat.pl</title><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"><style type=\"text/css\">p {font-family: Verdana, Arial, Helvetica, sans-serif;font-size: 12px;line-height : 1%;}</style></head><body>").toUtf8() << "\n";
				

		struct Film m_buff;
		QFile fn_m(QString::fromWCharArray(flm_d.pths.BF_PDB));
		fn_m.open(QFile::ReadOnly);
		unsigned int stop_m = fn_m.size();
		for (unsigned int y = 0; y < stop_m; )
		{
				fn_m.seek(y);
				fn_m.read(reinterpret_cast<char *>(&m_buff),sizeof(m_buff));

				fnout << QString::fromWCharArray(L"<h1>").toUtf8() << "\n";
				fnout << QString::fromWCharArray(m_buff.tytul).toUtf8();
				fnout << QString::fromWCharArray(L"</h1><table ><tr><td><img src=\"").toUtf8();
				fnout << QString::fromWCharArray(m_buff.skan_przod_path).toUtf8();
				fnout << QString::fromWCharArray(L"\" alt=\"\"></td></tr><tr><td><p>Oryginalny tytu³ : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.oryginalny_tytul).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Gatunek : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.gatunek_filmu).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Rok produkcji : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_rok_produkcji).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data premiery : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_data_premiery).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Czas projekcji : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_czas_trwania).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Jêzyk lektora : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_jezyk_lektora).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Jêzyk napisów : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_jezyk_napisow).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Format wyœwietlania : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_format_wysw).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>System kodowania obrazu : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_system_kodowania_obrazu).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kraj produkcji filmu : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_kraj_produkcji_filmu).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Cena : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_cena).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Wartoœæ aktualna : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_wartosc_akt).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data zakupu : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_data_zakupu).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data utraty : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_data_utraty).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data skatalogowania : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_data_skatalogowania).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Noœnik : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_rodzaj_nosnika).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Muzyka : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.WOF_sciezka_dz).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Obsada : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.WOF_obsada).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Zdjêcia : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.WOF_zdjecia).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Wartoœæ artystyczna : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.WOF_w_art).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Ca³oœæ : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.WOF_calosc).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Nr Kat : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_Nr_kat).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>W³aœciciel - Imiê : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_WKF_imie).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>W³aœciciel - Nazwisko : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_WKF_nazwisko).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>W³aœciciel - Adres : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_WKF_adres).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Nazwa : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_MN_nazwa).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Adres : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_MN_adres).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Telefon : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_MN_telefon).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - email : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_MN_email).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - WWW : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_MN_www).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Fax : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.DOE_MN_fax).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek wideo - Nazwa : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_KODEK_nazwa).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek wideo - typ : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_KODEK_typ).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek wideo - wersja : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_KODEK_wersja).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Zabezpieczenia - Nazwa : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_ZABEZP_nazwa).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Zabezpieczenia - typ : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_ZABEZP_typ).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Zabezpieczenia - wersja : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_ZABEZP_wersja).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek audio - Nazwa : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_DZWIEK_nazwa).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek audio - typ : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_DZWIEK_typ).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek audio - wersja : </p></td><td><p>").toUtf8();
				fnout << QString::fromWCharArray(m_buff.IOF_DZWIEK_wersja).toUtf8();
				fnout << QString::fromWCharArray(L"</p></td></tr></table>").toUtf8() << "\n";

				if (ui->checkBox_OB->isChecked() == true)
				{
					fnout << QString::fromWCharArray(L"<h1>Tabela Obsada</h1><table >").toUtf8() << "\n";
					struct Obsada ob_buff;
					QFile fn_ob(QString::fromWCharArray(flm_d.pths.BF_OB));
					fn_ob.open(QFile::ReadOnly);
					unsigned int stop = fn_ob.size();
					for (unsigned int i = 0; i < stop; )
					{
						fn_ob.seek(i);
						fn_ob.read(reinterpret_cast<char *>(&ob_buff),sizeof(ob_buff));
						if (ob_buff.IDPDB == m_buff.ID)
						{
							fnout << QString::fromWCharArray(L"<tr><td><p>Imiê i Nazwisko : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(ob_buff.imie_nazw).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Rola : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(ob_buff.rola).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr>").toUtf8();
						}
						i = i + sizeof(ob_buff);
					}
					fn_ob.close();
					fnout << QString::fromWCharArray(L"</table>").toUtf8() << "\n"; 
				}
				if (ui->checkBox_OC->isChecked() == true)
				{
					fnout << QString::fromWCharArray(L"<h1>Tabela Ocena</h1><table >").toUtf8() << "\n";
					struct Ocena oc_buff;
					QFile fn_oc(QString::fromWCharArray(flm_d.pths.BF_OC));
					fn_oc.open(QFile::ReadOnly);
					unsigned int stop = fn_oc.size();
					for (unsigned int i = 0; i < stop; )
					{
						fn_oc.seek(i);
						fn_oc.read(reinterpret_cast<char *>(&oc_buff),sizeof(oc_buff));
						if (oc_buff.IDPDB == m_buff.ID)
						{
							fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(oc_buff.nazwa).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Tytu³ tekstu : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(oc_buff.tytul_tekstu).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Autor tekstu : </p></td/><td><p>").toUtf8();
							fnout << QString::fromWCharArray(oc_buff.autor_tekstu).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Strona WWW : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(oc_buff.strona_www).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena krytyka : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(oc_buff.ocena_krytyka).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr>").toUtf8();

						}
						i = i + sizeof(oc_buff);
						
					}
					fn_oc.close();
					fnout << QString::fromWCharArray(L"</table>").toUtf8() << "\n"; 
				}
				if (ui->checkBox_PROD->isChecked() == true)
				{
					fnout << QString::fromWCharArray(L"<h1>Tabela Produkcja</h1><table >").toUtf8() << "\n";
					struct Producent p_buff;
					QFile fn_p(QString::fromWCharArray(flm_d.pths.BF_PRP));
					fn_p.open(QFile::ReadOnly);
					unsigned int stop = fn_p.size();
					for (unsigned int i = 0; i < stop; )
					{
						fn_p.seek(i);
						fn_p.read(reinterpret_cast<char *>(&p_buff),sizeof(p_buff));
						if (p_buff.IDPDB == m_buff.ID)
						{
							fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa firmy : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(p_buff.nazwa_firmy).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Adres : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(p_buff.adres).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Telefon : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(p_buff.telefon).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Fax : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(p_buff.fax).toUtf8();
							fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>E - mail : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(p_buff.email).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Strona WWW : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(p_buff.strona_www).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Nrodowoœæ : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(p_buff.narodowosc).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr>").toUtf8();
						}
						i = i + sizeof(p_buff);
					}
					fn_p.close();
					fnout << QString::fromWCharArray(L"</table>").toUtf8() << "\n"; 

				}
				if (ui->checkBox_DYSTR->isChecked() == true)
				{
					fnout << QString::fromWCharArray(L"<h1>Tabela Dystrybucja</h1><table >").toUtf8() << "\n";
					struct Dystrybutor d_buff;
					QFile fn_d(QString::fromWCharArray(flm_d.pths.BF_PRD));
					fn_d.open(QFile::ReadOnly);
					unsigned int stop = fn_d.size();
					for (unsigned int i = 0; i < stop; )
					{
						fn_d.seek(i);
						fn_d.read(reinterpret_cast<char *>(&d_buff),sizeof(d_buff));
						if (d_buff.IDPDB == m_buff.ID)
						{
							fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa firmy : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(d_buff.nazwa_firmy).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Adres : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(d_buff.adres).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Telefon : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(d_buff.telefon).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Fax : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(d_buff.fax).toUtf8();
							fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>E - mail : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(d_buff.email).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Strona WWW : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(d_buff.strona_www).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Nrodowoœæ : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(d_buff.narodowosc).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr>").toUtf8();
						}
						i = i + sizeof(d_buff);
					}
					fn_d.close();
					fnout << QString::fromWCharArray(L"</table>").toUtf8() << "\n"; 

				}
				if (ui->checkBox_LZ->isChecked() == true)
				{
					fnout << QString::fromWCharArray(L"<h1>Tabela Lokalizacje zdjêciowe</h1><table >").toUtf8() << "\n";
					struct Lok_zdjeciowe z_buff;
					QFile fn_z(QString::fromWCharArray(flm_d.pths.BF_LZ));
					fn_z.open(QFile::ReadOnly);
					unsigned int stop = fn_z.size();
					for (unsigned int i = 0; i < stop; )
					{
						fn_z.seek(i);
						fn_z.read(reinterpret_cast<char *>(&z_buff),sizeof(z_buff));
						if (z_buff.IDPDB == m_buff.ID)
						{
							fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa obiektu : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(z_buff.nazwa_obiektu).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kraj : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(z_buff.kraj).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Miejscowoœæ : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(z_buff.miejscowosc).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Region : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(z_buff.region).toUtf8();
							fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>Pora roku : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(z_buff.pora_roku).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(z_buff.data).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr>").toUtf8();
						}
						i = i + sizeof(z_buff);
					}
					fn_z.close();
					fnout << QString::fromWCharArray(L"</table>").toUtf8() << "\n"; 
				}
				if (ui->checkBox_WYPIN->isChecked() == true)
				{
					fnout << QString::fromWCharArray(L"<h1>Tabela Wypo¿yczenia innym osobom</h1><table >").toUtf8() << "\n";
					struct Wypozycz_Innym wi_buff;
					QFile fn_wi(QString::fromWCharArray(flm_d.pths.BF_WI));
					fn_wi.open(QFile::ReadOnly);
					unsigned int stop = fn_wi.size();
					for (unsigned int i = 0; i < stop; )
					{
						fn_wi.seek(i);
						fn_wi.read(reinterpret_cast<char *>(&wi_buff),sizeof(wi_buff));
						if (wi_buff.IDPDB == m_buff.ID)
						{
							fnout << QString::fromWCharArray(L"<tr><td><p>Data wypo¿yczenia : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(wi_buff.data_wypozyczenia).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data oddania : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(wi_buff.data_oddania).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan przed wypo¿yczeniem : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(wi_buff.stan_przed_wypozycz).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan po oddaniu : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(wi_buff.stan_po_oddaniu).toUtf8();
							fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>Osoba : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(wi_buff.osoba).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr>").toUtf8();
						}
						i = i + sizeof(wi_buff);
					}
					fn_wi.close();
					fnout << QString::fromWCharArray(L"</table>").toUtf8() << "\n"; 
				}
				if (ui->checkBox_WYPODIN->isChecked() == true)
				{
					fnout << QString::fromWCharArray(L"<h1>Tabela Wypo¿yczenia od innych osób</h1><table >").toUtf8() << "\n";
					struct Wypozycz_Od_Innych wo_buff;
					QFile fn_wo(QString::fromWCharArray(flm_d.pths.BF_WO));
					fn_wo.open(QFile::ReadOnly);
					unsigned int stop = fn_wo.size();
					for (unsigned int i = 0; i < stop; )
					{
						fn_wo.seek(i);
						fn_wo.read(reinterpret_cast<char *>(&wo_buff),sizeof(wo_buff));
						if (wo_buff.IDPDB == m_buff.ID)
						{
							fnout << QString::fromWCharArray(L"<tr><td><p>Data wypo¿yczenia : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(wo_buff.data_wypozyczenia).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data oddania : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(wo_buff.data_oddania).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan przed wypo¿yczeniem : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(wo_buff.stan_przed_wypozycz).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan po oddaniu : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(wo_buff.stan_po_oddaniu).toUtf8();
							fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>Osoba : </p></td><td><p>").toUtf8();
							fnout << QString::fromWCharArray(wo_buff.osoba).toUtf8();
							fnout << QString::fromWCharArray(L"</p></td></tr>").toUtf8();
						}
						i = i + sizeof(wo_buff);
					}
					fn_wo.close();
					fnout << QString::fromWCharArray(L"</table>").toUtf8() << "\n"; 
				}
				y = y + sizeof(m_buff);
		}
		fnout << QString::fromWCharArray(L"</body></html>").toUtf8();
		fn_exp.close();
		print_doc();
	}
}

void Drukuj::on_pushButton_Cancel_clicked()
{
	this->close();
}

void Drukuj::print_doc()
{
		QFile file("wydruk.html");
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return;
 
		QString htmlContent;
		QTextStream in(&file);
		in >> htmlContent;
 
		QTextDocument *document = new QTextDocument();
		document->setHtml(htmlContent);
 
		QPrinter printer;
 
		QPrintDialog *dialog = new QPrintDialog(&printer, this);
		if (dialog->exec() != QDialog::Accepted)
			return;
 
		document->print(&printer);
 
		delete document;

}
