#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QList>


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

        MainWindow::Insert_TAB_Item();
        MainWindow::SetDlgBoxs(10);
        MainWindow::SetListCtrls(5);
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
        ui->lineEdit_ID->setText(dest); // tu jest problem BEX
        //F_EDIT_ID.SetReadOnly(TRUE);
        ui->lineEdit_Tytul->setText(flm.film_tbl.tytul);
        ui->lineEdit_TytulOrig->setText(flm.film_tbl.oryginalny_tytul);
        ui->lineEdit_Gatunek->setText(flm.film_tbl.gatunek_filmu);
        //ui->textEdit_Opis->setText(flm.film2_ftbl.opis);


        if (_tcscmp(flm.film_tbl.skan_przod_path,_TEXT("")) != 0)
        {
            QFile pic_front(flm.film_tbl.skan_przod_path);
            if (pic_front.exist())
            {
                QImage img_front(flm.film_tbl.skan_przod_path,NULL);
                img_front.scaled(139,172,Qt::IgnoreAspectRatio,Qt::);
                ui->label_PicFront->setPixmap(QPixmap::fromImage(img_front));

            }
        }
        else
        {
            QImage img_front("/covers/no_img.bmp",NULL);
            img_front.scaled(139,172,Qt::IgnoreAspectRatio,Qt::);
            ui->label_PicFront->setPixmap(QPixmap::fromImage(img_front));



        }


        //TAB OCENA

        ui->lineEdit_OC_OW_SD->setText(flm.film_tbl.WOF_sciezka_dz);
        ui->lineEdit_OC_OW_Obs->setText(flm.film_tbl.WOF_obsada);
        ui->lineEdit__OC_OW_Zdj->setText(flm.film_tbl.WOF_zdjecia);
        ui->lineEdit__OC_OW_WA->setText(flm.film_tbl.WOF_w_art);
        ui->lineEdit__OC_OW_All->setText(flm.film_tbl.WOF_calosc);

        // TAB PRODUKCJA


        // TAB DOE
        ui->lineEdit_DOE_W_Imie->setText(flm.film_tbl.DOE_WKF_imie);
        ui->lineEdit_DOE_W_Nazw->setText(flm.film_tbl.DOE_WKF_nazwisko);
        ui->lineEdit_DOE_W_Adres->setText(flm.film_tbl.DOE_WKF_adres);
        ui->lineEdit_DOE_S_Nazwa->setText(flm.film_tbl.DOE_MN_nazwa);
        ui->lineEdit_DOE_S_Adres->setText(flm.film_tbl.DOE_MN_adres);
        ui->lineEdit_DOE_S_WWW->setText(flm.film_tbl.DOE_MN_www);
        ui->lineEdit_DOE_S_Tel->setText(flm.film_tbl.DOE_MN_telefon);
        ui->lineEdit_DOE_S_Fax->setText(flm.film_tbl.DOE_MN_fax);
        ui->lineEdit_DOE_S_Email->setText(flm.film_tbl.DOE_MN_email);
        ui->lineEdit_DOE_Cena->setText(flm.film_tbl.DOE_cena);
        ui->lineEdit_DOE_Wakt->setText(flm.film_tbl.DOE_wartosc_akt);
        ui->lineEdit_DOE_DataZak->setText(flm.film_tbl.DOE_data_zakupu);
        ui->lineEdit_DOE_DataUtr->setText(flm.film_tbl.DOE_data_utraty);
        ui->lineEdit_DOE_DataSkat->setText(flm.film_tbl.DOE_data_skatalogowania);
        ui->lineEdit_DOE_NrKat->setText(flm.film_tbl.DOE_Nr_kat);
        ui->fontComboBox_DOE_Nosnik->lineEdit()->setText(flm.film_tbl.DOE_rodzaj_nosnika);
        // TAB IOF
        ui->lineEdit_RokProd->setText(flm.film_tbl.IOF_rok_produkcji);
        ui->lineEdit_DataPrem->setText(flm.film_tbl.IOF_data_premiery);
        ui->lineEdit_CzasProj->setText(flm.film_tbl.IOF_czas_trwania);
        ui->lineEdit_FormWysw->setText(flm.film_tbl.IOF_format_wysw);
        ui->lineEdit_SysKodObr->setText(flm.film_tbl.IOF_system_kodowania_obrazu);
        ui->lineEdit_JezLekt->setText(flm.film_tbl.IOF_jezyk_lektora);
        ui->lineEdit_JezNap->setText(flm.film_tbl.IOF_jezyk_napisow);
        ui->lineEdit_KrajProd->setText(flm.film_tbl.IOF_kraj_produkcji_filmu);
        ui->lineEdit_KodVidNazwa->setText(flm.film_tbl.IOF_KODEK_nazwa);
        ui->lineEdit_KodVidTyp->setText(flm.film_tbl.IOF_KODEK_typ);
        ui->lineEdit_KodVidWersja->setText(flm.film_tbl.IOF_KODEK_wersja);
        ui->lineEdit_KodAudNazwa->setText(flm.film_tbl.IOF_DZWIEK_nazwa);
        ui->lineEdit_KodAudTyp->setText(flm.film_tbl.IOF_DZWIEK_typ);
        ui->lineEdit_KodAudWersja->setText(flm.film_tbl.IOF_DZWIEK_wersja);
        ui->lineEdit_ZabNazwa->setText(flm.film_tbl.IOF_ZABEZP_nazwa);
        ui->lineEdit_ZabTyp->setText(flm.film_tbl.IOF_ZABEZP_typ);
        ui->lineEdit_ZabWersja->setText(flm.film_tbl.IOF_ZABEZP_wersja);

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
    QFileInfo fi(flm.pths.BF_PDB);
    if (fi.exists())
    {
        test[0] = true;
    }
    else
    {
        test[0] = false;
    }
    QFileInfo fi(flm.pths.BF_OC);
    if (fi.exists())
    {
        test[1] = true;
    }
    else
    {
        test[1] = false;
    }
    QFileInfo fi(flm.pths.BF_OB);
    if (fi.exists())
    {
        test[2] = true;
    }
    else
    {
        test[2] = false;
    }
    QFileInfo fi(flm.pths.BF_PRP);
    if (fi.exists())
    {
        test[3] = true;
    }
    else
    {
        test[3] = false;
    }
    QFileInfo fi(flm.pths.BF_PRD);
    if (fi.exists())
    {
        test[4] = true;
    }
    else
    {
        test[4] = false;
    }
    QFileInfo fi(flm.pths.BF_LZ);
    if (fi.exists())
    {
        test[5] = true;
    }
    else
    {
        test[5] = false;
    }
    QFileInfo fi(flm.pths.BF_WI);
    if (fi.exists())
    {
        test[6] = true;
    }
    else
    {
        test[6] = false;
    }
    QFileInfo fi(flm.pths.BF_WO);
    if (fi.exists())
    {
        test[7] = true;
    }
    else
    {
        test[7] = false;
    }
    QFileInfo fi(flm.pths.BF_MCF);
    if (fi.exists())
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
        QMessageBox msgbox(QMessageBox::Critical,L"Biblioteka Filmów",L"Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.", QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }
    else if ((test[0] == true && test[8] == true) && (test[1] == false))
    {
        QMessageBox msgbox(QMessageBox::Critical,L"Biblioteka Filmów",L"Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.",QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }
    else if ((test[0] == true && test[8] == true) && (test[2] == false))
    {
        QMessageBox msgbox(QMessageBox::Critical,L"Biblioteka Filmów",L"Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.",QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }
    else if ((test[0] == true && test[8] == true) && (test[3] == false))
    {
        QMessageBox msgbox(QMessageBox::Critical,L"Biblioteka Filmów",L"Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.",QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }
    else if ((test[0] == true && test[8] == true) && (test[4] == false))
    {
        QMessageBox msgbox(QMessageBox::Critical,L"Biblioteka Filmów",L"Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.",QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }
    else if ((test[0] == true && test[8] == true) && (test[5] == false))
    {
        QMessageBox msgbox(QMessageBox::Critical,L"Biblioteka Filmów",L"Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.",QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }
    else if ((test[0] == true && test[8] == true) && (test[6] == false))
    {
        QMessageBox msgbox(QMessageBox::Critical,L"Biblioteka Filmów",L"Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.",QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }
    else if ((test[0] == true && test[8] == true) && (test[7]== false))
    {
        QMessageBox msgbox(QMessageBox::Critical,L"Biblioteka Filmów",L"Baza danych jest uszkodzona !!!! Biblioteka Filmów nie może jej otworzyć. Spróbuj ozdyskać uszkodzone dane lub samodzielnie skasuj(na własne ryzyko !!!!) pliki bazy danych - program odtworzy pustą strukture bazy danych.",QMessageBox::Ok, this);
        msgbox.show();
        return 2;
    }

}

bool MainWindow::CheckBFVER(void)
{
// pobiera strukturę "POMIDOR" z poczatku pliku BF.dat celem sprawdzenia wersji bazy danych i co z tym idzie zgodności z
// ta wersją BF

    struct POMIDOR pom;
    QFile plik(flm.pths.BF_MCF);
    plik.open(QFile::ReadOnly);
    plik.seek(0);
    plik.read(static_cast<char *>(&pom),sizeof(struct POMIDOR));
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
            QFile plik(flm.pths.BF_PDB);
                plik.open(QFile::ReadOnly);
                if (start)
                {
                    plik.seek(0);
                }
                else if (start == false)
                {
                    plik.seek(zadana_pozycja_pliku);
                }
                plik.read(static_cast<char *>(&flm.film_tbl),sizeof(struct Film));
                plik.close();

                Clear_TABS(); // czyszczenie kontrolek pól list

                Fill_Opis();
                Fill_Oc(false); // wypełnianie kontrolek pól list
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
            QFile plik(flm.pths.BF_PDB);
                plik.open(QFile::WriteOnly);
                akt_pozycja_pliku = zadana_pozycja_pliku;
                plik.seek(zadana_pozycja_pliku);
                plik.write(static_cast<char *>(&flm.film_tbl),sizeof(flm.film_tbl));
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
            QFile plik(flm.pths.BF_PDB);
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

            plik.write(static_cast<char *>(&flm.film_tbl),sizeof(flm.film_tbl));
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
    QFile plik(flm.pths.BF_MCF);
    plik.open(QFile::ReadOnly);
    plik.seek(0);
    plik.read(static_cast<char *>(&pom),sizeof(struct POMIDOR));
    plik.close();
    flm.film_tbl.ID = pom.najw_ID + 1;
    pom.najw_ID = flm.film_tbl.ID;
    plik.open(QFile::WriteOnly);
    plik.seek(0);
    plik.write(static_cast<char *>(&pom),sizeof(struct POMIDOR));
    plik.close();

}
LONGLONG MainWindow::Search_Last_Pos(void) {
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
        QFile plik(flm.pths.BF_PDB);
        plik.open(QFile::ReadOnly);
/*
        LONGLONG i;
        LONGLONG y;
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

        LONGLONG off;
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
        QDir di(flm.pths.cur_db_path);
        if (!(di.exists() == TRUE))
        {
            QDir::mkpath(flm.pths.cur_db_path);
        }
    }
    QDir di(flm.pths.BF_COVERS);
    if (!(di.exists() == TRUE))
    {
        QDir::mkpath(flm.pths.BF_COVERS);
    }
    QFile fi(flm.pths.BF_MCF);
    if (!(fi.exists() == TRUE))
    {
        QFile bf(flm.pths.BF_MCF);
        struct POMIDOR pom;
        wcscpy(pom.BF_VER,akt_BF_VER);
        pom.najw_ID = 1;
        bf.open(QFile::WriteOnly);
        bf.close();
        bf.open(QFile::WriteOnly);
        bf.write(static_cast<char *>(&pom),sizeof(pom));
        bf.close();
    }
    QFile fi(flm.pths.BF_PDB);
    if (!(fi.exists() ==  TRUE))
    {
        QFile bf_pdb(flm.pths.BF_PDB);
        bf_pdb.open(QFile::WriteOnly);
        bf_pdb.close();
    }
    QFile fi(flm.pths.BF_OC);
    if (!(fi.exists() == TRUE))
    {
        QFile bf_oc(flm.pths.BF_OC);
        bf_oc.open(QFile::WriteOnly);
        bf_oc.close();
    }
    QFile fi(flm.pths.BF_OB);
    if (!(fi.exists() == TRUE))
    {
        QFile bf_ob(flm.pths.BF_OB);
        bf_ob.open(QFile::WriteOnly);
        bf_ob.close();
    }
    QFile fi(flm.pths.BF_PRP);
    if (!(fi.exists() == TRUE))
    {
        QFile bf_pr(flm.pths.BF_PRP);
        bf_pr.open(QFile::WriteOnly);
        bf_pr.close();
    }
    QFile fi(flm.pths.BF_PRD);
    if (!(fi.exists() == TRUE))
    {
        QFile bf_dr(flm.pths.BF_PRD);
        bf_dr.open(QFile::WriteOnly);
        bf_dr.close();
    }
    QFile fi(flm.pths.BF_LZ);
    if (!(fi.exists() == TRUE))
    {
        QFile bf_lz(flm.pths.BF_LZ);
        bf_lz.open(QFile::WriteOnly);
        bf_lz.close();
    }
    QFile fi(flm.pths.BF_WI);
    if (!(fi.exists() == TRUE))
    {
        QFile bf_wi(flm.pths.BF_WI);
        bf_wi.open(QFile::WriteOnly);
        bf_wi.close();
    }
    QFile fi(flm.pths.BF_WO);
    if (!(fi.exists() == TRUE))
    {
        QFile bf_wo(flm.pths.BF_WO);
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
                QFile plik(flm.pths.BF_PDB);
                plik.open(QFile::WriteOnly);
                plik.seek(zadana_pozycja_pliku);
                plik.write(static_cast<char *>(&flm.film_tbl),sizeof(struct Film));

                plik.rename(L"BF_PDB.bf0");
                plik.close();

                QFile plik(flm.pths.BF_PDB);
                plik.open(QFile::WriteOnly);
                QFile src_file(L"BF_PDB.bf0");
                src_file.open(QFile::ReadOnly);
                struct Film flm_src;
                LONGLONG i;
                for (i = 0; i <(src_file.size()) ; )
                {
                    src_file.seek(i);
                    src_file.read(static_cast<char *>(&flm_src),sizeof(struct Film));
                    if (flm_src.ID == 0)
                    {
                        i = i + sizeof(struct Film);
                    }
                    else
                    {
                        plik.write(static_cast<char *>(&flm_src),sizeof(struct Film));
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
    QFile fi(flm.pths.BF_PDB);
    if (fi.exists())
        {
            if (fi.size() == 0)
                {

                    ui->lineEdit_RecNo->setText(_TEXT("0"));
                    ui->lineEdit_RecCount->setText(_TEXT("0"));
                    return true;
                }
            else
                {
                    // policz rekordy w trybie niesortowanym i wypełnij Film_tab_wsk
                    QFile plik(flm.pths.BF_PDB);
                    struct Film film_test;
                    plik.open(QFile::ReadOnly);
                    LONGLONG stop = 0;
                    stop = plik.size();
                    LONGLONG i = 0;
                    int cur_rec = 0;
                    int rec_count = 0;
                    wchar_t crec_txt[34];
                    wchar_t recc_txt[34];
                    for (i = 0; i < stop; )
                    {
                        plik.seek(i);
                        plik.read(static_cast<char *>(&film_test),sizeof(film_test));
                        rec_count = rec_count + 1;
                        if (flm.film_tbl.ID == film_test.ID)
                        {
                            cur_rec = rec_count;
                        }

                            i = i + sizeof(film_test);
                        }
                            _itow(cur_rec,crec_txt,10);
                            _itow(rec_count,recc_txt,10);
                            ui->lineEdit_RecNo->setText(crec_txt);
                            ui->lineEdit_RecCount->setText(recc_txt);

                    }


                    return false;

                }
        }
}
void MainWindow::Read_Settings()
{
//TODO : Napisać odczytywanie ustawień, jak nie ma utworzyc plik z domyślnymi

}

void MainWindow::SetDBFNPaths(bool cust, wchar_t* cust_path)
{
    _tcscpy(flm.pths.BF_PDB,L"BF_PDB.bf");
    _tcscpy(flm.pths.BF_OC,L"BF_OC.bf");
    _tcscpy(flm.pths.BF_OB,L"BF_OB.bf");
    _tcscpy(flm.pths.BF_PRP,L"BF_PRB.bf");
    _tcscpy(flm.pths.BF_PRD,L"BF_PRD.bf");
    _tcscpy(flm.pths.BF_LZ,L"BF_LZ.bf");
    _tcscpy(flm.pths.BF_WI,L"BF_WI.bf");
    _tcscpy(flm.pths.BF_WO,L"BF_WO.bf");
    _tcscpy(flm.pths.BF_COVERS,_TEXT("covers\\"));
    _tcscpy(flm.pths.BF_MCF,L"BF.bf");
    _tcscpy(flm.pths.db_path,_TEXT("\\default_db\\"));
    if (cust)
    {
        _tcscpy(flm.pths.cur_db_path,cust_path);
        _tcscat(flm.pths.cur_db_path, TEXT("\\"));

        wchar_t *buff = new wchar_t;

        _tcscpy(buff,flm.pths.cur_db_path);
        _tcscat(buff,flm.pths.BF_PDB);
        _tcscpy(flm.pths.BF_PDB, buff);

        _tcscpy(buff,flm.pths.cur_db_path);
        _tcscat(buff,flm.pths.BF_OC);
        _tcscpy(flm.pths.BF_OC, buff);

        _tcscpy(buff,flm.pths.cur_db_path);
        _tcscat(buff,flm.pths.BF_OB);
        _tcscpy(flm.pths.BF_OB, buff);

        _tcscpy(buff,flm.pths.cur_db_path);
        _tcscat(buff,flm.pths.BF_LZ);
        _tcscpy(flm.pths.BF_LZ,buff);

        _tcscpy(buff,flm.pths.cur_db_path);
        _tcscat(buff,flm.pths.BF_PRD);
        _tcscpy(flm.pths.BF_PRD,buff);

        _tcscpy(buff,flm.pths.cur_db_path);
        _tcscat(buff,flm.pths.BF_PRP);
        _tcscpy(flm.pths.BF_PRP, buff);

        _tcscpy(buff,flm.pths.cur_db_path);
        _tcscat(buff,flm.pths.BF_WI);
        _tcscpy(flm.pths.BF_WI, buff);

        _tcscpy(buff,flm.pths.cur_db_path);
        _tcscat(buff,flm.pths.BF_WO);
        _tcscpy(flm.pths.BF_WO,buff);

        _tcscpy(buff,flm.pths.cur_db_path);
        _tcscat(buff,flm.pths.BF_MCF);
        _tcscpy(flm.pths.BF_MCF,buff);

        _tcscpy(buff, flm.pths.cur_db_path);
        _tcscat(buff, flm.pths.BF_COVERS);
        _tcscpy(flm.pths.BF_COVERS, buff);

    }
    else
    {

        wchar_t buff[1024];
        wchar_t *cur_dir;
        cur_dir = _tgetcwd(NULL,0);

        /*if (buff[_tcsclen(buff)] == '\\')
        {
            buff[_tcsclen(buff)] = '\0';
        }*/
        _tcscpy(buff,cur_dir);

        _tcscpy(flm.pths.cur_db_path,buff);
        _tcscat(flm.pths.cur_db_path,flm.pths.db_path); // ustawianie katalogu gł bazy danych

        _tcscat(buff,flm.pths.db_path); // BF_PDB
        _tcscat(buff,flm.pths.BF_PDB);
        _tcscpy(flm.pths.BF_PDB,buff);

        _tcscpy(buff,cur_dir);

        _tcscat(buff,flm.pths.db_path); //BF MCF
        _tcscat(buff,flm.pths.BF_MCF);
        _tcscpy(flm.pths.BF_MCF,buff);

        _tcscpy(buff,cur_dir);

        _tcscat(buff,flm.pths.db_path); // BF_COVERS
        _tcscat(buff,flm.pths.BF_COVERS);
        _tcscpy(flm.pths.BF_COVERS,buff);

        _tcscpy(buff,cur_dir);

        _tcscat(buff,flm.pths.db_path);
        _tcscat(buff,flm.pths.BF_OC);
        _tcscpy(flm.pths.BF_OC,buff);

        _tcscpy(buff,cur_dir);

        _tcscat(buff,flm.pths.db_path);
        _tcscat(buff,flm.pths.BF_OB);
        _tcscpy(flm.pths.BF_OB,buff);

        _tcscpy(buff,cur_dir);

        _tcscat(buff,flm.pths.db_path);
        _tcscat(buff,flm.pths.BF_PRP);
        _tcscpy(flm.pths.BF_PRP,buff);

        _tcscpy(buff,cur_dir);

        _tcscat(buff,flm.pths.db_path);
        _tcscat(buff,flm.pths.BF_PRD);
        _tcscpy(flm.pths.BF_PRD,buff);

        _tcscpy(buff,cur_dir);

        _tcscat(buff,flm.pths.db_path);
        _tcscat(buff,flm.pths.BF_LZ);
        _tcscpy(flm.pths.BF_LZ,buff);

        _tcscpy(buff,cur_dir);

        _tcscat(buff,flm.pths.db_path);
        _tcscat(buff,flm.pths.BF_WI);
        _tcscpy(flm.pths.BF_WI,buff);

        _tcscpy(buff,cur_dir);

        _tcscat(buff,flm.pths.db_path);
        _tcscat(buff,flm.pths.BF_WO);
        _tcscpy(flm.pths.BF_WO,buff);
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
    QFile fi(_TEXT("BF.bf"));
    if (fi.exists())
    {
        test[0] = true;
    }
    else
    {
        test[0] = false;
    }
    QFile fi(_TEXT("BF_PDB.bf"));
    if (fi.exists())
    {
        test[1] = true;
    }
    else
    {
        test[1] = false;
    }
    QFile fi(_TEXT("BF_OC.bf"));
    if (fi.exists())
    {
        test[2] = true;
    }
    else
    {
        test[2] = false;
    }
    QFile fi(_TEXT("BF_OB.bf");
    if (fi.exists())
    {
        test[3] = true;
    }
    else
    {
        test[3] = false;
    }
    QFile fi(_TEXT("BF_PRB.bf"));
    if (fi.exists())
    {
        test[4] = true;
    }
    else
    {
        test[4] = false;
    }
    QFile fi(_TEXT("BF_PRD.bf"));
    if (fi.exists())
    {
        test[5] = true;
    }
    else
    {
        test[5] = false;
    }
    QFile fi(_TEXT("BF_LZ.bf"));
    if (fi.exists())
    {
        test[6] = true;
    }
    else
    {
        test[6] = false;
    }
    QFile fi(_TEXT("BF_WI.bf"));
    if (fi.exists())
    {
        test[7] = true;
    }
    else
    {
        test[7] = false;
    }
    QFile fi(_TEXT("BF_WO.bf"));
    if (fi.exists())
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
    QString buff_path;
    buff_path = flm.pths.cur_db_path;
    CopyFile(_TEXT("BF.bf"),buff_path + _TEXT("BF.bf"),FALSE);
    CopyFile(_TEXT("BF_PDB.bf"),buff_path + _TEXT("BF_PDB.bf"),FALSE);
    CopyFile(_TEXT("BF_OC.bf"),buff_path + _TEXT("BF_OC.bf"),FALSE);
    CopyFile(_TEXT("BF_OB.bf"),buff_path + _TEXT("BF_OB.bf"),FALSE);
    CopyFile(_TEXT("BF_PRB.bf"),buff_path + _TEXT("BF_PRB.bf"),FALSE);
    CopyFile(_TEXT("BF_PRD.bf"),buff_path + _TEXT("BF_PRD.bf"),FALSE);
    CopyFile(_TEXT("BF_WI.bf"),buff_path + _TEXT("BF_WI.bf"),FALSE);
    CopyFile(_TEXT("BF_WO.bf"),buff_path + _TEXT("BF_WO.bf"),FALSE);
    CopyFile(_TEXT("BF_LZ.bf"),buff_path + _TEXT("BF_LZ.bf"),FALSE);
    DeleteFile(_TEXT("BF.bf"));
    DeleteFile(_TEXT("BF_PDB.bf"));
    DeleteFile(_TEXT("BF_OC.bf"));
    DeleteFile(_TEXT("BF_OB.bf"));
    DeleteFile(_TEXT("BF_PRB.bf"));
    DeleteFile(_TEXT("BF_PRD.bf"));
    DeleteFile(_TEXT("BF_WI.bf"));
    DeleteFile(_TEXT("BF_WO.bf"));
    DeleteFile(_TEXT("BF_LZ.bf"));
}

void MainWindow::ClearBIBLIO(void)
{
    ui->tableWidget_BIBLIO_WYPIN->clearContents();
    ui->tableWidget_BIBLIO_WYPODIN->clearContents();
}

void MainWindow::Fill_Wi(void)
{
    QFile plik(flm.pths.BF_WI);
    plik.open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
    stop = plik.size();


    ui->tableWidget_BIBLIO_WYPIN->clearContents();
    wi_arr.clear();

    for (i = 0;i<stop ; )
    {
        plik.seek(i);
        plik.read(static_cast<char *>(&wi),sizeof(wi));
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
    QFile plik(flm.pths.BF_WO);
    plik.Open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
    stop = plik.size();


    ui->tableWidget_BIBLIO_WYPODIN->clearContents();
    wo_arr.clear();



    for (i = 0;i<stop ; )
    {
        plik.seek(i);
        plik.read(static_cast<char *>(&wo),sizeof(wo));
        if (wo.IDPDB == flm_b.film_tbl.ID)
        {
            wo_arr.append(wo);

        }
        i = i + sizeof(wo);
    }
    plik.close();

    Refresh_Wo();


}

void MainWindow::OnBnClickedButtonFrmFBWoiNowy()
{
    Save_Wo();
    Add_New_WO(Get_Hi_ID_WO());
    add_new_wo = true;
}

void MainWindow::OnBnClickedButtonFrmFBWoiZapisz()
{
    Save_Wo();
}

void MainWindow::Refresh_Wi(void)
{
    ui->tableWidget_BIBLIO_WYPIN->clearContents();

    int x;
    QTableWidgetItem *item;
    for (x=0;x<wi_arr.count(); x++)
    {
        ui->tableWidget_BIBLIO_WYPIN->insertRow(x);

        item->setText(wi_arr[x].osoba);
        ui->tableWidget_BIBLIO_WYPIN->setItem(x,0,item);

        item->setText(wi_arr[x].data_wypozyczenia);
        ui->tableWidget_BIBLIO_WYPIN->setItem(x,1,item);

        item->setText(wi_arr[x].data_oddania);
        ui->tableWidget_BIBLIO_WYPIN->setItem(x,2,item);

        item->setText(wi_arr[x].stan_przed_wypozycz);
        ui->tableWidget_BIBLIO_WYPIN->setItem(x,3,item);

        item->setText(wi_arr[x].stan_po_oddaniu);
        ui->tableWidget_BIBLIO_WYPIN->setItem(x,4,item);

        item->setText(wi_arr[x].ID);
        ui->tableWidget_BIBLIO_WYPIN->setItem(x,5,item);

        item->setText(wi_arr[x].IDPDB);
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

        item->setText(wo_arr[x].osoba);
        ui->tableWidget_BIBLIO_WYPODIN->setItem(x,0,item);

        item->setText(wo_arr[x].data_wypozyczenia);
        ui->tableWidget_BIBLIO_WYPODIN->setItem(x,1,item);

        item->setText(wo_arr[x].data_oddania);
        ui->tableWidget_BIBLIO_WYPODIN->setItem(x,2,item);

        item->setText(wo_arr[x].stan_przed_wypozycz);
        ui->tableWidget_BIBLIO_WYPODIN->setItem(x,3,item);

        item->setText(wo_arr[x].stan_po_oddaniu);
        ui->tableWidget_BIBLIO_WYPODIN->setItem(x,4,item);

        item->setText(wo_arr[x].ID);
        ui->tableWidget_BIBLIO_WYPODIN->setItem(x,5,item);

        item->setText(wo_arr[x].IDPDB);
        ui->tableWidget_BIBLIO_WYPODIN->setItem(x,6,item);

    }

}

void MainWindow::Save_Wi(void)
{
    QFile plik(flm.pths.BF_WI);
    struct Wypozycz_Innym wi_buf;
    plik.open(QFile::ReadWrite);

    LONGLONG stop;
    LONGLONG i;
    int y;

    wchar_t buff[34];
    stop = plik.size();

    for (y=0;y<wi_arr.count() ;y++ )
    {
        if (GetRecC_WI() == 0)
            {
                plik.seek(0);
                plik.write(static_cast<char *> (&wi_arr[y]),sizeof(wi));

            }
        else if (GetRecC_WI() > 0)
            {
                if ((plik.size()) > 2147483647)
                {
                    QMessageBox(QMessageBox::Warning,L"Biblioteka Filmów",L"Nie można więcej zapisywać do tego pliku - jest przepełniony !!! ",QMessageBox::Ok);
                    break;
                }
                else if ((plik.size()) < 2147483647)
                {
                    for (i=0; i<stop; )
                    {
                        plik.seek(i);
                        plik.read(static_cast<char *>(&wi_buf),sizeof(wi_buf));
                            if (wi_arr[y].ID == wi_buf.ID)
                            {
                                plik.seek(i);
                                plik.write(static_cast<char *>(&wi_arr[y]),sizeof(wi));
                            }

                        i = i + sizeof(wi);
                    }
                    if (add_new_wi)
                    {

                        int x;
                        x = (wi_arr.count()-1);
                        plik.seek(plik.size());
                        plik.write(static_cast<char *>(&wi_arr[x]),sizeof(wi));
                        add_new_wi = false;
                    }
                }
            }

    }

    plik.close();


}

void MainWindow::Save_Wo(void)
{
    QFile plik(flm.pths.BF_WO);
    struct Wypozycz_Od_Innych wo_buf;
    plik.open(QFile::ReadWrite);

    LONGLONG stop;
    LONGLONG i;
    int y;

    wchar_t buff[34];
    stop = plik.size();

    for (y=0;y<wo_arr.count() ;y++ )
    {
        if (GetRecC_WO() == 0)
            {
                plik.seek(0);
                plik.write(static_cast<char *>(&wo_arr[y]),sizeof(wo));

            }
        else if (GetRecC_WO() > 0)
            {
                if ((plik.size()) > 2147483647)
                {
                    QMessageBox(QMessageBox::Warning,L"Biblioteka Filmów",L"Nie można więcej zapisywać do tego pliku - jest przepełniony !!! ",QMessageBox::Ok);
                    break;
                }
                else if ((plik.size()) < 2147483647)
                {
                    for (i=0; i<stop; )
                    {
                        plik.seek(i);
                        plik.read(static_cast<char *>(&wo_buf),sizeof(wo_buf));
                            if (wo_arr[y].ID == wo_buf.ID)
                            {
                                plik.seek(i);
                                plik.write(static_cast<char *>(&wo_arr[y]),sizeof(wo));
                            }

                        i = i + sizeof(wo);
                    }
                    if (add_new_wo)
                    {

                        int x;
                        x = (wo_arr.count()-1);
                        plik.seek(plik.size());
                        plik.write(static_cast<char *>(&wo_arr.[x]),sizeof(wo));
                        add_new_wo = false;
                    }
                }
            }

    }

    plik.close();
}

int MainWindow::GetRecC_WI(void)
{
    QFile plik(flm.pths.BF_WI);
    plik.open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
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
        plik.read(static_cast<char *>(&wi_t),sizeof(wi_t));
        rec_count = rec_count + 1;
        i = i + sizeof(wi_t);
    }
    plik.close();
    return rec_count;

}

int MainWindow::GetRecC_WO(void)
{
    QFile plik(flm.pths.BF_WO);
    plik.open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
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
        plik.read(static_cast<char *>(&wo_t),sizeof(wo_t));
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


    QFile plik(flm.pths.BF_WI);
    plik.open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        if (i == (stop - sizeof(wi)))
        {
            plik.read(static_cast<char *>(&wi),sizeof(wi));
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


    QFile plik(flm.pths.BF_WO);
    plik.open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        if (i == (stop - sizeof(wo)))
        {
            plik.read(static_cast<char *>(&wo),sizeof(wo));
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

void MainWindow::Usun_Rec_WI(LONGLONG pos)
{
        struct Wypozycz_Innym wi_src;
        wi.ID = 0;
        QFile plik(flm.pths.BF_WI);
        plik.open(QFile::ReadOnly);
        plik.seek(pos);
        plik.write(static_cast<char *>(&wi),sizeof(wi));

        plik.rename(flm.pths.BF_WI,(LPCTSTR)"BF_WI.bf0");

        plik.close();
        QFile plik(flm.pths.BF_WI);
        plik.Open(QFile::WriteOnly);
        QFile src_file((LPCTSTR)"BF_WI.bf0");
        src_file.open(QFile::ReadOnly);
        LONGLONG i;
        for (i = 0; i <(src_file.size()) ; )
        {
            src_file.seek(i);
            src_file.read(static_cast<char *>(&wi_src),sizeof(wi_src));
            if (wi_src.ID == 0)
            {
                i = i + sizeof(wi_src);
            }
            else
            {
                plik.write(static_cast<char *>(&wi_src),sizeof(wi_src));
                i = i + sizeof(wi_src);
            }
        }
        plik.close();
        src_file.remove();
        src_file.close();
        Fill_Wi();


}

void MainWindow::Usun_Rec_WO(LONGLONG pos)
{

        struct Wypozycz_Od_Innych wo_src;
        wo.ID = 0;
        QFile plik(flm.pths.BF_WO);
        plik.open(QFile::WriteOnly);
        plik.seek(pos);
        plik.write(static_cast<char *>(&wo),sizeof(wo));

        plik.rename(flm.pths.BF_WO,(LPCTSTR)"BF_WO.bf0");
        plik.close();

        QFile plik(flm.pths.BF_WO);
        plik.open(QFile::WriteOnly);
        QFile src_file((LPCTSTR)"BF_WO.bf0");
        src_file.Open(QFile::ReadOnly);
        LONGLONG i;
        for (i = 0; i <(src_file.size()) ; )
        {
            src_file.seek(i);
            src_file.read(static_cast<char *>(&wo_src),sizeof(wo_src));
            if (wo_src.ID == 0)
            {
                i = i + sizeof(wo_src);
            }
            else
            {
                plik.write(static_cast<char *>(&wo_src),sizeof(wo_src));
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

    QFile plik(flm.pths.BF_LZ);
    plik.open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
    stop = plik.size();


    ui->tableWidget_IOF_LZ->clearContents();
    lz_arr.clear();

    for (i = 0;i<stop ; )
    {
        plik.seek(i);
        plik.read(static_cast<char *>(&lz),sizeof(lz));
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
    QFile plik(flm.pths.BF_LZ);
    struct Lok_zdjeciowe lz_buf;
    plik.open(QFile::ReadWrite);

    LONGLONG stop;
    LONGLONG i;
    int y;

    wchar_t buff[34];
    stop = plik.size();

    for (y=0;y<lz_arr.count() ;y++ )
    {
        if (GetRecC_WI() == 0)
            {
                plik.seek(0);
                plik.write(static_cast<char *> (&lz_arr[y]),sizeof(lz));

            }
        else if (GetRecC_WI() > 0)
            {
                if ((plik.size()) > 2147483647)
                {
                    QMessageBox(QMessageBox::Warning,L"Biblioteka Filmów",L"Nie można więcej zapisywać do tego pliku - jest przepełniony !!! ",QMessageBox::Ok);
                    break;
                }
                else if ((plik.size()) < 2147483647)
                {
                    for (i=0; i<stop; )
                    {
                        plik.seek(i);
                        plik.read(static_cast<char *>(&lz_buf),sizeof(lz_buf));
                            if (lz_arr[y].ID == lz_buf.ID)
                            {
                                plik.seek(i);
                                plik.write(static_cast<char *>(&lz_arr[y]),sizeof(lz));
                            }

                        i = i + sizeof(lz);
                    }
                    if (add_new_lz)
                    {

                        int x;
                        x = (lz_arr.count()-1);
                        plik.seek(plik.size());
                        plik.write(static_cast<char *>(&lz_arr[x]),sizeof(lz));
                        add_new_lz = false;
                    }
                }
            }

    }

    plik.close();


}

int MainWindow::GetRecC_LZ(void)
{
    QFile plik(flm.pths.BF_LZ);
    plik.open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
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
        plik.read(static_cast<char *>(&lz_t),sizeof(lz_t));
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


    QFile plik(flm.pths.BF_LZ);
    plik.open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        if (i == (stop - sizeof(lz)))
        {
            plik.read(static_cast<char *>(&lz),sizeof(lz));
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
    lz.IDPDB = flm_i.film_tbl.ID;
    wcscpy(lz.nazwa_obiektu,L"Wpisz tutaj coś");
    wcscpy(lz.kraj,L"Wpisz tutaj coś");
    wcscpy(lz.miejscowosc,L"Wpisz tutaj coś");
    wcscpy(lz.region,L"Wpisz tutaj coś");
    wcscpy(lz.pora_roku,L"Wpisz tutaj coś");
    wcscpy(lz.data,L"Wpisz tutaj coś");

    lz_arr.append(lz);

    Refresh_Lz();

}

void MainWindow::Usun_Rec_LZ(LONGLONG pos)
{
    struct Lok_zdjeciowe lz_src;
    lz.ID = 0;
    QFile plik(flm.pths.BF_LZ);
    plik.open(QFile::ReadOnly);
    plik.seek(pos);
    plik.write(static_cast<char *>(&lz),sizeof(lz));

    plik.rename(flm.pths.BF_LZ,(LPCTSTR)"BF_LZ.bf0");

    plik.close();
    QFile plik(flm.pths.BF_LZ);
    plik.Open(QFile::WriteOnly);
    QFile src_file((LPCTSTR)"BF_LZ.bf0");
    src_file.open(QFile::ReadOnly);
    LONGLONG i;
    for (i = 0; i <(src_file.size()) ; )
    {
        src_file.seek(i);
        src_file.read(static_cast<char *>(&lz_src),sizeof(lz_src));
        if (lz_src.ID == 0)
        {
            i = i + sizeof(lz_src);
        }
        else
        {
            plik.write(static_cast<char *>(&lz_src),sizeof(lz_src));
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
    QFile plik(flm.pths.BF_OB);
    plik.open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
    stop = plik.size();


    ui->tableWidget_Obsada->clearContents();
    ob_arr.clear();

    for (i = 0;i<stop ; )
    {
        plik.seek(i);
        plik.read(static_cast<char *>(&ob),sizeof(ob));
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
    QFile plik(flm.pths.BF_OB);
    struct Obsada ob_buf;
    plik.open(QFile::ReadWrite);

    LONGLONG stop;
    LONGLONG i;
    int y;

    wchar_t buff[34];
    stop = plik.size();

    for (y=0;y<ob_arr.count() ;y++ )
    {
        if (GetRecC_OB() == 0)
            {
                plik.seek(0);
                plik.write(static_cast<char *> (&ob_arr[y]),sizeof(ob));

            }
        else if (GetRecC_OB() > 0)
            {
                if ((plik.size()) > 2147483647)
                {
                    QMessageBox(QMessageBox::Warning,L"Biblioteka Filmów",L"Nie można więcej zapisywać do tego pliku - jest przepełniony !!! ",QMessageBox::Ok);
                    break;
                }
                else if ((plik.size()) < 2147483647)
                {
                    for (i=0; i<stop; )
                    {
                        plik.seek(i);
                        plik.read(static_cast<char *>(&ob_buf),sizeof(ob_buf));
                            if (ob_arr[y].ID == ob_buf.ID)
                            {
                                plik.seek(i);
                                plik.write(static_cast<char *>(&ob_arr[y]),sizeof(ob));
                            }

                        i = i + sizeof(ob);
                    }
                    if (add_new_ob)
                    {

                        int x;
                        x = (ob_arr.count()-1);
                        plik.seek(plik.size());
                        plik.write(static_cast<char *>(&ob_arr[x]),sizeof(ob));
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


    QFile plik(flm.pths.BF_OB);
    plik.open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        if (i == (stop - sizeof(ob)))
        {
            plik.read(static_cast<char *>(&ob),sizeof(ob));
            plik.close();
            return ob.ID;
        }
        i = i + sizeof(ob);
    }

}

int MainWindow::GetRecC_OB(void)
{
    QFile plik(flm.pths.BF_OB);
    plik.open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
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
        plik.read(static_cast<char *>(&ob_t),sizeof(ob_t));
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

        item->setText(ob_arr[x].imie_nazw);
        ui->tableWidget_Obsada->setItem(x,0,item);

        item->setText(ob_arr[x].rola);
        ui->tableWidget_Obsada->setItem(x,1,item);

        item->setText(ob_arr[x].ID);
        ui->tableWidget_Obsada->setItem(x,2,item);

        item->setText(ob_arr[x].IDPDB);
        ui->tableWidget_Obsada->setItem(x,2,item);

    }

}

void MainWindow::Usun_Rec_OB(LONGLONG pos)
{
    struct Obsada ob_src;
    ob.ID = 0;
    QFile plik(flm.pths.BF_OB);
    plik.open(QFile::ReadOnly);
    plik.seek(pos);
    plik.write(static_cast<char *>(&ob),sizeof(ob));

    plik.rename(flm.pths.BF_OB,(LPCTSTR)"BF_OB.bf0");

    plik.close();
    QFile plik(flm.pths.BF_OB);
    plik.Open(QFile::WriteOnly);
    QFile src_file((LPCTSTR)"BF_OB.bf0");
    src_file.open(QFile::ReadOnly);
    LONGLONG i;
    for (i = 0; i <(src_file.size()) ; )
    {
        src_file.seek(i);
        src_file.read(static_cast<char *>(&ob_src),sizeof(ob_src));
        if (ob_src.ID == 0)
        {
            i = i + sizeof(ob_src);
        }
        else
        {
            plik.write(static_cast<char *>(&ob_src),sizeof(ob_src));
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

    QFile plik(flm.pths.BF_OC);
    struct Ocena oc_buf;
    plik.open(QFile::ReadWrite);

    LONGLONG stop;
    LONGLONG i;
    int y;

    wchar_t buff[34];
    stop = plik.size();

    for (y=0;y<oc_arr.count() ;y++ )
    {
        if (GetRecC_OC() == 0)
            {
                plik.seek(0);
                plik.write(static_cast<char *> (&oc_arr[y]),sizeof(oc));

            }
        else if (GetRecC_OC() > 0)
            {
                if ((plik.size()) > 2147483647)
                {
                    QMessageBox(QMessageBox::Warning,L"Biblioteka Filmów",L"Nie można więcej zapisywać do tego pliku - jest przepełniony !!! ",QMessageBox::Ok);
                    break;
                }
                else if ((plik.size()) < 2147483647)
                {
                    for (i=0; i<stop; )
                    {
                        plik.seek(i);
                        plik.read(static_cast<char *>(&oc_buf),sizeof(oc_buf));
                            if (oc_arr[y].ID == ob_buf.ID)
                            {
                                plik.seek(i);
                                plik.write(static_cast<char *>(&oc_arr[y]),sizeof(oc));
                            }

                        i = i + sizeof(ob);
                    }
                    if (add_new_oc)
                    {

                        int x;
                        x = (oc_arr.count()-1);
                        plik.seek(plik.size());
                        plik.write(static_cast<char *>(&oc_arr[x]),sizeof(oc));
                        add_new_oc = false;
                    }
                }
            }

    }

    plik.close();



}

void MainWindow::Fill_Oc(bool nie_kas)
{
// ta i podobne procedury odczytuja plik bd danej tabeli i sprawdzaja czy idpdb sie zgadza z polem if flm_o.film_tbl
// a jesli tak to pobieraja z pliku do tabeli struktur zawierajacej dane z jednego pola listy form. film dla jednego
// rekordu, jesli nie ida dalej wzdluz pliku do jego konca..

    QFile plik(flm.pths.BF_OC);
    plik.open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
    stop = plik.size();


    ui->tableWidget_OC->clearContents();
    oc_arr.clear();

    for (i = 0;i<stop ; )
    {
        plik.seek(i);
        plik.read(static_cast<char *>(&oc),sizeof(oc));
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

QFile plik(flm.pths.BF_OC);
plik.open(QFile::ReadOnly);
LONGLONG i;
LONGLONG stop;
stop = plik.size();
for (i=0;i<stop; )
{
    plik.seek(i);
    if (i == (stop - sizeof(oc)))
    {
        plik.read(static_cast<char *>(&oc),sizeof(oc));
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
    oc.IDPDB = flm_o.film_tbl.ID;
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
    QFile plik(flm.pths.BF_OC);
    plik.open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
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
        plik.read(static_cast<char *>(&oc_t),sizeof(oc_t));
        rec_count = rec_count + 1;
        i = i + sizeof(oc_t);
    }
    plik.close();
    return rec_count;



}

void MainWindow::Usun_Rec_OC(LONGLONG pos)
{


    struct Ocena oc_src;
    oc.ID = 0;
    QFile plik(flm.pths.BF_OC);
    plik.open(QFile::ReadOnly);
    plik.seek(pos);
    plik.write(static_cast<char *>(&oc),sizeof(oc));

    plik.rename(flm.pths.BF_OC,(LPCTSTR)"BF_OC.bf0");

    plik.close();
    QFile plik(flm.pths.BF_OC);
    plik.Open(QFile::WriteOnly);
    QFile src_file((LPCTSTR)"BF_OC.bf0");
    src_file.open(QFile::ReadOnly);
    LONGLONG i;
    for (i = 0; i <(src_file.size()) ; )
    {
        src_file.seek(i);
        src_file.read(static_cast<char *>(&oc_src),sizeof(oc_src));
        if (oc_src.ID == 0)
        {
            i = i + sizeof(oc_src);
        }
        else
        {
            plik.write(static_cast<char *>(&oc_src),sizeof(oc_src));
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

        item->setText(oc_arr[x].nazwa);
        ui->tableWidget_OC->setItem(x,0,item);

        item->setText(oc_arr[x].tytul_tekstu);
        ui->tableWidget_OC->setItem(x,1,item);

        item->setText(oc_arr[x].autor_tekstu);
        ui->tableWidget_OC->setItem(x,2,item);

        item->setText(oc_arr[x].strona_www);
        ui->tableWidget_OC->setItem(x,3,item);

        item->setText(oc_arr[x].ocena_krytyka);
        ui->tableWidget_OC->setItem(x,4,item);

        item->setText(oc_arr[x].ID);
        ui->tableWidget_OC->setItem(x,5,item);

        item->setText(oc_arr[x].IDPDB);
        ui->tableWidget_OC->setItem(x,6,item);

    }
}

void TAB_Produkcja::ClearProd(void)
{
TAB_Prod_LIST_Prod.DeleteAllItems();

}

void TAB_Produkcja::ClearDystr(void)
{
TAB_Prod_LIST_Dystr.DeleteAllItems();

}

void TAB_Produkcja::Fill_PP(void)
{
CFile plik;
plik.Open(flm_p.pths.BF_PRP,CFile::modeRead);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();


TAB_Prod_LIST_Prod.DeleteAllItems();
pp_arr.RemoveAll();



for (i = 0;i<stop ; )
{
    plik.Seek(i,CFile::begin);
    plik.Read(&pp,sizeof(pp));
    if (pp.IDPDB == flm_p.film_tbl.ID)
    {
        pp_arr.Add(pp);

    }
    i = i + sizeof(pp);
}
plik.Close();

Refresh_PP();

}

void TAB_Produkcja::Fill_PD(void)
{
CFile plik;
plik.Open(flm_p.pths.BF_PRD,CFile::modeRead);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();


TAB_Prod_LIST_Dystr.DeleteAllItems();
pd_arr.RemoveAll();



for (i = 0;i<stop ; )
{
    plik.Seek(i,CFile::begin);
    plik.Read(&pd,sizeof(pd));
    if (pd.IDPDB == flm_p.film_tbl.ID)
    {
        pd_arr.Add(pd);

    }
    i = i + sizeof(pd);
}
plik.Close();

Refresh_PD();

}



void TAB_Produkcja::Refresh_PP(void)
{

TAB_Prod_LIST_Prod.DeleteAllItems();

    int x;
    for (x=0;x<pp_arr.GetCount(); x++)
    {
        LVITEM lvitm;
        lvitm.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
        lvitm.iItem = x;
        lvitm.iSubItem = 0;
        lvitm.state = 0;
        lvitm.stateMask = 0;
        lvitm.lParam = (LPARAM) &pp_arr.GetAt(x);
        lvitm.pszText = LPSTR_TEXTCALLBACK;
        TAB_Prod_LIST_Prod.InsertItem(&lvitm);
    }

}

void TAB_Produkcja::Refresh_PD(void)
{
TAB_Prod_LIST_Dystr.DeleteAllItems();

    int x;
    for (x=0;x<pd_arr.GetCount(); x++)
    {
        LVITEM lvitm;
        lvitm.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
        lvitm.iItem = x;
        lvitm.iSubItem = 0;
        lvitm.state = 0;
        lvitm.stateMask = 0;
        lvitm.lParam = (LPARAM) &pd_arr.GetAt(x);
        lvitm.pszText = LPSTR_TEXTCALLBACK;
        TAB_Prod_LIST_Dystr.InsertItem(&lvitm);
    }



}



void TAB_Produkcja::OnBnClickedButtonFrmFPProdNowy()
{

    Save_PP();
    Add_New_PP(Get_Hi_ID_PP());
    add_new_pp = true;



}



void TAB_Produkcja::OnBnClickedButtonFrmFPProdZapisz()
{
    Save_PP();
}

void TAB_Produkcja::OnBnClickedButtonFrmFPProdUsun()
{
wchar_t buff[34];
LVITEM lvitm;
int delitem = 0;
int delID = 0;
delitem = TAB_Prod_LIST_Prod.GetNextItem(-1,LVNI_SELECTED);
TAB_Prod_LIST_Prod.GetItemText(delitem,7,(LPTSTR)buff,34);
delID = _wtoi(buff);

CFile plik;
plik.Open(flm_p.pths.BF_PRP,CFile::modeRead | CFile::shareDenyNone);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
for (i=0;i<stop; )
{
    plik.Seek(i,CFile::begin);
    plik.Read(&pp,sizeof(pp));
    if (delID == pp.ID)
    {
    plik.Close();
    Usun_Rec_PP(i);
    break;
    }
    i = i + sizeof(pp);
}
if (plik.m_hFile != CFile::hFileNull)
{
    plik.Close();
}
}



void TAB_Produkcja::OnBnClickedButtonFrmFPDystrNowy()
{

    Save_PD();
    Add_New_PD(Get_Hi_ID_PD());
    add_new_pd = true;
}



void TAB_Produkcja::OnBnClickedButtonFrmFPDystrZapisz()
{
    Save_PD();
}

void TAB_Produkcja::OnBnClickedButtonFrmFPDystrUsun()
{
wchar_t buff[34];
LVITEM lvitm;
int delitem = 0;
int delID = 0;
delitem = TAB_Prod_LIST_Dystr.GetNextItem(-1,LVNI_SELECTED);
TAB_Prod_LIST_Dystr.GetItemText(delitem,7,(LPTSTR)buff,34);
delID = _wtoi(buff);

CFile plik;
plik.Open(flm_p.pths.BF_PRD,CFile::modeRead | CFile::shareDenyNone);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
for (i=0;i<stop; )
{
    plik.Seek(i,CFile::begin);
    plik.Read(&pd,sizeof(pd));
    if (delID == pd.ID)
    {
    plik.Close();
    Usun_Rec_PD(i);
    break;
    }
    i = i + sizeof(pd);
}
if (plik.m_hFile != CFile::hFileNull)
{
    plik.Close();
}

}



void TAB_Produkcja::Save_PP(void)
{
    CFile plik;
    struct Producent pp_buf;
    plik.Open(flm_p.pths.BF_PRP,CFile::modeReadWrite | CFile::shareDenyNone);

    LONGLONG stop;
    LONGLONG i;
    int y;

    wchar_t buff[34];
    stop = plik.SeekToEnd();

    for (y=0;y<pp_arr.GetCount() ;y++ )
    {
        if (GetRecC_PP() == 0)
            {
                plik.Seek(0,CFile::begin);
                plik.Write(&pp_arr.GetAt(y),sizeof(pp));

            }
        else if (GetRecC_PP() > 0)
            {
                if ((plik.SeekToEnd()) > 2147483647)
                {
                    MessageBoxW(L"Nie można więcej zapisywać do tego pliku - jest przepełniony !!! ",L"Biblioteka Filmów - Błąd zapisu",MB_OK);
                    break;
                }
                else if ((plik.SeekToEnd()) < 2147483647)
                {
                    for (i=0; i<stop; )
                    {
                        plik.Seek(i,CFile::begin);
                        plik.Read(&pp_buf,sizeof(pp_buf));
                            if (pp_arr.GetAt(y).ID == pp_buf.ID)
                            {
                                plik.Seek(i,CFile::begin);
                                plik.Write(&pp_arr.GetAt(y),sizeof(pp));
                            }

                        i = i + sizeof(pp);
                    }
                    if (add_new_pp)
                    {

                        int x;
                        x = (pp_arr.GetCount()-1);
                        plik.Seek((plik.SeekToEnd()),CFile::begin);
                        plik.Write(&pp_arr.GetAt(x),sizeof(pp));
                        add_new_pp = false;
                    }
                }
            }

    }

    plik.Close();



}

void TAB_Produkcja::Save_PD(void)
{

    CFile plik;
    struct Dystrybutor pd_buf;
    plik.Open(flm_p.pths.BF_PRD,CFile::modeReadWrite | CFile::shareDenyNone);

    LONGLONG stop;
    LONGLONG i;
    int y;

    wchar_t buff[34];
    stop = plik.SeekToEnd();

    for (y=0;y<pd_arr.GetCount() ;y++ )
    {
        if (GetRecC_PD() == 0)
            {
                plik.Seek(0,CFile::begin);
                plik.Write(&pd_arr.GetAt(y),sizeof(pd));

            }
        else if (GetRecC_PD() > 0)
            {
                if ((plik.SeekToEnd()) > 2147483647)
                {
                    MessageBoxW(L"Nie można więcej zapisywać do tego pliku - jest przepełniony !!! ",L"Biblioteka Filmów - Błąd zapisu",MB_OK);
                    break;
                }
                else if ((plik.SeekToEnd()) < 2147483647)
                {
                    for (i=0; i<stop; )
                    {
                        plik.Seek(i,CFile::begin);
                        plik.Read(&pd_buf,sizeof(pd_buf));
                            if (pd_arr.GetAt(y).ID == pd_buf.ID)
                            {
                                plik.Seek(i,CFile::begin);
                                plik.Write(&pd_arr.GetAt(y),sizeof(pd));
                            }

                        i = i + sizeof(pd);
                    }
                    if (add_new_pd)
                    {

                        int x;
                        x = (pd_arr.GetCount()-1);
                        plik.Seek((plik.SeekToEnd()),CFile::begin);
                        plik.Write(&pd_arr.GetAt(x),sizeof(pd));
                        add_new_pd = false;
                    }
                }
            }

    }

    plik.Close();

}

void TAB_Produkcja::Add_New_PP(int id)
{
int id_new;
id_new = id + 1;
wchar_t buff[34];


// Metoda callbacku
pp.ID = id_new;
pp.IDPDB = flm_p.film_tbl.ID;
wcscpy(pp.nazwa_firmy,L"Wpisz tutaj coś");
wcscpy(pp.adres,L"Wpisz tutaj coś");
wcscpy(pp.telefon,L"Wpisz tutaj coś");
wcscpy(pp.fax,L"Wpisz tutaj coś");
wcscpy(pp.email,L"Wpisz tutaj coś");
wcscpy(pp.strona_www,L"Wpisz tutaj coś");
wcscpy(pp.narodowosc,L"Wpisz tutaj coś");


pp_arr.Add(pp);

Refresh_PP();

}

void TAB_Produkcja::Add_New_PD(int id)
{
int id_new;
id_new = id + 1;
wchar_t buff[34];


// Metoda callbacku
pd.ID = id_new;
pd.IDPDB = flm_p.film_tbl.ID;
wcscpy(pd.nazwa_firmy,L"Wpisz tutaj coś");
wcscpy(pd.adres,L"Wpisz tutaj coś");
wcscpy(pd.telefon,L"Wpisz tutaj coś");
wcscpy(pd.fax,L"Wpisz tutaj coś");
wcscpy(pd.email,L"Wpisz tutaj coś");
wcscpy(pd.strona_www,L"Wpisz tutaj coś");
wcscpy(pd.narodowosc,L"Wpisz tutaj coś");


pd_arr.Add(pd);

Refresh_PD();


}

int TAB_Produkcja::Get_Hi_ID_PP(void)
{
if (GetRecC_PP() == 0)
{
    return 0;
}


CFile plik;
plik.Open(flm_p.pths.BF_PRP,CFile::modeRead);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
for (i=0;i<stop; )
{
    plik.Seek(i,CFile::begin);
    if (i == (stop - sizeof(pp)))
    {
        plik.Read(&pp,sizeof(pp));
        plik.Close();
        return pp.ID;
    }
    i = i + sizeof(pp);
}

}

int TAB_Produkcja::Get_Hi_ID_PD(void)
{

if (GetRecC_PD() == 0)
{
    return 0;
}


CFile plik;
plik.Open(flm_p.pths.BF_PRD,CFile::modeRead);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
for (i=0;i<stop; )
{
    plik.Seek(i,CFile::begin);
    if (i == (stop - sizeof(pd)))
    {
        plik.Read(&pd,sizeof(pd));
        plik.Close();
        return pd.ID;
    }
    i = i + sizeof(pd);
}

}

int TAB_Produkcja::GetRecC_PP(void)
{
CFile plik;
plik.Open(flm_p.pths.BF_PRP,CFile::modeRead | CFile::shareDenyNone);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
int rec_count = 0;
struct Producent pp_t;
if (stop == 0)
{
    plik.Close();
    return 0;
}
    for (i = 0; i <stop; )
    {
        plik.Seek(i,CFile::begin);
        plik.Read(&pp_t,sizeof(pp_t));
        rec_count = rec_count + 1;
        i = i + sizeof(pp_t);
    }
    plik.Close();
return rec_count;


}

int TAB_Produkcja::GetRecC_PD(void)
{
CFile plik;
plik.Open(flm_p.pths.BF_PRD,CFile::modeRead | CFile::shareDenyNone);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
int rec_count = 0;
struct Dystrybutor pd_t;
if (stop == 0)
{
    plik.Close();
    return 0;
}
    for (i = 0; i <stop; )
    {
        plik.Seek(i,CFile::begin);
        plik.Read(&pd_t,sizeof(pd_t));
        rec_count = rec_count + 1;
        i = i + sizeof(pd_t);
    }
    plik.Close();
return rec_count;


}

void TAB_Produkcja::Usun_Rec_PP(LONGLONG pos)
{
        struct Producent pp_src;
        pp.ID = 0;
        CFile plik;
        plik.Open(flm_p.pths.BF_PRP,CFile::modeWrite | CFile::shareDenyNone);
        plik.Seek(pos,CFile::begin);
        plik.Write(&pp,sizeof(pp));
        plik.Close();

        CFile::Rename(flm_p.pths.BF_PRP,(LPCTSTR)"BF_PRB.bf0");

        plik.Open(flm_p.pths.BF_PRP,CFile::modeCreate);
        plik.Close();
        CFile src_file;
        src_file.Open((LPCTSTR)"BF_PRB.bf0",CFile::modeRead);
        plik.Open(flm_p.pths.BF_PRP,CFile::modeWrite);
        LONGLONG i;
        for (i = 0; i <(src_file.SeekToEnd()) ; )
        {
            src_file.Seek(i,CFile::begin);
            src_file.Read(&pp_src,sizeof(pp_src));
            if (pp_src.ID == 0)
            {
                i = i + sizeof(pp_src);
            }
            else
            {
                plik.Write(&pp_src,sizeof(pp_src));
                i = i + sizeof(pp_src);
            }
        }
        plik.Close();
        src_file.Close();
        CFile::Remove((LPCTSTR)"BF_PRB.bf0");
        Fill_PP();


}

void TAB_Produkcja::Usun_Rec_PD(LONGLONG pos)
{
        struct Dystrybutor pd_src;
        pd.ID = 0;
        CFile plik;
        plik.Open(flm_p.pths.BF_PRD,CFile::modeWrite | CFile::shareDenyNone);
        plik.Seek(pos,CFile::begin);
        plik.Write(&pd,sizeof(pd));
        plik.Close();

        CFile::Rename(flm_p.pths.BF_PRD,(LPCTSTR)"BF_PRD.bf0");

        plik.Open(flm_p.pths.BF_PRD,CFile::modeCreate);
        plik.Close();
        CFile src_file;
        src_file.Open((LPCTSTR)"BF_PRD.bf0",CFile::modeRead);
        plik.Open(flm_p.pths.BF_PRD,CFile::modeWrite);
        LONGLONG i;
        for (i = 0; i <(src_file.SeekToEnd()) ; )
        {
            src_file.Seek(i,CFile::begin);
            src_file.Read(&pd_src,sizeof(pd_src));
            if (pd_src.ID == 0)
            {
                i = i + sizeof(pd_src);
            }
            else
            {
                plik.Write(&pd_src,sizeof(pd_src));
                i = i + sizeof(pd_src);
            }
        }
        plik.Close();
        src_file.Close();
        CFile::Remove((LPCTSTR)"BF_PRD.bf0");
        Fill_PD();



}

void MainWindow::on_actionOtw_rz_Utw_rz_baze_danych_triggered()
{
    CString buffCSTR;
    BROWSEINFO dir_info;
    dir_info.hwndOwner = NULL;
    dir_info.pidlRoot = NULL;
    dir_info.lpszTitle = TEXT("Podaj katalog z bazą danych w formacie Biblioteka Filmów lub utwórz katalog na nową bazę danych i wskaż go");
    dir_info.ulFlags = NULL;
    open_folder = false;
    if (theApp.GetShellManager()->BrowseForFolder(buffCSTR, this, NULL,TEXT("Podaj katalog z bazą danych w formacie Biblioteka Filmów lub utwórz katalog na nową bazę danych i wskaż go"),BIF_NEWDIALOGSTYLE))
    {
        int cstr_size = buffCSTR.GetLength() + 1;
        char *chr = new char[cstr_size];
        wchar_t *buff = new wchar_t[cstr_size];
        _tcscpy_s(buff,cstr_size,buffCSTR);
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
    TCHAR szFiltr[] = _T("Pliki graficzne (*.bmp)|*.bmp| (*.jpg)|*.jpg| (*.jpeg)|*.jpeg| (*.png)|*.png||");
    CFileDialog plik_dlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST | OFN_NONETWORKBUTTON,szFiltr);
    if (plik_dlg.DoModal() == IDOK)
    {
        //plik_dlg.DoModal();
        CString plk_path = plik_dlg.GetPathName();
        CString buff;

        buff = flm.pths.BF_COVERS;
        buff = buff + plik_dlg.GetFileName();

        CopyFile(plk_path,buff,FALSE);
        _tcscpy(flm.film_tbl.skan_przod_path,buff);
        CBibliotekaFilmówDlg::OnBnClickedButtonFrmFSave();
    }
}

void MainWindow::on_pushButton_DelPic_clicked()
{
    if (!(CBibliotekaFilmówDlg::Licz_Rec()))
    {
        _tcscpy(flm.film_tbl.skan_przod_path,_TEXT(""));
        CBibliotekaFilmówDlg::OnBnClickedButtonFrmFSave();

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

    QFile plik(flm.pths.BF_WI);
    plik.Open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        plik.read(static_cast<char *>(&wi),sizeof(wi));
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

    QFile plik(flm.pths.BF_WO);
    plik.Open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        plik.read(static_cast<char *>(&wo),sizeof(wo));
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

    QFile plik(flm.pths.BF_LZ);
    plik.Open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        plik.read(static_cast<char *>(&lz),sizeof(lz));
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

    QFile plik(flm.pths.BF_OB);
    plik.open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        plik.read(static_cast<char *>(&ob),sizeof(ob));
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

        item->setText(lz_arr[x].nazwa_obiektu);
        ui->tableWidget_IOF_LZ->setItem(x,0,item);

        item->setText(lz_arr[x].kraj);
        ui->tableWidget_IOF_LZ->setItem(x,1,item);

        item->setText(lz_arr[x].miejscowosc);
        ui->tableWidget_IOF_LZ->setItem(x,2,item);

        item->setText(lz_arr[x].region);
        ui->tableWidget_IOF_LZ->setItem(x,3,item);

        item->setText(lz_arr[x].pora_roku);
        ui->tableWidget_IOF_LZ->setItem(x,4,item);

        item->setText(lz_arr[x].data);
        ui->tableWidget_IOF_LZ->setItem(x,5,item);

        item->setText(lz_arr[x].ID);
        ui->tableWidget_IOF_LZ->setItem(x,6,item);

        item->setText(lz_arr[x].IDPDB);
        ui->tableWidget_IOF_LZ->setItem(x,7,item);

    }


}

void MainWindow::on_pushButton_OC_New_clicked()
{
    Save_Oc();
    Add_New_Oc(Get_Hi_ID_OC());
    add_new = true;
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

    QFile plik(flm.pths.BF_OC);
    plik.open(QFile::ReadOnly);
    LONGLONG i;
    LONGLONG stop;
    stop = plik.size();
    for (i=0;i<stop; )
    {
        plik.seek(i);
        plik.read(static_cast<char *>(&oc),sizeof(oc));
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
