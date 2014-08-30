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
	if (QFile::exists(QString::fromUtf8("wydruk.html")))
	{
		QFile::remove(QString::fromUtf8("wydruk.html"));
	}
	if (ui->radioButton_Akt->isChecked() == true)
	{
		Film* flm_p = &flm_d.film_tbl;
		bool head_wrttn = false;
		bool close_html = true;
		GetFLM_HTML(flm_p, head_wrttn, close_html);
		
		print_doc();

	}
	else if (ui->radioButton_All->isChecked() == true)
	{
		struct Film m_buff;
		QFile fn_m(QString::fromWCharArray(flm_d.pths.BF_PDB));
		fn_m.open(QFile::ReadOnly);
		unsigned int stop_m = fn_m.size();
		bool head_wrttn = false;
		bool close_html = false;
		for (unsigned int y = 0; y < stop_m; )
		{
				fn_m.seek(y);
				fn_m.read(reinterpret_cast<char *>(&m_buff),sizeof(m_buff));
				if (y == (fn_m.size() - sizeof(m_buff)))
				{
					close_html = true;
				}
				GetFLM_HTML(&m_buff, head_wrttn, close_html);
				head_wrttn = true;
				y = y + sizeof(m_buff);
		}
		
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
	htmlContent = in.readAll();

    QTextDocument *document = new QTextDocument();
	document->setHtml(htmlContent);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    if (dialog->exec() != QDialog::Accepted)
    return;

    document->print(&printer);

    delete document;
}

