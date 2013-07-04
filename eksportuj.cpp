#include "eksportuj.h"
#include "ui_eksportuj.h"

#include "film_ftbl_class.h"
#include "Unmngd.h"

Ftbl flm_eks;

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

    fnout << "Biblioteka Filmów - wyeksportowane dane \n\r";


        if (ui->checkBox_MainFilm->isChecked() == true)
        {
            struct Film film_buff;
            QFile main(QString::fromWCharArray(flm_eks.pths.BF_PDB));
            main.open(QFile::ReadOnly);
            unsigned int stop = main.size();
            fnout << "Tabela główna - Film \n\r";
            fnout << "\"ID\"" <<
            ",\"tytuł\"" <<
            ",\"oryginalny tytuł\"" <<
            ",\"gatunek filmu\"" <<
            ",\"Dane o Egzemplarzu - Cena\"" <<
            ",\"Dane o Egzemplarzu - Data skatalogowania\"" <<
            ",\"Dane o Egzemplarzu - Data utraty\"" <<
            ",\"Dane o Egzemplarzu - Data zakupu\"" <<
            ",\"Dane o Egzemplarzu - Miejsce Nabycia - Nazwa\"" <<
            ",\"Dane o Egzemplarzu - Miejsce Nabycia - Adres\"" <<
            ",\"Dane o Egzemplarzu - Miejsce Nabycia - E-mail\"" <<
            ",\"Dane o Egzemplarzu - Miejsce Nabycia - Telefon\"" <<
            ",\"Dane o Egzemplarzu - Miejsce Nabycia - Fax\"" <<
            ",\"Dane o Egzemplarzu - Miejsce Nabycia - WWW\"" <<
            ",\"Dane o Egzemplarzu - Właściciel Kopii Filmu - Imię\"" <<
            ",\"Dane o Egzemplarzu - Właściciel Kopii Filmu - Nazwisko\"" <<
            ",\"Dane o Egzemplarzu - Właściciel Kopii Filmu - Adres\"" <<
            ",\"Dane o Egzemplarzu - Nr katalogowy\"" <<
            ",\"Dane o Egzemplarzu - Nośnik\"" <<
            ",\"Dane o Egzemplarzu - Wartość aktualna\"" <<
            ",\"Informacje o Filmie - Data premiery\"" <<
            ",\"Informacje o Filmie - Czas trwania\"" <<
            ",\"Informacje o Filmie - Format wyświetlania\"" <<
            ",\"Informacje o Filmie - język lektora\"" <<
            ",\"Informacje o Filmie - język napisów\"" <<
            ",\"Informacje o Filmie - Kodek dźwięku - nazwa\"" <<
            ",\"Informacje o Filmie - Kodek dźwięku - typ\"" <<
            ",\"Informacje o Filmie - Kodek dźwięku - wersja\"" <<
            ",\"Informacje o Filmie - Kodek wideo - nazwa\"" <<
            ",\"Informacje o Filmie - Kodek wideo - typ\"" <<
            ",\"Informacje o Filmie - Kodek wideo - wersja\"" <<
            ",\"Informacje o Filmie - Zabezpieczenia - nazwa\"" <<
            ",\"Informacje o Filmie - Zabezpieczenia - typ\"" <<
            ",\"Informacje o Filmie - Zabezpieczenia - wersja\"" <<
            ",\"Informacje o Filmie - Kraj produkcji filmu\"" <<
            ",\"Informacje o Filmie - Rok produkcji\"" <<
            ",\"Informacje o Filmie - System kodowania obrazu\"" <<
            ",\"Obsada - Reżyser - Imie i Nazwisko\"" <<
            ",\"Obsada - Reżyser - Narodowość\"" <<
            ",\"Obsada - Scenarzysta - Imię i Nazwisko\"" <<
            ",\"Obsada - Scenarzysta - Narodowość\"" <<
            ",\"Obsada - Muzyka - Imie i Nazwisko\"" <<
            ",\"Obsada - Muzyka - Narodowość\"" <<
            ",\"Obsada - Zdjęcia - Imię i Nazwisko\"" <<
            ",\"Obsada - Zdjęcia - Narodowość\"" <<
            ",\"Ocena - Własna Ocena Filmu - Obsada\"" <<
            ",\"Ocena - Własna Ocena Filmu - Ścieżka dźwiękowa\"" <<
            ",\"Ocena - Własna Ocena Filmu - Wartośc artystyczna\"" <<
            ",\"Ocena - Własna Ocena Filmu - Zdjęcia\"" <<
            ",\"Ocena - Własna Ocena Filmu - Całość\"" <<
            ",\"Scieżka - skan okładki - przód\"" <<
            ",\"Scieżka - skan okładki - tył\"" <<
            "\n\r";


            for (unsigned int i = 0; i < stop; )
            {
                main.seek(i);
                main.read(reinterpret_cast<char *)(&film_buff),sizeof(Film));
                fnout << "\"" <<
                film_buff.ID <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.tytul) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.oryginalny_tytul) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.gatunek_filmu) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_cena) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_data_skatalogowania) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_data_utraty) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_data_zakupu) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_MN_nazwa) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_MN_adres) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_MN_email) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_MN_telefon) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_MN_fax) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_MN_www) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_WKF_imie) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_WKF_nazwisko) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_WKF_adres) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_Nr_kat) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_rodzaj_nosnika) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.DOE_wartosc_akt) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_data_premiery) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_czas_trwania) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_format_wysw) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_jezyk_lektora) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_jezyk_napisow) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_DZWIEK_nazwa) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_DZWIEK_typ) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_DZWIEK_wersja) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_KODEK_nazwa) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_KODEK_typ) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_KODEK_wersja) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_ZABEZP_nazwa) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_ZABEZP_typ) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_ZABEZP_wersja) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_kraj_produkcji_filmu) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_rok_produkcji) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.IOF_system_kodowania_obrazu) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.O_rezyser_imie_nazw) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.O_rezyser_narod) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.O_scenariusz_imie_nazw) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.O_scenariusz_narod) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.O_muzyka_imie_nazw) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.O_muzyka_narod) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.O_operator_imie_nazw) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.O_operator_narod) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.WOF_obsada) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.WOF_sciezka_dz) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.WOF_w_art) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.WOF_zdjecia) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.WOF_calosc) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.skan_przod_path) <<
                "\"" <<
                "," <<
                "\"" <<
                QString::fromWCharArray(film_buff.skan_tyl_path) <<
                "\"" <<
                "\n\r";
                i = i + sizeof(Film);
            }
            main.close();
        }



        if (ui->checkBox_TabOcena->isChecked() == true)
        {
            struct Ocena oc_buff;
            CFile oc_src;
            oc_src.Open(flm_eks.pths.BF_OC,CFile::modeRead);
            _tcscpy(line_save,_TEXT("Tabela Ocena \n\r"));
            fn_exp.WriteString(line_save);
            LONGLONG stop = oc_src.SeekToEnd();

            _tcscpy(line_save,_TEXT("\"ID\""));
            _tcscat(line_save,_TEXT(",\"IDPDB\""));
            _tcscat(line_save,_TEXT(",\"Nazwa\""));
            _tcscat(line_save,_TEXT(",\"Tytuł tekstu\""));
            _tcscat(line_save,_TEXT(",\"Autor tekstu\""));
            _tcscat(line_save,_TEXT(",\"Strona WWW\""));
            _tcscat(line_save,_TEXT(",\"Ocena krytyka\"\n\r"));
            fn_exp.WriteString(line_save);


            for (LONGLONG i = 0; i < stop; )
            {
                oc_src.Seek(i,CFile::begin);
                oc_src.Read(&oc_buff,sizeof(oc_buff));

                _tcscpy(line_save,_TEXT("\""));
                wchar_t buff[20];
                _itow(oc_buff.ID,buff,10);
                _tcscat(line_save,buff);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _itow(oc_buff.IDPDB,buff,10);
                _tcscat(line_save,buff);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,oc_buff.nazwa);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,oc_buff.tytul_tekstu);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,oc_buff.autor_tekstu);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,oc_buff.strona_www);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,oc_buff.ocena_krytyka);
                _tcscat(line_save,_TEXT("\""));

                _tcscat(line_save,_TEXT("\n\r"));
                fn_exp.WriteString(line_save);
                i = i + sizeof(oc_src);
            }
            oc_src.Close();
        }

        if (ui->checkBox_TabObsada->isChecked() == true)
        {
            struct Obsada ob_buff;
            CFile ob_src;
            ob_src.Open(flm_eks.pths.BF_OB,CFile::modeRead);
            _tcscpy(line_save,TEXT("Tabela Obsada\n\r"));
            fn_exp.WriteString(line_save);
            LONGLONG stop = ob_src.SeekToEnd();

            _tcscpy(line_save,_TEXT("\"ID\""));
            _tcscat(line_save,_TEXT(",\"IDPDB\""));
            _tcscat(line_save,_TEXT(",\" Imię i Nazwisko\""));
            _tcscat(line_save,_TEXT(",\" Rola\"\n\r"));
            fn_exp.WriteString(line_save);


            for (LONGLONG i = 0; i < stop; )
            {
                ob_src.Seek(i,CFile::begin);
                ob_src.Read(&ob_buff,sizeof(ob_buff));

                _tcscpy(line_save,_TEXT("\""));
                wchar_t buff[20];
                _itow(ob_buff.ID,buff,10);
                _tcscat(line_save,buff);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _itow(ob_buff.IDPDB,buff,10);
                _tcscat(line_save,buff);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,ob_buff.imie_nazw);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save, ob_buff.rola);
                _tcscat(line_save,_TEXT("\""));

                _tcscat(line_save,_TEXT("\n\r"));
                fn_exp.WriteString(line_save);
                i = i + sizeof(ob_buff);
            }
            ob_src.Close();

        }

        if (ui->checkBox_TabPD->isChecked() == true)
        {
            struct Producent pp_buff;
            CFile pp_src;
            pp_src.Open(flm_eks.pths.BF_PRP,CFile::modeRead);
            _tcscpy(line_save,TEXT("Tabela Produkcja\n\r"));
            fn_exp.WriteString(line_save);
            LONGLONG stop = pp_src.SeekToEnd();

            _tcscpy(line_save,_TEXT("\"ID\""));
            _tcscat(line_save,_TEXT(",\"IDPDB\""));
            _tcscat(line_save,_TEXT(",\"Nazwa Firmy\""));
            _tcscat(line_save,_TEXT(",\"Adres\""));
            _tcscat(line_save,_TEXT(",\"Telefon\""));
            _tcscat(line_save,_TEXT(",\"Fax\""));
            _tcscat(line_save,_TEXT(",\"E-mail\""));
            _tcscat(line_save,_TEXT(",\"Strona WWW\""));
            _tcscat(line_save,_TEXT(",\"Narodowość\""));

            _tcscat(line_save,_TEXT("\n\r"));
            fn_exp.WriteString(line_save);

            for (LONGLONG i = 0; i < stop; )
            {
                pp_src.Seek(i,CFile::begin);
                pp_src.Read(&pp_buff,sizeof(pp_buff));

                _tcscpy(line_save,_TEXT("\""));
                wchar_t buff[20];
                _itow(pp_buff.ID,buff,10);
                _tcscat(line_save,buff);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _itow(pp_buff.IDPDB,buff,10);
                _tcscat(line_save,buff);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,pp_buff.nazwa_firmy);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,pp_buff.adres);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,pp_buff.telefon);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,pp_buff.fax);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,pp_buff.email);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,pp_buff.strona_www);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,pp_buff.narodowosc);
                _tcscat(line_save,_TEXT("\""));

                _tcscat(line_save,_TEXT("\n\r"));
                fn_exp.WriteString(line_save);
                i = i + sizeof(pp_buff);
            }
            pp_src.Close();

            struct Dystrybutor pd_buff;
            CFile pd_src;
            pd_src.Open(flm_eks.pths.BF_PRD,CFile::modeRead);
            _tcscpy(line_save,TEXT("Tabela Dystrybucja\n\r"));
            fn_exp.WriteString(line_save);
            stop = pd_src.SeekToEnd();

            _tcscpy(line_save,_TEXT("\"ID\""));
            _tcscat(line_save,_TEXT(",\"IDPDB\""));
            _tcscat(line_save,_TEXT(",\"Nazwa Firmy\""));
            _tcscat(line_save,_TEXT(",\"Adres\""));
            _tcscat(line_save,_TEXT(",\"Telefon\""));
            _tcscat(line_save,_TEXT(",\"Fax\""));
            _tcscat(line_save,_TEXT(",\"E-mail\""));
            _tcscat(line_save,_TEXT(",\"Strona WWW\""));
            _tcscat(line_save,_TEXT(",\"Narodowość\""));

            _tcscat(line_save,_TEXT("\n\r"));
            fn_exp.WriteString(line_save);

            for (LONGLONG i = 0; i < stop; )
            {
                pd_src.Seek(i,CFile::begin);
                pd_src.Read(&pd_buff,sizeof(pd_buff));

                _tcscpy(line_save,_TEXT("\""));
                wchar_t buff[20];
                _itow(pd_buff.ID,buff,10);
                _tcscat(line_save,buff);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _itow(pd_buff.IDPDB,buff,10);
                _tcscat(line_save,buff);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,pd_buff.nazwa_firmy);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,pd_buff.adres);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,pd_buff.telefon);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,pd_buff.fax);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,pd_buff.email);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,pd_buff.strona_www);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,pd_buff.narodowosc);
                _tcscat(line_save,_TEXT("\""));

                _tcscat(line_save,_TEXT("\n\r"));
                fn_exp.WriteString(line_save);
                i = i + sizeof(pd_buff);
            }
            pd_src.Close();

        }

        if (ui->checkBox_TabLZ->isChecked() == true)
        {
            struct Lok_zdjeciowe lz_buff;
            CFile lz_src;
            lz_src.Open(flm_eks.pths.BF_LZ,CFile::modeRead);
            _tcscpy(line_save,TEXT("Tabela Lokalizacje Zdjęciowe\n\r"));
            fn_exp.WriteString(line_save);
            LONGLONG stop = lz_src.SeekToEnd();

            _tcscpy(line_save,_TEXT("\"ID\""));
            _tcscat(line_save,_TEXT(",\"IDPDB\""));
            _tcscat(line_save,_TEXT(",\"Nazwa obiektu\""));
            _tcscat(line_save,_TEXT(",\"Kraj\""));
            _tcscat(line_save,_TEXT(",\"Miejscowość\""));
            _tcscat(line_save,_TEXT(",\"Region\""));
            _tcscat(line_save,_TEXT(",\"Pora roku\""));
            _tcscat(line_save,_TEXT(",\"Data\""));

            _tcscat(line_save,_TEXT("\n\r"));
            fn_exp.WriteString(line_save);

            for (LONGLONG i = 0; i < stop; )
            {
                lz_src.Seek(i,CFile::begin);
                lz_src.Read(&lz_buff,sizeof(lz_buff));

                _tcscpy(line_save,_TEXT("\""));
                wchar_t buff[20];
                _itow(lz_buff.ID,buff,10);
                _tcscat(line_save,buff);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _itow(lz_buff.IDPDB,buff,10);
                _tcscat(line_save,buff);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,lz_buff.nazwa_obiektu);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,lz_buff.kraj);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,lz_buff.miejscowosc);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,lz_buff.region);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,lz_buff.pora_roku);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,lz_buff.data);
                _tcscat(line_save,_TEXT("\""));

                _tcscat(line_save,_TEXT("\n\r"));
                fn_exp.WriteString(line_save);
                i = i + sizeof(lz_buff);
            }
            lz_src.Close();
        }

        if (ui->checkBox_TabW->isChecked() == true)
        {
            struct Wypozycz_Innym wi_buff;
            CFile wi_src;
            wi_src.Open(flm_eks.pths.BF_WI,CFile::modeRead);
            _tcscpy(line_save,TEXT("Tabela Wypożyczenia Innym Osobom\n\r"));
            fn_exp.WriteString(line_save);
            LONGLONG stop = wi_src.SeekToEnd();

            _tcscpy(line_save,_TEXT("\"ID\""));
            _tcscat(line_save,_TEXT(",\"IDPDB\""));
            _tcscat(line_save,_TEXT(",\"Data wypożyczenia\""));
            _tcscat(line_save,_TEXT(",\"Data oddania\""));
            _tcscat(line_save,_TEXT(",\"Stan przed wypożyczeniem\""));
            _tcscat(line_save,_TEXT(",\"Stan po oddaniu\""));
            _tcscat(line_save,_TEXT(",\"Osoba\""));
            _tcscat(line_save,_TEXT(",\"Nr katalogowy\""));

            _tcscat(line_save,_TEXT("\n\r"));
            fn_exp.WriteString(line_save);

            for (LONGLONG i = 0; i < stop; )
            {
                wi_src.Seek(i,CFile::begin);
                wi_src.Read(&wi_buff,sizeof(wi_buff));

                _tcscpy(line_save,_TEXT("\""));
                wchar_t buff[20];
                _itow(wi_buff.ID,buff,10);
                _tcscat(line_save,buff);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _itow(wi_buff.IDPDB,buff,10);
                _tcscat(line_save,buff);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,wi_buff.data_wypozyczenia);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,wi_buff.data_oddania);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,wi_buff.stan_przed_wypozycz);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,wi_buff.stan_po_oddaniu);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,wi_buff.osoba);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,wi_buff.Nr_kat);
                _tcscat(line_save,_TEXT("\""));


                _tcscat(line_save,_TEXT("\n\r"));
                fn_exp.WriteString(line_save);
                i = i + sizeof(wi_buff);
            }
            wi_src.Close();

            struct Wypozycz_Od_Innych wo_buff;
            CFile wo_src;
            wo_src.Open(flm_eks.pths.BF_WO,CFile::modeRead);
            _tcscpy(line_save,TEXT("Tabela Wypożyczenia od Innych Osób\n\r"));
            fn_exp.WriteString(line_save);
            stop = wo_src.SeekToEnd();

            _tcscpy(line_save,_TEXT("\"ID\""));
            _tcscat(line_save,_TEXT(",\"IDPDB\""));
            _tcscat(line_save,_TEXT(",\"Data wypożyczenia\""));
            _tcscat(line_save,_TEXT(",\"Data oddania\""));
            _tcscat(line_save,_TEXT(",\"Stan przed wypożyczeniem\""));
            _tcscat(line_save,_TEXT(",\"Stan po oddaniu\""));
            _tcscat(line_save,_TEXT(",\"Osoba\""));
            _tcscat(line_save,_TEXT(",\"Nr katalogowy\""));

            _tcscat(line_save,_TEXT("\n\r"));
            fn_exp.WriteString(line_save);

            for (LONGLONG i = 0; i < stop; )
            {
                wo_src.Seek(i,CFile::begin);
                wo_src.Read(&wo_buff,sizeof(wo_buff));

                _tcscpy(line_save,_TEXT("\""));
                wchar_t buff[20];
                _itow(wo_buff.ID,buff,10);
                _tcscat(line_save,buff);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _itow(wo_buff.IDPDB,buff,10);
                _tcscat(line_save,buff);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,wo_buff.data_wypozyczenia);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,wo_buff.data_oddania);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,wo_buff.stan_przed_wypozycz);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,wo_buff.stan_po_oddaniu);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,wo_buff.osoba);
                _tcscat(line_save,_TEXT("\""));
                _tcscat(line_save,_TEXT(",\""));
                _tcscat(line_save,wo_buff.Nr_kat);
                _tcscat(line_save,_TEXT("\""));


                _tcscat(line_save,_TEXT("\n\r"));
                fn_exp.WriteString(line_save);
                i = i + sizeof(wo_buff);
            }
            wo_src.Close();
        }
        fn_exp.Close();

    }

