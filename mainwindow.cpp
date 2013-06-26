#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QList>
#include <QFileDialog>
#include <windows.h>

struct Film Ftbl::film_tbl;    // struktura mieszczaca jeden rekord form film
bool Ftbl::sort = false;
struct DB_paths Ftbl::pths;

Ftbl flm;

unsigned int sort_idx = 0; // zmienna pomocnicza slużaca do poruszania sie po indeksie film_tbl_wsk
unsigned int zadana_pozycja_pliku = 0; // pozycja rekordu w BF_PDB
unsigned int akt_pozycja_pliku = 0; // pozycja rekordu w BF_PDB

wchar_t akt_BF_VER[16] = L"1.0.6.0";
bool first_act = true;
bool start = true; // oznacza czy aplikacja startuje;
bool open_folder = false;

bool add_new_wi = false;
bool add_new_wo = false;
struct Wypozycz_Innym wi;
struct Wypozycz_Od_Innych wo;
QList <Wypozycz_Innym> wi_arr;
QList <Wypozycz_Od_Innych> wo_arr;

struct Lok_zdjeciowe lz;
bool add_new_lz = false;
QList <Lok_zdjeciowe> lz_arr;

struct Obsada ob;
bool add_new_ob = false;
QList <Obsada> ob_arr;

struct Ocena oc;
bool add_new_oc = false;
QList <Ocena> oc_arr;

struct Producent pp;
struct Dystrybutor pd;
bool add_new_pp = false;
bool add_new_pd = false;
QList <Producent> pp_arr;
QList <Dystrybutor> pd_arr;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start = true;
        MainWindow::Read_Settings();
        MainWindow::SetDBFNPaths(false, NULL);
        if ((MainWindow::CheckbOpenDB() == 1))
        {
            if (CheckOLDDB())
            {
                KopiujOLDDB();
            }
            else
            {
                UtworzDB(false);
            }
        }
        else if (MainWindow::CheckbOpenDB() == 2)
        {
            this->close();

        }

        //MainWindow::Insert_TAB_Item();
        //MainWindow::SetDlgBoxs(10);
        //MainWindow::SetListCtrls(5);
        MainWindow::SetButtons();
        MainWindow::SetBTNIcons();



        flm.sort = false;
        //_spawnl(_P_NOWAIT,"MK_AUTOUPDATE.exe","MK_AUTOUPDATE.exe",NULL);

        UpdateCtrls(false,true);
        Licz_Rec();
        //UpdateCtrls(false,true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_First_clicked()
{
    if (!(Licz_Rec()))
    {
        //OnBnClickedButtonFrmFSave();
        zadana_pozycja_pliku = 0;
        ClearCtrls(false);
        UpdateCtrls(false,false);
        Licz_Rec();
    }

}

void MainWindow::on_pushButton_Prev_clicked()
{
    if (!(Licz_Rec()))
    {
        //OnBnClickedButtonFrmFSave();
        if (zadana_pozycja_pliku > 0)
        {
            zadana_pozycja_pliku = zadana_pozycja_pliku - (sizeof(struct Film));
        }
        else if (zadana_pozycja_pliku < 0)
        {
            zadana_pozycja_pliku = 0;
        }
        ClearCtrls(false);
        UpdateCtrls(false,false);
        Licz_Rec();

    }
}

void MainWindow::on_pushButton_Next_clicked()
{
    if (!(Licz_Rec()))
    {
        //OnBnClickedButtonFrmFSave();
        zadana_pozycja_pliku = zadana_pozycja_pliku + (sizeof(struct Film));
        if (zadana_pozycja_pliku >= Search_Last_Pos())
        {
            zadana_pozycja_pliku = 0;
        }
        ClearCtrls(false);
        UpdateCtrls(false,false);
        Licz_Rec();
    }

}

void MainWindow::on_pushButton_Last_clicked()
{
    if (!(Licz_Rec()))
    {
        //OnBnClickedButtonFrmFSave();
        zadana_pozycja_pliku = MainWindow::Search_Last_Pos() - (sizeof(flm.film_tbl));
        ClearCtrls(true);
        UpdateCtrls(false,false);
        Licz_Rec();

    }
}

void MainWindow::on_pushButton_New_clicked()
{
    ClearCtrls(true); // wyczyść kontrolki

    bool test;
    if (Licz_Rec() == true)
    {
        test = MainWindow::Film_DodajRec(true);                   // wywołaj procedure dodania nowego rekordu włącznie z zapisem
    }
    else
    {
        test = MainWindow::Film_DodajRec(false);
    }
    if (test)
    {
        ClearCtrls(false);
        UpdateCtrls(false,false); // odswież kontrolki
        Licz_Rec();
        MainWindow::Enable_BTNS_NOREC();
    }
    else
    {
                // wyświetl komunikat o błędzie
    }

}

void MainWindow::on_pushButton_Save_clicked()
{
    UpdateCtrls(true,false);
        if (Save_Full_Film()) {
            ClearCtrls(false);
            UpdateCtrls(false,false);

        }
        else
        {
            // wyswietl komunikat o błędzie zapisu
        }
}

void MainWindow::on_pushButton_Del_clicked()
{
    Del_Film_Rec();
        UpdateCtrls(false,true);
        if (Licz_Rec())
        {
            MainWindow::Disable_BTNS_NOREC();

        }
}

void MainWindow::on_pushButton_IntWiz_clicked()
{

}

