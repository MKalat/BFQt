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
    fdlg.setNameFilter("Pliki arkuszy (*.csv )");
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
                Eksportuj_all();
            }
            else
            {
                Eksportuj_current();
            }
}
void Eksportuj::Eksportuj_all()
{

    QFile fn_exp(ui->lineEdit_Eks_path->text());
    fn_exp.open(QFile::Append | QFile::Text);
    QTextStream fnout(&fn_exp);

    fnout << QString::fromWCharArray(L"Biblioteka Filmów - wyeksportowane dane") << "\n\r";


        if (ui->checkBox_MainFilm->isChecked() == true)
        {
            struct Film film_buff;
            QFile main(QString::fromWCharArray(flm_eks.pths.BF_PDB));
            main.open(QFile::ReadOnly);
            unsigned int stop = main.size();
            fnout << QString::fromWCharArray(L"Tabela g³ówna - Film") << "\n\r";
            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"tytu³\"") <<  QString::fromWCharArray(L",\"oryginalny tytu³\"") << QString::fromWCharArray(L",\"gatunek filmu\"");
            fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Cena\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Data skatalogowania\"");
            fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Data utraty\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Data zakupu\"");
            fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Miejsce Nabycia - Nazwa\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Miejsce Nabycia - Adres\"");
            fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Miejsce Nabycia - E-mail\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Miejsce Nabycia - Telefon\"");
            fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Miejsce Nabycia - Fax\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Miejsce Nabycia - WWW\"");
            fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - W³aœciciel Kopii Filmu - Imiê\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - W³aœciciel Kopii Filmu - Nazwisko\"");
            fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - W³aœciciel Kopii Filmu - Adres\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Nr katalogowy\"");
            fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Noœnik\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Wartoœæ aktualna\"");
            fnout << QString::fromWCharArray(L",\"Informacje o Filmie - Data premiery\"") << QString::fromWCharArray(L",\"Informacje o Filmie - Czas trwania\"");
            fnout << QString::fromWCharArray(L",\"Informacje o Filmie - Format wyœwietlania\"") << QString::fromWCharArray(L",\"Informacje o Filmie - jêzyk lektora\"");
            fnout << QString::fromWCharArray(L",\"Informacje o Filmie - jêzyk napisów\"") << QString::fromWCharArray(L",\"Informacje o Filmie - Kodek dŸwiêku - nazwa\"");
            fnout << QString::fromWCharArray(L",\"Informacje o Filmie - Kodek dŸwiêku - typ\"") << QString::fromWCharArray(L",\"Informacje o Filmie - Kodek dŸwiêku - wersja\"");
            fnout << QString::fromWCharArray(L",\"Informacje o Filmie - Kodek wideo - nazwa\"") << QString::fromWCharArray(L",\"Informacje o Filmie - Kodek wideo - typ\"");
            fnout << QString::fromWCharArray(L",\"Informacje o Filmie - Kodek wideo - wersja\"") << QString::fromWCharArray(L",\"Informacje o Filmie - Zabezpieczenia - nazwa\"");
            fnout << QString::fromWCharArray(L",\"Informacje o Filmie - Zabezpieczenia - typ\"") << QString::fromWCharArray(L",\"Informacje o Filmie - Zabezpieczenia - wersja\"");
            fnout << QString::fromWCharArray(L",\"Informacje o Filmie - Kraj produkcji filmu\"") << QString::fromWCharArray(L",\"Informacje o Filmie - Rok produkcji\"");
            fnout << QString::fromWCharArray(L",\"Informacje o Filmie - System kodowania obrazu\"") << QString::fromWCharArray(L",\"Obsada - Re¿yser - Imie i Nazwisko\"");
            fnout << QString::fromWCharArray(L",\"Obsada - Re¿yser - Narodowoœæ\"") << QString::fromWCharArray(L",\"Obsada - Scenarzysta - Imiê i Nazwisko\"");
            fnout << QString::fromWCharArray(L",\"Obsada - Scenarzysta - Narodowoœæ\"") << QString::fromWCharArray(L",\"Obsada - Muzyka - Imie i Nazwisko\"");
            fnout << QString::fromWCharArray(L",\"Obsada - Muzyka - Narodowoœæ\"") << QString::fromWCharArray(L",\"Obsada - Zdjêcia - Imiê i Nazwisko\"");
            fnout << QString::fromWCharArray(L",\"Obsada - Zdjêcia - Narodowoœæ\"") << QString::fromWCharArray(L",\"Ocena - W³asna Ocena Filmu - Obsada\"");
            fnout << QString::fromWCharArray(L",\"Ocena - W³asna Ocena Filmu - Œcie¿ka dŸwiêkowa\"") << QString::fromWCharArray(L",\"Ocena - W³asna Ocena Filmu - Wartoœc artystyczna\"");
            fnout << QString::fromWCharArray(L",\"Ocena - W³asna Ocena Filmu - Zdjêcia\"") << QString::fromWCharArray(L",\"Ocena - W³asna Ocena Filmu - Ca³oœæ\"");
            fnout << QString::fromWCharArray(L",\"Scie¿ka - skan ok³adki - przód\"") << QString::fromWCharArray(L",\"Scie¿ka - skan ok³adki - ty³\"") << "\n\r";


            for (unsigned int i = 0; i < stop; )
            {
                main.seek(i);
                main.read(reinterpret_cast<char *>(&film_buff),sizeof(Film));
                fnout << "\"" << film_buff.ID << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.tytul);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.oryginalny_tytul);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.gatunek_filmu);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_cena);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_data_skatalogowania);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_data_utraty);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_data_zakupu);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_MN_nazwa);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_MN_adres);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_MN_email);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_MN_telefon);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_MN_fax);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_MN_www);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_WKF_imie);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_WKF_nazwisko);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_WKF_adres);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_Nr_kat);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_rodzaj_nosnika);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_wartosc_akt);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_data_premiery);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_czas_trwania);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_format_wysw);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_jezyk_lektora);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_jezyk_napisow);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_DZWIEK_nazwa);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_DZWIEK_typ);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_DZWIEK_wersja);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_KODEK_nazwa);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_KODEK_typ);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_KODEK_wersja);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_ZABEZP_nazwa);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_ZABEZP_typ);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_ZABEZP_wersja);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_kraj_produkcji_filmu);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_rok_produkcji);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_system_kodowania_obrazu);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_rezyser_imie_nazw);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_rezyser_narod);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_scenariusz_imie_nazw);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_scenariusz_narod);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_muzyka_imie_nazw);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_muzyka_narod);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_operator_imie_nazw);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_operator_narod);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.WOF_obsada);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.WOF_sciezka_dz);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.WOF_w_art);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.WOF_zdjecia);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.WOF_calosc);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.skan_przod_path);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.skan_tyl_path);
                fnout << "\"" << "\n\r";
                i = i + sizeof(Film);
            }
            main.close();
        }



        if (ui->checkBox_TabOcena->isChecked() == true)
        {
            struct Ocena oc_buff;
            QFile oc_src(QString::fromWCharArray(flm_eks.pths.BF_OC));
            oc_src.open(QFile::ReadOnly);
            fnout << QString::fromWCharArray(L"Tabela Ocena") << "\n\r";

            unsigned int stop = oc_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << QString::fromWCharArray(L",\"Nazwa\"") << QString::fromWCharArray(L",\"Tytu³ tekstu\"") << QString::fromWCharArray(L",\"Autor tekstu\"") <<
            QString::fromWCharArray(L",\"Strona WWW\"") << QString::fromWCharArray(L",\"Ocena krytyka\"") << "\n\r";


            for (unsigned int i = 0; i < stop; )
            {
                oc_src.seek(i);
                oc_src.read(reinterpret_cast<char *>(&oc_buff),sizeof(oc_buff));

                fnout << "\"" << oc_buff.ID << "\"" << ",\"" << oc_buff.IDPDB << "\"" << ",\"";
                fnout << QString::fromWCharArray(oc_buff.nazwa);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(oc_buff.tytul_tekstu);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(oc_buff.autor_tekstu);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(oc_buff.strona_www);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(oc_buff.ocena_krytyka);
                fnout << "\"" << "\n\r";
                i = i + sizeof(oc_src);
            }
            oc_src.close();
        }

        if (ui->checkBox_TabObsada->isChecked() == true)
        {
            struct Obsada ob_buff;
            QFile ob_src(QString::fromWCharArray(flm_eks.pths.BF_OB));
            ob_src.open(QFile::ReadOnly);
            fnout << QString::fromWCharArray(L"Tabela Obsada") << "\n\r";

            unsigned int stop = ob_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << QString::fromWCharArray(L",\" Imiê i Nazwisko\"") << QString::fromWCharArray(L",\" Rola\"") << "\n\r";


            for (unsigned int i = 0; i < stop; )
            {
                ob_src.seek(i);
                ob_src.read(reinterpret_cast<char *>(&ob_buff),sizeof(ob_buff));

                fnout << "\"" << ob_buff.ID << "\"" << ",\"" << ob_buff.IDPDB << "\"" << ",\"";
                fnout << QString::fromWCharArray(ob_buff.imie_nazw);
                fnout << "\"" << ",\"" << QString::fromWCharArray(ob_buff.rola) << "\"" << "\n\r";

                i = i + sizeof(ob_buff);
            }
            ob_src.close();

        }

        if (ui->checkBox_TabPD->isChecked() == true)
        {
            struct Producent pp_buff;
            QFile pp_src(QString::fromWCharArray(flm_eks.pths.BF_PRP));
            pp_src.open(QFile::ReadOnly);
            fnout << QString::fromWCharArray(L"Tabela Produkcja") << "\n\r";

            unsigned int stop = pp_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << QString::fromWCharArray(L",\"Nazwa Firmy\"") << QString::fromWCharArray(L",\"Adres\"") << QString::fromWCharArray(L",\"Telefon\"");
            fnout << QString::fromWCharArray(L",\"Fax\"") << QString::fromWCharArray(L",\"E-mail\"") << QString::fromWCharArray(L",\"Strona WWW\"") << QString::fromWCharArray(L",\"Narodowoœæ\"") << "\n\r";

            for (unsigned int i = 0; i < stop; )
            {
                pp_src.seek(i);
                pp_src.read(reinterpret_cast<char *>(&pp_buff),sizeof(pp_buff));

                fnout << "\"" << pp_buff.ID << "\"" << ",\"" << pp_buff.IDPDB << "\"" << ",\"";
                fnout << QString::fromWCharArray(pp_buff.nazwa_firmy);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(pp_buff.adres);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(pp_buff.telefon);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(pp_buff.fax);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(pp_buff.email);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(pp_buff.strona_www);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(pp_buff.narodowosc);
                fnout << "\"" << "\n\r";

                i = i + sizeof(pp_buff);
            }
            pp_src.close();

            struct Dystrybutor pd_buff;
            QFile pd_src(QString::fromWCharArray(flm_eks.pths.BF_PRD));
            pd_src.open(QFile::ReadOnly);
            fnout << QString::fromWCharArray(L"Tabela Dystrybucja") <<"\n\r";

            stop = pd_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << QString::fromWCharArray(L",\"Nazwa Firmy\"") << QString::fromWCharArray(L",\"Adres\"") << QString::fromWCharArray(L",\"Telefon\"");
            fnout << QString::fromWCharArray(L",\"Fax\"") << QString::fromWCharArray(L",\"E-mail\"") << QString::fromWCharArray(L",\"Strona WWW\"") << QString::fromWCharArray(L",\"Narodowoœæ\"") << "\n\r";


            for (unsigned int i = 0; i < stop; )
            {
                pd_src.seek(i);
                pd_src.read(reinterpret_cast<char *>(&pd_buff),sizeof(pd_buff));

                fnout << "\"" << pd_buff.ID << "\"" << ",\"" << pd_buff.IDPDB << "\"" << ",\"";
                fnout << QString::fromWCharArray(pd_buff.nazwa_firmy);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(pd_buff.adres);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(pd_buff.telefon);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(pd_buff.fax);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(pd_buff.email);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(pd_buff.strona_www);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(pd_buff.narodowosc);
                fnout << "\"" << "\n\r";

                i = i + sizeof(pd_buff);
            }
            pd_src.close();

        }

        if (ui->checkBox_TabLZ->isChecked() == true)
        {
            struct Lok_zdjeciowe lz_buff;
            QFile lz_src(QString::fromWCharArray(flm_eks.pths.BF_LZ));
            lz_src.open(QFile::ReadOnly);
            fnout << QString::fromWCharArray(L"Tabela Lokalizacje Zdjêciowe") << "\n\r";

            unsigned int stop = lz_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << QString::fromWCharArray(L",\"Nazwa obiektu\"") << QString::fromWCharArray(L",\"Kraj\"") << QString::fromWCharArray(L",\"Miejscowoœæ\"");
            fnout << QString::fromWCharArray(L",\"Region\"") << QString::fromWCharArray(L",\"Pora roku\"") << QString::fromWCharArray(L",\"Data\"") << "\n\r";


            for (unsigned int i = 0; i < stop; )
            {
                lz_src.seek(i);
                lz_src.read(reinterpret_cast<char *>(&lz_buff),sizeof(lz_buff));

                fnout << "\"" << lz_buff.ID << "\"" << ",\"" << lz_buff.IDPDB << "\"" << ",\"";
                fnout << QString::fromWCharArray(lz_buff.nazwa_obiektu);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(lz_buff.kraj);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(lz_buff.miejscowosc);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(lz_buff.region);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(lz_buff.pora_roku);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(lz_buff.data);
                fnout << "\"" << "\n\r";

                i = i + sizeof(lz_buff);
            }
            lz_src.close();
        }

        if (ui->checkBox_TabW->isChecked() == true)
        {
            struct Wypozycz_Innym wi_buff;
            QFile wi_src(QString::fromWCharArray(flm_eks.pths.BF_WI));
            wi_src.open(QFile::ReadOnly);
            fnout << QString::fromWCharArray(L"Tabela Wypo¿yczenia Innym Osobom") << "\n\r";

            unsigned int stop = wi_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << QString::fromWCharArray(L",\"Data wypo¿yczenia\"") << QString::fromWCharArray(L",\"Data oddania\"");
            fnout << QString::fromWCharArray(L",\"Stan przed wypo¿yczeniem\"") << QString::fromWCharArray(L",\"Stan po oddaniu\"") << QString::fromWCharArray(L",\"Osoba\"");
            fnout << QString::fromWCharArray(L",\"Nr katalogowy\"") << "\n\r";


            for (unsigned int i = 0; i < stop; )
            {
                wi_src.seek(i);
                wi_src.read(reinterpret_cast<char *>(&wi_buff),sizeof(wi_buff));

                fnout << "\"" << wi_buff.ID << "\"" << ",\"" << wi_buff.IDPDB;
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(wi_buff.data_wypozyczenia);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(wi_buff.data_oddania);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(wi_buff.stan_przed_wypozycz);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(wi_buff.stan_po_oddaniu);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(wi_buff.osoba);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(wi_buff.Nr_kat);
                fnout << "\"" << "\n\r";

                i = i + sizeof(wi_buff);
            }
            wi_src.close();

            struct Wypozycz_Od_Innych wo_buff;
            QFile wo_src(QString::fromWCharArray(flm_eks.pths.BF_WO));
            wo_src.open(QFile::ReadOnly);
            fnout << QString::fromWCharArray(L"Tabela Wypo¿yczenia od Innych Osób") << "\n\r";

            stop = wo_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << QString::fromWCharArray(L",\"Data wypo¿yczenia\"") << QString::fromWCharArray(L",\"Data oddania\"");
            fnout << QString::fromWCharArray(L",\"Stan przed wypo¿yczeniem\"") << QString::fromWCharArray(L",\"Stan po oddaniu\"") << QString::fromWCharArray(L",\"Osoba\"");
            fnout << QString::fromWCharArray(L",\"Nr katalogowy\"") << "\n\r";


            for (unsigned int i = 0; i < stop; )
            {
                wo_src.seek(i);
                wo_src.read(reinterpret_cast<char *>(&wo_buff),sizeof(wo_buff));

                fnout << "\"" << wo_buff.ID << "\"" << ",\"" << wo_buff.IDPDB;
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(wo_buff.data_wypozyczenia);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(wo_buff.data_oddania);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(wo_buff.stan_przed_wypozycz);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(wo_buff.stan_po_oddaniu);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(wo_buff.osoba);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(wo_buff.Nr_kat);
                fnout << "\"" << "\n\r";

                i = i + sizeof(wo_buff);
            }
            wo_src.close();
        }
        fn_exp.close();

}

