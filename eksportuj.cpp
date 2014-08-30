﻿#include "eksportuj.h"
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

    fnout << tr("Biblioteka Filmow - eksported data") << "\n\r";


        if (ui->checkBox_MainFilm->isChecked() == true)
        {
            struct Film film_buff;
            QFile main(QString::fromWCharArray(flm_eks.pths.BF_PDB));
            main.open(QFile::ReadOnly);
            unsigned int stop = main.size();
            fnout << tr("Main Table - Film") << "\n\r";
            fnout << QString::fromWCharArray(L"\"ID\"") << tr(",\"title\"") <<  tr(",\"original title\"") << tr(",\"genre\"");
            fnout << tr(",\"Data about copy - Price\"") << tr(",\"Data about copy - Data skatalogowania\"");
            fnout << tr(",\"Data about copy - Data utraty\"") << tr(",\"Data about copy - Data zakupu\"");
            fnout << tr(",\"Data about copy - Miejsce Nabycia - Nazwa\"") << tr(",\"Data about copy - Miejsce Nabycia - Adres\"");
            fnout << tr(",\"Data about copy - Miejsce Nabycia - E-mail\"") << tr(",\"Data about copy - Miejsce Nabycia - Telefon\"");
            fnout << tr(",\"Data about copy - Miejsce Nabycia - Fax\"") << tr(",\"Data about copy - Miejsce Nabycia - WWW\"");
            fnout << tr(",\"Data about copy - Właściciel Kopii Filmu - Imię\"") << tr(",\"Data about copy - Właściciel Kopii Filmu - Nazwisko\"");
            fnout << tr(",\"Data about copy - Właściciel Kopii Filmu - Adres\"") << tr(",\"Data about copy - Nr katalogowy\"");
            fnout << tr(",\"Data about copy - Nośnik\"") << tr(",\"Data about copy - Wartość aktualna\"");
            fnout << tr(",\"Information about Movie - Data premiery\"") << tr(",\"Information about Movie - Czas trwania\"");
            fnout << tr(",\"Information about Movie - Format wyświetlania\"") << tr(",\"Information about Movie - język lektora\"");
            fnout << tr(",\"Information about Movie - język napisów\"") << tr(",\"Information about Movie - Kodek dźwięku - nazwa\"");
            fnout << tr(",\"Information about Movie - Kodek dźwięku - typ\"") << tr(",\"Information about Movie - Kodek dźwięku - wersja\"");
            fnout << tr(",\"Information about Movie - Kodek wideo - nazwa\"") << tr(",\"Information about Movie - Kodek wideo - typ\"");
            fnout << tr(",\"Information about Movie - Kodek wideo - wersja\"") << tr(",\"Information about Movie - Zabezpieczenia - nazwa\"");
            fnout << tr(",\"Information about Movie - Zabezpieczenia - typ\"") << tr(",\"Information about Movie - Zabezpieczenia - wersja\"");
            fnout << tr(",\"Information about Movie - Kraj produkcji filmu\"") << tr(",\"Information about Movie - Rok produkcji\"");
            fnout << tr(",\"Information about Movie - System kodowania obrazu\"") << tr(",\"Cast - Reżyser - Imie i Nazwisko\"");
            fnout << tr(",\"Cast - Reżyser - Narodowość\"") << tr(",\"Cast - Scenarzysta - Imię i Nazwisko\"");
            fnout << tr(",\"Cast - Scenarzysta - Narodowość\"") << tr(",\"Cast - Muzyka - Imie i Nazwisko\"");
            fnout << tr(",\"Cast - Muzyka - Narodowość\"") << tr(",\"Cast - Zdjęcia - Imię i Nazwisko\"");
            fnout << tr(",\"Cast - Zdjęcia - Narodowość\"") << tr(",\"Score - Własna Score Filmu - Cast\"");
            fnout << tr(",\"Score - Własna Score Filmu - Ścieżka dźwiękowa\"") << tr(",\"Score - Własna Score Filmu - Wartośc artystyczna\"");
            fnout << tr(",\"Score - Własna Score Filmu - Zdjęcia\"") << tr(",\"Score - Własna Score Filmu - Całość\"");
            fnout << tr(",\"Path - skan okładki - przód\"") << tr(",\"Path - skan okładki - tył\"") << "\n\r";


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



        if (ui->checkBox_TabScore->isChecked() == true)
        {
            struct Score oc_buff;
            QFile oc_src(QString::fromWCharArray(flm_eks.pths.BF_OC));
            oc_src.open(QFile::ReadOnly);
            fnout << tr("Tabela Score") << "\n\r";

            unsigned int stop = oc_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Nazwa\"") << tr(",\"Tytuł tekstu\"") << tr(",\"Autor tekstu\"") <<
            tr(",\"Strona WWW\"") << tr(",\"Score krytyka\"") << "\n\r";


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

        if (ui->checkBox_TabCast->isChecked() == true)
        {
            struct Cast ob_buff;
            QFile ob_src(QString::fromWCharArray(flm_eks.pths.BF_OB));
            ob_src.open(QFile::ReadOnly);
            fnout << tr("Tabela Cast") << "\n\r";

            unsigned int stop = ob_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\" Imię i Nazwisko\"") << tr(",\" Rola\"") << "\n\r";


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
            fnout << tr("Tabela Produkcja") << "\n\r";

            unsigned int stop = pp_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Nazwa Firmy\"") << tr(",\"Adres\"") << tr(",\"Telefon\"");
            fnout << tr(",\"Fax\"") << tr(",\"E-mail\"") << tr(",\"Strona WWW\"") << tr(",\"Narodowość\"") << "\n\r";

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
            fnout << tr("Tabela Dystrybucja") <<"\n\r";

            stop = pd_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Nazwa Firmy\"") << tr(",\"Adres\"") << tr(",\"Telefon\"");
            fnout << tr(",\"Fax\"") << tr(",\"E-mail\"") << tr(",\"Strona WWW\"") << tr(",\"Narodowość\"") << "\n\r";


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
            fnout << tr("Tabela Lokalizacje Zdjęciowe") << "\n\r";

            unsigned int stop = lz_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Nazwa obiektu\"") << tr(",\"Kraj\"") << tr(",\"Miejscowość\"");
            fnout << tr(",\"Region\"") << tr(",\"Pora roku\"") << tr(",\"Data\"") << "\n\r";


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
            fnout << tr("Tabela Wypożyczenia Innym Osobom") << "\n\r";

            unsigned int stop = wi_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Data wypożyczenia\"") << tr(",\"Data oddania\"");
            fnout << tr(",\"Stan przed wypożyczeniem\"") << tr(",\"Stan po oddaniu\"") << tr(",\"Osoba\"");
            fnout << tr(",\"Nr katalogowy\"") << "\n\r";


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
            fnout << tr("Tabela Wypożyczenia od Innych Osób") << "\n\r";

            stop = wo_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Data wypożyczenia\"") << tr(",\"Data oddania\"");
            fnout << tr(",\"Stan przed wypożyczeniem\"") << tr(",\"Stan po oddaniu\"") << tr(",\"Osoba\"");
            fnout << tr(",\"Nr katalogowy\"") << "\n\r";


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

    fnout << tr("Biblioteka Filmów - wyeksportowane dane") << "\n\r";
    if (ui->checkBox_MainFilm->isChecked() == true)
    {
        struct Film film_buff;
        QFile main(QString::fromWCharArray(flm_eks.pths.BF_PDB));
        main.open(QFile::ReadOnly);
        unsigned int stop = main.size();
		fnout << tr("Tabela główna - Film") << "\n\r";
        fnout << QString::fromWCharArray(L"\"ID\"") << tr(",\"tytuł\"") <<  tr(",\"oryginalny tytuł\"") << tr(",\"gatunek filmu\"");
        fnout << tr(",\"Data about copy - Cena\"") << tr(",\"Data about copy - Data skatalogowania\"");
        fnout << tr(",\"Data about copy - Data utraty\"") << tr(",\"Data about copy - Data zakupu\"");
        fnout << tr(",\"Data about copy - Miejsce Nabycia - Nazwa\"") << tr(",\"Data about copy - Miejsce Nabycia - Adres\"");
        fnout << tr(",\"Data about copy - Miejsce Nabycia - E-mail\"") << tr(",\"Data about copy - Miejsce Nabycia - Telefon\"");
        fnout << tr(",\"Data about copy - Miejsce Nabycia - Fax\"") << tr(",\"Data about copy - Miejsce Nabycia - WWW\"");
		fnout << tr(",\"Data about copy - Właściciel Kopii Filmu - Imię\"") << tr(",\"Data about copy - Właściciel Kopii Filmu - Nazwisko\"");
		fnout << tr(",\"Data about copy - Właściciel Kopii Filmu - Adres\"") << tr(",\"Data about copy - Nr katalogowy\"");
        fnout << tr(",\"Data about copy - Nośnik\"") << tr(",\"Data about copy - Wartość aktualna\"");
        fnout << tr(",\"Information about Movie - Data premiery\"") << tr(",\"Information about Movie - Czas trwania\"");
        fnout << tr(",\"Information about Movie - Format wyświetlania\"") << tr(",\"Information about Movie - język lektora\"");
        fnout << tr(",\"Information about Movie - język napisów\"") << tr(",\"Information about Movie - Kodek dźwięku - nazwa\"");
        fnout << tr(",\"Information about Movie - Kodek dźwięku - typ\"") << tr(",\"Information about Movie - Kodek dźwięku - wersja\"");
        fnout << tr(",\"Information about Movie - Kodek wideo - nazwa\"") << tr(",\"Information about Movie - Kodek wideo - typ\"");
        fnout << tr(",\"Information about Movie - Kodek wideo - wersja\"") << tr(",\"Information about Movie - Zabezpieczenia - nazwa\"");
        fnout << tr(",\"Information about Movie - Zabezpieczenia - typ\"") << tr(",\"Information about Movie - Zabezpieczenia - wersja\"");
        fnout << tr(",\"Information about Movie - Kraj produkcji filmu\"") << tr(",\"Information about Movie - Rok produkcji\"");
        fnout << tr(",\"Information about Movie - System kodowania obrazu\"") << tr(",\"Cast - Reżyser - Imie i Nazwisko\"");
        fnout << tr(",\"Cast - Reżyser - Narodowość\"") << tr(",\"Cast - Scenarzysta - Imię i Nazwisko\"");
        fnout << tr(",\"Cast - Scenarzysta - Narodowość\"") << tr(",\"Cast - Muzyka - Imie i Nazwisko\"");
        fnout << tr(",\"Cast - Muzyka - Narodowość\"") << tr(",\"Cast - Zdjęcia - Imię i Nazwisko\"");
        fnout << tr(",\"Cast - Zdjęcia - Narodowość\"") << tr(",\"Score - Własna Score Filmu - Cast\"");
        fnout << tr(",\"Score - Własna Score Filmu - Ścieżka dźwiękowa\"") << tr(",\"Score - Własna Score Filmu - Wartośc artystyczna\"");
        fnout << tr(",\"Score - Własna Score Filmu - Zdjęcia\"") << tr(",\"Score - Własna Score Filmu - Całość\"");
        fnout << tr(",\"Path - skan okładki - przód\"") << tr(",\"Path - skan okładki - tył\"") << "\n\r";
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

    if (ui->checkBox_TabScore->isChecked() == true)
    {
        struct Score oc_buff;
        QFile oc_src(QString::fromWCharArray(flm_eks.pths.BF_OC));
        oc_src.open(QFile::ReadOnly);
        fnout << tr("Tabela Score") << "\n\r";

        unsigned int stop = oc_src.size();

        fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Nazwa\"") << tr(",\"Tytuł tekstu\"") << tr(",\"Autor tekstu\"") <<
        tr(",\"Strona WWW\"") << tr(",\"Score krytyka\"") << "\n\r";


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

    if (ui->checkBox_TabCast->isChecked() == true)
    {
        struct Cast ob_buff;
        QFile ob_src(QString::fromWCharArray(flm_eks.pths.BF_OB));
        ob_src.open(QFile::ReadOnly);
        fnout << tr("Tabela Cast") << "\n\r";

        unsigned int stop = ob_src.size();

        fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\" Imię i Nazwisko\"") << tr(",\" Rola\"") << "\n\r";


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
        fnout << tr("Tabela Produkcja") << "\n\r";

        unsigned int stop = pp_src.size();

        fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Nazwa Firmy\"") << tr(",\"Adres\"") << tr(",\"Telefon\"");
        fnout << tr(",\"Fax\"") << tr(",\"E-mail\"") << tr(",\"Strona WWW\"") << tr(",\"Narodowość\"") << "\n\r";


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
            fnout << tr("Tabela Dystrybucja") <<"\n\r";

            stop = pd_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Nazwa Firmy\"") << tr(",\"Adres\"") << tr(",\"Telefon\"");
            fnout << tr(",\"Fax\"") << tr(",\"E-mail\"") << tr(",\"Strona WWW\"") << tr(",\"Narodowość\"") << "\n\r";


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
        fnout << tr("Tabela Lokalizacje Zdjęciowe") << "\n\r";

        unsigned int stop = lz_src.size();

        fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Nazwa obiektu\"") << tr(",\"Kraj\"") << tr(",\"Miejscowość\"");
        fnout << tr(",\"Region\"") << tr(",\"Pora roku\"") << tr(",\"Data\"") << "\n\r";



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
        fnout << tr("Tabela Wypożyczenia Innym Osobom") << "\n\r";

        unsigned int stop = wi_src.size();

        fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Data wypożyczenia\"") << tr(",\"Data oddania\"");
        fnout << tr(",\"Stan przed wypożyczeniem\"") << tr(",\"Stan po oddaniu\"") << tr(",\"Osoba\"");
        fnout << tr(",\"Nr katalogowy\"") << "\n\r";


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
            fnout << tr("Tabela Wypożyczenia od Innych Osób") << "\n\r";

            stop = wo_src.size();

            fnout << QString::fromWCharArray(L"\"ID\"") << QString::fromWCharArray(L",\"IDPDB\"") << tr(",\"Data wypożyczenia\"") << tr(",\"Data oddania\"");
            fnout << tr(",\"Stan przed wypożyczeniem\"") << tr(",\"Stan po oddaniu\"") << tr(",\"Osoba\"");
            fnout << tr(",\"Nr katalogowy\"") << "\n\r";


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