void MainWindow::UpdateCtrls(bool BINDOUT, bool start)
{
    if (BINDOUT == true) {
            Bind_OUT_Controls();
        }
        else if (BINDOUT == false) {
            if (start)
            {
                Fill_Full_Film(true);
            }
            else if (start == false)
            {
                Fill_Full_Film(false);
            }
            Bind_IN_Controls();
        }
}
void MainWindow::Bind_IN_Controls(void)
{
    // ta funkcja pobiera dane ze struktury flm.film_tbl i zapisuje w kontrolkach
        wchar_t dest[34];
        //F_EDIT_ID.SetReadOnly(FALSE);
        _itow(flm.film_tbl.ID,dest,10); // tu jest problem - access violation
        ui->lineEdit_ID->setText(QString::fromWCharArray(dest)); // tu jest problem BEX
        //F_EDIT_ID.SetReadOnly(TRUE);
        ui->lineEdit_Tytul->setText(QString::fromWCharArray(flm.film_tbl.tytul));
        ui->lineEdit_TytulOrig->setText(QString::fromWCharArray(flm.film_tbl.oryginalny_tytul));
        ui->lineEdit_Gatunek->setText(QString::fromWCharArray(flm.film_tbl.gatunek_filmu));
        //ui->textEdit_Opis->setText(flm.film2_ftbl.opis);


        if ((QString::fromWCharArray(flm.film_tbl.skan_przod_path).compare("")) != 0)
        {
            //QFile pic_front(QString::fromWCharArray(flm.film_tbl.skan_przod_path));
            QFileInfo img_stat(QString::fromWCharArray(flm.film_tbl.skan_przod_path));
            if (img_stat.exists())
            {

                QImage img_front(QString::fromWCharArray(flm.film_tbl.skan_przod_path),NULL);
                img_front.scaled(139,172,Qt::IgnoreAspectRatio);
                ui->label_PicFront->setPixmap(QPixmap::fromImage(img_front));

            }
        }
        else
        {
            QImage img_front("/covers/no_img.bmp",NULL);
            img_front.scaled(139,172,Qt::IgnoreAspectRatio);
            ui->label_PicFront->setPixmap(QPixmap::fromImage(img_front));



        }


        //TAB OCENA

        ui->lineEdit_OC_OW_SD->setText(QString::fromWCharArray(flm.film_tbl.WOF_sciezka_dz));
        ui->lineEdit_OC_OW_Obs->setText(QString::fromWCharArray(flm.film_tbl.WOF_obsada));
        ui->lineEdit__OC_OW_Zdj->setText(QString::fromWCharArray(flm.film_tbl.WOF_zdjecia));
        ui->lineEdit__OC_OW_WA->setText(QString::fromWCharArray(flm.film_tbl.WOF_w_art));
        ui->lineEdit__OC_OW_All->setText(QString::fromWCharArray(flm.film_tbl.WOF_calosc));

        // TAB PRODUKCJA


        // TAB DOE
        ui->lineEdit_DOE_W_Imie->setText(QString::fromWCharArray(flm.film_tbl.DOE_WKF_imie));
        ui->lineEdit_DOE_W_Nazw->setText(QString::fromWCharArray(flm.film_tbl.DOE_WKF_nazwisko));
        ui->lineEdit_DOE_W_Adres->setText(QString::fromWCharArray(flm.film_tbl.DOE_WKF_adres));
        ui->lineEdit_DOE_S_Nazwa->setText(QString::fromWCharArray(flm.film_tbl.DOE_MN_nazwa));
        ui->lineEdit_DOE_S_Adres->setText(QString::fromWCharArray(flm.film_tbl.DOE_MN_adres));
        ui->lineEdit_DOE_S_WWW->setText(QString::fromWCharArray(flm.film_tbl.DOE_MN_www));
        ui->lineEdit_DOE_S_Tel->setText(QString::fromWCharArray(flm.film_tbl.DOE_MN_telefon));
        ui->lineEdit_DOE_S_Fax->setText(QString::fromWCharArray(flm.film_tbl.DOE_MN_fax));
        ui->lineEdit_DOE_S_Email->setText(QString::fromWCharArray(flm.film_tbl.DOE_MN_email));
        ui->lineEdit_DOE_Cena->setText(QString::fromWCharArray(flm.film_tbl.DOE_cena));
        ui->lineEdit_DOE_Wakt->setText(QString::fromWCharArray(flm.film_tbl.DOE_wartosc_akt));
        ui->lineEdit_DOE_DataZak->setText(QString::fromWCharArray(flm.film_tbl.DOE_data_zakupu));
        ui->lineEdit_DOE_DataUtr->setText(QString::fromWCharArray(flm.film_tbl.DOE_data_utraty));
        ui->lineEdit_DOE_DataSkat->setText(QString::fromWCharArray(flm.film_tbl.DOE_data_skatalogowania));
        ui->lineEdit_DOE_NrKat->setText(QString::fromWCharArray(flm.film_tbl.DOE_Nr_kat));
        ui->fontComboBox_DOE_Nosnik->lineEdit()->setText(QString::fromWCharArray(flm.film_tbl.DOE_rodzaj_nosnika));
        // TAB IOF
        ui->lineEdit_RokProd->setText(QString::fromWCharArray(flm.film_tbl.IOF_rok_produkcji));
        ui->lineEdit_DataPrem->setText(QString::fromWCharArray(flm.film_tbl.IOF_data_premiery));
        ui->lineEdit_CzasProj->setText(QString::fromWCharArray(flm.film_tbl.IOF_czas_trwania));
        ui->lineEdit_FormWysw->setText(QString::fromWCharArray(flm.film_tbl.IOF_format_wysw));
        ui->lineEdit_SysKodObr->setText(QString::fromWCharArray(flm.film_tbl.IOF_system_kodowania_obrazu));
        ui->lineEdit_JezLekt->setText(QString::fromWCharArray(flm.film_tbl.IOF_jezyk_lektora));
        ui->lineEdit_JezNap->setText(QString::fromWCharArray(flm.film_tbl.IOF_jezyk_napisow));
        ui->lineEdit_KrajProd->setText(QString::fromWCharArray(flm.film_tbl.IOF_kraj_produkcji_filmu));
        ui->lineEdit_KodVidNazwa->setText(QString::fromWCharArray(flm.film_tbl.IOF_KODEK_nazwa));
        ui->lineEdit_KodVidTyp->setText(QString::fromWCharArray(flm.film_tbl.IOF_KODEK_typ));
        ui->lineEdit_KodVidWersja->setText(QString::fromWCharArray(flm.film_tbl.IOF_KODEK_wersja));
        ui->lineEdit_KodAudNazwa->setText(QString::fromWCharArray(flm.film_tbl.IOF_DZWIEK_nazwa));
        ui->lineEdit_KodAudTyp->setText(QString::fromWCharArray(flm.film_tbl.IOF_DZWIEK_typ));
        ui->lineEdit_KodAudWersja->setText(QString::fromWCharArray(flm.film_tbl.IOF_DZWIEK_wersja));
        ui->lineEdit_ZabNazwa->setText(QString::fromWCharArray(flm.film_tbl.IOF_ZABEZP_nazwa));
        ui->lineEdit_ZabTyp->setText(QString::fromWCharArray(flm.film_tbl.IOF_ZABEZP_typ));
        ui->lineEdit_ZabWersja->setText(QString::fromWCharArray(flm.film_tbl.IOF_ZABEZP_wersja));

        //Invalidate();
        //UpdateWindow();

}
void MainWindow::Bind_OUT_Controls(void)
{
    // ta funkcja pobiera dane z formularza i zapisuje w strukturze flm.film_tbl

        // FORM FILM
        ui->lineEdit_Tytul->text().toWCharArray(flm.film_tbl.tytul);
        ui->lineEdit_TytulOrig->text().toWCharArray(flm.film_tbl.oryginalny_tytul);
        ui->lineEdit_Gatunek->text().toWCharArray(flm.film_tbl.gatunek_filmu);
        //ui->textEdit_Opis->toPlainText().toWCharArray((flm.film2_ftbl.opis));
        //TAB OCENA
        ui->lineEdit_OC_OW_SD->text().toWCharArray(flm.film_tbl.WOF_sciezka_dz);
        ui->lineEdit_OC_OW_Obs->text().toWCharArray(flm.film_tbl.WOF_obsada);
        ui->lineEdit__OC_OW_Zdj->text().toWCharArray(flm.film_tbl.WOF_zdjecia);
        ui->lineEdit__OC_OW_WA->text().toWCharArray(flm.film_tbl.WOF_w_art);
        ui->lineEdit__OC_OW_All->text().toWCharArray(flm.film_tbl.WOF_calosc);

        // TAB PRODUKCJA

        // TAB DOE
        ui->lineEdit_DOE_W_Imie->text().toWCharArray(flm.film_tbl.DOE_WKF_imie);
        ui->lineEdit_DOE_W_Nazw->text().toWCharArray(flm.film_tbl.DOE_WKF_nazwisko);
        ui->lineEdit_DOE_W_Adres->text().toWCharArray(flm.film_tbl.DOE_WKF_adres);
        ui->lineEdit_DOE_S_Nazwa->text().toWCharArray(flm.film_tbl.DOE_MN_nazwa);
        ui->lineEdit_DOE_S_Adres->text().toWCharArray(flm.film_tbl.DOE_MN_adres);
        ui->lineEdit_DOE_S_WWW->text().toWCharArray(flm.film_tbl.DOE_MN_www);
        ui->lineEdit_DOE_S_Tel->text().toWCharArray(flm.film_tbl.DOE_MN_telefon);
        ui->lineEdit_DOE_S_Fax->text().toWCharArray(flm.film_tbl.DOE_MN_fax);
        ui->lineEdit_DOE_S_Email->text().toWCharArray(flm.film_tbl.DOE_MN_email);
        ui->lineEdit_DOE_Cena->text().toWCharArray(flm.film_tbl.DOE_cena);
        ui->lineEdit_DOE_Wakt->text().toWCharArray(flm.film_tbl.DOE_wartosc_akt);
        ui->lineEdit_DOE_DataZak->text().toWCharArray(flm.film_tbl.DOE_data_zakupu);
        ui->lineEdit_DOE_DataUtr->text().toWCharArray(flm.film_tbl.DOE_data_utraty);
        ui->lineEdit_DOE_DataSkat->text().toWCharArray(flm.film_tbl.DOE_data_skatalogowania);
        ui->lineEdit_DOE_NrKat->text().toWCharArray(flm.film_tbl.DOE_Nr_kat);
        ui->fontComboBox_DOE_Nosnik->lineEdit()->text().toWCharArray(flm.film_tbl.DOE_rodzaj_nosnika);
        // TAB IOF
        ui->lineEdit_RokProd->text().toWCharArray(flm.film_tbl.IOF_rok_produkcji);
        ui->lineEdit_DataPrem->text().toWCharArray(flm.film_tbl.IOF_data_premiery);
        ui->lineEdit_CzasProj->text().toWCharArray(flm.film_tbl.IOF_czas_trwania);
        ui->lineEdit_FormWysw->text().toWCharArray(flm.film_tbl.IOF_format_wysw);
        ui->lineEdit_SysKodObr->text().toWCharArray(flm.film_tbl.IOF_system_kodowania_obrazu);
        ui->lineEdit_JezLekt->text().toWCharArray(flm.film_tbl.IOF_jezyk_lektora);
        ui->lineEdit_JezNap->text().toWCharArray(flm.film_tbl.IOF_jezyk_napisow);
        ui->lineEdit_KrajProd->text().toWCharArray(flm.film_tbl.IOF_kraj_produkcji_filmu);
        ui->lineEdit_KodVidNazwa->text().toWCharArray(flm.film_tbl.IOF_KODEK_nazwa);
        ui->lineEdit_KodVidTyp->text().toWCharArray(flm.film_tbl.IOF_KODEK_typ);
        ui->lineEdit_KodVidWersja->text().toWCharArray(flm.film_tbl.IOF_KODEK_wersja);
        ui->lineEdit_KodAudNazwa->text().toWCharArray(flm.film_tbl.IOF_DZWIEK_nazwa);
        ui->lineEdit_KodAudTyp->text().toWCharArray(flm.film_tbl.IOF_DZWIEK_typ);
        ui->lineEdit_KodAudWersja->text().toWCharArray(flm.film_tbl.IOF_DZWIEK_wersja);
        ui->lineEdit_ZabNazwa->text().toWCharArray(flm.film_tbl.IOF_ZABEZP_nazwa);
        ui->lineEdit_ZabTyp->text().toWCharArray(flm.film_tbl.IOF_ZABEZP_typ);
        ui->lineEdit_ZabWersja->text().toWCharArray(flm.film_tbl.IOF_ZABEZP_wersja);
}
void MainWindow::ClearCtrls(bool all)
{
// Clear Form

    ui->lineEdit_ID->clear();
    ui->lineEdit_Tytul->clear();
    ui->lineEdit_TytulOrig->clear();
    ui->lineEdit_Gatunek->clear();
    //ui->textEdit_Opis->clear();

    //TAB OCENA

    ui->lineEdit_OC_OW_SD->clear();
    ui->lineEdit_OC_OW_Obs->clear();
    ui->lineEdit__OC_OW_Zdj->clear();
    ui->lineEdit__OC_OW_WA->clear();
    ui->lineEdit__OC_OW_All->clear();

    ui->tableWidget_OC->clearContents(); // czyszczenie listctrl

    // TAB OBSADA

    ui->tableWidget_Obsada->clearContents(); // czyszczenie listctrl;

    // TAB PRODUKCJA

    ui->tableWidget_Prod->clearContents();  // czyszczenie listctrl
    ui->tableWidget_Dystr->clearContents();

    // TAB DOE
    ui->lineEdit_DOE_W_Imie->clear();
    ui->lineEdit_DOE_W_Nazw->clear();
    ui->lineEdit_DOE_W_Adres->clear();
    ui->lineEdit_DOE_S_Nazwa->clear();
    ui->lineEdit_DOE_S_Adres->clear();
    ui->lineEdit_DOE_S_WWW->clear();
    ui->lineEdit_DOE_S_Tel->clear();
    ui->lineEdit_DOE_S_Fax->clear();
    ui->lineEdit_DOE_S_Email->clear();
    ui->lineEdit_DOE_Cena->clear();
    ui->lineEdit_DOE_Wakt->clear();
    ui->lineEdit_DOE_DataZak->clear();
    ui->lineEdit_DOE_DataUtr->clear();
    ui->lineEdit_DOE_DataSkat->clear();
    ui->lineEdit_DOE_NrKat->clear();
    ui->fontComboBox_DOE_Nosnik->lineEdit()->clear();
    // TAB IOF
    ui->lineEdit_RokProd->clear();
    ui->lineEdit_DataPrem->clear();
    ui->lineEdit_CzasProj->clear();
    ui->lineEdit_FormWysw->clear();
    ui->lineEdit_SysKodObr->clear();
    ui->lineEdit_JezLekt->clear();
    ui->lineEdit_JezNap->clear();
    ui->lineEdit_KrajProd->clear();
    ui->lineEdit_KodVidNazwa->clear();
    ui->lineEdit_KodVidTyp->clear();
    ui->lineEdit_KodVidWersja->clear();
    ui->lineEdit_KodAudNazwa->clear();
    ui->lineEdit_KodAudTyp->clear();
    ui->lineEdit_KodAudWersja->clear();
    ui->lineEdit_ZabNazwa->clear();
    ui->lineEdit_ZabTyp->clear();
    ui->lineEdit_ZabWersja->clear();

    ui->tableWidget_IOF_LZ->clearContents(); // czyszczenie listctrl;

    // TAB Bibliotekarz
    ui->tableWidget_BIBLIO_WYPIN->clearContents(); // czyszczenie listctrl
    ui->tableWidget_BIBLIO_WYPODIN->clearContents();

// STRUCT flm.film_tbl CLEAR
if (all)
{
    wcscpy(flm.film_tbl.DOE_cena,L"");
    wcscpy(flm.film_tbl.DOE_data_skatalogowania,L"");
    wcscpy(flm.film_tbl.DOE_data_utraty,L"");
    wcscpy(flm.film_tbl.DOE_data_zakupu,L"");
    wcscpy(flm.film_tbl.DOE_MN_adres,L"");
    wcscpy(flm.film_tbl.DOE_MN_email,L"");
    wcscpy(flm.film_tbl.DOE_MN_fax,L"");
    wcscpy(flm.film_tbl.DOE_MN_nazwa,L"");
    wcscpy(flm.film_tbl.DOE_MN_telefon,L"");
    wcscpy(flm.film_tbl.DOE_MN_www,L"");
    wcscpy(flm.film_tbl.DOE_Nr_kat,L"");
    wcscpy(flm.film_tbl.DOE_rodzaj_nosnika,L"");
    wcscpy(flm.film_tbl.DOE_wartosc_akt,L"");
    wcscpy(flm.film_tbl.DOE_WKF_adres,L"");
    wcscpy(flm.film_tbl.DOE_WKF_imie,L"");
    wcscpy(flm.film_tbl.DOE_WKF_nazwisko,L"");
    wcscpy(flm.film_tbl.gatunek_filmu,L"");
    flm.film_tbl.ID = 0;
    wcscpy(flm.film_tbl.IOF_czas_trwania,L"");
    wcscpy(flm.film_tbl.IOF_data_premiery,L"");
    wcscpy(flm.film_tbl.IOF_DZWIEK_nazwa,L"");
    wcscpy(flm.film_tbl.IOF_DZWIEK_typ,L"");
    wcscpy(flm.film_tbl.IOF_DZWIEK_wersja,L"");
    wcscpy(flm.film_tbl.IOF_format_wysw,L"");
    wcscpy(flm.film_tbl.IOF_jezyk_lektora,L"");
    wcscpy(flm.film_tbl.IOF_jezyk_napisow,L"");
    wcscpy(flm.film_tbl.IOF_KODEK_nazwa,L"");
    wcscpy(flm.film_tbl.IOF_KODEK_typ,L"");
    wcscpy(flm.film_tbl.IOF_KODEK_wersja,L"");
    wcscpy(flm.film_tbl.IOF_kraj_produkcji_filmu,L"");
    wcscpy(flm.film_tbl.IOF_rok_produkcji,L"");
    wcscpy(flm.film_tbl.IOF_system_kodowania_obrazu,L"");
    wcscpy(flm.film_tbl.IOF_ZABEZP_nazwa,L"");
    wcscpy(flm.film_tbl.IOF_ZABEZP_typ,L"");
    wcscpy(flm.film_tbl.IOF_ZABEZP_wersja,L"");
    wcscpy(flm.film_tbl.O_muzyka_imie_nazw,L"");
    wcscpy(flm.film_tbl.O_muzyka_narod,L"");
    wcscpy(flm.film_tbl.O_operator_imie_nazw,L"");
    wcscpy(flm.film_tbl.O_operator_narod,L"");
    wcscpy(flm.film_tbl.O_rezyser_imie_nazw,L"");
    wcscpy(flm.film_tbl.O_rezyser_narod,L"");
    wcscpy(flm.film_tbl.O_scenariusz_imie_nazw,L"");
    wcscpy(flm.film_tbl.O_scenariusz_narod,L"");
    wcscpy(flm.film_tbl.oryginalny_tytul,L"");
    wcscpy(flm.film_tbl.tytul,L"");
    wcscpy(flm.film_tbl.WOF_calosc,L"");
    wcscpy(flm.film_tbl.WOF_obsada,L"");
    wcscpy(flm.film_tbl.WOF_sciezka_dz,L"");
    wcscpy(flm.film_tbl.WOF_w_art,L"");
    wcscpy(flm.film_tbl.WOF_zdjecia,L"");
    wcscpy(flm.film_tbl.skan_przod_path,L"");
    wcscpy(flm.film_tbl.skan_tyl_path,L"");
}
}
int MainWindow::CheckbOpenDB(void) {
// Sprawdza czy istnieją pliki bazy danych i, jesli tak,  zwraca true.
    bool test[9];
    QFileInfo fi(QString::fromWCharArray(flm.pths.BF_PDB));
    if (fi.exists())
    {
        test[0] = true;
    }
    else
    {
        test[0] = false;
    }
    QFileInfo fi2(QString::fromWCharArray(flm.pths.BF_OC));
    if (fi2.exists())
    {
        test[1] = true;
    }
    else
    {
        test[1] = false;
    }
    QFileInfo fi3(QString::fromWCharArray(flm.pths.BF_OB));
    if (fi3.exists())
    {
        test[2] = true;
    }
    else
    {
        test[2] = false;
    }
    QFileInfo fi4(QString::fromWCharArray(flm.pths.BF_PRP));
    if (fi4.exists())
    {
        test[3] = true;
    }
    else
    {
        test[3] = false;
    }
    QFileInfo fi5(QString::fromWCharArray(flm.pths.BF_PRD));
    if (fi5.exists())
    {
        test[4] = true;
    }
    else
    {
        test[4] = false;
    }
    QFileInfo fi6(QString::fromWCharArray(flm.pths.BF_LZ));
    if (fi6.exists())
    {
        test[5] = true;
    }
    else
    {
        test[5] = false;
    }
    QFileInfo fi7(QString::fromWCharArray(flm.pths.BF_WI));
    if (fi7.exists())
    {
        test[6] = true;
    }
    else
    {
        test[6] = false;
    }
    QFileInfo fi8(QString::fromWCharArray(flm.pths.BF_WO));
    if (fi8.exists())
    {
        test[7] = true;
    }
    else
    {
        test[7] = false;
    }
    QFileInfo fi9(QString::fromWCharArray(flm.pths.BF_MCF));
    if (fi9.exists())
    {
        test[8] = true;
    }
    else
    {
        test[8] = false;
    }

    if (test[0] == true && test[8] == true && test[1] == true && test[2] == true && test[3] == true && test[4] == true && test[5] == true && test[6] == true && test[7]== true)
    {
        return 0;
    }

    if (test[0] == false && test[8] == false && test[1] == false && test[2] == false && test[3] == false && test[4] == false && test[5] == false && test[6] == false && test[7]== false)
    {
        return 1;
    }
    else if ((test[0] == false || test[8] == false) && (test[1] == true || test[2] == true || test[3] == true || test[4] == true || test[5] == true || test[6] == true || test[7]== true))
    {
        QMessageBox msgbox(QMessageBox::Critical,"Biblioteka Filmów","Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.", QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }
    else if ((test[0] == true && test[8] == true) && (test[1] == false))
    {
        QMessageBox msgbox(QMessageBox::Critical,"Biblioteka Filmów","Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.",QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }
    else if ((test[0] == true && test[8] == true) && (test[2] == false))
    {
        QMessageBox msgbox(QMessageBox::Critical,"Biblioteka Filmów","Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.",QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }
    else if ((test[0] == true && test[8] == true) && (test[3] == false))
    {
        QMessageBox msgbox(QMessageBox::Critical,"Biblioteka Filmów","Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.",QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }
    else if ((test[0] == true && test[8] == true) && (test[4] == false))
    {
        QMessageBox msgbox(QMessageBox::Critical,"Biblioteka Filmów","Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.",QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }
    else if ((test[0] == true && test[8] == true) && (test[5] == false))
    {
        QMessageBox msgbox(QMessageBox::Critical,"Biblioteka Filmów","Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.",QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }
    else if ((test[0] == true && test[8] == true) && (test[6] == false))
    {
        QMessageBox msgbox(QMessageBox::Critical,"Biblioteka Filmów","Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.",QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }
    else if ((test[0] == true && test[8] == true) && (test[7]== false))
    {
        QMessageBox msgbox(QMessageBox::Critical,"Biblioteka Filmów","Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.",QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }

}

bool MainWindow::CheckBFVER(void)
{
// pobiera strukturę "POMIDOR" z poczatku pliku BF.dat celem sprawdzenia wersji bazy danych i co z tym idzie zgodności z
// ta wersją BF

    struct POMIDOR pom;
    QFile plik(QString::fromWCharArray(flm.pths.BF_MCF));
    plik.open(QFile::ReadOnly);
    plik.seek(0);

    plik.read(reinterpret_cast<char *>(&pom),sizeof(struct POMIDOR));
    plik.close();
    if ((wcscmp(pom.BF_VER,akt_BF_VER)) == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool MainWindow::Fill_Full_Film(bool start)
{
    if (CheckbOpenDB() == 0) // CheckbOpenDB()
    {
        if (true) //CheckBFVER()
        {

            // przeanalizuj filtr film_tbl_wsk[] i odczytaj pierwszy lub nastepny element wedlug zapisanej
            // w tablicy pozycji

            // pobierz pierwsza strukture z pliku "BF_PDB.dat" i przepisz ja do zmiennej struktury Film,
                // celem wyswietlenia
            QFile plik(QString::fromWCharArray(flm.pths.BF_PDB));
                plik.open(QFile::ReadOnly);
                if (start)
                {
                    plik.seek(0);
                }
                else if (start == false)
                {
                    plik.seek(zadana_pozycja_pliku);
                }
                plik.read(reinterpret_cast<char *>(&flm.film_tbl),sizeof(struct Film));

                plik.close();

                //Clear_TABS(); // czyszczenie kontrolek pól list

                //Fill_Opis();
                Fill_Oc(); // wypełnianie kontrolek pól list
                Fill_Ob();
                Fill_PD();
                Fill_PP();
                Fill_Lz();
                Fill_Wi();
                Fill_Wo();
                return true;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

}


bool MainWindow::Save_Full_Film(void) {
    if (CheckbOpenDB() == 0)
    {
        if (CheckBFVER())
        {
                //  odszukaj zadana strukture z pliku "BF_PDB.dat" i zapisz do pliku zawartosc zmiennej struktury Film,
                // , a potem odczytaj z pliku,celem wyswietlenia
            QFile plik(QString::fromWCharArray(flm.pths.BF_PDB));
                plik.open(QFile::WriteOnly);
                akt_pozycja_pliku = zadana_pozycja_pliku;
                plik.seek(zadana_pozycja_pliku);
                plik.write(reinterpret_cast<char *>(&flm.film_tbl),sizeof(flm.film_tbl));

                plik.close();
                Save_Oc();
                Save_Ob();
                Save_PP();
                Save_PD();
                Save_Lz();
                Save_Wi();
                Save_Wo();
                return true;

        }
        else
        {
            return false;
        }
    }
    else {
        return false;
    }

}

bool MainWindow::Film_DodajRec(bool first) {
    if (CheckbOpenDB()== 0)
    {
        if (CheckBFVER())
        {
            Oblicz_NewID();
            QFile plik(QString::fromWCharArray(flm.pths.BF_PDB));
            plik.open(QFile::WriteOnly);
            //akt_pozycja_pliku = plik.Seek(Search_Last_Pos(),CFile::begin);
            if (first)
            {
                plik.seek(0);
            }
            else
            {
                plik.seek(plik.size());
            }

            //plik.write(reinterpret_cast<char *>(&flm.film_tbl),sizeof(flm.film_tbl));

            plik.close();
            if (first)
            {
                zadana_pozycja_pliku = 0;
            }
            else
            {
                zadana_pozycja_pliku = MainWindow::Search_Last_Pos() - (sizeof(flm.film_tbl));
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

}

void MainWindow::Oblicz_NewID(void) {
    struct POMIDOR pom;
    QFile plik(QString::fromWCharArray(flm.pths.BF_MCF));
    plik.open(QFile::ReadOnly);
    plik.seek(0);
    //plik.read(reinterpret_cast<char *>(&pom),sizeof(struct POMIDOR));

    plik.close();
    flm.film_tbl.ID = pom.najw_ID + 1;
    pom.najw_ID = flm.film_tbl.ID;
    plik.open(QFile::WriteOnly);
    plik.seek(0);
    //plik.write(reinterpret_cast<char *>(&pom),sizeof(struct POMIDOR));

    plik.close();

}
unsigned int MainWindow::Search_Last_Pos(void) {
    if (!(Licz_Rec()))
    {
/*
        struct POMIDOR pom;
        CFile pom_file;
        pom_file.Open((BF_MCF),CFile::modeRead);
        pom_file.Seek(0,CFile::begin);
        pom_file.Read(&pom,sizeof(pom));
        pom_file.Close();

*/
        struct Film film_test;
        QFile plik(QString::fromWCharArray(flm.pths.BF_PDB));
        plik.open(QFile::ReadOnly);
/*
        unsigned int i;
        unsigned int y;
        for (y = 0 ;(plik.GetLength()) ;  )
        {
            plik.Seek(y,CFile::begin);
            plik.Read(&film_test,sizeof(film_test));
            if (pom.najw_ID == film_test.ID)
            {
                i = y + sizeof(film_test);
                return i;
            }
            else
            {
                    y = y + sizeof(film_test);
            }

        }
        plik.Close();
        */

        unsigned int off;
        off = plik.size();

        plik.close();

        return off;


    }
    else
    {
        return 0;
    }

}
void MainWindow::UtworzDB(bool cust)
{


    if (cust == false)
    {
        QDir di(QString::fromWCharArray(flm.pths.cur_db_path));
        if (!(di.exists() == TRUE))
        {
            di.mkpath(QString::fromWCharArray(flm.pths.cur_db_path));
        }
    }
    QDir di(QString::fromWCharArray(flm.pths.BF_COVERS));
    if (!(di.exists() == TRUE))
    {
        di.mkpath(QString::fromWCharArray(flm.pths.BF_COVERS));
    }
    QFile fi(QString::fromWCharArray(flm.pths.BF_MCF));
    if (!(fi.exists() == TRUE))
    {
        QFile bf(QString::fromWCharArray(flm.pths.BF_MCF));
        struct POMIDOR pom;
        wcscpy(pom.BF_VER,akt_BF_VER);
        pom.najw_ID = 1;
        bf.open(QFile::WriteOnly);
        bf.close();
        bf.open(QFile::WriteOnly);
        bf.write(reinterpret_cast<char *>(&pom),sizeof(pom));
        bf.close();
    }
    QFile fi2(QString::fromWCharArray(flm.pths.BF_PDB));
    if (!(fi2.exists() ==  TRUE))
    {
        QFile bf_pdb(QString::fromWCharArray(flm.pths.BF_PDB));
        bf_pdb.open(QFile::WriteOnly);
        bf_pdb.close();
    }
    QFile fi3(QString::fromWCharArray(flm.pths.BF_OC));
    if (!(fi3.exists() == TRUE))
    {
        QFile bf_oc(QString::fromWCharArray(flm.pths.BF_OC));
        bf_oc.open(QFile::WriteOnly);
        bf_oc.close();
    }
    QFile fi4(QString::fromWCharArray(flm.pths.BF_OB));
    if (!(fi4.exists() == TRUE))
    {
        QFile bf_ob(QString::fromWCharArray(flm.pths.BF_OB));
        bf_ob.open(QFile::WriteOnly);
        bf_ob.close();
    }
    QFile fi5(QString::fromWCharArray(flm.pths.BF_PRP));
    if (!(fi5.exists() == TRUE))
    {
        QFile bf_pr(QString::fromWCharArray(flm.pths.BF_PRP));
        bf_pr.open(QFile::WriteOnly);
        bf_pr.close();
    }
    QFile fi6(QString::fromWCharArray(flm.pths.BF_PRD));
    if (!(fi6.exists() == TRUE))
    {
        QFile bf_dr(QString::fromWCharArray(flm.pths.BF_PRD));
        bf_dr.open(QFile::WriteOnly);
        bf_dr.close();
    }
    QFile fi7(QString::fromWCharArray(flm.pths.BF_LZ));
    if (!(fi7.exists() == TRUE))
    {
        QFile bf_lz(QString::fromWCharArray(flm.pths.BF_LZ));
        bf_lz.open(QFile::WriteOnly);
        bf_lz.close();
    }
    QFile fi8(QString::fromWCharArray(flm.pths.BF_WI));
    if (!(fi8.exists() == TRUE))
    {
        QFile bf_wi(QString::fromWCharArray(flm.pths.BF_WI));
        bf_wi.open(QFile::WriteOnly);
        bf_wi.close();
    }
    QFile fi9(QString::fromWCharArray(flm.pths.BF_WO));
    if (!(fi9.exists() == TRUE))
    {
        QFile bf_wo(QString::fromWCharArray(flm.pths.BF_WO));
        bf_wo.open(QFile::WriteOnly);
        bf_wo.close();
    }

}

bool MainWindow::Del_Film_Rec(void)
{
    if (CheckbOpenDB()== 0)
    {
        if (CheckBFVER())
        {
                // kasuj rekord i kompaktuj baze danych
                flm.film_tbl.ID = 0;
                QFile plik0(QString::fromWCharArray(flm.pths.BF_PDB));
                plik0.open(QFile::WriteOnly);
                plik0.seek(zadana_pozycja_pliku);
                plik0.write(reinterpret_cast<char *>(&flm.film_tbl),sizeof(struct Film));

                plik0.rename("BF_PDB.bf0");
                plik0.close();

                QFile plik(QString::fromWCharArray(flm.pths.BF_PDB));
                plik.open(QFile::WriteOnly);
                QFile src_file("BF_PDB.bf0");
                src_file.open(QFile::ReadOnly);
                struct Film flm_src;
                unsigned int i;
                for (i = 0; i <(src_file.size()) ; )
                {
                    src_file.seek(i);
                    src_file.read(reinterpret_cast<char *>(&flm_src),sizeof(struct Film));
                    if (flm_src.ID == 0)
                    {
                        i = i + sizeof(struct Film);
                    }
                    else
                    {
                        plik.write(reinterpret_cast<char *>(&flm_src),sizeof(struct Film));
                        i = i + sizeof(struct Film);
                    }
                }
                plik.close();
                src_file.close();
                src_file.remove();


                return true;

        }
        else
        {
            return false;
        }

    }
    else
    {
        return false;
    }
}

bool MainWindow::Licz_Rec(void)
{
    //funkcja zwraca true jesli plik jest pusty co oznacza ze nie ma w nim zadnych danych = 0 rekordow.
    // ta funkcja liczy ile jest rekordow w bazie danych, wypelnia stosowne pola formularza Film oraz wypelnia
    // tablice flm.film_tbl_wsk
    QFile fi(QString::fromWCharArray(flm.pths.BF_PDB));
    if (fi.exists())
        {
            if (fi.size() == 0)
                {

                    ui->lineEdit_RecNo->setText("0");
                    ui->lineEdit_RecCount->setText("0");
                    return true;
                }
            else
                {
                    // policz rekordy w trybie niesortowanym i wypełnij Film_tab_wsk
                    QFile plik(QString::fromWCharArray(flm.pths.BF_PDB));
                    struct Film film_test;
                    plik.open(QFile::ReadOnly);
                    unsigned int stop = 0;
                    stop = plik.size();
                    unsigned int i = 0;
                    int cur_rec = 0;
                    int rec_count = 0;
                    wchar_t crec_txt[34];
                    wchar_t recc_txt[34];
                    for (i = 0; i < stop; )
                    {
                        plik.seek(i);
                        plik.read(reinterpret_cast<char *>(&film_test),sizeof(film_test));
                        rec_count = rec_count + 1;
                        if (flm.film_tbl.ID == film_test.ID)
                        {
                            cur_rec = rec_count;
                        }

                            i = i + sizeof(film_test);
                    }
                            _itow(cur_rec,crec_txt,10);
                            _itow(rec_count,recc_txt,10);
                            ui->lineEdit_RecNo->setText(QString::fromWCharArray(crec_txt));
                            ui->lineEdit_RecCount->setText(QString::fromWCharArray(recc_txt));

               }


                    return false;

        }

}
void MainWindow::Read_Settings()
{
//TODO : Napisać odczytywanie ustawień, jak nie ma utworzyc plik z domyślnymi

}

void MainWindow::SetDBFNPaths(bool cust, wchar_t* cust_path)
{
    wcscpy(flm.pths.BF_PDB,L"BF_PDB.bf");
    wcscpy(flm.pths.BF_OC,L"BF_OC.bf");
    wcscpy(flm.pths.BF_OB,L"BF_OB.bf");
    wcscpy(flm.pths.BF_PRP,L"BF_PRB.bf");
    wcscpy(flm.pths.BF_PRD,L"BF_PRD.bf");
    wcscpy(flm.pths.BF_LZ,L"BF_LZ.bf");
    wcscpy(flm.pths.BF_WI,L"BF_WI.bf");
    wcscpy(flm.pths.BF_WO,L"BF_WO.bf");
    wcscpy(flm.pths.BF_COVERS,L"covers/");
    wcscpy(flm.pths.BF_MCF,L"BF.bf");
    wcscpy(flm.pths.db_path,L"/default_db/");
    if (cust)
    {
        wcscpy(flm.pths.cur_db_path,cust_path);
        wcscat(flm.pths.cur_db_path, L"/");

        wchar_t *buff = new wchar_t[1024];

        wcscpy(buff,flm.pths.cur_db_path);
        wcscat(buff,flm.pths.BF_PDB);
        wcscpy(flm.pths.BF_PDB, buff);

        wcscpy(buff,flm.pths.cur_db_path);
        wcscat(buff,flm.pths.BF_OC);
        wcscpy(flm.pths.BF_OC, buff);

        wcscpy(buff,flm.pths.cur_db_path);
        wcscat(buff,flm.pths.BF_OB);
        wcscpy(flm.pths.BF_OB, buff);

        wcscpy(buff,flm.pths.cur_db_path);
        wcscat(buff,flm.pths.BF_LZ);
        wcscpy(flm.pths.BF_LZ,buff);

        wcscpy(buff,flm.pths.cur_db_path);
        wcscat(buff,flm.pths.BF_PRD);
        wcscpy(flm.pths.BF_PRD,buff);

        wcscpy(buff,flm.pths.cur_db_path);
        wcscat(buff,flm.pths.BF_PRP);
        wcscpy(flm.pths.BF_PRP, buff);

        wcscpy(buff,flm.pths.cur_db_path);
        wcscat(buff,flm.pths.BF_WI);
        wcscpy(flm.pths.BF_WI, buff);

        wcscpy(buff,flm.pths.cur_db_path);
        wcscat(buff,flm.pths.BF_WO);
        wcscpy(flm.pths.BF_WO,buff);

        wcscpy(buff,flm.pths.cur_db_path);
        wcscat(buff,flm.pths.BF_MCF);
        wcscpy(flm.pths.BF_MCF,buff);

        wcscpy(buff, flm.pths.cur_db_path);
        wcscat(buff, flm.pths.BF_COVERS);
        wcscpy(flm.pths.BF_COVERS, buff);

    }
    else
    {

        wchar_t buff[1024];
        wchar_t *cur_dir;
        cur_dir = getcwd(NULL,0);

        /*if (buff[_tcsclen(buff)] == '\\')
        {
            buff[_tcsclen(buff)] = '\0';
        }*/
        wcscpy(buff,cur_dir);

        wcscpy(flm.pths.cur_db_path,buff);
        wcscat(flm.pths.cur_db_path,flm.pths.db_path); // ustawianie katalogu gł bazy danych

        wcscat(buff,flm.pths.db_path); // BF_PDB
        wcscat(buff,flm.pths.BF_PDB);
        wcscpy(flm.pths.BF_PDB,buff);

        wcscpy(buff,cur_dir);

        wcscat(buff,flm.pths.db_path); //BF MCF
        wcscat(buff,flm.pths.BF_MCF);
        wcscpy(flm.pths.BF_MCF,buff);

        wcscpy(buff,cur_dir);

        wcscat(buff,flm.pths.db_path); // BF_COVERS
        wcscat(buff,flm.pths.BF_COVERS);
        wcscpy(flm.pths.BF_COVERS,buff);

        wcscpy(buff,cur_dir);

        wcscat(buff,flm.pths.db_path);
        wcscat(buff,flm.pths.BF_OC);
        wcscpy(flm.pths.BF_OC,buff);

        wcscpy(buff,cur_dir);

        wcscat(buff,flm.pths.db_path);
        wcscat(buff,flm.pths.BF_OB);
        wcscpy(flm.pths.BF_OB,buff);

        wcscpy(buff,cur_dir);

        wcscat(buff,flm.pths.db_path);
        wcscat(buff,flm.pths.BF_PRP);
        wcscpy(flm.pths.BF_PRP,buff);

        wcscpy(buff,cur_dir);

        wcscat(buff,flm.pths.db_path);
        wcscat(buff,flm.pths.BF_PRD);
        wcscpy(flm.pths.BF_PRD,buff);

        wcscpy(buff,cur_dir);

        wcscat(buff,flm.pths.db_path);
        wcscat(buff,flm.pths.BF_LZ);
        wcscpy(flm.pths.BF_LZ,buff);

        wcscpy(buff,cur_dir);

        wcscat(buff,flm.pths.db_path);
        wcscat(buff,flm.pths.BF_WI);
        wcscpy(flm.pths.BF_WI,buff);

        wcscpy(buff,cur_dir);

        wcscat(buff,flm.pths.db_path);
        wcscat(buff,flm.pths.BF_WO);
        wcscpy(flm.pths.BF_WO,buff);
    }

}

void MainWindow::Disable_BTNS_NOREC()
{
    ui->pushButton_LoadPic->setEnabled(FALSE);
    ui->pushButton_DelPic->setEnabled(FALSE);
    //ui->pushthis->TAB_DOE_BUTTON_OklT_Otw.EnableWindow(FALSE);
    //this->TAB_DOE_BUTTON_OklT_Usun.EnableWindow(FALSE);
    ui->pushButton_OC_New->setEnabled(FALSE);
    ui->pushButton_OC_Del->setEnabled(FALSE);
    ui->pushButton_OC_Save->setEnabled(FALSE);
    ui->pushButton_OB_new->setEnabled(FALSE);
    ui->pushButton_OBDel->setEnabled(FALSE);
    ui->pushButton_OBSave->setEnabled(FALSE);
    ui->pushButton_B_WYPIN_New->setEnabled(FALSE);
    ui->pushButton_BIBLIOWYPINDel->setEnabled(FALSE);
    ui->pushButton_BIBLIOWYPISave->setEnabled(FALSE);
    ui->pushButton_B_WYPODIN_New->setEnabled(FALSE);
    ui->pushButton_BIBLIOWYPODINDel->setEnabled(FALSE);
    ui->pushButton_BIBLIOWYPODINSave->setEnabled(FALSE);
    ui->pushButton_D_New->setEnabled(FALSE);
    ui->pushButton_DYSTDel->setEnabled(FALSE);
    ui->pushButton_DYSTSave->setEnabled(FALSE);
    ui->pushButto_P_New->setEnabled(FALSE);
    ui->pushButton_PRODDel->setEnabled(FALSE);
    ui->pushButton_PRODSave->setEnabled(FALSE);
    ui->pushButton_LZ_New->setEnabled(FALSE);
    ui->pushButton_LZDel->setEnabled(FALSE);
    ui->pushButton_LZSave->setEnabled(FALSE);

}

void MainWindow::Enable_BTNS_NOREC()
{
    ui->pushButton_LoadPic->setEnabled(TRUE);
    ui->pushButton_DelPic->setEnabled(TRUE);
    //ui->pushthis->TAB_DOE_BUTTON_OklT_Otw.EnableWindow(FALSE);
    //this->TAB_DOE_BUTTON_OklT_Usun.EnableWindow(FALSE);
    ui->pushButton_OC_New->setEnabled(TRUE);
    ui->pushButton_OC_Del->setEnabled(TRUE);
    ui->pushButton_OC_Save->setEnabled(TRUE);
    ui->pushButton_OB_new->setEnabled(TRUE);
    ui->pushButton_OBDel->setEnabled(TRUE);
    ui->pushButton_OBSave->setEnabled(TRUE);
    ui->pushButton_B_WYPIN_New->setEnabled(TRUE);
    ui->pushButton_BIBLIOWYPINDel->setEnabled(TRUE);
    ui->pushButton_BIBLIOWYPISave->setEnabled(TRUE);
    ui->pushButton_B_WYPODIN_New->setEnabled(TRUE);
    ui->pushButton_BIBLIOWYPODINDel->setEnabled(TRUE);
    ui->pushButton_BIBLIOWYPODINSave->setEnabled(TRUE);
    ui->pushButton_D_New->setEnabled(TRUE);
    ui->pushButton_DYSTDel->setEnabled(TRUE);
    ui->pushButton_DYSTSave->setEnabled(TRUE);
    ui->pushButto_P_New->setEnabled(TRUE);
    ui->pushButton_PRODDel->setEnabled(TRUE);
    ui->pushButton_PRODSave->setEnabled(TRUE);
    ui->pushButton_LZ_New->setEnabled(TRUE);
    ui->pushButton_LZDel->setEnabled(TRUE);
    ui->pushButton_LZSave->setEnabled(TRUE);

}
bool MainWindow::CheckOLDDB()
{
    bool test[9];
    QFile fi(QString("BF.bf"));
    if (fi.exists())
    {
        test[0] = true;
    }
    else
    {
        test[0] = false;
    }
    QFile fi2(QString("BF_PDB.bf"));
    if (fi2.exists())
    {
        test[1] = true;
    }
    else
    {
        test[1] = false;
    }
    QFile fi3(QString("BF_OC.bf"));
    if (fi3.exists())
    {
        test[2] = true;
    }
    else
    {
        test[2] = false;
    }
    QFile fi4(QString("BF_OB.bf"));
    if (fi4.exists())
    {
        test[3] = true;
    }
    else
    {
        test[3] = false;
    }
    QFile fi5(QString("BF_PRB.bf"));
    if (fi5.exists())
    {
        test[4] = true;
    }
    else
    {
        test[4] = false;
    }
    QFile fi6(QString("BF_PRD.bf"));
    if (fi6.exists())
    {
        test[5] = true;
    }
    else
    {
        test[5] = false;
    }
    QFile fi7(QString("BF_LZ.bf"));
    if (fi7.exists())
    {
        test[6] = true;
    }
    else
    {
        test[6] = false;
    }
    QFile fi8(QString("BF_WI.bf"));
    if (fi8.exists())
    {
        test[7] = true;
    }
    else
    {
        test[7] = false;
    }
    QFile fi9(QString("BF_WO.bf"));
    if (fi9.exists())
    {
        test[8] = true;
    }
    else
    {
        test[8] = false;
    }

    if ( (test[0]) && (test[1]) && (test[2]) && (test[3]) && (test[4]) && (test[5]) && (test[6]) && (test[7]) && (test[8]))
    {
        return true;
    }
    else
    {
        return false;
    }

}

void MainWindow::KopiujOLDDB()
{
    wchar_t buff_path[1024];
    wcscpy(buff_path,flm.pths.cur_db_path);
    wchar_t buff_path_suf[1024];
    wcscpy(buff_path_suf,buff_path);
    wcscat(buff_path_suf,(LPCWSTR)"BF.bf");
    //buff_path = flm.pths.cur_db_path;
    CopyFile((LPCWSTR)"BF.bf",buff_path_suf,FALSE);
    wcscpy(buff_path_suf,buff_path);
    wcscat(buff_path_suf,(LPCWSTR)"BF_PDB.bf");
    CopyFile((LPCWSTR)"BF_PDB.bf",buff_path_suf,FALSE);
    wcscpy(buff_path_suf,buff_path);
    wcscat(buff_path_suf,(LPCWSTR)"BF_OC.bf");
    CopyFile((LPCWSTR)"BF_OC.bf",buff_path_suf,FALSE);
    wcscpy(buff_path_suf, buff_path);
    wcscat(buff_path_suf,(LPCWSTR)"BF_OB.bf");
    CopyFile((LPCWSTR)"BF_OB.bf",buff_path_suf,FALSE);
    wcscpy(buff_path_suf,buff_path);
    wcscat(buff_path_suf,(LPCWSTR)"BF_PRB.bf");
    CopyFile((LPCWSTR)"BF_PRB.bf",buff_path_suf,FALSE);
    wcscpy(buff_path_suf,buff_path);
    wcscat(buff_path_suf,(LPCWSTR)"BF_PRD.bf");
    CopyFile((LPCWSTR)"BF_PRD.bf",buff_path_suf,FALSE);
    wcscpy(buff_path_suf,buff_path);
    wcscat(buff_path_suf,(LPCWSTR)"BF_WI.bf");
    CopyFile((LPCWSTR)"BF_WI.bf",buff_path_suf,FALSE);
    wcscpy(buff_path_suf,buff_path);
    wcscat(buff_path_suf,(LPCWSTR)"BF_WO.bf");
    CopyFile((LPCWSTR)"BF_WO.bf",buff_path_suf,FALSE);
    wcscpy(buff_path_suf,buff_path);
    wcscat(buff_path_suf,(LPCWSTR)"BF_LZ.bf");
    CopyFile((LPCWSTR)"BF_LZ.bf",buff_path_suf,FALSE);
    DeleteFile((LPCWSTR)"BF.bf");
    DeleteFile((LPCWSTR)"BF_PDB.bf");
    DeleteFile((LPCWSTR)"BF_OC.bf");
    DeleteFile((LPCWSTR)"BF_OB.bf");
    DeleteFile((LPCWSTR)"BF_PRB.bf");
    DeleteFile((LPCWSTR)"BF_PRD.bf");
    DeleteFile((LPCWSTR)"BF_WI.bf");
    DeleteFile((LPCWSTR)"BF_WO.bf");
    DeleteFile((LPCWSTR)"BF_LZ.bf");
}

void MainWindow::ClearBIBLIO(void)
{
    ui->tableWidget_BIBLIO_WYPIN->clearContents();
    ui->tableWidget_BIBLIO_WYPODIN->clearContents();
}

void MainWindow::Fill_Wi(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_WI));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();


    ui->tableWidget_BIBLIO_WYPIN->clearContents();
    wi_arr.clear();

    for (i = 0;i<stop ; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&wi),sizeof(wi));
        if (wi.IDPDB == flm.film_tbl.ID)
        {
            wi_arr.append(wi);

        }
        i = i + sizeof(wi);
    }
    plik.close();

    Refresh_Wi();


}

void MainWindow::Fill_Wo(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_WO));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();


    ui->tableWidget_BIBLIO_WYPODIN->clearContents();
    wo_arr.clear();



    for (i = 0;i<stop ; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&wo),sizeof(wo));
        if (wo.IDPDB == flm.film_tbl.ID)
        {
            wo_arr.append(wo);

        }
        i = i + sizeof(wo);
    }
    plik.close();

    Refresh_Wo();


}

void MainWindow::Refresh_Wi(void)
{
    ui->tableWidget_BIBLIO_WYPIN->clearContents();

    int x;
    QTableWidgetItem *item;
    for (x=0;x<wi_arr.count(); x++)
    {
        ui->tableWidget_BIBLIO_WYPIN->insertRow(x);

        item->setText(QString::fromWCharArray(wi_arr[x].osoba));
        ui->tableWidget_BIBLIO_WYPIN->setItem(x,0,item);

        item->setText(QString::fromWCharArray(wi_arr[x].data_wypozyczenia));
        ui->tableWidget_BIBLIO_WYPIN->setItem(x,1,item);

        item->setText(QString::fromWCharArray(wi_arr[x].data_oddania));
        ui->tableWidget_BIBLIO_WYPIN->setItem(x,2,item);

        item->setText(QString::fromWCharArray(wi_arr[x].stan_przed_wypozycz));
        ui->tableWidget_BIBLIO_WYPIN->setItem(x,3,item);

        item->setText(QString::fromWCharArray(wi_arr[x].stan_po_oddaniu));
        ui->tableWidget_BIBLIO_WYPIN->setItem(x,4,item);

        item->setText(QString::number(wi_arr[x].ID,10));
        ui->tableWidget_BIBLIO_WYPIN->setItem(x,5,item);

        item->setText(QString::number(wi_arr[x].IDPDB,10));
        ui->tableWidget_BIBLIO_WYPIN->setItem(x,6,item);

    }


}

void MainWindow::Refresh_Wo(void)
{
    ui->tableWidget_BIBLIO_WYPODIN->clearContents();

    int x;
    QTableWidgetItem *item;
    for (x=0;x<wo_arr.count(); x++)
    {
        ui->tableWidget_BIBLIO_WYPODIN->insertRow(x);

        item->setText(QString::fromWCharArray(wo_arr[x].osoba));
        ui->tableWidget_BIBLIO_WYPODIN->setItem(x,0,item);

        item->setText(QString::fromWCharArray(wo_arr[x].data_wypozyczenia));
        ui->tableWidget_BIBLIO_WYPODIN->setItem(x,1,item);

        item->setText(QString::fromWCharArray(wo_arr[x].data_oddania));
        ui->tableWidget_BIBLIO_WYPODIN->setItem(x,2,item);

        item->setText(QString::fromWCharArray(wo_arr[x].stan_przed_wypozycz));
        ui->tableWidget_BIBLIO_WYPODIN->setItem(x,3,item);

        item->setText(QString::fromWCharArray(wo_arr[x].stan_po_oddaniu));
        ui->tableWidget_BIBLIO_WYPODIN->setItem(x,4,item);

        item->setText(QString::number(wo_arr[x].ID,10));
        ui->tableWidget_BIBLIO_WYPODIN->setItem(x,5,item);

        item->setText(QString::number(wo_arr[x].IDPDB,10));
        ui->tableWidget_BIBLIO_WYPODIN->setItem(x,6,item);

    }

}

void MainWindow::Save_Wi(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_WI));
    struct Wypozycz_Innym wi_buf;
    plik.open(QFile::ReadWrite);

    unsigned int stop;
    unsigned int i;
    int y;

    wchar_t buff[34];
    stop = plik.size();

    for (y=0;y<wi_arr.count() ;y++ )
    {
        if (GetRecC_WI() == 0)
            {
                plik.seek(0);
                plik.write(reinterpret_cast<char *> (&wi_arr[y]),sizeof(wi));

            }
        else if (GetRecC_WI() > 0)
            {
                if ((plik.size()) > 2147483647)
                {
                    QMessageBox(QMessageBox::Warning,QString::fromWCharArray((LPCWSTR)"Biblioteka Filmów"),QString::fromWCharArray((LPCWSTR)"Nie można więcej zapisywać do tego pliku - jest przepełniony !!! "),QMessageBox::Ok);
                    break;
                }
                else if ((plik.size()) < 2147483647)
                {
                    for (i=0; i<stop; )
                    {
                        plik.seek(i);
                        plik.read(reinterpret_cast<char *>(&wi_buf),sizeof(wi_buf));
                            if (wi_arr[y].ID == wi_buf.ID)
                            {
                                plik.seek(i);
                                plik.write(reinterpret_cast<char *>(&wi_arr[y]),sizeof(wi));
                            }

                        i = i + sizeof(wi);
                    }
                    if (add_new_wi)
                    {

                        int x;
                        x = (wi_arr.count()-1);
                        plik.seek(plik.size());
                        plik.write(reinterpret_cast<char *>(&wi_arr[x]),sizeof(wi));
                        add_new_wi = false;
                    }
                }
            }

    }

    plik.close();


}

void MainWindow::Save_Wo(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_WO));
    struct Wypozycz_Od_Innych wo_buf;
    plik.open(QFile::ReadWrite);

    unsigned int stop;
    unsigned int i;
    int y;

    wchar_t buff[34];
    stop = plik.size();

    for (y=0;y<wo_arr.count() ;y++ )
    {
        if (GetRecC_WO() == 0)
            {
                plik.seek(0);
                plik.write(reinterpret_cast<char *>(&wo_arr[y]),sizeof(wo));

            }
        else if (GetRecC_WO() > 0)
            {
                if ((plik.size()) > 2147483647)
                {
                    QMessageBox(QMessageBox::Warning,QString::fromWCharArray((LPCWSTR)"Biblioteka Filmów"),QString::fromWCharArray((LPCWSTR)"Nie można więcej zapisywać do tego pliku - jest przepełniony !!! "),QMessageBox::Ok);
                    break;
                }
                else if ((plik.size()) < 2147483647)
                {
                    for (i=0; i<stop; )
                    {
                        plik.seek(i);
                        plik.read(reinterpret_cast<char *>(&wo_buf),sizeof(wo_buf));
                            if (wo_arr[y].ID == wo_buf.ID)
                            {
                                plik.seek(i);
                                plik.write(reinterpret_cast<char *>(&wo_arr[y]),sizeof(wo));
                            }

                        i = i + sizeof(wo);
                    }
                    if (add_new_wo)
                    {

                        int x;
                        x = (wo_arr.count()-1);
                        plik.seek(plik.size());
                        plik.write(reinterpret_cast<char *>(&wo_arr[x]),sizeof(wo));
                        add_new_wo = false;
                    }
                }
            }

    }

    plik.close();
}

int MainWindow::GetRecC_WI(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_WI));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    int rec_count = 0;
    struct Wypozycz_Innym wi_t;
    if (stop == 0)
    {
        plik.close();
        return 0;
    }
    for (i = 0; i <stop; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&wi_t),sizeof(wi_t));
        rec_count = rec_count + 1;
        i = i + sizeof(wi_t);
    }
    plik.close();
    return rec_count;

}