void Eksportuj::Eksportuj_current()
{
    QFile fn_exp(ui->lineEdit_Eks_path->text());
    fn_exp.open(QFile::Append | QFile::Text);
    QTextStream fnout(&fn_exp);

    fnout << QString::fromWCharArray(L"Biblioteka Filmów - wyeksportowane dane") << "\n\r";
    if (ui->checkBox_MainFilm->isChecked() == true)
    {
        struct Film film_buff;
        QFile main(QString::fromWCharArray(flm_eks.pths.BF_PDB));
        main.open(QFile::ReadOnly);
        unsigned int stop = main.size();
		fnout << QString::fromWCharArray(L"Tabela g³ówna - Film") << "\n\r";
        fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"tytu³\"") <<  QString::fromWCharArray(L",\"oryginalny tytu³\"") << QString::fromWCharArray(L",\"gatunek filmu\"");
        fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Cena\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Data skatalogowania\"");
        fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Data utraty\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Data zakupu\"");
        fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Miejsce Nabycia - Nazwa\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Miejsce Nabycia - Adres\"");
        fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Miejsce Nabycia - E-mail\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Miejsce Nabycia - Telefon\"");
        fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Miejsce Nabycia - Fax\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Miejsce Nabycia - WWW\"");
		fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - W³aœciciel Kopii Filmu - Imiê\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - W³aœciciel Kopii Filmu - Nazwisko\"");
		fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - W³aœciciel Kopii Filmu - Adres\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Nr katalogowy\"");
        fnout << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Noœnik\"") << QString::fromWCharArray(L",\"Dane o Egzemplarzu - Wartoœæ aktualna\"");
        fnout << QString::fromWCharArray(L",\"Informacje o Filmie - Data premiery\"") << QString::fromWCharArray(L",\"Informacje o Filmie - Czas trwania\"");
        fnout << QString::fromWCharArray(L",\"Informacje o Filmie - Format wyœwietlania\"") << QString::fromWCharArray(L",\"Informacje o Filmie - jêzyk lektora\"");
        fnout << QString::fromWCharArray(L",\"Informacje o Filmie - jêzyk napisów\"") << QString::fromWCharArray(L",\"Informacje o Filmie - Kodek dŸwiêku - nazwa\"");
        fnout << QString::fromWCharArray(L",\"Informacje o Filmie - Kodek dŸwiêku - typ\"") << QString::fromWCharArray(L",\"Informacje o Filmie - Kodek dŸwiêku - wersja\"");
        fnout << QString::fromWCharArray(L",\"Informacje o Filmie - Kodek wideo - nazwa\"") << QString::fromWCharArray(L",\"Informacje o Filmie - Kodek wideo - typ\"");
        fnout << QString::fromWCharArray(L",\"Informacje o Filmie - Kodek wideo - wersja\"") << QString::fromWCharArray(L",\"Informacje o Filmie - Zabezpieczenia - nazwa\"");
        fnout << QString::fromWCharArray(L",\"Informacje o Filmie - Zabezpieczenia - typ\"") << QString::fromWCharArray(L",\"Informacje o Filmie - Zabezpieczenia - wersja\"");
        fnout << QString::fromWCharArray(L",\"Informacje o Filmie - Kraj produkcji filmu\"") << QString::fromWCharArray(L",\"Informacje o Filmie - Rok produkcji\"");
        fnout << QString::fromWCharArray(L",\"Informacje o Filmie - System kodowania obrazu\"") << QString::fromWCharArray(L",\"Obsada - Re¿yser - Imie i Nazwisko\"");
        fnout << QString::fromWCharArray(L",\"Obsada - Re¿yser - Narodowoœæ\"") << QString::fromWCharArray(L",\"Obsada - Scenarzysta - Imiê i Nazwisko\"");
        fnout << QString::fromWCharArray(L",\"Obsada - Scenarzysta - Narodowoœæ\"") << QString::fromWCharArray(L",\"Obsada - Muzyka - Imie i Nazwisko\"");
        fnout << QString::fromWCharArray(L",\"Obsada - Muzyka - Narodowoœæ\"") << QString::fromWCharArray(L",\"Obsada - Zdjêcia - Imiê i Nazwisko\"");
        fnout << QString::fromWCharArray(L",\"Obsada - Zdjêcia - Narodowoœæ\"") << QString::fromWCharArray(L",\"Ocena - W³asna Ocena Filmu - Obsada\"");
        fnout << QString::fromWCharArray(L",\"Ocena - W³asna Ocena Filmu - Œcie¿ka dŸwiêkowa\"") << QString::fromWCharArray(L",\"Ocena - W³asna Ocena Filmu - Wartoœc artystyczna\"");
        fnout << QString::fromWCharArray(L",\"Ocena - W³asna Ocena Filmu - Zdjêcia\"") << QString::fromWCharArray(L",\"Ocena - W³asna Ocena Filmu - Ca³oœæ\"");
        fnout << QString::fromWCharArray(L",\"Scie¿ka - skan ok³adki - przód\"") << QString::fromWCharArray(L",\"Scie¿ka - skan ok³adki - ty³\"") << "\n\r";
        for (unsigned int i = 0; i < stop; )
        {
            main.seek(i);
            main.read(reinterpret_cast<char *>(&film_buff),sizeof(Film));
            if (film_buff.ID == flm_eks.film_tbl.ID)
            {
                fnout << "\"" << film_buff.ID << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.tytul);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.oryginalny_tytul);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.gatunek_filmu);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_cena);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_data_skatalogowania);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_data_utraty);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_data_zakupu);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_MN_nazwa);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_MN_adres);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_MN_email);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_MN_telefon);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_MN_fax);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_MN_www);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_WKF_imie);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_WKF_nazwisko);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_WKF_adres);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_Nr_kat);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_rodzaj_nosnika);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.DOE_wartosc_akt);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_data_premiery);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_czas_trwania);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_format_wysw);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_jezyk_lektora);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_jezyk_napisow);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_DZWIEK_nazwa);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_DZWIEK_typ);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_DZWIEK_wersja);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_KODEK_nazwa);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_KODEK_typ);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_KODEK_wersja);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_ZABEZP_nazwa);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_ZABEZP_typ);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_ZABEZP_wersja);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_kraj_produkcji_filmu);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_rok_produkcji);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.IOF_system_kodowania_obrazu);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_rezyser_imie_nazw);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_rezyser_narod);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_scenariusz_imie_nazw);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_scenariusz_narod);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_muzyka_imie_nazw);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_muzyka_narod);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_operator_imie_nazw);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.O_operator_narod);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.WOF_obsada);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.WOF_sciezka_dz);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.WOF_w_art);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.WOF_zdjecia);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.WOF_calosc);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.skan_przod_path);
                fnout << "\"" << "," << "\"";
                fnout << QString::fromWCharArray(film_buff.skan_tyl_path);
                fnout << "\"" << "\n\r";
                }
                i = i + sizeof(Film);

            }
            main.close();
        }

    if (ui->checkBox_TabOcena->isChecked() == true)
    {
        struct Ocena oc_buff;
        QFile oc_src(QString::fromWCharArray(flm_eks.pths.BF_OC));
        oc_src.open(QFile::ReadOnly);
        fnout << QString::fromWCharArray(L"Tabela Ocena") << "\n\r";

        unsigned int stop = oc_src.size();

        fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << QString::fromWCharArray(L",\"Nazwa\"") << QString::fromWCharArray(L",\"Tytu³ tekstu\"") << QString::fromWCharArray(L",\"Autor tekstu\"") <<
        QString::fromWCharArray(L",\"Strona WWW\"") << QString::fromWCharArray(L",\"Ocena krytyka\"") << "\n\r";


        for (unsigned int i = 0; i < stop; )
        {
            oc_src.seek(i);
            oc_src.read(reinterpret_cast<char *>(&oc_buff),sizeof(oc_buff));
            if (oc_buff.IDPDB == flm_eks.film_tbl.ID)
            {
                fnout << "\"" << oc_buff.ID << "\"" << ",\"" << oc_buff.IDPDB << "\"" << ",\"";
                fnout << QString::fromWCharArray(oc_buff.nazwa);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(oc_buff.tytul_tekstu);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(oc_buff.autor_tekstu);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(oc_buff.strona_www);
                fnout << "\"" << ",\"";
                fnout << QString::fromWCharArray(oc_buff.ocena_krytyka);
                fnout << "\"" << "\n\r";
             }
                i = i + sizeof(oc_src);
         }
            oc_src.close();
     }

    if (ui->checkBox_TabObsada->isChecked() == true)
    {
        struct Obsada ob_buff;
        QFile ob_src(QString::fromWCharArray(flm_eks.pths.BF_OB));
        ob_src.open(QFile::ReadOnly);
        fnout << QString::fromWCharArray(L"Tabela Obsada") << "\n\r";

        unsigned int stop = ob_src.size();

        fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << QString::fromWCharArray(L",\" Imiê i Nazwisko\"") << QString::fromWCharArray(L",\" Rola\"") << "\n\r";


        for (unsigned int i = 0; i < stop; )
        {
            ob_src.seek(i);
            ob_src.read(reinterpret_cast<char *>(&ob_buff),sizeof(ob_buff));

            if (ob_buff.IDPDB == flm_eks.film_tbl.ID)
            {
                fnout << "\"" << ob_buff.ID << "\"" << ",\"" << ob_buff.IDPDB << "\"" << ",\"";
                fnout << QString::fromWCharArray(ob_buff.imie_nazw);
                fnout << "\"" << ",\"" << QString::fromWCharArray(ob_buff.rola) << "\"" << "\n\r";
            }
                i = i + sizeof(ob_buff);
        }
            ob_src.close();

     }

    if (ui->checkBox_TabPD->isChecked() == true)
    {
        struct Producent pp_buff;
        QFile pp_src(QString::fromWCharArray(flm_eks.pths.BF_PRP));
        pp_src.open(QFile::ReadOnly);
        fnout << QString::fromWCharArray(L"Tabela Produkcja") << "\n\r";

        unsigned int stop = pp_src.size();

        fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << QString::fromWCharArray(L",\"Nazwa Firmy\"") << QString::fromWCharArray(L",\"Adres\"") << QString::fromWCharArray(L",\"Telefon\"");
        fnout << QString::fromWCharArray(L",\"Fax\"") << QString::fromWCharArray(L",\"E-mail\"") << QString::fromWCharArray(L",\"Strona WWW\"") << QString::fromWCharArray(L",\"Narodowoœæ\"") << "\n\r";


        for (unsigned int i = 0; i < stop; )
        {
            pp_src.seek(i);
            pp_src.read(reinterpret_cast<char *>(&pp_buff),sizeof(pp_buff));

                if (pp_buff.IDPDB == flm_eks.film_tbl.ID)
                {
                    fnout << "\"" << pp_buff.ID << "\"" << ",\"" << pp_buff.IDPDB << "\"" << ",\"";
                    fnout << QString::fromWCharArray(pp_buff.nazwa_firmy);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(pp_buff.adres);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(pp_buff.telefon);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(pp_buff.fax);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(pp_buff.email);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(pp_buff.strona_www);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(pp_buff.narodowosc);
                    fnout << "\"" << "\n\r";
                }
                i = i + sizeof(pp_buff);
            }
            pp_src.close();

            struct Dystrybutor pd_buff;
            QFile pd_src(QString::fromWCharArray(flm_eks.pths.BF_PRD));
            pd_src.open(QFile::ReadOnly);
            fnout << QString::fromWCharArray(L"Tabela Dystrybucja") <<"\n\r";

            stop = pd_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << QString::fromWCharArray(L",\"Nazwa Firmy\"") << QString::fromWCharArray(L",\"Adres\"") << QString::fromWCharArray(L",\"Telefon\"");
            fnout << QString::fromWCharArray(L",\"Fax\"") << QString::fromWCharArray(L",\"E-mail\"") << QString::fromWCharArray(L",\"Strona WWW\"") << QString::fromWCharArray(L",\"Narodowoœæ\"") << "\n\r";


            for (unsigned int i = 0; i < stop; )
            {
                pd_src.seek(i);
                pd_src.read(reinterpret_cast<char *>(&pd_buff),sizeof(pd_buff));

                if (pd_buff.IDPDB == flm_eks.film_tbl.ID)
                {
                    fnout << "\"" << pd_buff.ID << "\"" << ",\"" << pd_buff.IDPDB << "\"" << ",\"";
                    fnout << QString::fromWCharArray(pd_buff.nazwa_firmy);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(pd_buff.adres);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(pd_buff.telefon);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(pd_buff.fax);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(pd_buff.email);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(pd_buff.strona_www);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(pd_buff.narodowosc);
                    fnout << "\"" << "\n\r";

                }
                i = i + sizeof(pd_buff);
            }
            pd_src.close();

        }

    if (ui->checkBox_TabLZ->isChecked() == true)
    {
        struct Lok_zdjeciowe lz_buff;
        QFile lz_src(QString::fromWCharArray(flm_eks.pths.BF_LZ));
        lz_src.open(QFile::ReadOnly);
        fnout << QString::fromWCharArray(L"Tabela Lokalizacje Zdjêciowe") << "\n\r";

        unsigned int stop = lz_src.size();

        fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << QString::fromWCharArray(L",\"Nazwa obiektu\"") << QString::fromWCharArray(L",\"Kraj\"") << QString::fromWCharArray(L",\"Miejscowoœæ\"");
        fnout << QString::fromWCharArray(L",\"Region\"") << QString::fromWCharArray(L",\"Pora roku\"") << QString::fromWCharArray(L",\"Data\"") << "\n\r";



        for (unsigned int i = 0; i < stop; )
        {
            lz_src.seek(i);
            lz_src.read(reinterpret_cast<char *>(&lz_buff),sizeof(lz_buff));

                if (lz_buff.IDPDB == flm_eks.film_tbl.ID)
                {
                    fnout << "\"" << lz_buff.ID << "\"" << ",\"" << lz_buff.IDPDB << "\"" << ",\"";
                    fnout << QString::fromWCharArray(lz_buff.nazwa_obiektu);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(lz_buff.kraj);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(lz_buff.miejscowosc);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(lz_buff.region);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(lz_buff.pora_roku);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(lz_buff.data);
                    fnout << "\"" << "\n\r";
                }
                i = i + sizeof(lz_buff);
            }
            lz_src.close();
        }

    if (ui->checkBox_TabW->isChecked() == true)
    {
        struct Wypozycz_Innym wi_buff;
        QFile wi_src(QString::fromWCharArray(flm_eks.pths.BF_WI));
        wi_src.open(QFile::ReadOnly);
        fnout << QString::fromWCharArray(L"Tabela Wypo¿yczenia Innym Osobom") << "\n\r";

        unsigned int stop = wi_src.size();

        fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << QString::fromWCharArray(L",\"Data wypo¿yczenia\"") << QString::fromWCharArray(L",\"Data oddania\"");
        fnout << QString::fromWCharArray(L",\"Stan przed wypo¿yczeniem\"") << QString::fromWCharArray(L",\"Stan po oddaniu\"") << QString::fromWCharArray(L",\"Osoba\"");
        fnout << QString::fromWCharArray(L",\"Nr katalogowy\"") << "\n\r";


        for (unsigned int i = 0; i < stop; )
        {
            wi_src.seek(i);
            wi_src.read(reinterpret_cast<char *>(&wi_buff),sizeof(wi_buff));
                if (wi_buff.IDPDB == flm_eks.film_tbl.ID)
                {
                    fnout << "\"" << wi_buff.ID << "\"" << ",\"" << wi_buff.IDPDB;
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(wi_buff.data_wypozyczenia);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(wi_buff.data_oddania);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(wi_buff.stan_przed_wypozycz);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(wi_buff.stan_po_oddaniu);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(wi_buff.osoba);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(wi_buff.Nr_kat);
                    fnout << "\"" << "\n\r";
                }


                i = i + sizeof(wi_buff);
            }
            wi_src.close();

            struct Wypozycz_Od_Innych wo_buff;
            QFile wo_src(QString::fromWCharArray(flm_eks.pths.BF_WO));
            wo_src.open(QFile::ReadOnly);
            fnout << QString::fromWCharArray(L"Tabela Wypo¿yczenia od Innych Osób") << "\n\r";

            stop = wo_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << QString::fromWCharArray(L",\"Data wypo¿yczenia\"") << QString::fromWCharArray(L",\"Data oddania\"");
            fnout << QString::fromWCharArray(L",\"Stan przed wypo¿yczeniem\"") << QString::fromWCharArray(L",\"Stan po oddaniu\"") << QString::fromWCharArray(L",\"Osoba\"");
            fnout << QString::fromWCharArray(L",\"Nr katalogowy\"") << "\n\r";


            for (unsigned int i = 0; i < stop; )
            {
                wo_src.seek(i);
                wo_src.read(reinterpret_cast<char *>(&wo_buff),sizeof(wo_buff));
                if (wo_buff.IDPDB == flm_eks.film_tbl.ID)
                {
                    fnout << "\"" << wo_buff.ID << "\"" << ",\"" << wo_buff.IDPDB;
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(wo_buff.data_wypozyczenia);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(wo_buff.data_oddania);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(wo_buff.stan_przed_wypozycz);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(wo_buff.stan_po_oddaniu);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(wo_buff.osoba);
                    fnout << "\"" << ",\"";
                    fnout << QString::fromWCharArray(wo_buff.Nr_kat);
                    fnout << "\"" << "\n\r";
                }
                i = i + sizeof(wo_buff);
            }
            wo_src.close();
        }
        fn_exp.close();

    }




void Eksportuj::on_pushButton_Anuluj_clicked()
{
    this->close();
}