void Eksportuj::Eksportuj_current()
{
        CStdioFile fn_exp;

        fn_exp.Open(fn_path,CStdioFile::modeCreate | CStdioFile::modeWrite | CStdioFile::typeText);

        wchar_t line_save[102400];
        _tcscpy(line_save,TEXT("MK Film DB - wyeksportowane dane\n\r"));
        fn_exp.WriteString(line_save);
        if (this->CHECK_MAIN.GetCheck() == BST_CHECKED)
        {
            struct Film film_buff;
            CFile main;
            main.Open(flm_eks.pths.BF_PDB,CFile::modeRead);
            LONGLONG stop = main.SeekToEnd();
            _tcscpy(line_save,TEXT("Tabela główna - Film\n\r"));
            fn_exp.WriteString(line_save);
            _tcscpy(line_save,_TEXT("\"ID\""));
            _tcscat(line_save,_TEXT(",\"tytuł\""));
            _tcscat(line_save,_TEXT(",\"oryginalny tytuł\""));
            _tcscat(line_save,_TEXT(",\"gatunek filmu\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Cena\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Data skatalogowania\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Data utraty\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Data zakupu\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Miejsce Nabycia - Nazwa\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Miejsce Nabycia - Adres\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Miejsce Nabycia - E-mail\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Miejsce Nabycia - Telefon\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Miejsce Nabycia - Fax\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Miejsce Nabycia - WWW\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Właściciel Kopii Filmu - Imię\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Właściciel Kopii Filmu - Nazwisko\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Właściciel Kopii Filmu - Adres\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Nr katalogowy\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Nośnik\""));
            _tcscat(line_save,_TEXT(",\"Dane o Egzemplarzu - Wartość aktualna\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - Data premiery\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - Czas trwania\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - Format wyświetlania\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - język lektora\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - język napisów\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - Kodek dźwięku - nazwa\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - Kodek dźwięku - typ\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - Kodek dźwięku - wersja\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - Kodek wideo - nazwa\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - Kodek wideo - typ\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - Kodek wideo - wersja\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - Zabezpieczenia - nazwa\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - Zabezpieczenia - typ\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - Zabezpieczenia - wersja\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - Kraj produkcji filmu\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - Rok produkcji\""));
            _tcscat(line_save,_TEXT(",\"Informacje o Filmie - System kodowania obrazu\""));
            _tcscat(line_save,_TEXT(",\"Obsada - Reżyser - Imie i Nazwisko\""));
            _tcscat(line_save,_TEXT(",\"Obsada - Reżyser - Narodowość\""));
            _tcscat(line_save,_TEXT(",\"Obsada - Scenarzysta - Imię i Nazwisko\""));
            _tcscat(line_save,_TEXT(",\"Obsada - Scenarzysta - Narodowość\""));
            _tcscat(line_save,_TEXT(",\"Obsada - Muzyka - Imie i Nazwisko\""));
            _tcscat(line_save,_TEXT(",\"Obsada - Muzyka - Narodowość\""));
            _tcscat(line_save,_TEXT(",\"Obsada - Zdjęcia - Imię i Nazwisko\""));
            _tcscat(line_save,_TEXT(",\"Obsada - Zdjęcia - Narodowość\""));
            _tcscat(line_save,_TEXT(",\"Ocena - Własna Ocena Filmu - Obsada\""));
            _tcscat(line_save,_TEXT(",\"Ocena - Własna Ocena Filmu - Ścieżka dźwiękowa\""));
            _tcscat(line_save,_TEXT(",\"Ocena - Własna Ocena Filmu - Wartośc artystyczna\""));
            _tcscat(line_save,_TEXT(",\"Ocena - Własna Ocena Filmu - Zdjęcia\""));
            _tcscat(line_save,_TEXT(",\"Ocena - Własna Ocena Filmu - Całość\""));
            _tcscat(line_save,_TEXT(",\"Scieżka - skan okładki - przód\""));
            _tcscat(line_save,_TEXT(",\"Scieżka - skan okładki - tył\""));
            _tcscat(line_save,_TEXT("\n\r"));

            fn_exp.WriteString(line_save);
            for (LONGLONG i = 0; i < stop; )
            {
                main.Seek(i,CFile::begin);
                main.Read(&film_buff,sizeof(Film));
                if (film_buff.ID == flm_eks.film_tbl.ID)
                {
                    _tcscpy(line_save,_TEXT("\""));
                    wchar_t buff[20];
                    _itow(film_buff.ID,buff,10);
                    _tcscat(line_save,buff);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.tytul);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.oryginalny_tytul);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.gatunek_filmu);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_cena);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_data_skatalogowania);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_data_utraty);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_data_zakupu);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_MN_nazwa);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_MN_adres);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_MN_email);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_MN_telefon);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_MN_fax);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_MN_www);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_WKF_imie);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_WKF_nazwisko);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_WKF_adres);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_Nr_kat);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_rodzaj_nosnika);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.DOE_wartosc_akt);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_data_premiery);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_czas_trwania);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_format_wysw);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_jezyk_lektora);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_jezyk_napisow);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_DZWIEK_nazwa);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_DZWIEK_typ);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_DZWIEK_wersja);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_KODEK_nazwa);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_KODEK_typ);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_KODEK_wersja);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_ZABEZP_nazwa);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_ZABEZP_typ);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_ZABEZP_wersja);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_kraj_produkcji_filmu);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_rok_produkcji);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.IOF_system_kodowania_obrazu);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.O_rezyser_imie_nazw);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.O_rezyser_narod);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.O_scenariusz_imie_nazw);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.O_scenariusz_narod);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.O_muzyka_imie_nazw);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.O_muzyka_narod);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.O_operator_imie_nazw);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.O_operator_narod);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.WOF_obsada);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.WOF_sciezka_dz);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.WOF_w_art);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.WOF_zdjecia);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.WOF_calosc);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.skan_przod_path);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(","));
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,film_buff.skan_tyl_path);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT("\n\r"));
                    fn_exp.WriteString(line_save);
                }
                i = i + sizeof(Film);

            }
            main.Close();
        }

        if (this->CHECK_OC.GetCheck() == BST_CHECKED)
        {
            struct Ocena oc_buff;
            CFile oc_src;
            oc_src.Open(flm_eks.pths.BF_OC,CFile::modeRead);
            _tcscpy(line_save,TEXT("Tabela Ocena\n\r"));
            fn_exp.WriteString(line_save);
            LONGLONG stop = oc_src.SeekToEnd();

            _tcscpy(line_save,_TEXT("\"ID\""));
            _tcscat(line_save,_TEXT(",\"IDPDB\""));
            _tcscat(line_save,_TEXT(",\"Nazwa\""));
            _tcscat(line_save,_TEXT(",\"Tytuł tekstu\""));
            _tcscat(line_save,_TEXT(",\"Autor tekstu\""));
            _tcscat(line_save,_TEXT(",\"Strona WWW\""));
            _tcscat(line_save,_TEXT(",\"Ocena krytyka\""));

            _tcscat(line_save,_TEXT("\n\r"));
            fn_exp.WriteString(line_save);

            for (LONGLONG i = 0; i < stop; )
            {
                oc_src.Seek(i,CFile::begin);
                oc_src.Read(&oc_buff,sizeof(oc_buff));
                if (oc_buff.IDPDB == flm_eks.film_tbl.ID)
                {

                    _tcscpy(line_save,_TEXT("\""));
                    wchar_t buff[20];
                    _itow(oc_buff.ID,buff,10);
                    _tcscat(line_save,buff);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _itow(oc_buff.IDPDB,buff,10);
                    _tcscat(line_save,buff);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,oc_buff.nazwa);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,oc_buff.tytul_tekstu);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,oc_buff.autor_tekstu);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,oc_buff.strona_www);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,oc_buff.ocena_krytyka);
                    _tcscat(line_save,_TEXT("\""));

                    _tcscat(line_save,_TEXT("\n\r"));
                    fn_exp.WriteString(line_save);
                }
                i = i + sizeof(oc_src);
            }
            oc_src.Close();
        }

        if (this->CHECK_OB.GetCheck() == BST_CHECKED)
        {
            struct Obsada ob_buff;
            CFile ob_src;
            ob_src.Open(flm_eks.pths.BF_OB,CFile::modeRead);
            _tcscpy(line_save,TEXT("Tabela Obsada\n\r"));
            fn_exp.WriteString(line_save);
            LONGLONG stop = ob_src.SeekToEnd();

            _tcscpy(line_save,_TEXT("\"ID\""));
            _tcscat(line_save,_TEXT(",\"IDPDB\""));
            _tcscat(line_save,_TEXT(",\" Imię i Nazwisko\""));
            _tcscat(line_save,_TEXT(",\" Rola\""));

            _tcscat(line_save,_TEXT("\n\r"));
            fn_exp.WriteString(line_save);

            for (LONGLONG i = 0; i < stop; )
            {
                ob_src.Seek(i,CFile::begin);
                ob_src.Read(&ob_buff,sizeof(ob_buff));

                if (ob_buff.IDPDB == flm_eks.film_tbl.ID)
                {

                    _tcscpy(line_save,_TEXT("\""));
                    wchar_t buff[20];
                    _itow(ob_buff.ID,buff,10);
                    _tcscat(line_save,buff);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _itow(ob_buff.IDPDB,buff,10);
                    _tcscat(line_save,buff);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,ob_buff.imie_nazw);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save, ob_buff.rola);
                    _tcscat(line_save,_TEXT("\""));

                    _tcscat(line_save,_TEXT("\n\r"));
                    fn_exp.WriteString(line_save);
                }
                i = i + sizeof(ob_buff);
            }
            ob_src.Close();

        }

        if (this->CHECK_PD.GetCheck() == BST_CHECKED)
        {
            struct Producent pp_buff;
            CFile pp_src;
            pp_src.Open(flm_eks.pths.BF_PRP,CFile::modeRead);
            _tcscpy(line_save,TEXT("Tabela Produkcja\n\r"));
            fn_exp.WriteString(line_save);
            LONGLONG stop = pp_src.SeekToEnd();

            _tcscpy(line_save,_TEXT("\"ID\""));
            _tcscat(line_save,_TEXT(",\"IDPDB\""));
            _tcscat(line_save,_TEXT(",\"Nazwa Firmy\""));
            _tcscat(line_save,_TEXT(",\"Adres\""));
            _tcscat(line_save,_TEXT(",\"Telefon\""));
            _tcscat(line_save,_TEXT(",\"Fax\""));
            _tcscat(line_save,_TEXT(",\"E-mail\""));
            _tcscat(line_save,_TEXT(",\"Strona WWW\""));
            _tcscat(line_save,_TEXT(",\"Narodowość\""));

            _tcscat(line_save,_TEXT("\n\r"));
            fn_exp.WriteString(line_save);

            for (LONGLONG i = 0; i < stop; )
            {
                pp_src.Seek(i,CFile::begin);
                pp_src.Read(&pp_buff,sizeof(pp_buff));

                if (pp_buff.IDPDB == flm_eks.film_tbl.ID)
                {

                    _tcscpy(line_save,_TEXT("\""));
                    wchar_t buff[20];
                    _itow(pp_buff.ID,buff,10);
                    _tcscat(line_save,buff);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _itow(pp_buff.IDPDB,buff,10);
                    _tcscat(line_save,buff);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,pp_buff.nazwa_firmy);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,pp_buff.adres);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,pp_buff.telefon);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,pp_buff.fax);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,pp_buff.email);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,pp_buff.strona_www);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,pp_buff.narodowosc);
                    _tcscat(line_save,_TEXT("\""));

                    _tcscat(line_save,_TEXT("\n\r"));
                    fn_exp.WriteString(line_save);
                }
                i = i + sizeof(pp_buff);
            }
            pp_src.Close();

            struct Dystrybutor pd_buff;
            CFile pd_src;
            pd_src.Open(flm_eks.pths.BF_PRD,CFile::modeRead);
            _tcscpy(line_save,TEXT("Tabela Dystrybucja\n\r"));
            fn_exp.WriteString(line_save);
            stop = pd_src.SeekToEnd();

            _tcscpy(line_save,_TEXT("\"ID\""));
            _tcscat(line_save,_TEXT(",\"IDPDB\""));
            _tcscat(line_save,_TEXT(",\"Nazwa Firmy\""));
            _tcscat(line_save,_TEXT(",\"Adres\""));
            _tcscat(line_save,_TEXT(",\"Telefon\""));
            _tcscat(line_save,_TEXT(",\"Fax\""));
            _tcscat(line_save,_TEXT(",\"E-mail\""));
            _tcscat(line_save,_TEXT(",\"Strona WWW\""));
            _tcscat(line_save,_TEXT(",\"Narodowość\""));

            _tcscat(line_save,_TEXT("\n\r"));
            fn_exp.WriteString(line_save);

            for (LONGLONG i = 0; i < stop; )
            {
                pd_src.Seek(i,CFile::begin);
                pd_src.Read(&pd_buff,sizeof(pd_buff));

                if (pd_buff.IDPDB == flm_eks.film_tbl.ID)
                {

                    _tcscpy(line_save,_TEXT("\""));
                    wchar_t buff[20];
                    _itow(pd_buff.ID,buff,10);
                    _tcscat(line_save,buff);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _itow(pd_buff.IDPDB,buff,10);
                    _tcscat(line_save,buff);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,pd_buff.nazwa_firmy);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,pd_buff.adres);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,pd_buff.telefon);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,pd_buff.fax);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,pd_buff.email);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,pd_buff.strona_www);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,pd_buff.narodowosc);
                    _tcscat(line_save,_TEXT("\""));

                    _tcscat(line_save,_TEXT("\n\r"));
                    fn_exp.WriteString(line_save);
                }
                i = i + sizeof(pd_buff);
            }
            pd_src.Close();

        }

        if (this->CHECK_LZ.GetCheck() == BST_CHECKED)
        {
            struct Lok_zdjeciowe lz_buff;
            CFile lz_src;
            lz_src.Open(flm_eks.pths.BF_LZ,CFile::modeRead);
            _tcscpy(line_save,TEXT("Tabela Lokalizacje Zdjęciowe\n\r"));
            fn_exp.WriteString(line_save);
            LONGLONG stop = lz_src.SeekToEnd();

            _tcscpy(line_save,_TEXT("\"ID\""));
            _tcscat(line_save,_TEXT(",\"IDPDB\""));
            _tcscat(line_save,_TEXT(",\"Nazwa obiektu\""));
            _tcscat(line_save,_TEXT(",\"Kraj\""));
            _tcscat(line_save,_TEXT(",\"Miejscowość\""));
            _tcscat(line_save,_TEXT(",\"Region\""));
            _tcscat(line_save,_TEXT(",\"Pora roku\""));
            _tcscat(line_save,_TEXT(",\"Data\""));

            _tcscat(line_save,_TEXT("\n\r"));
            fn_exp.WriteString(line_save);

            for (LONGLONG i = 0; i < stop; )
            {
                lz_src.Seek(i,CFile::begin);
                lz_src.Read(&lz_buff,sizeof(lz_buff));

                if (lz_buff.IDPDB == flm_eks.film_tbl.ID)
                {
                    _tcscpy(line_save,_TEXT("\""));
                    wchar_t buff[20];
                    _itow(lz_buff.ID,buff,10);
                    _tcscat(line_save,buff);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _itow(lz_buff.IDPDB,buff,10);
                    _tcscat(line_save,buff);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,lz_buff.nazwa_obiektu);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,lz_buff.kraj);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,lz_buff.miejscowosc);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,lz_buff.region);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,lz_buff.pora_roku);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,lz_buff.data);
                    _tcscat(line_save,_TEXT("\""));

                    _tcscat(line_save,_TEXT("\n\r"));
                    fn_exp.WriteString(line_save);
                }
                i = i + sizeof(lz_buff);
            }
            lz_src.Close();
        }

        if (this->CHECK_WYP.GetCheck() == BST_CHECKED)
        {
            struct Wypozycz_Innym wi_buff;
            CFile wi_src;
            wi_src.Open(flm_eks.pths.BF_WI,CFile::modeRead);
            _tcscpy(line_save,TEXT("Tabela Wypożyczenia Innym Osobom\n\r"));
            fn_exp.WriteString(line_save);
            LONGLONG stop = wi_src.SeekToEnd();

            _tcscpy(line_save,_TEXT("\"ID\""));
            _tcscat(line_save,_TEXT(",\"IDPDB\""));
            _tcscat(line_save,_TEXT(",\"Data wypożyczenia\""));
            _tcscat(line_save,_TEXT(",\"Data oddania\""));
            _tcscat(line_save,_TEXT(",\"Stan przed wypożyczeniem\""));
            _tcscat(line_save,_TEXT(",\"Stan po oddaniu\""));
            _tcscat(line_save,_TEXT(",\"Osoba\""));
            _tcscat(line_save,_TEXT(",\"Nr katalogowy\""));

            _tcscat(line_save,_TEXT("\n\r"));
            fn_exp.WriteString(line_save);

            for (LONGLONG i = 0; i < stop; )
            {
                wi_src.Seek(i,CFile::begin);
                wi_src.Read(&wi_buff,sizeof(wi_buff));

                if (wi_buff.IDPDB == flm_eks.film_tbl.ID)
                {

                    _tcscpy(line_save,_TEXT("\""));
                    wchar_t buff[20];
                    _itow(wi_buff.ID,buff,10);
                    _tcscat(line_save,buff);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _itow(wi_buff.IDPDB,buff,10);
                    _tcscat(line_save,buff);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,wi_buff.data_wypozyczenia);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,wi_buff.data_oddania);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,wi_buff.stan_przed_wypozycz);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,wi_buff.stan_po_oddaniu);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,wi_buff.osoba);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,wi_buff.Nr_kat);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT("\n\r"));
                    fn_exp.WriteString(line_save);
                }


                i = i + sizeof(wi_buff);
            }
            wi_src.Close();

            struct Wypozycz_Od_Innych wo_buff;
            CFile wo_src;
            wo_src.Open(flm_eks.pths.BF_WO,CFile::modeRead);
            _tcscpy(line_save,TEXT("Tabela Wypożyczenia od Innych Osób\n\r"));
            fn_exp.WriteString(line_save);
            stop = wo_src.SeekToEnd();

            _tcscpy(line_save,_TEXT("\"ID\""));
            _tcscat(line_save,_TEXT(",\"IDPDB\""));
            _tcscat(line_save,_TEXT(",\"Data wypożyczenia\""));
            _tcscat(line_save,_TEXT(",\"Data oddania\""));
            _tcscat(line_save,_TEXT(",\"Stan przed wypożyczeniem\""));
            _tcscat(line_save,_TEXT(",\"Stan po oddaniu\""));
            _tcscat(line_save,_TEXT(",\"Osoba\""));
            _tcscat(line_save,_TEXT(",\"Nr katalogowy\""));

            _tcscat(line_save,_TEXT("\n\r"));
            fn_exp.WriteString(line_save);

            for (LONGLONG i = 0; i < stop; )
            {
                wo_src.Seek(i,CFile::begin);
                wo_src.Read(&wo_buff,sizeof(wo_buff));
                if (wo_buff.IDPDB == flm_eks.film_tbl.ID)
                {
                    _tcscpy(line_save,_TEXT("\""));
                    wchar_t buff[20];
                    _itow(wo_buff.ID,buff,10);
                    _tcscat(line_save,buff);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _itow(wo_buff.IDPDB,buff,10);
                    _tcscat(line_save,buff);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,wo_buff.data_wypozyczenia);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,wo_buff.data_oddania);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,wo_buff.stan_przed_wypozycz);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,wo_buff.stan_po_oddaniu);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,wo_buff.osoba);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT(",\""));
                    _tcscat(line_save,wo_buff.Nr_kat);
                    _tcscat(line_save,_TEXT("\""));
                    _tcscat(line_save,_TEXT("\n\r"));
                    fn_exp.WriteString(line_save);
                }
                i = i + sizeof(wo_buff);
            }
            wo_src.Close();
        }
        fn_exp.Close();

    }




void Eksportuj::on_pushButton_Anuluj_clicked()
{
    this->close();
}
