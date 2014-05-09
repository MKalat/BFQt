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

		fnout << QString::fromWCharArray(L"<!DOCTYPE HTML><html><head><title>Biblioteka Film�w Wydruk danych z bazy - http://mkalat.pl</title><meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1250\"><style type=\"text/css\">p {font-family: Verdana, Arial, Helvetica, sans-serif;font-size: 12px;line-height : 1%;}</style></head><body><h1>") << "\n";
        fnout << QString::fromWCharArray(flm_d.film_tbl.tytul);
        fnout << QString::fromWCharArray(L"</h1><table ><tr><td><img src=\"file://");
        fnout << QString::fromWCharArray(flm_d.film_tbl.skan_przod_path);
		fnout << QString::fromWCharArray(L"\" alt=\"\"></td></tr><tr><td><p>Oryginalny tytu�: </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.oryginalny_tytul);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Gatunek : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.gatunek_filmu);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Rok produkcji : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_rok_produkcji);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data premiery : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_data_premiery);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Czas projekcji : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_czas_trwania);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>J�zyk lektora : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_jezyk_lektora);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>J�zyk napis�w </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_jezyk_napisow);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Format wy�wietlania : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_format_wysw);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>System kodowania obrazu : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_system_kodowania_obrazu);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kraj produkcji filmu : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_kraj_produkcji_filmu);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Cena : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_cena);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Warto�� aktualna : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_wartosc_akt);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data zakupu : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_data_zakupu);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data utraty : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_data_utraty);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data skatalogowania : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_data_skatalogowania);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>No�nik : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_rodzaj_nosnika);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Muzyka : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.WOF_sciezka_dz);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Obsada : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.WOF_obsada);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Zdj�cia : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.WOF_zdjecia);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Warto�� artystyczna : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.WOF_w_art);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Ca�o�� : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.WOF_calosc);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Nr Kat : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_Nr_kat);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>W�a�ciciel - Imi� : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_WKF_imie);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>W�a�ciciel - Nazwisko : </p></td><td><p>");
		fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_WKF_nazwisko);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>W�a�ciciel - Adres : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_WKF_adres);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Nazwa : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_nazwa);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Adres : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_adres);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Telefon : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_telefon);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - email : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_email);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - WWW : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_www);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Fax : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.DOE_MN_fax);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek wideo - Nazwa : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_KODEK_nazwa);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek wideo - typ : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_KODEK_typ);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek wideo - wersja : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_KODEK_wersja);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Zabezpieczenia - Nazwa : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_ZABEZP_nazwa);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Zabezpieczenia - typ : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_ZABEZP_typ);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Zabezpieczenia - wersja : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_ZABEZP_wersja);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek audio - Nazwa : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_DZWIEK_nazwa);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek audio - typ : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_DZWIEK_typ);
        fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek audio - wersja : </p></td><td><p>");
        fnout << QString::fromWCharArray(flm_d.film_tbl.IOF_DZWIEK_wersja);
        fnout << QString::fromWCharArray(L"</p></td></tr></table>") << "\n";
		
		
		if (ui->checkBox_OB->isChecked() == true)
		{
            fnout << QString::fromWCharArray(L"<h1>Tabela Obsada</h1><table >") << "\n";
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
                    fnout << QString::fromWCharArray(L"<tr><td><p>Imi� i Nazwisko : </p></td><td><p>");
                    fnout << QString::fromWCharArray(ob_buff.imie_nazw);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Rola : </p></td><td><p>");
                    fnout << QString::fromWCharArray(ob_buff.rola);
                    fnout << QString::fromWCharArray(L"</p></td></tr>");


				}
				i = i + sizeof(ob_buff);
			}
			fn_ob.close();
            fnout << QString::fromWCharArray(L"</table>") << "\n";
		}
		if (ui->checkBox_OC->isChecked() == true)
		{
            fnout << QString::fromWCharArray(L"<h1>Tabela Ocena</h1><table >") << "\n";
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
                    fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa : </p></td><td><p>");
                    fnout << QString::fromWCharArray(oc_buff.nazwa);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Tytu� tekstu : </p></td><td><p>");
                    fnout << QString::fromWCharArray(oc_buff.tytul_tekstu);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Autor tekstu : </p></td/><td><p>");
                    fnout << QString::fromWCharArray(oc_buff.autor_tekstu);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Strona WWW : </p></td><td><p>");
                    fnout << QString::fromWCharArray(oc_buff.strona_www);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena krytyka : </p></td><td><p>");
                    fnout << QString::fromWCharArray(oc_buff.ocena_krytyka);
                    fnout << QString::fromWCharArray(L"</p></td></tr>");


				}
				i = i + sizeof(oc_buff);
				
			}
			fn_oc.close();
            fnout << QString::fromWCharArray(L"</table>") << "\n";
		}
		if (ui->checkBox_PROD->isChecked() == true)
		{
            fnout << QString::fromWCharArray(L"<h1>Tabela Produkcja</h1><table >") << "\n";
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
                    fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa firmy : </p></td><td><p>");
                    fnout << QString::fromWCharArray(p_buff.nazwa_firmy);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Adres : </p></td><td><p>");
                    fnout << QString::fromWCharArray(p_buff.adres);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Telefon : </p></td><td><p>");
                    fnout << QString::fromWCharArray(p_buff.telefon);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Fax : </p></td><td><p>");
                    fnout << QString::fromWCharArray(p_buff.fax);
                    fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>E - mail : </p></td><td><p>");
                    fnout << QString::fromWCharArray(p_buff.email);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Strona WWW : </p></td><td><p>");
                    fnout << QString::fromWCharArray(p_buff.strona_www);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Nrodowo�� : </p></td><td><p>");
                    fnout << QString::fromWCharArray(p_buff.narodowosc);
                    fnout << QString::fromWCharArray(L"</p></td></tr>");


				}
				i = i + sizeof(p_buff);
			}
			fn_p.close();
            fnout << QString::fromWCharArray(L"</table>") << "\n";

		}
		if (ui->checkBox_DYSTR->isChecked() == true)
		{
            fnout << QString::fromWCharArray(L"<h1>Tabela Dystrybucja</h1><table >") << "\n";
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
                    fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa firmy : </p></td><td><p>");
                    fnout << QString::fromWCharArray(d_buff.nazwa_firmy);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Adres : </p></td><td><p>");
                    fnout << QString::fromWCharArray(d_buff.adres);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Telefon : </p></td><td><p>");
                    fnout << QString::fromWCharArray(d_buff.telefon);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Fax : </p></td><td><p>");
                    fnout << QString::fromWCharArray(d_buff.fax);
                    fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>E - mail : </p></td><td><p>");
                    fnout << QString::fromWCharArray(d_buff.email);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Strona WWW : </p></td><td><p>");
                    fnout << QString::fromWCharArray(d_buff.strona_www);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Nrodowo�� : </p></td><td><p>");
                    fnout << QString::fromWCharArray(d_buff.narodowosc);
                    fnout << QString::fromWCharArray(L"</p></td></tr>");


				}
				i = i + sizeof(d_buff);
			}
			fn_d.close();
            fnout << QString::fromWCharArray(L"</table>").toLocal8Bit() << "\n";

		}
		if (ui->checkBox_LZ->isChecked() == true)
		{
            fnout << QString::fromWCharArray(L"<h1>Tabela Lokalizacje zdj�ciowe</h1><table >") << "\n";
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
                    fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa obiektu : </p></td><td><p>");
                    fnout << QString::fromWCharArray(z_buff.nazwa_obiektu);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kraj : </p></td><td><p>");
                    fnout << QString::fromWCharArray(z_buff.kraj);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Miejscowo�� : </p></td><td><p>");
                    fnout << QString::fromWCharArray(z_buff.miejscowosc);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Region : </p></td><td><p>");
                    fnout << QString::fromWCharArray(z_buff.region);
                    fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>Pora roku : </p></td><td><p>");
                    fnout << QString::fromWCharArray(z_buff.pora_roku);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data : </p></td><td><p>");
                    fnout << QString::fromWCharArray(z_buff.data);
                    fnout << QString::fromWCharArray(L"</p></td></tr>");


				}
				i = i + sizeof(z_buff);
			}
			fn_z.close();
            fnout << QString::fromWCharArray(L"</table>").toLocal8Bit() << "\n";
		}
		if (ui->checkBox_WYPIN->isChecked() == true)
		{
            fnout << QString::fromWCharArray(L"<h1>Tabela Wypo�yczenia innym osobom</h1><table >") << "\n";
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
                    fnout << QString::fromWCharArray(L"<tr><td><p>Data wypo�yczenia : </p></td><td><p>");
                    fnout << QString::fromWCharArray(wi_buff.data_wypozyczenia);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data oddania : </p></td><td><p>");
                    fnout << QString::fromWCharArray(wi_buff.data_oddania);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan przed wypo�yczeniem : </p></td><td><p>");
                    fnout << QString::fromWCharArray(wi_buff.stan_przed_wypozycz);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan po oddaniu : </p></td><td><p>");
                    fnout << QString::fromWCharArray(wi_buff.stan_po_oddaniu);
                    fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>Osoba : </p></td><td><p>");
                    fnout << QString::fromWCharArray(wi_buff.osoba);
                    fnout << QString::fromWCharArray(L"</p></td></tr>");


				}
				i = i + sizeof(wi_buff);
			}
			fn_wi.close();
            fnout << QString::fromWCharArray(L"</table>").toLocal8Bit() << "\n";
		}
		if (ui->checkBox_WYPODIN->isChecked() == true)
		{
            fnout << QString::fromWCharArray(L"<h1>Tabela Wypo�yczenia od innych os�b</h1><table >") << "\n";
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
                    fnout << QString::fromWCharArray(L"<tr><td><p>Data wypo�yczenia : </p></td><td><p>");
                    fnout << QString::fromWCharArray(wo_buff.data_wypozyczenia);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data oddania : </p></td><td><p>");
                    fnout << QString::fromWCharArray(wo_buff.data_oddania);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan przed wypo�yczeniem : </p></td><td><p>");
                    fnout << QString::fromWCharArray(wo_buff.stan_przed_wypozycz);
                    fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan po oddaniu : </p></td><td><p>");
                    fnout << QString::fromWCharArray(wo_buff.stan_po_oddaniu);
                    fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>Osoba : </p></td><td><p>");
                    fnout << QString::fromWCharArray(wo_buff.osoba);
                    fnout << QString::fromWCharArray(L"</p></td></tr>");



				}
				i = i + sizeof(wo_buff);
			}
			fn_wo.close();
            fnout << QString::fromWCharArray(L"</table>") << "\n";
		}
        fnout << QString::fromWCharArray(L"</body></html>");
		fn_exp.close();
		print_doc();

	}
	else if (ui->radioButton_All->isChecked() == true)
	{
		QFile fn_exp(QString::fromWCharArray(L"wydruk.html"));
		fn_exp.open(QFile::WriteOnly | QFile::Text);
		QTextStream fnout(&fn_exp);

        fnout << QString::fromWCharArray(L"<!DOCTYPE HTML><html><head><title>Biblioteka Film�w - Wydruk danych z bazy - http://mkalat.pl</title><meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1250\"><style type=\"text/css\">p {font-family: Verdana, Arial, Helvetica, sans-serif;font-size: 12px;line-height : 1%;}</style></head><body>") << "\n";
				

		struct Film m_buff;
		QFile fn_m(QString::fromWCharArray(flm_d.pths.BF_PDB));
		fn_m.open(QFile::ReadOnly);
		unsigned int stop_m = fn_m.size();
		for (unsigned int y = 0; y < stop_m; )
		{
				fn_m.seek(y);
				fn_m.read(reinterpret_cast<char *>(&m_buff),sizeof(m_buff));

                fnout << QString::fromWCharArray(L"<h1>") << "\n";
                fnout << QString::fromWCharArray(m_buff.tytul);
                fnout << QString::fromWCharArray(L"</h1><table ><tr><td><img src=\"file://");
                fnout << QString::fromWCharArray(m_buff.skan_przod_path);
                fnout << QString::fromWCharArray(L"\" alt=\"\"></td></tr><tr><td><p>Oryginalny tytu� : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.oryginalny_tytul);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Gatunek : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.gatunek_filmu);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Rok produkcji : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_rok_produkcji);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data premiery : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_data_premiery);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Czas projekcji : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_czas_trwania);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>J�zyk lektora : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_jezyk_lektora);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>J�zyk napis�w : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_jezyk_napisow);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Format wy�wietlania : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_format_wysw);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>System kodowania obrazu : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_system_kodowania_obrazu);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kraj produkcji filmu : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_kraj_produkcji_filmu);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Cena : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_cena);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Warto�� aktualna : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_wartosc_akt);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data zakupu : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_data_zakupu);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data utraty : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_data_utraty);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data skatalogowania : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_data_skatalogowania);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>No�nik : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_rodzaj_nosnika);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Muzyka : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.WOF_sciezka_dz);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Obsada : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.WOF_obsada);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Zdj�cia : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.WOF_zdjecia);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Warto�� artystyczna : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.WOF_w_art);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena - Ca�o�� : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.WOF_calosc);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Nr Kat : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_Nr_kat);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>W�a�ciciel - Imi� : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_WKF_imie);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>W�a�ciciel - Nazwisko : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_WKF_nazwisko);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>W�a�ciciel - Adres : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_WKF_adres);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Nazwa : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_MN_nazwa);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Adres : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_MN_adres);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Telefon : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_MN_telefon);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - email : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_MN_email);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - WWW : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_MN_www);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Sklep - Fax : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.DOE_MN_fax);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek wideo - Nazwa : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_KODEK_nazwa);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek wideo - typ : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_KODEK_typ);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek wideo - wersja : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_KODEK_wersja);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Zabezpieczenia - Nazwa : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_ZABEZP_nazwa);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Zabezpieczenia - typ : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_ZABEZP_typ);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Zabezpieczenia - wersja : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_ZABEZP_wersja);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek audio - Nazwa : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_DZWIEK_nazwa);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek audio - typ : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_DZWIEK_typ);
                fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kodek audio - wersja : </p></td><td><p>");
                fnout << QString::fromWCharArray(m_buff.IOF_DZWIEK_wersja);
                fnout << QString::fromWCharArray(L"</p></td></tr></table>") << "\n";

				if (ui->checkBox_OB->isChecked() == true)
				{
                    fnout << QString::fromWCharArray(L"<h1>Tabela Obsada</h1><table >") << "\n";
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
                            fnout << QString::fromWCharArray(L"<tr><td><p>Imi� i Nazwisko : </p></td><td><p>");
                            fnout << QString::fromWCharArray(ob_buff.imie_nazw);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Rola : </p></td><td><p>");
                            fnout << QString::fromWCharArray(ob_buff.rola);
                            fnout << QString::fromWCharArray(L"</p></td></tr>");


						}
						i = i + sizeof(ob_buff);
					}
					fn_ob.close();
                    fnout << QString::fromWCharArray(L"</table>") << "\n";
				}
				if (ui->checkBox_OC->isChecked() == true)
				{
                    fnout << QString::fromWCharArray(L"<h1>Tabela Ocena</h1><table >") << "\n";
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
                            fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa : </p></td><td><p>");
                            fnout << QString::fromWCharArray(oc_buff.nazwa);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Tytu� tekstu : </p></td><td><p>");
                            fnout << QString::fromWCharArray(oc_buff.tytul_tekstu);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Autor tekstu : </p></td/><td><p>");
                            fnout << QString::fromWCharArray(oc_buff.autor_tekstu);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Strona WWW : </p></td><td><p>");
                            fnout << QString::fromWCharArray(oc_buff.strona_www);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Ocena krytyka : </p></td><td><p>");
                            fnout << QString::fromWCharArray(oc_buff.ocena_krytyka);
                            fnout << QString::fromWCharArray(L"</p></td></tr>");



						}
						i = i + sizeof(oc_buff);
						
					}
					fn_oc.close();
                    fnout << QString::fromWCharArray(L"</table>") << "\n";
				}
				if (ui->checkBox_PROD->isChecked() == true)
				{
                    fnout << QString::fromWCharArray(L"<h1>Tabela Produkcja</h1><table >") << "\n";
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
                            fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa firmy : </p></td><td><p>");
                            fnout << QString::fromWCharArray(p_buff.nazwa_firmy);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Adres : </p></td><td><p>");
                            fnout << QString::fromWCharArray(p_buff.adres);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Telefon : </p></td><td><p>");
                            fnout << QString::fromWCharArray(p_buff.telefon);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Fax : </p></td><td><p>");
                            fnout << QString::fromWCharArray(p_buff.fax);
                            fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>E - mail : </p></td><td><p>");
                            fnout << QString::fromWCharArray(p_buff.email);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Strona WWW : </p></td><td><p>");
                            fnout << QString::fromWCharArray(p_buff.strona_www);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Nrodowo�� : </p></td><td><p>");
                            fnout << QString::fromWCharArray(p_buff.narodowosc);
                            fnout << QString::fromWCharArray(L"</p></td></tr>");


						}
						i = i + sizeof(p_buff);
					}
					fn_p.close();
                    fnout << QString::fromWCharArray(L"</table>") << "\n";

				}
				if (ui->checkBox_DYSTR->isChecked() == true)
				{
                    fnout << QString::fromWCharArray(L"<h1>Tabela Dystrybucja</h1><table >") << "\n";
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
                            fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa firmy : </p></td><td><p>");
                            fnout << QString::fromWCharArray(d_buff.nazwa_firmy);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Adres : </p></td><td><p>");
                            fnout << QString::fromWCharArray(d_buff.adres);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Telefon : </p></td><td><p>");
                            fnout << QString::fromWCharArray(d_buff.telefon);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Fax : </p></td><td><p>");
                            fnout << QString::fromWCharArray(d_buff.fax);
                            fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>E - mail : </p></td><td><p>");
                            fnout << QString::fromWCharArray(d_buff.email);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Strona WWW : </p></td><td><p>");
                            fnout << QString::fromWCharArray(d_buff.strona_www);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Narodowo�� : </p></td><td><p>");
                            fnout << QString::fromWCharArray(d_buff.narodowosc);
                            fnout << QString::fromWCharArray(L"</p></td></tr>");


						}
						i = i + sizeof(d_buff);
					}
					fn_d.close();
                    fnout << QString::fromWCharArray(L"</table>") << "\n";

				}
				if (ui->checkBox_LZ->isChecked() == true)
				{
                    fnout << QString::fromWCharArray(L"<h1>Tabela Lokalizacje zdj�ciowe</h1><table >") << "\n";
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
                            fnout << QString::fromWCharArray(L"<tr><td><p>Nazwa obiektu : </p></td><td><p>");
                            fnout << QString::fromWCharArray(z_buff.nazwa_obiektu);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Kraj : </p></td><td><p>");
                            fnout << QString::fromWCharArray(z_buff.kraj);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Miejscowo�� : </p></td><td><p>");
                            fnout << QString::fromWCharArray(z_buff.miejscowosc);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Region : </p></td><td><p>");
                            fnout << QString::fromWCharArray(z_buff.region);
                            fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>Pora roku : </p></td><td><p>");
                            fnout << QString::fromWCharArray(z_buff.pora_roku);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data : </p></td><td><p>");
                            fnout << QString::fromWCharArray(z_buff.data);
                            fnout << QString::fromWCharArray(L"</p></td></tr>");


						}
						i = i + sizeof(z_buff);
					}
					fn_z.close();
                    fnout << QString::fromWCharArray(L"</table>") << "\n";
				}
				if (ui->checkBox_WYPIN->isChecked() == true)
				{
                    fnout << QString::fromWCharArray(L"<h1>Tabela Wypo�yczenia innym osobom</h1><table >") << "\n";
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
                            fnout << QString::fromWCharArray(L"<tr><td><p>Data wypo�yczenia : </p></td><td><p>");
                            fnout << QString::fromWCharArray(wi_buff.data_wypozyczenia);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data oddania : </p></td><td><p>");
                            fnout << QString::fromWCharArray(wi_buff.data_oddania);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan przed wypo�yczeniem : </p></td><td><p>");
                            fnout << QString::fromWCharArray(wi_buff.stan_przed_wypozycz);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan po oddaniu : </p></td><td><p>");
                            fnout << QString::fromWCharArray(wi_buff.stan_po_oddaniu);
                            fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>Osoba : </p></td><td><p>");
                            fnout << QString::fromWCharArray(wi_buff.osoba);
                            fnout << QString::fromWCharArray(L"</p></td></tr>");


						}
						i = i + sizeof(wi_buff);
					}
					fn_wi.close();
                    fnout << QString::fromWCharArray(L"</table>") << "\n";
				}
				if (ui->checkBox_WYPODIN->isChecked() == true)
				{
                    fnout << QString::fromWCharArray(L"<h1>Tabela Wypo�yczenia od innych os�b</h1><table >") << "\n";
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
                            fnout << QString::fromWCharArray(L"<tr><td><p>Data wypo�yczenia : </p></td><td><p>");
                            fnout << QString::fromWCharArray(wo_buff.data_wypozyczenia);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Data oddania : </p></td><td><p>");
                            fnout << QString::fromWCharArray(wo_buff.data_oddania);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan przed wypo�yczeniem : </p></td><td><p>");
                            fnout << QString::fromWCharArray(wo_buff.stan_przed_wypozycz);
                            fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>Stan po oddaniu : </p></td><td><p>");
                            fnout << QString::fromWCharArray(wo_buff.stan_po_oddaniu);
                            fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>Osoba : </p></td><td><p>");
                            fnout << QString::fromWCharArray(wo_buff.osoba);
                            fnout << QString::fromWCharArray(L"</p></td></tr>");


						}
						i = i + sizeof(wo_buff);
					}
					fn_wo.close();
                    fnout << QString::fromWCharArray(L"</table>") << "\n";
				}
				y = y + sizeof(m_buff);
		}
        fnout << QString::fromWCharArray(L"</body></html>");
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