int MainWindow::GetRecC_WO(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_WO));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    int rec_count = 0;
    struct Wypozycz_Od_Innych wo_t;
    if (stop == 0)
    {
        plik.close();
        return 0;
    }
    for (i = 0; i <stop; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&wo_t),sizeof(wo_t));
        rec_count = rec_count + 1;
        i = i + sizeof(wo_t);
    }
    plik.close();
    return rec_count;


}

int MainWindow::Get_Hi_ID_WI(void)
{
    if (GetRecC_WI() == 0)
    {
        return 0;
    }


    QFile plik(QString::fromWCharArray(flm.pths.BF_WI));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        if (i == (stop - sizeof(wi)))
        {
            plik.read(reinterpret_cast<char *>(&wi),sizeof(wi));
            plik.close();
            return wi.ID;
        }
        i = i + sizeof(wi);
    }

}

int MainWindow::Get_Hi_ID_WO(void)
{
    if (GetRecC_WO() == 0)
    {
        return 0;
    }


    QFile plik(QString::fromWCharArray(flm.pths.BF_WO));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        if (i == (stop - sizeof(wo)))
        {
            plik.read(reinterpret_cast<char *>(&wo),sizeof(wo));
            plik.close();
            return wo.ID;
        }
        i = i + sizeof(wo);
    }

}

