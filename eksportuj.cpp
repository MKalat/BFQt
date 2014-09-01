#include "eksportuj.h"
#include "ui_eksportuj.h"

#include "film_ftbl_class.h"
#include "Unmngd.h"

Ftbl flm_eks;
QTextCodec *codec = QTextCodec::codecForName("windows-1250");

Eksportuj::Eksportuj(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Eksportuj)
{
    ui->setupUi(this);
}

Eksportuj::~Eksportuj()
{
    delete ui;
}

void Eksportuj::on_pushButton_GetPath_clicked()
{
    QFileDialog fdlg(this);
    fdlg.setFileMode(QFileDialog::AnyFile);
    fdlg.setViewMode(QFileDialog::Detail);
    fdlg.setNameFilter(tr("Comma Separated Values file (*.csv )"));
    fdlg.setAcceptMode(QFileDialog::AcceptSave);
    if (fdlg.exec())
    {
        QString dir_path = fdlg.selectedFiles().at(0);
        ui->lineEdit_Eks_path->setText(dir_path);
    }
}

void Eksportuj::on_pushButton_Eksport_clicked()
{
    if (ui->checkBox_AllRec->isChecked() == true)
            {
				if (ui->checkBox_MainFilm->isChecked() == true)
				{
					struct Film m_buff;
					QFile fn_m(QString::fromWCharArray(flm_eks.pths.BF_PDB));
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
						Eksportuj_data_MAIN(&m_buff, head_wrttn, close_html);
						head_wrttn = true;
						y = y + sizeof(m_buff);
					}
				}
				if (ui->checkBox_TabOcena->isChecked() == true)
				{
					struct Ocena m_buff;
					QFile oc_src(QString::fromWCharArray(flm_eks.pths.BF_OC));
					oc_src.open(QFile::ReadOnly);
					unsigned int stop_m = oc_src.size();
					bool head_wrttn = false;
					bool close_html = false;
					for (unsigned int y = 0; y < stop_m; )
					{
						oc_src.seek(y);
						oc_src.read(reinterpret_cast<char *>(&m_buff),sizeof(m_buff));
						if (y == (oc_src.size() - sizeof(m_buff)))
						{
							close_html = true;
						}
						Eksportuj_data_OC(&m_buff, head_wrttn, close_html);
						head_wrttn = true;
						y = y + sizeof(m_buff);
					}
				}
				if (ui->checkBox_TabObsada->isChecked() == true)
				{
					struct Obsada m_buff;
					QFile ob_src(QString::fromWCharArray(flm_eks.pths.BF_OB));
					ob_src.open(QFile::ReadOnly);
					unsigned int stop_m = ob_src.size();
					bool head_wrttn = false;
					bool close_html = false;
					for (unsigned int y = 0; y < stop_m; )
					{
						ob_src.seek(y);
						ob_src.read(reinterpret_cast<char *>(&m_buff),sizeof(m_buff));
						if (y == (ob_src.size() - sizeof(m_buff)))
						{
							close_html = true;
						}
						Eksportuj_data_OB(&m_buff, head_wrttn, close_html);
						head_wrttn = true;
						y = y + sizeof(m_buff);
					}
				}
				if (ui->checkBox_TabPD->isChecked() == true)
				{
					struct Producent m_buff;
					QFile pp_src(QString::fromWCharArray(flm_eks.pths.BF_PRP));
					pp_src.open(QFile::ReadOnly);
					unsigned int stop_m = pp_src.size();
					bool head_wrttn = false;
					bool close_html = false;
					for (unsigned int y = 0; y < stop_m; )
					{
						pp_src.seek(y);
						pp_src.read(reinterpret_cast<char *>(&m_buff),sizeof(m_buff));
						if (y == (pp_src.size() - sizeof(m_buff)))
						{
							close_html = true;
						}
						Eksportuj_data_PP(&m_buff, head_wrttn, close_html);
						head_wrttn = true;
						y = y + sizeof(m_buff);
					}
				
					struct Dystrybutor md_buff;
					QFile pd_src(QString::fromWCharArray(flm_eks.pths.BF_PRD));
					pd_src.open(QFile::ReadOnly);
					unsigned int stop_md = pd_src.size();
					bool head_wrttnd = false;
					bool close_htmld = false;
					for (unsigned int y = 0; y < stop_md; )
					{
						pd_src.seek(y);
						pd_src.read(reinterpret_cast<char *>(&md_buff),sizeof(md_buff));
						if (y == (pd_src.size() - sizeof(md_buff)))
						{
							close_html = true;
						}
						Eksportuj_data_PD(&md_buff, head_wrttnd, close_htmld);
						head_wrttn = true;
						y = y + sizeof(md_buff);
					}
				}
				if (ui->checkBox_TabLZ->isChecked() == true)
				{
					struct Lok_zdjeciowe m_buff;
					QFile lz_src(QString::fromWCharArray(flm_eks.pths.BF_LZ));
					lz_src.open(QFile::ReadOnly);
					unsigned int stop_m = lz_src.size();
					bool head_wrttn = false;
					bool close_html = false;
					for (unsigned int y = 0; y < stop_m; )
					{
						lz_src.seek(y);
						lz_src.read(reinterpret_cast<char *>(&m_buff),sizeof(m_buff));
						if (y == (lz_src.size() - sizeof(m_buff)))
						{
							close_html = true;
						}
						Eksportuj_data_LZ(&m_buff, head_wrttn, close_html);
						head_wrttn = true;
						y = y + sizeof(m_buff);
					}
				}
		        if (ui->checkBox_TabW->isChecked() == true)
				{
					struct Wypozycz_Innym m_buff;
					QFile wi_src(QString::fromWCharArray(flm_eks.pths.BF_WI));
					wi_src.open(QFile::ReadOnly);
					unsigned int stop_m = wi_src.size();
					bool head_wrttn = false;
					bool close_html = false;
					for (unsigned int y = 0; y < stop_m; )
					{
						wi_src.seek(y);
						wi_src.read(reinterpret_cast<char *>(&m_buff),sizeof(m_buff));
						if (y == (wi_src.size() - sizeof(m_buff)))
						{
							close_html = true;
						}
						Eksportuj_data_WIN(&m_buff, head_wrttn, close_html);
						head_wrttn = true;
						y = y + sizeof(m_buff);
					}

					struct Wypozycz_Od_Innych md_buff;
					QFile wo_src(QString::fromWCharArray(flm_eks.pths.BF_WO));
					wo_src.open(QFile::ReadOnly);
					unsigned int stop_md = wo_src.size();
					bool head_wrttnd = false;
					bool close_htmld = false;
					for (unsigned int y = 0; y < stop_md; )
					{
						wo_src.seek(y);
						wo_src.read(reinterpret_cast<char *>(&md_buff),sizeof(md_buff));
						if (y == (wo_src.size() - sizeof(md_buff)))
						{
							close_html = true;
						}
						Eksportuj_data_WON(&md_buff, head_wrttnd, close_htmld);
						head_wrttnd = true;
						y = y + sizeof(m_buff);
					}
				}
               
            }
            else
            {
				Film* flm_p = &flm_eks.film_tbl;
				bool head_wrttn = false;
				bool close_html = true;
				
                Eksportuj_data_MAIN(flm_p, head_wrttn, close_html);
				if (ui->checkBox_TabOcena->isChecked() == true)
				{
					struct Ocena m_buff;
					QFile oc_src(QString::fromWCharArray(flm_eks.pths.BF_OC));
					oc_src.open(QFile::ReadOnly);
					unsigned int stop_m = oc_src.size();
					bool head_wrttn = false;
					bool close_html = false;
					for (unsigned int y = 0; y < stop_m; )
					{
						oc_src.seek(y);
						oc_src.read(reinterpret_cast<char *>(&m_buff),sizeof(m_buff));
						if (y == (oc_src.size() - sizeof(m_buff)))
						{
							close_html = true;
						}
						if (m_buff.IDPDB == flm_p->ID)
						{
							Eksportuj_data_OC(&m_buff, head_wrttn, close_html);
							head_wrttn = true;
						}
						
						y = y + sizeof(m_buff);
					}
				}
				if (ui->checkBox_TabObsada->isChecked() == true)
				{
					struct Obsada m_buff;
					QFile ob_src(QString::fromWCharArray(flm_eks.pths.BF_OB));
					ob_src.open(QFile::ReadOnly);
					unsigned int stop_m = ob_src.size();
					bool head_wrttn = false;
					bool close_html = false;
					for (unsigned int y = 0; y < stop_m; )
					{
						ob_src.seek(y);
						ob_src.read(reinterpret_cast<char *>(&m_buff),sizeof(m_buff));
						if (y == (ob_src.size() - sizeof(m_buff)))
						{
							close_html = true;
						}
						if (m_buff.IDPDB == flm_p->ID)
						{
							Eksportuj_data_OB(&m_buff, head_wrttn, close_html);
							head_wrttn = true;
						}
						
						y = y + sizeof(m_buff);
					}
				}
				if (ui->checkBox_TabPD->isChecked() == true)
				{
					struct Producent m_buff;
					QFile pp_src(QString::fromWCharArray(flm_eks.pths.BF_PRP));
					pp_src.open(QFile::ReadOnly);
					unsigned int stop_m = pp_src.size();
					bool head_wrttn = false;
					bool close_html = false;
					for (unsigned int y = 0; y < stop_m; )
					{
						pp_src.seek(y);
						pp_src.read(reinterpret_cast<char *>(&m_buff),sizeof(m_buff));
						if (y == (pp_src.size() - sizeof(m_buff)))
						{
							close_html = true;
						}
						if (m_buff.IDPDB == flm_p->ID)
						{
							Eksportuj_data_PP(&m_buff, head_wrttn, close_html);
							head_wrttn = true;
						}
						
						y = y + sizeof(m_buff);
					}
				
					struct Dystrybutor md_buff;
					QFile pd_src(QString::fromWCharArray(flm_eks.pths.BF_PRD));
					pd_src.open(QFile::ReadOnly);
					unsigned int stop_md = pd_src.size();
					bool head_wrttnd = false;
					bool close_htmld = false;
					for (unsigned int y = 0; y < stop_md; )
					{
						pd_src.seek(y);
						pd_src.read(reinterpret_cast<char *>(&md_buff),sizeof(md_buff));
						if (y == (pd_src.size() - sizeof(md_buff)))
						{
							close_htmld = true;
						}
						if (md_buff.IDPDB == flm_p->ID)
						{
							Eksportuj_data_PD(&md_buff, head_wrttnd, close_htmld);
							head_wrttnd = true;
						}
						
						y = y + sizeof(md_buff);
					}
				}
				if (ui->checkBox_TabLZ->isChecked() == true)
				{
					struct Lok_zdjeciowe m_buff;
					QFile lz_src(QString::fromWCharArray(flm_eks.pths.BF_LZ));
					lz_src.open(QFile::ReadOnly);
					unsigned int stop_m = lz_src.size();
					bool head_wrttn = false;
					bool close_html = false;
					for (unsigned int y = 0; y < stop_m; )
					{
						lz_src.seek(y);
						lz_src.read(reinterpret_cast<char *>(&m_buff),sizeof(m_buff));
						if (y == (lz_src.size() - sizeof(m_buff)))
						{
							close_html = true;
						}
						if (m_buff.IDPDB == flm_p->ID)
						{
							Eksportuj_data_LZ(&m_buff, head_wrttn, close_html);
							head_wrttn = true;
						}
						
						y = y + sizeof(m_buff);
					}
				}
				if (ui->checkBox_TabW->isChecked() == true)
				{
					struct Wypozycz_Innym m_buff;
					QFile wi_src(QString::fromWCharArray(flm_eks.pths.BF_WI));
					wi_src.open(QFile::ReadOnly);
					unsigned int stop_m = wi_src.size();
					bool head_wrttn = false;
					bool close_html = false;
					for (unsigned int y = 0; y < stop_m; )
					{
						wi_src.seek(y);
						wi_src.read(reinterpret_cast<char *>(&m_buff),sizeof(m_buff));
						if (y == (wi_src.size() - sizeof(m_buff)))
						{
							close_html = true;
						}
						if (m_buff.IDPDB == flm_p->ID)
						{
							Eksportuj_data_WIN(&m_buff, head_wrttn, close_html);
							head_wrttn = true;
						}
						
						y = y + sizeof(m_buff);
					}

					struct Wypozycz_Od_Innych md_buff;
					QFile wo_src(QString::fromWCharArray(flm_eks.pths.BF_WO));
					wo_src.open(QFile::ReadOnly);
					unsigned int stop_md = wo_src.size();
					bool head_wrttnd = false;
					bool close_htmld = false;
					for (unsigned int y = 0; y < stop_md; )
					{
						wo_src.seek(y);
						wo_src.read(reinterpret_cast<char *>(&md_buff),sizeof(md_buff));
						if (y == (wo_src.size() - sizeof(md_buff)))
						{
							close_htmld = true;
						}
						if (md_buff.IDPDB == flm_p->ID)
						{
							Eksportuj_data_WON(&md_buff, head_wrttnd, close_htmld);
							head_wrttnd = true;
						}
						
						y = y + sizeof(m_buff);
					}
				}

            }
}
void Eksportuj::Eksportuj_data_MAIN(struct Film* flm_ptr, bool head_wrttn, bool html_end)
{
    QFile fn_exp(ui->lineEdit_Eks_path->text());
    fn_exp.open(QFile::Append | QFile::Text);
    QTextStream fnout(&fn_exp);

	if (!head_wrttn)
	{
		fnout << tr("Biblioteka Filmow - eksported data") << "\n\r";
	}
    struct Film film_buff;
    QFile main(QString::fromWCharArray(flm_eks.pths.BF_PDB));
    main.open(QFile::ReadOnly);
    unsigned int stop = main.size();
	if (!head_wrttn)
	{
		fnout << tr("Tabela g³ówna - Film") << "\n\r";
		fnout << QString::fromWCharArray(L"\"ID\"") << tr(",\"title\"") <<  tr(",\"original title\"") << tr(",\"genre\"");
		fnout << tr(",\"Dane o Egzemplarzu - Cena\"") << tr(",\"Dane o Egzemplarzu - Data skatalogowania\"");
		fnout << tr(",\"Dane o Egzemplarzu - Data utraty\"") << tr(",\"Dane o Egzemplarzu - Data zakupu\"");
		fnout << tr(",\"Dane o Egzemplarzu - Miejsce Nabycia - Nazwa\"") << tr(",\"Dane o Egzemplarzu - Miejsce Nabycia - Adres\"");
		fnout << tr(",\"Dane o Egzemplarzu - Miejsce Nabycia - E-mail\"") << tr(",\"Dane o Egzemplarzu - Miejsce Nabycia - Telefon\"");
		fnout << tr(",\"Dane o Egzemplarzu - Miejsce Nabycia - Fax\"") << tr(",\"Dane o Egzemplarzu - Miejsce Nabycia - WWW\"");
		fnout << tr(",\"Dane o Egzemplarzu - W³aœciciel Kopii Filmu - Imiê\"") << tr(",\"Dane o Egzemplarzu - W³aœciciel Kopii Filmu - Nazwisko\"");
		fnout << tr(",\"Dane o Egzemplarzu - W³aœciciel Kopii Filmu - Adres\"") << tr(",\"Dane o Egzemplarzu - Nr katalogowy\"");
		fnout << tr(",\"Dane o Egzemplarzu - Noœnik\"") << tr(",\"Dane o Egzemplarzu - Wartoœæ aktualna\"");
		fnout << tr(",\"Informacje o Filmie - Data premiery\"") << tr(",\"Informacje o Filmie - Czas trwania\"");
		fnout << tr(",\"Informacje o Filmie - Format wyœwietlania\"") << tr(",\"Informacje o Filmie - jêzyk lektora\"");
		fnout << tr(",\"Informacje o Filmie - jêzyk napisów\"") << tr(",\"Informacje o Filmie - Kodek dŸwiêku - nazwa\"");
		fnout << tr(",\"Informacje o Filmie - Kodek dŸwiêku - typ\"") << tr(",\"Informacje o Filmie - Kodek dŸwiêku - wersja\"");
		fnout << tr(",\"Informacje o Filmie - Kodek wideo - nazwa\"") << tr(",\"Informacje o Filmie - Kodek wideo - typ\"");
		fnout << tr(",\"Informacje o Filmie - Kodek wideo - wersja\"") << tr(",\"Informacje o Filmie - Zabezpieczenia - nazwa\"");
		fnout << tr(",\"Informacje o Filmie - Zabezpieczenia - typ\"") << tr(",\"Informacje o Filmie - Zabezpieczenia - wersja\"");
		fnout << tr(",\"Informacje o Filmie - Kraj produkcji filmu\"") << tr(",\"Informacje o Filmie - Rok produkcji\"");
		fnout << tr(",\"Informacje o Filmie - System kodowania obrazu\"") << tr(",\"Obsada - Re¿yser - Imie i Nazwisko\"");
		fnout << tr(",\"Obsada - Re¿yser - Narodowoœæ\"") << tr(",\"Obsada - Scenarzysta - Imiê i Nazwisko\"");
		fnout << tr(",\"Obsada - Scenarzysta - Narodowoœæ\"") << tr(",\"Obsada - Muzyka - Imie i Nazwisko\"");
		fnout << tr(",\"Obsada - Muzyka - Narodowoœæ\"") << tr(",\"Obsada - Zdjêcia - Imiê i Nazwisko\"");
		fnout << tr(",\"Obsada - Zdjêcia - Narodowoœæ\"") << tr(",\"Ocena - W³asna Ocena Filmu - Obsada\"");
		fnout << tr(",\"Ocena - W³asna Ocena Filmu - Œcie¿ka dŸwiêkowa\"") << tr(",\"Ocena - W³asna Ocena Filmu - Wartoœc artystyczna\"");
		fnout << tr(",\"Ocena - W³asna Ocena Filmu - Zdjêcia\"") << tr(",\"Ocena - W³asna Ocena Filmu - Ca³oœæ\"");
		fnout << tr(",\"Œcie¿ka - skan ok³adki - przód\"") << tr(",\"Œcie¿ka - skan ok³adki - ty³\"") << "\n\r";
	}
    fnout << "\"" << flm_ptr->ID << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->tytul);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->oryginalny_tytul);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->gatunek_filmu);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_cena);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_data_skatalogowania);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_data_utraty);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_data_zakupu);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_MN_nazwa);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_MN_adres);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_MN_email);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_MN_telefon);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_MN_fax);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_MN_www);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_WKF_imie);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_WKF_nazwisko);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_WKF_adres);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_Nr_kat);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_rodzaj_nosnika);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->DOE_wartosc_akt);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_data_premiery);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_czas_trwania);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_format_wysw);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_jezyk_lektora);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_jezyk_napisow);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_DZWIEK_nazwa);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_DZWIEK_typ);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_DZWIEK_wersja);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_KODEK_nazwa);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_KODEK_typ);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_KODEK_wersja);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_ZABEZP_nazwa);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_ZABEZP_typ);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_ZABEZP_wersja);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_kraj_produkcji_filmu);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_rok_produkcji);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->IOF_system_kodowania_obrazu);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->O_rezyser_imie_nazw);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->O_rezyser_narod);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->O_scenariusz_imie_nazw);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->O_scenariusz_narod);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->O_muzyka_imie_nazw);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->O_muzyka_narod);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->O_operator_imie_nazw);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->O_operator_narod);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->WOF_obsada);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->WOF_sciezka_dz);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->WOF_w_art);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->WOF_zdjecia);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->WOF_calosc);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->skan_przod_path);
    fnout << "\"" << "," << "\"";
    fnout << QString::fromWCharArray(flm_ptr->skan_tyl_path);
    fnout << "\"" << "\n\r";

   fn_exp.close();
}
void Eksportuj::Eksportuj_data_OC(struct Ocena* oc_ptr, bool head_wrttn, bool html_end)
{
    QFile fn_exp(ui->lineEdit_Eks_path->text());
    fn_exp.open(QFile::Append | QFile::Text);
    QTextStream fnout(&fn_exp);
       
    if (!head_wrttn)
	{
		fnout << tr("Tabela Ocena") << "\n\r";
		fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Nazwa\"") << tr(",\"Tytu³ tekstu\"") << tr(",\"Autor tekstu\"") <<
		tr(",\"Strona WWW\"") << tr(",\"Ocena krytyka\"") << "\n\r";
	}

    fnout << "\"" << oc_ptr->ID << "\"" << ",\"" << oc_ptr->IDPDB << "\"" << ",\"";
    fnout << QString::fromWCharArray(oc_ptr->nazwa);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(oc_ptr->tytul_tekstu);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(oc_ptr->autor_tekstu);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(oc_ptr->strona_www);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(oc_ptr->ocena_krytyka);
    fnout << "\"" << "\n\r";
    fn_exp.close();
}
void Eksportuj::Eksportuj_data_OB(struct Obsada* ob_ptr, bool head_wrttn, bool html_end)
{
    QFile fn_exp(ui->lineEdit_Eks_path->text());
    fn_exp.open(QFile::Append | QFile::Text);
    QTextStream fnout(&fn_exp);
	if (!head_wrttn)
	{
		fnout << tr("Tabela Obsada") << "\n\r";
	    fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\" Imiê i Nazwisko\"") << tr(",\" Rola\"") << "\n\r";
	}

    fnout << "\"" << ob_ptr->ID << "\"" << ",\"" << ob_ptr->IDPDB << "\"" << ",\"";
    fnout << QString::fromWCharArray(ob_ptr->imie_nazw);
    fnout << "\"" << ",\"" << QString::fromWCharArray(ob_ptr->rola) << "\"" << "\n\r";

    fn_exp.close();

}
void Eksportuj::Eksportuj_data_PP(struct Producent* pp_ptr, bool head_wrttn, bool html_end)
{
	QFile fn_exp(ui->lineEdit_Eks_path->text());
    fn_exp.open(QFile::Append | QFile::Text);
    QTextStream fnout(&fn_exp);
	if(!head_wrttn)
	{
        fnout << tr("Tabela Produkcja") << "\n\r";
        fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Nazwa Firmy\"") << tr(",\"Adres\"") << tr(",\"Telefon\"");
        fnout << tr(",\"Fax\"") << tr(",\"E-mail\"") << tr(",\"Strona WWW\"") << tr(",\"Narodowoœæ\"") << "\n\r";
	}

    fnout << "\"" << pp_ptr->ID << "\"" << ",\"" << pp_ptr->IDPDB << "\"" << ",\"";
    fnout << QString::fromWCharArray(pp_ptr->nazwa_firmy);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(pp_ptr->adres);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(pp_ptr->telefon);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(pp_ptr->fax);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(pp_ptr->email);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(pp_ptr->strona_www);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(pp_ptr->narodowosc);
    fnout << "\"" << "\n\r";
    fn_exp.close();
}
void Eksportuj::Eksportuj_data_PD(struct Dystrybutor* pd_ptr, bool head_wrttn, bool html_end)
{
		QFile fn_exp(ui->lineEdit_Eks_path->text());
		fn_exp.open(QFile::Append | QFile::Text);
		QTextStream fnout(&fn_exp);

if (!head_wrttn)
	{
            fnout << tr("Tabela Dystrybucja") <<"\n\r";
            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Nazwa Firmy\"") << tr(",\"Adres\"") << tr(",\"Telefon\"");
            fnout << tr(",\"Fax\"") << tr(",\"E-mail\"") << tr(",\"Strona WWW\"") << tr(",\"Narodowoœæ\"") << "\n\r";
	}

    fnout << "\"" << pd_ptr->ID << "\"" << ",\"" << pd_ptr->IDPDB << "\"" << ",\"";
    fnout << QString::fromWCharArray(pd_ptr->nazwa_firmy);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(pd_ptr->adres);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(pd_ptr->telefon);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(pd_ptr->fax);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(pd_ptr->email);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(pd_ptr->strona_www);
    fnout << "\"" << ",\"";
    fnout << QString::fromWCharArray(pd_ptr->narodowosc);
    fnout << "\"" << "\n\r";

    fn_exp.close();

}
void Eksportuj::Eksportuj_data_LZ(struct Lok_zdjeciowe* lz_ptr, bool head_wrttn, bool html_end)
{
        QFile fn_exp(ui->lineEdit_Eks_path->text());
		fn_exp.open(QFile::Append | QFile::Text);
		QTextStream fnout(&fn_exp);

		if (!head_wrttn)
		{
            fnout << tr("Tabela Lokalizacje Zdjêciowe") << "\n\r";
            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Nazwa obiektu\"") << tr(",\"Kraj\"") << tr(",\"Miejscowoœæ\"");
            fnout << tr(",\"Region\"") << tr(",\"Pora roku\"") << tr(",\"Data\"") << "\n\r";
		}
        fnout << "\"" << lz_ptr->ID << "\"" << ",\"" << lz_ptr->IDPDB << "\"" << ",\"";
        fnout << QString::fromWCharArray(lz_ptr->nazwa_obiektu);
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(lz_ptr->kraj);
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(lz_ptr->miejscowosc);
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(lz_ptr->region);
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(lz_ptr->pora_roku);
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(lz_ptr->data);
        fnout << "\"" << "\n\r";
        fn_exp.close();

}
void Eksportuj::Eksportuj_data_WIN(struct Wypozycz_Innym* wi_ptr, bool head_wrttn, bool html_end)
{
        QFile fn_exp(ui->lineEdit_Eks_path->text());
		fn_exp.open(QFile::Append | QFile::Text);
		QTextStream fnout(&fn_exp);

		if (!head_wrttn)
		{
			fnout << tr("Tabela Wypo¿yczenia Innym Osobom") << "\n\r";
            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Data wypo¿yczenia\"") << tr(",\"Data oddania\"");
            fnout << tr(",\"Stan przed wypo¿yczeniem\"") << tr(",\"Stan po oddaniu\"") << tr(",\"Osoba\"");
            fnout << tr(",\"Nr katalogowy\"") << "\n\r";
		}

        fnout << "\"" << wi_ptr->ID << "\"" << ",\"" << wi_ptr->IDPDB;
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(wi_ptr->data_wypozyczenia);
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(wi_ptr->data_oddania);
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(wi_ptr->stan_przed_wypozycz);
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(wi_ptr->stan_po_oddaniu);
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(wi_ptr->osoba);
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(wi_ptr->Nr_kat);
        fnout << "\"" << "\n\r";
        fn_exp.close();

}
void Eksportuj::Eksportuj_data_WON(struct Wypozycz_Od_Innych* wo_ptr, bool head_wrttn, bool html_end)
{
        QFile fn_exp(ui->lineEdit_Eks_path->text());
		fn_exp.open(QFile::Append | QFile::Text);
		QTextStream fnout(&fn_exp);

		if (!head_wrttn)
		{
            fnout << tr("Tabela Wypo¿yczenia od Innych Osób") << "\n\r";
            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Data wypo¿yczenia\"") << tr(",\"Data oddania\"");
            fnout << tr(",\"Stan przed wypo¿yczeniem\"") << tr(",\"Stan po oddaniu\"") << tr(",\"Osoba\"");
            fnout << tr(",\"Nr katalogowy\"") << "\n\r";
		}

        fnout << "\"" << wo_ptr->ID << "\"" << ",\"" << wo_ptr->IDPDB;
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(wo_ptr->data_wypozyczenia);
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(wo_ptr->data_oddania);
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(wo_ptr->stan_przed_wypozycz);
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(wo_ptr->stan_po_oddaniu);
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(wo_ptr->osoba);
        fnout << "\"" << ",\"";
        fnout << QString::fromWCharArray(wo_ptr->Nr_kat);
        fnout << "\"" << "\n\r";
        fn_exp.close();

}

void Eksportuj::on_pushButton_Anuluj_clicked()
{
    this->close();
}