void Drukuj::GetFLM_HTML(struct Film *flm_ptr, bool head_wrttn, bool html_end)
{
		QFile fn_exp(QString::fromUtf8("wydruk.html"));
		fn_exp.open(QFile::WriteOnly | QFile::Append | QFile::Text);
		QTextStream fnout(&fn_exp);
	
		
		if (!head_wrttn)
		{
			fnout << QString::fromUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\"><html><head><title>") << tr("Biblioteka Filmow Printing from database - http://mkalat.pl") << QString::fromUtf8("</title><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"><style type=\"text/css\">p {font-family: Verdana, Arial, Helvetica, sans-serif;font-size: 12px;}</style></head><body>") << "\n";
			
		}
		fnout << QString::fromUtf8("<h1>");
        fnout << QString::fromWCharArray(flm_ptr->tytul);
        fnout << QString::fromWCharArray(L"</h1><table ><tr><td><img src=\"file://");
        fnout << QString::fromWCharArray(flm_ptr->skan_przod_path);
		fnout << QString::fromUtf8("\"></td></tr><tr><td><p>") << tr("Oryginalny tytuł: ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->oryginalny_tytul);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Gatunek : ")<< QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->gatunek_filmu);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Rok produkcji : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_rok_produkcji);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Data premiery : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_data_premiery);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Czas projekcji : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_czas_trwania);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Język lektora : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_jezyk_lektora);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Język napisów ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_jezyk_napisow);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Format wyświetlania : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_format_wysw);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("System kodowania obrazu : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_system_kodowania_obrazu);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Kraj produkcji filmu : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_kraj_produkcji_filmu);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Cena : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->DOE_cena);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Wartość aktualna : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->DOE_wartosc_akt);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Data zakupu : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->DOE_data_zakupu);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Data utraty : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->DOE_data_utraty);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Data skatalogowania : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->DOE_data_skatalogowania);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Nośnik : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->DOE_rodzaj_nosnika);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Ocena - Muzyka : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->WOF_sciezka_dz);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Ocena - Obsada : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->WOF_obsada);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Ocena - Zdjęcia : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->WOF_zdjecia);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Ocena - Wartość artystyczna : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->WOF_w_art);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Ocena - Całość : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->WOF_calosc);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Nr Kat : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->DOE_Nr_kat);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Właściciel - Imię : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->DOE_WKF_imie);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Właściciel - Nazwisko : ") << QString::fromUtf8("</p></td><td><p>");
		fnout << QString::fromWCharArray(flm_ptr->DOE_WKF_nazwisko);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Właściciel - Adres : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->DOE_WKF_adres);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Sklep - Nazwa : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->DOE_MN_nazwa);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Sklep - Adres : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->DOE_MN_adres);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Sklep - Telefon : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->DOE_MN_telefon);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Sklep - email : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->DOE_MN_email);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Sklep - WWW : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->DOE_MN_www);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Sklep - Fax : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->DOE_MN_fax);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Kodek wideo - Nazwa : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_KODEK_nazwa);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Kodek wideo - typ : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_KODEK_typ);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Kodek wideo - wersja : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_KODEK_wersja);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Zabezpieczenia - Nazwa : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_ZABEZP_nazwa);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Zabezpieczenia - typ : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_ZABEZP_typ);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Zabezpieczenia - wersja : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_ZABEZP_wersja);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Kodek audio - Nazwa : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_DZWIEK_nazwa);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Kodek audio - typ : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_DZWIEK_typ);
		fnout << QString::fromUtf8("</p></td></tr><tr><td><p>") << tr("Kodek audio - wersja : ") << QString::fromUtf8("</p></td><td><p>");
        fnout << QString::fromWCharArray(flm_ptr->IOF_DZWIEK_wersja);
        fnout << QString::fromWCharArray(L"</p></td></tr></table>") << "\n";

		if (ui->checkBox_OB->isChecked() == true)
		{
			fnout << QString::fromUtf8("<h1>") << tr("Tabela Obsada") << QString::fromUtf8("</h1><table >") << "\n";
			struct Obsada ob_buff;
			QFile fn_ob(QString::fromWCharArray(flm_d.pths.BF_OB));
			fn_ob.open(QFile::ReadOnly);
			unsigned int stop = fn_ob.size();
			for (unsigned int i = 0; i < stop; )
			{
				fn_ob.seek(i);
				fn_ob.read(reinterpret_cast<char *>(&ob_buff),sizeof(ob_buff));
				if (ob_buff.IDPDB == flm_ptr->ID)
				{
					fnout << QString::fromWCharArray(L"<tr><td><p>") << tr("Imię i Nazwisko : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(ob_buff.imie_nazw);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Rola : ") << QString::fromUtf8("</p></td><td><p>");
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
			fnout << QString::fromWCharArray(L"<h1>") << tr("Tabela Ocena") << QString::fromUtf8("</h1><table >") << "\n";
			struct Ocena oc_buff;
			QFile fn_oc(QString::fromWCharArray(flm_d.pths.BF_OC));
			fn_oc.open(QFile::ReadOnly);
			unsigned int stop = fn_oc.size();
			for (unsigned int i = 0; i < stop; )
			{
				fn_oc.seek(i);
				fn_oc.read(reinterpret_cast<char *>(&oc_buff),sizeof(oc_buff));
				if (oc_buff.IDPDB == flm_ptr->ID)
				{
					fnout << QString::fromWCharArray(L"<tr><td><p>") << tr("Nazwa : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(oc_buff.nazwa);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Tytuł tekstu : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(oc_buff.tytul_tekstu);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Autor tekstu : ") << QString::fromUtf8("</p></td/><td><p>");
                    fnout << QString::fromWCharArray(oc_buff.autor_tekstu);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Strona WWW : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(oc_buff.strona_www);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Ocena krytyka : ") << QString::fromUtf8("</p></td><td><p>");
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
			fnout << QString::fromWCharArray(L"<h1>") << tr("Tabela Produkcja") << QString::fromUtf8("</h1><table >") << "\n";
			struct Producent p_buff;
			QFile fn_p(QString::fromWCharArray(flm_d.pths.BF_PRP));
			fn_p.open(QFile::ReadOnly);
			unsigned int stop = fn_p.size();
			for (unsigned int i = 0; i < stop; )
			{
				fn_p.seek(i);
				fn_p.read(reinterpret_cast<char *>(&p_buff),sizeof(p_buff));
				if (p_buff.IDPDB == flm_ptr->ID)
				{
					fnout << QString::fromWCharArray(L"<tr><td><p>") << tr("Nazwa firmy : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(p_buff.nazwa_firmy);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Adres : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(p_buff.adres);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Telefon : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(p_buff.telefon);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Fax : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(p_buff.fax);
					fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>") << tr("E - mail : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(p_buff.email);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Strona WWW : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(p_buff.strona_www);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Nrodowość : ") << QString::fromUtf8("</p></td><td><p>");
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
			fnout << QString::fromWCharArray(L"<h1>") << tr("Tabela Dystrybucja") << QString::fromUtf8("</h1><table >") << "\n";
			struct Dystrybutor d_buff;
			QFile fn_d(QString::fromWCharArray(flm_d.pths.BF_PRD));
			fn_d.open(QFile::ReadOnly);
			unsigned int stop = fn_d.size();
			for (unsigned int i = 0; i < stop; )
			{
				fn_d.seek(i);
				fn_d.read(reinterpret_cast<char *>(&d_buff),sizeof(d_buff));
				if (d_buff.IDPDB == flm_ptr->ID)
				{
					fnout << QString::fromWCharArray(L"<tr><td><p>") << tr("Nazwa firmy : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(d_buff.nazwa_firmy);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Adres : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(d_buff.adres);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Telefon : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(d_buff.telefon);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Fax : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(d_buff.fax);
					fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>") << tr("E - mail : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(d_buff.email);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Strona WWW : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(d_buff.strona_www);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Nrodowość : ") << QString::fromUtf8("</p></td><td><p>");
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
			fnout << QString::fromWCharArray(L"<h1>") << tr("Tabela Lokalizacje zdjęciowe") << QString::fromUtf8("</h1><table >") << "\n";
			struct Lok_zdjeciowe z_buff;
			QFile fn_z(QString::fromWCharArray(flm_d.pths.BF_LZ));
			fn_z.open(QFile::ReadOnly);
			unsigned int stop = fn_z.size();
			for (unsigned int i = 0; i < stop; )
			{
				fn_z.seek(i);
				fn_z.read(reinterpret_cast<char *>(&z_buff),sizeof(z_buff));
				if (z_buff.IDPDB == flm_ptr->ID)
				{
					fnout << QString::fromWCharArray(L"<tr><td><p>") << tr("Nazwa obiektu : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(z_buff.nazwa_obiektu);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Kraj : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(z_buff.kraj);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Miejscowość : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(z_buff.miejscowosc);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Region : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(z_buff.region);
					fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>") << tr("Pora roku : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(z_buff.pora_roku);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Data : ") << QString::fromUtf8("</p></td><td><p>");
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
			fnout << QString::fromWCharArray(L"<h1>") << tr("Tabela Wypożyczenia innym osobom") << QString::fromUtf8("</h1><table >") << "\n";
			struct Wypozycz_Innym wi_buff;
			QFile fn_wi(QString::fromWCharArray(flm_d.pths.BF_WI));
			fn_wi.open(QFile::ReadOnly);
			unsigned int stop = fn_wi.size();
			for (unsigned int i = 0; i < stop; )
			{
				fn_wi.seek(i);
				fn_wi.read(reinterpret_cast<char *>(&wi_buff),sizeof(wi_buff));
				if (wi_buff.IDPDB == flm_ptr->ID)
				{
					fnout << QString::fromWCharArray(L"<tr><td><p>") << tr("Data wypożyczenia : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(wi_buff.data_wypozyczenia);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Data oddania : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(wi_buff.data_oddania);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Stan przed wypożyczeniem : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(wi_buff.stan_przed_wypozycz);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Stan po oddaniu : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(wi_buff.stan_po_oddaniu);
					fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>") << tr("Osoba : ") << QString::fromUtf8("</p></td><td><p>");
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
			fnout << QString::fromWCharArray(L"<h1>") << tr("Tabela Wypożyczenia od innych osób") << QString::fromUtf8("</h1><table >") << "\n";
			struct Wypozycz_Od_Innych wo_buff;
			QFile fn_wo(QString::fromWCharArray(flm_d.pths.BF_WO));
			fn_wo.open(QFile::ReadOnly);
			unsigned int stop = fn_wo.size();
			for (unsigned int i = 0; i < stop; )
			{
				fn_wo.seek(i);
				fn_wo.read(reinterpret_cast<char *>(&wo_buff),sizeof(wo_buff));
				if (wo_buff.IDPDB == flm_ptr->ID)
				{
					fnout << QString::fromWCharArray(L"<tr><td><p>") << tr("Data wypożyczenia : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(wo_buff.data_wypozyczenia);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Data oddania : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(wo_buff.data_oddania);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Stan przed wypożyczeniem : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(wo_buff.stan_przed_wypozycz);
					fnout << QString::fromWCharArray(L"</p></td></tr><tr><td><p>") << tr("Stan po oddaniu : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(wo_buff.stan_po_oddaniu);
					fnout << QString::fromWCharArray(L"<p></td></tr><tr><td><p>") << tr("Osoba : ") << QString::fromUtf8("</p></td><td><p>");
                    fnout << QString::fromWCharArray(wo_buff.osoba);
                    fnout << QString::fromWCharArray(L"</p></td></tr>");



				}
				i = i + sizeof(wo_buff);
			}
			fn_wo.close();
            fnout << QString::fromWCharArray(L"</table>") << "\n";
		}
		if (html_end)
		{
			fnout << QString::fromWCharArray(L"</body></html>");
		}
		fn_exp.close();
}