void MainWindow::Add_New_WI(int id)
{
    int id_new;
    id_new = id + 1;

    // Metoda callbacku
    wi.ID = id_new;
    wi.IDPDB = flm.film_tbl.ID;
    wcscpy(wi.data_wypozyczenia,L"Wpisz tutaj coś");
    wcscpy(wi.stan_przed_wypozycz,L"Wpisz tutaj coś");
    wcscpy(wi.data_oddania,L"Wpisz tutaj coś");
    wcscpy(wi.stan_po_oddaniu,L"Wpisz tutaj coś");
    wcscpy(wi.osoba,L"Wpisz tutaj coś");
    wcscpy(wi.Nr_kat,L"Wpisz tutaj coś");

    wi_arr.append(wi);

    Refresh_Wi();

}

void MainWindow::Add_New_WO(int id)
{
    int id_new;
    id_new = id + 1;

    // Metoda callbacku
    wo.ID = id_new;
    wo.IDPDB = flm.film_tbl.ID;
    wcscpy(wo.data_wypozyczenia,L"Wpisz tutaj coś");
    wcscpy(wo.stan_przed_wypozycz,L"Wpisz tutaj coś");
    wcscpy(wo.data_oddania,L"Wpisz tutaj coś");
    wcscpy(wo.stan_po_oddaniu,L"Wpisz tutaj coś");
    wcscpy(wo.osoba,L"Wpisz tutaj coś");
    wcscpy(wo.Nr_kat,L"Wpisz tutaj coś");

    wo_arr.append(wo);

    Refresh_Wo();

}

void MainWindow::Usun_Rec_WI(unsigned int pos)
{
        struct Wypozycz_Innym wi_src;
        wi.ID = 0;
        QFile plik0(QString::fromWCharArray(flm.pths.BF_WI));
        plik0.open(QFile::ReadOnly);
        plik0.seek(pos);
        plik0.write(reinterpret_cast<char *>(&wi),sizeof(wi));

        plik0.rename(QString::fromWCharArray(flm.pths.BF_WI),QString::fromWCharArray((LPCTSTR)"BF_WI.bf0"));

        plik0.close();
        QFile plik(QString::fromWCharArray(flm.pths.BF_WI));
        plik.open(QFile::WriteOnly);
        QFile src_file(QString::fromWCharArray((LPCTSTR)"BF_WI.bf0"));
        src_file.open(QFile::ReadOnly);
        unsigned int i;
        for (i = 0; i <(src_file.size()) ; )
        {
            src_file.seek(i);
            src_file.read(reinterpret_cast<char *>(&wi_src),sizeof(wi_src));
            if (wi_src.ID == 0)
            {
                i = i + sizeof(wi_src);
            }
            else
            {
                plik.write(reinterpret_cast<char *>(&wi_src),sizeof(wi_src));
                i = i + sizeof(wi_src);
            }
        }
        plik.close();
        src_file.remove();
        src_file.close();
        Fill_Wi();


}

void MainWindow::Usun_Rec_WO(unsigned int pos)
{

        struct Wypozycz_Od_Innych wo_src;
        wo.ID = 0;
        QFile plik0(QString::fromWCharArray(flm.pths.BF_WO));
        plik0.open(QFile::WriteOnly);
        plik0.seek(pos);
        plik0.write(reinterpret_cast<char *>(&wo),sizeof(wo));

        plik0.rename(QString::fromWCharArray(flm.pths.BF_WO),QString::fromWCharArray((LPCTSTR)"BF_WO.bf0"));
        plik0.close();

        QFile plik(QString::fromWCharArray(flm.pths.BF_WO));
        plik.open(QFile::WriteOnly);
        QFile src_file(QString::fromWCharArray((LPCTSTR)"BF_WO.bf0"));
        src_file.open(QFile::ReadOnly);
        unsigned int i;
        for (i = 0; i <(src_file.size()) ; )
        {
            src_file.seek(i);
            src_file.read(reinterpret_cast<char *>(&wo_src),sizeof(wo_src));
            if (wo_src.ID == 0)
            {
                i = i + sizeof(wo_src);
            }
            else
            {
                plik.write(reinterpret_cast<char *>(&wo_src),sizeof(wo_src));
                i = i + sizeof(wo_src);
            }
        }
        plik.close();
        src_file.remove();
        src_file.close();
        Fill_Wo();


}

void MainWindow::ClearIOF(void)
{
    ui->tableWidget_IOF_LZ->clearContents();

}

void MainWindow::Fill_Lz(void)
{

    QFile plik(QString::fromWCharArray(flm.pths.BF_LZ));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();


    ui->tableWidget_IOF_LZ->clearContents();
    lz_arr.clear();

    for (i = 0;i<stop ; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&lz),sizeof(lz));
        if (lz.IDPDB == flm.film_tbl.ID)
        {
            lz_arr.append(lz);

        }
        i = i + sizeof(lz);
    }
    plik.close();

    Refresh_Lz();

}

void MainWindow::Save_Lz(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_LZ));
    struct Lok_zdjeciowe lz_buf;
    plik.open(QFile::ReadWrite);

    unsigned int stop;
    unsigned int i;
    int y;

    wchar_t buff[34];
    stop = plik.size();

    for (y=0;y<lz_arr.count() ;y++ )
    {
        if (GetRecC_WI() == 0)
            {
                plik.seek(0);
                plik.write(reinterpret_cast<char *> (&lz_arr[y]),sizeof(lz));

            }
        else if (GetRecC_WI() > 0)
            {
                if ((plik.size()) > 2147483647)
                {
                    QMessageBox(QMessageBox::Warning,QString::fromWCharArray((LPCWSTR)"Biblioteka Filmów"),QString::fromWCharArray((LPCWSTR)"Nie można więcej zapisywać do tego pliku - jest przepełniony !!! "),QMessageBox::Ok);
                    break;
                }
                else if ((plik.size()) < 2147483647)
                {
                    for (i=0; i<stop; )
                    {
                        plik.seek(i);
                        plik.read(reinterpret_cast<char *>(&lz_buf),sizeof(lz_buf));
                            if (lz_arr[y].ID == lz_buf.ID)
                            {
                                plik.seek(i);
                                plik.write(reinterpret_cast<char *>(&lz_arr[y]),sizeof(lz));
                            }

                        i = i + sizeof(lz);
                    }
                    if (add_new_lz)
                    {

                        int x;
                        x = (lz_arr.count()-1);
                        plik.seek(plik.size());
                        plik.write(reinterpret_cast<char *>(&lz_arr[x]),sizeof(lz));
                        add_new_lz = false;
                    }
                }
            }

    }

    plik.close();


}

int MainWindow::GetRecC_LZ(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_LZ));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    int rec_count = 0;
    struct Lok_zdjeciowe lz_t;
    if (stop == 0)
    {
        plik.close();
        return 0;
    }
    for (i = 0; i <stop; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&lz_t),sizeof(lz_t));
        rec_count = rec_count + 1;
        i = i + sizeof(lz_t);
    }
    plik.close();
    return rec_count;

}

int MainWindow::Get_Hi_ID_LZ(void)
{
    if (GetRecC_LZ() == 0)
    {
        return 0;
    }


    QFile plik(QString::fromWCharArray(flm.pths.BF_LZ));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        if (i == (stop - sizeof(lz)))
        {
            plik.read(reinterpret_cast<char *>(&lz),sizeof(lz));
            plik.close();
            return lz.ID;
        }
        i = i + sizeof(lz);
    }

}

void MainWindow::Add_New_LZ(int id)
{

    int id_new;
    id_new = id + 1;

// Metoda callbacku
    lz.ID = id_new;
    lz.IDPDB = flm.film_tbl.ID;
    wcscpy(lz.nazwa_obiektu,L"Wpisz tutaj coś");
    wcscpy(lz.kraj,L"Wpisz tutaj coś");
    wcscpy(lz.miejscowosc,L"Wpisz tutaj coś");
    wcscpy(lz.region,L"Wpisz tutaj coś");
    wcscpy(lz.pora_roku,L"Wpisz tutaj coś");
    wcscpy(lz.data,L"Wpisz tutaj coś");

    lz_arr.append(lz);

    Refresh_Lz();

}

void MainWindow::Usun_Rec_LZ(unsigned int pos)
{
    struct Lok_zdjeciowe lz_src;
    lz.ID = 0;
    QFile plik0(QString::fromWCharArray(flm.pths.BF_LZ));
    plik0.open(QFile::ReadOnly);
    plik0.seek(pos);
    plik0.write(reinterpret_cast<char *>(&lz),sizeof(lz));

    plik0.rename(QString::fromWCharArray(flm.pths.BF_LZ),QString::fromWCharArray((LPCTSTR)"BF_LZ.bf0"));

    plik0.close();
    QFile plik(QString::fromWCharArray(flm.pths.BF_LZ));
    plik.open(QFile::WriteOnly);
    QFile src_file(QString::fromWCharArray((LPCTSTR)"BF_LZ.bf0"));
    src_file.open(QFile::ReadOnly);
    unsigned int i;
    for (i = 0; i <(src_file.size()) ; )
    {
        src_file.seek(i);
        src_file.read(reinterpret_cast<char *>(&lz_src),sizeof(lz_src));
        if (lz_src.ID == 0)
        {
            i = i + sizeof(lz_src);
        }
        else
        {
            plik.write(reinterpret_cast<char *>(&lz_src),sizeof(lz_src));
            i = i + sizeof(lz_src);
        }
    }
    plik.close();
    src_file.remove();
    src_file.close();
    Fill_Lz();

}

void MainWindow::ClearObsada(void)
{

    ui->tableWidget_Obsada->clearContents();

}

void MainWindow::Fill_Ob(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_OB));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();


    ui->tableWidget_Obsada->clearContents();
    ob_arr.clear();

    for (i = 0;i<stop ; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&ob),sizeof(ob));
        if (ob.IDPDB == flm.film_tbl.ID)
        {
            ob_arr.append(ob);

        }
        i = i + sizeof(ob);
    }
    plik.close();

    Refresh_Ob();

}

void MainWindow::Save_Ob(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_OB));
    struct Obsada ob_buf;
    plik.open(QFile::ReadWrite);

    unsigned int stop;
    unsigned int i;
    int y;

    wchar_t buff[34];
    stop = plik.size();

    for (y=0;y<ob_arr.count() ;y++ )
    {
        if (GetRecC_OB() == 0)
            {
                plik.seek(0);
                plik.write(reinterpret_cast<char *> (&ob_arr[y]),sizeof(ob));

            }
        else if (GetRecC_OB() > 0)
            {
                if ((plik.size()) > 2147483647)
                {
                    QMessageBox(QMessageBox::Warning,QString::fromWCharArray((LPCWSTR)"Biblioteka Filmów"),QString::fromWCharArray((LPCWSTR)"Nie można więcej zapisywać do tego pliku - jest przepełniony !!! "),QMessageBox::Ok);
                    break;
                }
                else if ((plik.size()) < 2147483647)
                {
                    for (i=0; i<stop; )
                    {
                        plik.seek(i);
                        plik.read(reinterpret_cast<char *>(&ob_buf),sizeof(ob_buf));
                            if (ob_arr[y].ID == ob_buf.ID)
                            {
                                plik.seek(i);
                                plik.write(reinterpret_cast<char *>(&ob_arr[y]),sizeof(ob));
                            }

                        i = i + sizeof(ob);
                    }
                    if (add_new_ob)
                    {

                        int x;
                        x = (ob_arr.count()-1);
                        plik.seek(plik.size());
                        plik.write(reinterpret_cast<char *>(&ob_arr[x]),sizeof(ob));
                        add_new_ob = false;
                    }
                }
            }

    }

    plik.close();



}

void MainWindow::Add_New_Ob(int id)
{

    int id_new;
    id_new = id + 1;
    int itemcount = 0;
    wchar_t buff[34];


    // Metoda callbacku
    ob.ID = id_new;
    ob.IDPDB = flm.film_tbl.ID;
    wcscpy(ob.imie_nazw,L"Wpisz tutaj coś");
    wcscpy(ob.rola,L"Wpisz tutaj coś");

    ob_arr.append(ob);

    Refresh_Ob();


}

int MainWindow::Get_Hi_ID_OB(void)
{
    if (GetRecC_OB() == 0)
    {
        return 0;
    }


    QFile plik(QString::fromWCharArray(flm.pths.BF_OB));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        if (i == (stop - sizeof(ob)))
        {
            plik.read(reinterpret_cast<char *>(&ob),sizeof(ob));
            plik.close();
            return ob.ID;
        }
        i = i + sizeof(ob);
    }

}

int MainWindow::GetRecC_OB(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_OB));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    int rec_count = 0;
    struct Obsada ob_t;
    if (stop == 0)
    {
        plik.close();
        return 0;
    }
    for (i = 0; i <stop; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&ob_t),sizeof(ob_t));
        rec_count = rec_count + 1;
        i = i + sizeof(ob_t);
    }
    plik.close();
    return rec_count;

}

void MainWindow::Refresh_Ob(void)
{

    ui->tableWidget_Obsada->clearContents();

    int x;
    QTableWidgetItem *item;
    for (x=0;x<ob_arr.count(); x++)
    {
        ui->tableWidget_Obsada->insertRow(x);

        item->setText(QString::fromWCharArray(ob_arr[x].imie_nazw));
        ui->tableWidget_Obsada->setItem(x,0,item);

        item->setText(QString::fromWCharArray(ob_arr[x].rola));
        ui->tableWidget_Obsada->setItem(x,1,item);

        item->setText(QString::number(ob_arr[x].ID,10));
        ui->tableWidget_Obsada->setItem(x,2,item);

        item->setText(QString::number(ob_arr[x].IDPDB,10));
        ui->tableWidget_Obsada->setItem(x,2,item);

    }

}

void MainWindow::Usun_Rec_OB(unsigned int pos)
{
    struct Obsada ob_src;
    ob.ID = 0;
    QFile plik0(QString::fromWCharArray(flm.pths.BF_OB));
    plik0.open(QFile::ReadOnly);
    plik0.seek(pos);
    plik0.write(reinterpret_cast<char *>(&ob),sizeof(ob));

    plik0.rename(QString::fromWCharArray(flm.pths.BF_OB),QString::fromWCharArray((LPCTSTR)"BF_OB.bf0"));

    plik0.close();
    QFile plik(QString::fromWCharArray(flm.pths.BF_OB));
    plik.open(QFile::WriteOnly);
    QFile src_file(QString::fromWCharArray((LPCTSTR)"BF_OB.bf0"));
    src_file.open(QFile::ReadOnly);
    unsigned int i;
    for (i = 0; i <(src_file.size()) ; )
    {
        src_file.seek(i);
        src_file.read(reinterpret_cast<char *>(&ob_src),sizeof(ob_src));
        if (ob_src.ID == 0)
        {
            i = i + sizeof(ob_src);
        }
        else
        {
            plik.write(reinterpret_cast<char *>(&ob_src),sizeof(ob_src));
            i = i + sizeof(ob_src);
        }
    }
    plik.close();
    src_file.remove();
    src_file.close();
    Fill_Ob();

}

void MainWindow::Save_Oc(void)
{
    // ta i podobne procedury zapisuja do danego pliku tabele struktur zawierajacych dane z pól list w form. film.
// w przypadku nadpisywania danych wyszukuja najpierw czy rekord o danym id istnieje w pliku, potem jesli tak nad-
// -pisuja go, a jesli nie dodaja na koncu, i tak dla kazdej komorki tabeli struktur.

    QFile plik(QString::fromWCharArray(flm.pths.BF_OC));
    struct Ocena oc_buf;
    plik.open(QFile::ReadWrite);

    unsigned int stop;
    unsigned int i;
    int y;

    wchar_t buff[34];
    stop = plik.size();

    for (y=0;y<oc_arr.count() ;y++ )
    {
        if (GetRecC_OC() == 0)
            {
                plik.seek(0);
                plik.write(reinterpret_cast<char *> (&oc_arr[y]),sizeof(oc));

            }
        else if (GetRecC_OC() > 0)
            {
                if ((plik.size()) > 2147483647)
                {
                    QMessageBox(QMessageBox::Warning,QString::fromWCharArray((LPCWSTR)"Biblioteka Filmów"),QString::fromWCharArray((LPCWSTR)"Nie można więcej zapisywać do tego pliku - jest przepełniony !!! "),QMessageBox::Ok);
                    break;
                }
                else if ((plik.size()) < 2147483647)
                {
                    for (i=0; i<stop; )
                    {
                        plik.seek(i);
                        plik.read(reinterpret_cast<char *>(&oc_buf),sizeof(oc_buf));
                            if (oc_arr[y].ID == oc_buf.ID)
                            {
                                plik.seek(i);
                                plik.write(reinterpret_cast<char *>(&oc_arr[y]),sizeof(oc));
                            }

                        i = i + sizeof(ob);
                    }
                    if (add_new_oc)
                    {

                        int x;
                        x = (oc_arr.count()-1);
                        plik.seek(plik.size());
                        plik.write(reinterpret_cast<char *>(&oc_arr[x]),sizeof(oc));
                        add_new_oc = false;
                    }
                }
            }

    }

    plik.close();



}

void MainWindow::Fill_Oc()
{
// ta i podobne procedury odczytuja plik bd danej tabeli i sprawdzaja czy idpdb sie zgadza z polem if flm_o.film_tbl
// a jesli tak to pobieraja z pliku do tabeli struktur zawierajacej dane z jednego pola listy form. film dla jednego
// rekordu, jesli nie ida dalej wzdluz pliku do jego konca..

    QFile plik(QString::fromWCharArray(flm.pths.BF_OC));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();


    ui->tableWidget_OC->clearContents();
    oc_arr.clear();

    for (i = 0;i<stop ; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&oc),sizeof(oc));
        if (oc.IDPDB == flm.film_tbl.ID)
        {
            oc_arr.append(oc);

        }
        i = i + sizeof(oc);
    }
    plik.close();

    Refresh_Oc();
}

void MainWindow::ClearOcena(void)
{
        ui->tableWidget_OC->clearContents();

}

int MainWindow::Get_Hi_ID_OC(void)
{

if (GetRecC_OC() == 0)
{
    return 0;
}

QFile plik(QString::fromWCharArray(flm.pths.BF_OC));
plik.open(QFile::ReadOnly);
unsigned int i;
unsigned int stop;
stop = plik.size();
for (i=0;i<stop; )
{
    plik.seek(i);
    if (i == (stop - sizeof(oc)))
    {
        plik.read(reinterpret_cast<char *>(&oc),sizeof(oc));
        plik.close();
        return oc.ID;
    }
    i = i + sizeof(oc);
}

}

void MainWindow::Add_New_Oc(int id)
{

    int id_new;
    id_new = id + 1;
    int itemcount = 0;
    wchar_t buff[34];


// Metoda callbacku
    oc.ID = id_new;
    oc.IDPDB = flm.film_tbl.ID;
    wcscpy(oc.nazwa,L"Wpisz tutaj coś");
    wcscpy(oc.tytul_tekstu,L"Wpisz tutaj coś");
    wcscpy(oc.autor_tekstu,L"Wpisz tutaj coś");
    wcscpy(oc.ocena_krytyka,L"Wpisz tutaj coś");
    wcscpy(oc.strona_www,L"Wpisz tutaj coś");


    oc_arr.append(oc);

    Refresh_Oc();


}

int MainWindow::GetRecC_OC(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_OC));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    int rec_count = 0;
    struct Ocena oc_t;
    if (stop == 0)
    {
        plik.close();
        return 0;
    }
    for (i = 0; i <stop; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&oc_t),sizeof(oc_t));
        rec_count = rec_count + 1;
        i = i + sizeof(oc_t);
    }
    plik.close();
    return rec_count;



}

void MainWindow::Usun_Rec_OC(unsigned int pos)
{


    struct Ocena oc_src;
    oc.ID = 0;
    QFile plik0(QString::fromWCharArray(flm.pths.BF_OC));
    plik0.open(QFile::ReadOnly);
    plik0.seek(pos);
    plik0.write(reinterpret_cast<char *>(&oc),sizeof(oc));

    plik0.rename(QString::fromWCharArray(flm.pths.BF_OC),QString::fromWCharArray((LPCTSTR)"BF_OC.bf0"));

    plik0.close();
    QFile plik(QString::fromWCharArray(flm.pths.BF_OC));
    plik.open(QFile::WriteOnly);
    QFile src_file(QString::fromWCharArray((LPCTSTR)"BF_OC.bf0"));
    src_file.open(QFile::ReadOnly);
    unsigned int i;
    for (i = 0; i <(src_file.size()) ; )
    {
        src_file.seek(i);
        src_file.read(reinterpret_cast<char *>(&oc_src),sizeof(oc_src));
        if (oc_src.ID == 0)
        {
            i = i + sizeof(oc_src);
        }
        else
        {
            plik.write(reinterpret_cast<char *>(&oc_src),sizeof(oc_src));
            i = i + sizeof(oc_src);
        }
    }
    plik.close();
    src_file.remove();
    src_file.close();
    Fill_Oc();


}



void MainWindow::Refresh_Oc(void)
{

    ui->tableWidget_OC->clearContents();

    int x;
    QTableWidgetItem *item;
    for (x=0;x<oc_arr.count(); x++)
    {
        ui->tableWidget_IOF_LZ->insertRow(x);

        item->setText(QString::fromWCharArray(oc_arr[x].nazwa));
        ui->tableWidget_OC->setItem(x,0,item);

        item->setText(QString::fromWCharArray(oc_arr[x].tytul_tekstu));
        ui->tableWidget_OC->setItem(x,1,item);

        item->setText(QString::fromWCharArray(oc_arr[x].autor_tekstu));
        ui->tableWidget_OC->setItem(x,2,item);

        item->setText(QString::fromWCharArray(oc_arr[x].strona_www));
        ui->tableWidget_OC->setItem(x,3,item);

        item->setText(QString::fromWCharArray(oc_arr[x].ocena_krytyka));
        ui->tableWidget_OC->setItem(x,4,item);

        item->setText(QString::number(oc_arr[x].ID,10));
        ui->tableWidget_OC->setItem(x,5,item);

        item->setText(QString::number(oc_arr[x].IDPDB,10));
        ui->tableWidget_OC->setItem(x,6,item);

    }
}

void MainWindow::ClearProd(void)
{
    ui->tableWidget_Prod->clearContents();

}

void MainWindow::ClearDystr(void)
{
    ui->tableWidget_Dystr->clearContents();

}

void MainWindow::Fill_PP(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_PRP));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();


    ui->tableWidget_Prod->clearContents();
    pp_arr.clear();

    for (i = 0;i<stop ; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&pp),sizeof(pp));
        if (pp.IDPDB == flm.film_tbl.ID)
        {
            pp_arr.append(pp);

        }
        i = i + sizeof(pp);
    }
    plik.close();

    Refresh_PP();

}

void MainWindow::Fill_PD(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_PRD));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();


    ui->tableWidget_Dystr->clearContents();
    pd_arr.clear();

    for (i = 0;i<stop ; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&pd),sizeof(pd));
        if (pd.IDPDB == flm.film_tbl.ID)
        {
            pd_arr.append(pd);

        }
        i = i + sizeof(pd);
    }
    plik.close();

    Refresh_PD();

}



void MainWindow::Refresh_PP(void)
{
    ui->tableWidget_Prod->clearContents();

    int x;
    QTableWidgetItem *item;
    for (x=0;x<pp_arr.count(); x++)
    {
        ui->tableWidget_Prod->insertRow(x);

        item->setText(QString::fromWCharArray(pp_arr[x].nazwa_firmy));
        ui->tableWidget_Prod->setItem(x,0,item);

        item->setText(QString::fromWCharArray(pp_arr[x].adres));
        ui->tableWidget_Prod->setItem(x,1,item);

        item->setText(QString::fromWCharArray(pp_arr[x].telefon));
        ui->tableWidget_Prod->setItem(x,2,item);

        item->setText(QString::fromWCharArray(pp_arr[x].fax));
        ui->tableWidget_Prod->setItem(x,3,item);

        item->setText(QString::fromWCharArray(pp_arr[x].email));
        ui->tableWidget_Prod->setItem(x,4,item);

        item->setText(QString::fromWCharArray(pp_arr[x].strona_www));
        ui->tableWidget_Prod->setItem(x,5,item);

        item->setText(QString::number(pp_arr[x].ID,10));
        ui->tableWidget_Prod->setItem(x,6,item);

        item->setText(QString::number(pp_arr[x].IDPDB,10));
        ui->tableWidget_Prod->setItem(x,7,item);

    }

}

void MainWindow::Refresh_PD(void)
{
    ui->tableWidget_Dystr->clearContents();

    int x;
    QTableWidgetItem *item;
    for (x=0;x<pd_arr.count(); x++)
    {
        ui->tableWidget_Dystr->insertRow(x);

        item->setText(QString::fromWCharArray(pd_arr[x].nazwa_firmy));
        ui->tableWidget_Dystr->setItem(x,0,item);

        item->setText(QString::fromWCharArray(pd_arr[x].adres));
        ui->tableWidget_Dystr->setItem(x,1,item);

        item->setText(QString::fromWCharArray(pd_arr[x].telefon));
        ui->tableWidget_Dystr->setItem(x,2,item);

        item->setText(QString::fromWCharArray(pd_arr[x].fax));
        ui->tableWidget_Dystr->setItem(x,3,item);

        item->setText(QString::fromWCharArray(pd_arr[x].email));
        ui->tableWidget_Dystr->setItem(x,4,item);

        item->setText(QString::fromWCharArray(pd_arr[x].strona_www));
        ui->tableWidget_Dystr->setItem(x,5,item);

        item->setText(QString::number(pd_arr[x].ID,10));
        ui->tableWidget_Dystr->setItem(x,6,item);

        item->setText(QString::number(pd_arr[x].IDPDB,10));
        ui->tableWidget_Dystr->setItem(x,7,item);

    }

}

void MainWindow::Save_PP(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_PRP));
    struct Producent pp_buf;
    plik.open(QFile::ReadWrite);

    unsigned int stop;
    unsigned int i;
    int y;

    wchar_t buff[34];
    stop = plik.size();

    for (y=0;y<pp_arr.count() ;y++ )
    {
        if (GetRecC_PP() == 0)
            {
                plik.seek(0);
                plik.write(reinterpret_cast<char *> (&pp_arr[y]),sizeof(pp));

            }
        else if (GetRecC_PP() > 0)
            {
                if ((plik.size()) > 2147483647)
                {
                    QMessageBox(QMessageBox::Warning,QString::fromWCharArray((LPCWSTR)"Biblioteka Filmów"),QString::fromWCharArray((LPCWSTR)"Nie można więcej zapisywać do tego pliku - jest przepełniony !!! "),QMessageBox::Ok);
                    break;
                }
                else if ((plik.size()) < 2147483647)
                {
                    for (i=0; i<stop; )
                    {
                        plik.seek(i);
                        plik.read(reinterpret_cast<char *>(&pp_buf),sizeof(pp_buf));
                            if (pp_arr[y].ID == pp_buf.ID)
                            {
                                plik.seek(i);
                                plik.write(reinterpret_cast<char *>(&pp_arr[y]),sizeof(pp));
                            }

                        i = i + sizeof(pp);
                    }
                    if (add_new_pp)
                    {

                        int x;
                        x = (pp_arr.count()-1);
                        plik.seek(plik.size());
                        plik.write(reinterpret_cast<char *>(&pp_arr[x]),sizeof(pp));
                        add_new_pp = false;
                    }
                }
            }

    }

    plik.close();



}

void MainWindow::Save_PD(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_PRD));
    struct Producent pd_buf;
    plik.open(QFile::ReadWrite);

    unsigned int stop;
    unsigned int i;
    int y;

    wchar_t buff[34];
    stop = plik.size();

    for (y=0;y<pp_arr.count() ;y++ )
    {
        if (GetRecC_PD() == 0)
            {
                plik.seek(0);
                plik.write(reinterpret_cast<char *> (&pd_arr[y]),sizeof(pd));

            }
        else if (GetRecC_PD() > 0)
            {
                if ((plik.size()) > 2147483647)
                {
                    QMessageBox(QMessageBox::Warning,QString::fromWCharArray((LPCWSTR)"Biblioteka Filmów"),QString::fromWCharArray((LPCWSTR)"Nie można więcej zapisywać do tego pliku - jest przepełniony !!! "),QMessageBox::Ok);
                    break;
                }
                else if ((plik.size()) < 2147483647)
                {
                    for (i=0; i<stop; )
                    {
                        plik.seek(i);
                        plik.read(reinterpret_cast<char *>(&pd_buf),sizeof(pd_buf));
                            if (pd_arr[y].ID == pd_buf.ID)
                            {
                                plik.seek(i);
                                plik.write(reinterpret_cast<char *>(&pd_arr[y]),sizeof(pd));
                            }

                        i = i + sizeof(pd);
                    }
                    if (add_new_pd)
                    {

                        int x;
                        x = (pd_arr.count()-1);
                        plik.seek(plik.size());
                        plik.write(reinterpret_cast<char *>(&pd_arr[x]),sizeof(pd));
                        add_new_pd = false;
                    }
                }
            }

    }

    plik.close();


}

void MainWindow::Add_New_PP(int id)
{
    int id_new;
    id_new = id + 1;
    wchar_t buff[34];


    // Metoda callbacku
    pp.ID = id_new;
    pp.IDPDB = flm.film_tbl.ID;
    wcscpy(pp.nazwa_firmy,L"Wpisz tutaj coś");
    wcscpy(pp.adres,L"Wpisz tutaj coś");
    wcscpy(pp.telefon,L"Wpisz tutaj coś");
    wcscpy(pp.fax,L"Wpisz tutaj coś");
    wcscpy(pp.email,L"Wpisz tutaj coś");
    wcscpy(pp.strona_www,L"Wpisz tutaj coś");
    wcscpy(pp.narodowosc,L"Wpisz tutaj coś");


    pp_arr.append(pp);

    Refresh_PP();

}

void MainWindow::Add_New_PD(int id)
{
    int id_new;
    id_new = id + 1;
    wchar_t buff[34];


    // Metoda callbacku
    pd.ID = id_new;
    pd.IDPDB = flm.film_tbl.ID;
    wcscpy(pd.nazwa_firmy,L"Wpisz tutaj coś");
    wcscpy(pd.adres,L"Wpisz tutaj coś");
    wcscpy(pd.telefon,L"Wpisz tutaj coś");
    wcscpy(pd.fax,L"Wpisz tutaj coś");
    wcscpy(pd.email,L"Wpisz tutaj coś");
    wcscpy(pd.strona_www,L"Wpisz tutaj coś");
    wcscpy(pd.narodowosc,L"Wpisz tutaj coś");


    pd_arr.append(pd);

    Refresh_PD();


}

int MainWindow::Get_Hi_ID_PP(void)
{
    if (GetRecC_PP() == 0)
    {
        return 0;
    }

    QFile plik(QString::fromWCharArray(flm.pths.BF_PRP));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        if (i == (stop - sizeof(oc)))
        {
            plik.read(reinterpret_cast<char *>(&pp),sizeof(pp));
            plik.close();
            return pp.ID;
        }
        i = i + sizeof(pp);
    }

}

int MainWindow::Get_Hi_ID_PD(void)
{
    if (GetRecC_PD() == 0)
    {
        return 0;
    }

    QFile plik(QString::fromWCharArray(flm.pths.BF_PRD));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        if (i == (stop - sizeof(oc)))
        {
            plik.read(reinterpret_cast<char *>(&pd),sizeof(pd));
            plik.close();
            return pd.ID;
        }
        i = i + sizeof(pd);
    }


}

int MainWindow::GetRecC_PP(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_PRP));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    int rec_count = 0;
    struct Producent pp_t;
    if (stop == 0)
    {
        plik.close();
        return 0;
    }
    for (i = 0; i <stop; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&pp_t),sizeof(pp_t));
        rec_count = rec_count + 1;
        i = i + sizeof(pp_t);
    }
    plik.close();
    return rec_count;


}

int MainWindow::GetRecC_PD(void)
{
    QFile plik(QString::fromWCharArray(flm.pths.BF_PRD));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    int rec_count = 0;
    struct Dystrybutor pd_t;
    if (stop == 0)
    {
        plik.close();
        return 0;
    }
    for (i = 0; i <stop; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&pd_t),sizeof(pd_t));
        rec_count = rec_count + 1;
        i = i + sizeof(pd_t);
    }
    plik.close();
    return rec_count;


}

void MainWindow::Usun_Rec_PP(unsigned int pos)
{
    struct Producent pp_src;
    pp.ID = 0;
    QFile plik0(QString::fromWCharArray(flm.pths.BF_PRP));
    plik0.open(QFile::ReadOnly);
    plik0.seek(pos);
    plik0.write(reinterpret_cast<char *>(&pp),sizeof(pp));

    plik0.rename(QString::fromWCharArray(flm.pths.BF_PRP),QString::fromWCharArray((LPCTSTR)"BF_PRP.bf0"));

    plik0.close();
    QFile plik(QString::fromWCharArray(flm.pths.BF_PRP));
    plik.open(QFile::WriteOnly);
    QFile src_file(QString::fromWCharArray((LPCTSTR)"BF_PRP.bf0"));
    src_file.open(QFile::ReadOnly);
    unsigned int i;
    for (i = 0; i <(src_file.size()) ; )
    {
        src_file.seek(i);
        src_file.read(reinterpret_cast<char *>(&pp_src),sizeof(pp_src));
        if (pp_src.ID == 0)
        {
            i = i + sizeof(pp_src);
        }
        else
        {
            plik.write(reinterpret_cast<char *>(&pp_src),sizeof(pp_src));
            i = i + sizeof(pp_src);
        }
    }
    plik.close();
    src_file.remove();
    src_file.close();
    Fill_Oc();

}

void MainWindow::Usun_Rec_PD(unsigned int pos)
{
    struct Dystrybutor pd_src;
    pd.ID = 0;
    QFile plik0(QString::fromWCharArray(flm.pths.BF_PRD));
    plik0.open(QFile::ReadOnly);
    plik0.seek(pos);
    plik0.write(reinterpret_cast<char *>(&pd),sizeof(pd));

    plik0.rename(QString::fromWCharArray(flm.pths.BF_PRD),QString::fromWCharArray((LPCWSTR)"BF_PRD.bf0"));

    plik0.close();
    QFile plik(QString::fromWCharArray(flm.pths.BF_PRD));
    plik.open(QFile::WriteOnly);
    QFile src_file(QString::fromWCharArray((LPCTSTR)"BF_PRD.bf0"));
    src_file.open(QFile::ReadOnly);
    unsigned int i;
    for (i = 0; i <(src_file.size()) ; )
    {
        src_file.seek(i);
        src_file.read(reinterpret_cast<char *>(&pd_src),sizeof(pd_src));
        if (pd_src.ID == 0)
        {
            i = i + sizeof(pd_src);
        }
        else
        {
            plik.write(reinterpret_cast<char *>(&pd_src),sizeof(pd_src));
            i = i + sizeof(pd_src);
        }
    }
    plik.close();
    src_file.remove();
    src_file.close();
    Fill_Oc();

}

void MainWindow::on_actionOtw_rz_Utw_rz_baze_danych_triggered()
{
    QFileDialog fdlg(this);
    fdlg.setFileMode(QFileDialog::Directory);
    fdlg.setViewMode(QFileDialog::Detail);
    //fdlg.setNameFilter("Pliki graficzne (*.bmp *.jpg *.jpeg *.png)");
    if (fdlg.exec())
    {
        QString dir_path = fdlg.selectedFiles().at(0);
        wchar_t buff[1024];
        dir_path.toWCharArray(buff);
        SetDBFNPaths(true,buff);
        if (CheckbOpenDB() == 1)
        {
            UtworzDB(true);

        }
        Clear_TABS();
        ClearCtrls(true);
        UpdateCtrls(false,true);
        Licz_Rec();
        open_folder = false;
    }
}

void MainWindow::on_actionEksportuj_triggered()
{
    Eksport_Wizard *eks_wiz = new Eksport_Wizard(this);
    eks_wiz->Create(Eksport_Wizard::IDD,this);
    eks_wiz->ShowWindow(SW_SHOW);
}

void MainWindow::on_actionWyszukaj_triggered()
{

}

void MainWindow::on_actionKoniec_triggered()
{

}

void MainWindow::on_actionDrukuj_triggered()
{

}

void MainWindow::on_actionSprawd_aktualizacje_triggered()
{

}

void MainWindow::on_actionO_programie_triggered()
{

}

void MainWindow::on_actionPomoc_triggered()
{

}

void MainWindow::on_pushButton_LoadPic_clicked()
{
    QFileDialog fdlg(this);
    fdlg.setFileMode(QFileDialog::ExistingFile);
    fdlg.setViewMode(QFileDialog::Detail);
    fdlg.setNameFilter("Pliki graficzne (*.bmp *.jpg *.jpeg *.png)");
    if (fdlg.exec())
    {
        //plik_dlg.DoModal();
        QString plk_path = fdlg.selectedFiles().at(0);
        QString buff;

        buff = QString::fromWCharArray(flm.pths.BF_COVERS);
        buff = buff + QString::number(flm.film_tbl.ID);
        wchar_t buffchr[1024];
        buff.toWCharArray(buffchr);
        wchar_t buffchr2[1024];
        plk_path.toWCharArray(buffchr2);
        CopyFile(buffchr2,buffchr,FALSE);

        wcscpy(flm.film_tbl.skan_przod_path,buffchr);
        on_pushButton_Save_clicked();
    }
}

void MainWindow::on_pushButton_DelPic_clicked()
{
    if (!(Licz_Rec()))
    {
        wcscpy(flm.film_tbl.skan_przod_path,(LPCWSTR)"");
        on_pushButton_Save_clicked();

    }
}

void MainWindow::on_pushButton_B_WYPIN_New_clicked()
{
    Save_Wi();
    Add_New_WI(Get_Hi_ID_WI());
    add_new_wi = true;
}

void MainWindow::on_pushButton_BIBLIOWYPISave_clicked()
{
    Save_Wi();
}

void MainWindow::on_pushButton_BIBLIOWYPINDel_clicked()
{
    QList <QTableWidgetItem *> delitems;
    QTableWidgetItem *delitem;
    int delID = 0;
    delitems = ui->tableWidget_BIBLIO_WYPIN->selectedItems();
    delitem = delitems.at(5);
    delID = delitem->text().toInt();

    QFile plik(QString::fromWCharArray(flm.pths.BF_WI));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&wi),sizeof(wi));
        if (delID == wi.ID)
        {
            plik.close();
            Usun_Rec_WI(i);
            break;
        }
        i = i + sizeof(wi);
    }
    if (plik.isOpen() == true)
    {
        plik.close();
    }
}

void MainWindow::on_pushButton_B_WYPODIN_New_clicked()
{
    Save_Wo();
    Add_New_WO(Get_Hi_ID_WO());
    add_new_wo = true;
}

void MainWindow::on_pushButton_BIBLIOWYPODINSave_clicked()
{
    Save_Wo();
}

void MainWindow::on_pushButton_BIBLIOWYPODINDel_clicked()
{
    QList <QTableWidgetItem *> delitems;
    QTableWidgetItem *delitem;
    int delID = 0;
    delitems = ui->tableWidget_BIBLIO_WYPODIN->selectedItems();
    delitem = delitems.at(5);
    delID = delitem->text().toInt();

    QFile plik(QString::fromWCharArray(flm.pths.BF_WO));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&wo),sizeof(wo));
        if (delID == wi.ID)
        {
            plik.close();
            Usun_Rec_WO(i);
            break;
        }
        i = i + sizeof(wi);
    }
    if (plik.isOpen() == true)
    {
        plik.close();
    }
}

void MainWindow::on_pushButton_LZ_New_clicked()
{
    Save_Lz();
    Add_New_LZ(Get_Hi_ID_LZ());
    add_new_lz = true;
}

void MainWindow::on_pushButton_LZSave_clicked()
{
    Save_Lz();
}

void MainWindow::on_pushButton_LZDel_clicked()
{
    QList <QTableWidgetItem *> delitems;
    QTableWidgetItem *delitem;
    int delID = 0;
    delitems = ui->tableWidget_IOF_LZ->selectedItems();
    delitem = delitems.at(6);
    delID = delitem->text().toInt();

    QFile plik(QString::fromWCharArray(flm.pths.BF_LZ));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&lz),sizeof(lz));
        if (delID == lz.ID)
        {
            plik.close();
            Usun_Rec_LZ(i);
            break;
        }
        i = i + sizeof(lz);
    }
    if (plik.isOpen() == true)
    {
        plik.close();
    }
}

void MainWindow::on_pushButton_OB_new_clicked()
{
    Save_Ob();
    Add_New_Ob(Get_Hi_ID_OB());
    add_new_ob = true;
}

void MainWindow::on_pushButton_OBSave_clicked()
{
    Save_Ob();
}

void MainWindow::on_pushButton_OBDel_clicked()
{
    QList <QTableWidgetItem *> delitems;
    QTableWidgetItem *delitem;
    int delID = 0;
    delitems = ui->tableWidget_Obsada->selectedItems();
    delitem = delitems.at(2);
    delID = delitem->text().toInt();

    QFile plik(QString::fromWCharArray(flm.pths.BF_OB));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&ob),sizeof(ob));
        if (delID == ob.ID)
        {
            plik.close();
            Usun_Rec_OB(i);
            break;
        }
        i = i + sizeof(ob);
    }
    if (plik.isOpen() == true)
    {
        plik.close();
    }

}

void MainWindow::Refresh_Lz(void)
{
    ui->tableWidget_IOF_LZ->clearContents();

    int x;
    QTableWidgetItem *item;
    for (x=0;x<lz_arr.count(); x++)
    {
        ui->tableWidget_IOF_LZ->insertRow(x);

        item->setText(QString::fromWCharArray(lz_arr[x].nazwa_obiektu));
        ui->tableWidget_IOF_LZ->setItem(x,0,item);

        item->setText(QString::fromWCharArray(lz_arr[x].kraj));
        ui->tableWidget_IOF_LZ->setItem(x,1,item);

        item->setText(QString::fromWCharArray(lz_arr[x].miejscowosc));
        ui->tableWidget_IOF_LZ->setItem(x,2,item);

        item->setText(QString::fromWCharArray(lz_arr[x].region));
        ui->tableWidget_IOF_LZ->setItem(x,3,item);

        item->setText(QString::fromWCharArray(lz_arr[x].pora_roku));
        ui->tableWidget_IOF_LZ->setItem(x,4,item);

        item->setText(QString::fromWCharArray(lz_arr[x].data));
        ui->tableWidget_IOF_LZ->setItem(x,5,item);

        item->setText(QString::number(lz_arr[x].ID,10));
        ui->tableWidget_IOF_LZ->setItem(x,6,item);

        item->setText(QString::number(lz_arr[x].IDPDB,10));
        ui->tableWidget_IOF_LZ->setItem(x,7,item);

    }


}

void MainWindow::on_pushButton_OC_New_clicked()
{
    Save_Oc();
    Add_New_Oc(Get_Hi_ID_OC());
    add_new_oc = true;
}

void MainWindow::on_pushButton_OC_Save_clicked()
{
    Save_Oc();
}

void MainWindow::on_pushButton_OC_Del_clicked()
{
    QList <QTableWidgetItem *> delitems;
    QTableWidgetItem *delitem;
    int delID = 0;
    delitems = ui->tableWidget_OC->selectedItems();
    delitem = delitems.at(5);
    delID = delitem->text().toInt();

    QFile plik(QString::fromWCharArray(flm.pths.BF_OC));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&oc),sizeof(oc));
        if (delID == oc.ID)
        {
            plik.close();
            Usun_Rec_OC(i);
            break;
        }
        i = i + sizeof(oc);
    }
    if (plik.isOpen() == true)
    {
        plik.close();
    }



}

void MainWindow::Fill_Opis()
{




}

void MainWindow::on_pushButto_P_New_clicked()
{
    Save_PP();
    Add_New_PP(Get_Hi_ID_PP());
    add_new_pp = true;

}

void MainWindow::on_pushButton_PRODSave_clicked()
{
    Save_PP();
}

void MainWindow::on_pushButton_PRODDel_clicked()
{
    QList <QTableWidgetItem *> delitems;
    QTableWidgetItem *delitem;
    int delID = 0;
    delitems = ui->tableWidget_Prod->selectedItems();
    delitem = delitems.at(6);
    delID = delitem->text().toInt();

    QFile plik(QString::fromWCharArray(flm.pths.BF_PRP));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&pp),sizeof(pp));
        if (delID == pp.ID)
        {
            plik.close();
            Usun_Rec_OC(i);
            break;
        }
        i = i + sizeof(pp);
    }
    if (plik.isOpen() == true)
    {
        plik.close();
    }
}

void MainWindow::on_pushButton_D_New_clicked()
{
    Save_PD();
    Add_New_PD(Get_Hi_ID_PD());
    add_new_pd = true;
}

void MainWindow::on_pushButton_DYSTSave_clicked()
{
    Save_PD();
}

void MainWindow::on_pushButton_DYSTDel_clicked()
{
    QList <QTableWidgetItem *> delitems;
    QTableWidgetItem *delitem;
    int delID = 0;
    delitems = ui->tableWidget_Dystr->selectedItems();
    delitem = delitems.at(6);
    delID = delitem->text().toInt();

    QFile plik(QString::fromWCharArray(flm.pths.BF_PRD));
    plik.open(QFile::ReadOnly);
    unsigned int i;
    unsigned int stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        plik.read(reinterpret_cast<char *>(&pd),sizeof(pd));
        if (delID == pd.ID)
        {
            plik.close();
            Usun_Rec_OC(i);
            break;
        }
        i = i + sizeof(pd);
    }
    if (plik.isOpen() == true)
    {
        plik.close();
    }

}
