#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QFile>
#include <QDir>

struct Film Ftbl::film_tbl;    // struktura mieszczaca jeden rekord form film
bool Ftbl::sort = false;
struct DB_paths Ftbl::pths;

Ftbl flm;

unsigned int sort_idx = 0; // zmienna pomocnicza slużaca do poruszania sie po indeksie film_tbl_wsk
LONGLONG zadana_pozycja_pliku = 0; // pozycja rekordu w BF_PDB
ULONGLONG akt_pozycja_pliku = 0; // pozycja rekordu w BF_PDB

wchar_t akt_BF_VER[16] = L"1.0.6.0";
bool first_act = true;
bool start = true; // oznacza czy aplikacja startuje;
bool open_folder = false;

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
        _spawnl(_P_NOWAIT,"MK_AUTOUPDATE.exe","MK_AUTOUPDATE.exe",NULL);

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
        F_EDIT_ID.SetReadOnly(FALSE);
        _itow(flm.film_tbl.ID,dest,10); // tu jest problem - access violation
        F_EDIT_ID.SetWindowTextW(dest); // tu jest problem BEX
        F_EDIT_ID.SetReadOnly(TRUE);
        F_EDIT_Tytul.SetWindowTextW((LPCTSTR)flm.film_tbl.tytul);
        F_EDIT_TytulOryg.SetWindowTextW((LPCTSTR)flm.film_tbl.oryginalny_tytul);
        Frm_F_ComboBox_Gatunek.SetWindowTextW((LPCTSTR)flm.film_tbl.gatunek_filmu);

        CFileStatus status;
        //CImage pic_buff;
        RECT okl_rect;
        CString no_img;
        no_img = flm.pths.BF_COVERS;
        no_img = no_img + _TEXT("no_img.bmp");

        /*this->FRM_F_DOE_OKL_PRZOD.GetDC()->Detach();
        this->FRM_F_DOE_STATIC_OKL_TYL.GetDC()->Detach();*/
        if (_tcscmp(flm.film_tbl.skan_przod_path,_TEXT("")) != 0)
        {
            if (CFile::GetStatus(flm.film_tbl.skan_przod_path,status))
            {
                CImage pic_buff;
                pic_buff.Load(flm.film_tbl.skan_przod_path);
                this->FRM_F_DOE_OKL_PRZOD.GetClientRect(&okl_rect);
                SetStretchBltMode(this->FRM_F_DOE_OKL_PRZOD.GetDC()->m_hDC,HALFTONE);
                SetBrushOrgEx(this->FRM_F_DOE_OKL_PRZOD.GetDC()->m_hDC,0,0,NULL);
                pic_buff.StretchBlt(this->FRM_F_DOE_OKL_PRZOD.GetDC()->m_hDC,okl_rect,SRCCOPY);
                //pic_buff.ReleaseDC();

            }
        }
        else
        {
            CImage pic_buff;
            pic_buff.LoadFromResource(theApp.m_hInstance,MAKEINTRESOURCE(IDB_BITMAP2));
            this->FRM_F_DOE_OKL_PRZOD.GetClientRect(&okl_rect);
            SetStretchBltMode(this->FRM_F_DOE_OKL_PRZOD.GetDC()->m_hDC,HALFTONE);
            SetBrushOrgEx(this->FRM_F_DOE_OKL_PRZOD.GetDC()->m_hDC,0,0,NULL);
            pic_buff.StretchBlt(this->FRM_F_DOE_OKL_PRZOD.GetDC()->m_hDC,okl_rect,SRCCOPY);
            //pic_buff.ReleaseDC();


        }
        if (_tcscmp(flm.film_tbl.skan_tyl_path,_TEXT("")) != 0)
        {
            if (CFile::GetStatus(flm.film_tbl.skan_tyl_path,status))
            {
                CImage pic_buff;
                pic_buff.Load(flm.film_tbl.skan_tyl_path);
                this->FRM_F_DOE_STATIC_OKL_TYL.GetClientRect(&okl_rect);
                SetStretchBltMode(this->FRM_F_DOE_OKL_PRZOD.GetDC()->m_hDC,HALFTONE);
                SetBrushOrgEx(this->FRM_F_DOE_OKL_PRZOD.GetDC()->m_hDC,0,0,NULL);
                pic_buff.StretchBlt(this->FRM_F_DOE_STATIC_OKL_TYL.GetDC()->m_hDC,okl_rect,SRCCOPY);



            }
        }
        else
        {
            CImage pic_buff;
            pic_buff.LoadFromResource(theApp.m_hInstance,MAKEINTRESOURCE(IDB_BITMAP2));
            this->FRM_F_DOE_STATIC_OKL_TYL.GetClientRect(&okl_rect);
            SetStretchBltMode(this->FRM_F_DOE_OKL_PRZOD.GetDC()->m_hDC,HALFTONE);
            SetBrushOrgEx(this->FRM_F_DOE_OKL_PRZOD.GetDC()->m_hDC,0,0,NULL);
            pic_buff.StretchBlt(this->FRM_F_DOE_STATIC_OKL_TYL.GetDC()->m_hDC,okl_rect,SRCCOPY);



        }

        /*this->FRM_F_DOE_OKL_PRZOD.ReleaseDC(this->FRM_F_DOE_OKL_PRZOD.GetDC());
        this->FRM_F_DOE_STATIC_OKL_TYL.ReleaseDC(this->FRM_F_DOE_STATIC_OKL_TYL.GetDC());*/

        //TAB OCENA

        tab_oc->TAB_O_Edit_SD.SetWindowTextW((LPCTSTR)flm.film_tbl.WOF_sciezka_dz);
        tab_oc->TAB_O_Edit_Obsada.SetWindowTextW((LPCTSTR)flm.film_tbl.WOF_obsada);
        tab_oc->TAB_O_Edit_Zdjecia.SetWindowTextW((LPCTSTR)flm.film_tbl.WOF_zdjecia);
        tab_oc->TAB_O_Edit_WArt.SetWindowTextW((LPCTSTR)flm.film_tbl.WOF_w_art);
        tab_oc->TAB_O_Edit_Calosc.SetWindowTextW((LPCTSTR)flm.film_tbl.WOF_calosc);

        // TAB OBSADA
        tab_ob->TAB_OB_Edit_Rez_ImieNazw.SetWindowTextW((LPCTSTR)flm.film_tbl.O_rezyser_imie_nazw);
        tab_ob->TAB_OB_Edit_Rez_Narod.SetWindowTextW((LPCTSTR)flm.film_tbl.O_rezyser_narod);
        tab_ob->TAB_OB_Edit_Scen_ImieNazw.SetWindowTextW((LPCTSTR)flm.film_tbl.O_scenariusz_imie_nazw);
        tab_ob->TAB_OB_Edit_Scen_Narod.SetWindowTextW((LPCTSTR)flm.film_tbl.O_scenariusz_narod);
        tab_ob->TAB_OB_Edit_Zdj_ImieNazw.SetWindowTextW((LPCTSTR)flm.film_tbl.O_operator_imie_nazw);
        tab_ob->TAB_OB_Edit_Zdj_Narod.SetWindowTextW((LPCTSTR)flm.film_tbl.O_operator_narod);
        tab_ob->TAB_OB_Edit_Muz_ImieNazw.SetWindowTextW((LPCTSTR)flm.film_tbl.O_muzyka_imie_nazw);
        tab_ob->TAB_OB_Edit_Muz_Narod.SetWindowTextW((LPCTSTR)flm.film_tbl.O_muzyka_narod);

        // TAB PRODUKCJA


        // TAB DOE
        tab_doe->TAB_DOE_EDIT_W_Imie.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_WKF_imie);
        tab_doe->TAB_DOE_EDIT_W_Nazw.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_WKF_nazwisko);
        tab_doe->TAB_DOE_EDIT_W_Adres.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_WKF_adres);
        tab_doe->TAB_DOE_EDIT_MN_Nazwa.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_MN_nazwa);
        tab_doe->TAB_DOE_EDIT_MN_Adres.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_MN_adres);
        tab_doe->TAB_DOE_EDIT_MN_WWW.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_MN_www);
        tab_doe->TAB_DOE_EDIT_MN_Tel.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_MN_telefon);
        tab_doe->TAB_DOE_EDIT_MN_Fax.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_MN_fax);
        tab_doe->TAB_DOE_EDIT_MN_Email.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_MN_email);
        tab_doe->TAB_DOE_EDIT_Cena.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_cena);
        tab_doe->TAB_DOE_EDIT_WAkt.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_wartosc_akt);
        tab_doe->TAB_DOE_EDIT_DataZak.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_data_zakupu);
        tab_doe->TAB_DOE_EDIT_DataUtr.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_data_utraty);
        tab_doe->TAB_DOE_EDIT_DataSkat.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_data_skatalogowania);
        tab_doe->TAB_DOE_EDIT_NrKat.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_Nr_kat);
        tab_doe->Frm_F_DOE_ComboBox_RodzNosn.SetWindowTextW((LPCTSTR)flm.film_tbl.DOE_rodzaj_nosnika);
        // TAB IOF
        tab_iof->TAB_IOF_EDIT_RokProd.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_rok_produkcji);
        tab_iof->TAB_IOF_EDIT_DataPrem.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_data_premiery);
        tab_iof->TAB_IOF_EDIT_CzasTrw.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_czas_trwania);
        tab_iof->TAB_IOF_EDIT_FormWysw.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_format_wysw);
        tab_iof->TAB_IOF_EDIT_SysKodObr.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_system_kodowania_obrazu);
        tab_iof->TAB_IOF_EDIT_JezLekt.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_jezyk_lektora);
        tab_iof->TAB_IOF_EDIT_JezNap.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_jezyk_napisow);
        tab_iof->TAB_IOF_EDIT_KrajProd.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_kraj_produkcji_filmu);
        tab_iof->TAB_IOF_EDIT_KW_Nazwa.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_KODEK_nazwa);
        tab_iof->TAB_IOF_EDIT_KW_Typ.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_KODEK_typ);
        tab_iof->TAB_IOF_EDIT_KW_Wersja.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_KODEK_wersja);
        tab_iof->TAB_IOF_EDIT_SD_Nazwa.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_DZWIEK_nazwa);
        tab_iof->TAB_IOF_EDIT_SD_Typ.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_DZWIEK_typ);
        tab_iof->TAB_IOF_EDIT_SD_Wersja.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_DZWIEK_wersja);
        tab_iof->TAB_IOF_EDIT_Z_Nazwa.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_ZABEZP_nazwa);
        tab_iof->TAB_IOF_EDIT_Z_Typ.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_ZABEZP_typ);
        tab_iof->TAB_IOF_EDIT_Z_Wersja.SetWindowTextW((LPCTSTR)flm.film_tbl.IOF_ZABEZP_wersja);

        //Invalidate();
        //UpdateWindow();

}
void MainWindow::Bind_OUT_Controls(void)
{
    // ta funkcja pobiera dane z formularza i zapisuje w strukturze flm.film_tbl

        // FORM FILM
        F_EDIT_Tytul.GetWindowTextW((LPTSTR)flm.film_tbl.tytul, 501);
        F_EDIT_TytulOryg.GetWindowTextW((LPTSTR)flm.film_tbl.oryginalny_tytul,501);
        Frm_F_ComboBox_Gatunek.GetWindowTextW((LPTSTR)flm.film_tbl.gatunek_filmu,201);
        //TAB OCENA
        tab_oc->TAB_O_Edit_SD.GetWindowTextW((LPTSTR)flm.film_tbl.WOF_sciezka_dz,201);
        tab_oc->TAB_O_Edit_Obsada.GetWindowTextW((LPTSTR)flm.film_tbl.WOF_obsada,201);
        tab_oc->TAB_O_Edit_Zdjecia.GetWindowTextW((LPTSTR)flm.film_tbl.WOF_zdjecia,201);
        tab_oc->TAB_O_Edit_WArt.GetWindowTextW((LPTSTR)flm.film_tbl.WOF_w_art,201);
        tab_oc->TAB_O_Edit_Calosc.GetWindowTextW((LPTSTR)flm.film_tbl.WOF_calosc,201);

        // TAB OBSADA
        tab_ob->TAB_OB_Edit_Rez_ImieNazw.GetWindowTextW((LPTSTR)flm.film_tbl.O_rezyser_imie_nazw,501);
        tab_ob->TAB_OB_Edit_Rez_Narod.GetWindowTextW((LPTSTR)flm.film_tbl.O_rezyser_narod,501);
        tab_ob->TAB_OB_Edit_Scen_ImieNazw.GetWindowTextW((LPTSTR)flm.film_tbl.O_scenariusz_imie_nazw,501);
        tab_ob->TAB_OB_Edit_Scen_Narod.GetWindowTextW((LPTSTR)flm.film_tbl.O_scenariusz_narod,501);
        tab_ob->TAB_OB_Edit_Zdj_ImieNazw.GetWindowTextW((LPTSTR)flm.film_tbl.O_operator_imie_nazw,501);
        tab_ob->TAB_OB_Edit_Zdj_Narod.GetWindowTextW((LPTSTR)flm.film_tbl.O_operator_narod,501);
        tab_ob->TAB_OB_Edit_Muz_ImieNazw.GetWindowTextW((LPTSTR)flm.film_tbl.O_muzyka_imie_nazw,501);
        tab_ob->TAB_OB_Edit_Muz_Narod.GetWindowTextW((LPTSTR)flm.film_tbl.O_muzyka_narod,501);

        // TAB PRODUKCJA

        // TAB DOE
        tab_doe->TAB_DOE_EDIT_W_Imie.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_WKF_imie,501);
        tab_doe->TAB_DOE_EDIT_W_Nazw.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_WKF_nazwisko,501);
        tab_doe->TAB_DOE_EDIT_W_Adres.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_WKF_adres,501);
        tab_doe->TAB_DOE_EDIT_MN_Nazwa.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_MN_nazwa,501);
        tab_doe->TAB_DOE_EDIT_MN_Adres.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_MN_adres,501);
        tab_doe->TAB_DOE_EDIT_MN_WWW.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_MN_www,501);
        tab_doe->TAB_DOE_EDIT_MN_Tel.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_MN_telefon,31);
        tab_doe->TAB_DOE_EDIT_MN_Fax.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_MN_fax,31);
        tab_doe->TAB_DOE_EDIT_MN_Email.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_MN_email,201);
        tab_doe->TAB_DOE_EDIT_Cena.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_cena,101);
        tab_doe->TAB_DOE_EDIT_WAkt.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_wartosc_akt,101);
        tab_doe->TAB_DOE_EDIT_DataZak.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_data_zakupu,21);
        tab_doe->TAB_DOE_EDIT_DataUtr.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_data_utraty,21);
        tab_doe->TAB_DOE_EDIT_DataSkat.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_data_skatalogowania,21);
        tab_doe->TAB_DOE_EDIT_NrKat.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_Nr_kat,501);
        tab_doe->Frm_F_DOE_ComboBox_RodzNosn.GetWindowTextW((LPTSTR)flm.film_tbl.DOE_rodzaj_nosnika,201);
        // TAB IOF
        tab_iof->TAB_IOF_EDIT_RokProd.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_rok_produkcji,21);
        tab_iof->TAB_IOF_EDIT_DataPrem.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_data_premiery,21);
        tab_iof->TAB_IOF_EDIT_CzasTrw.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_czas_trwania,51);
        tab_iof->TAB_IOF_EDIT_FormWysw.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_format_wysw,51);
        tab_iof->TAB_IOF_EDIT_SysKodObr.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_system_kodowania_obrazu,51);
        tab_iof->TAB_IOF_EDIT_JezLekt.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_jezyk_lektora,1001);
        tab_iof->TAB_IOF_EDIT_JezNap.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_jezyk_napisow,1001);
        tab_iof->TAB_IOF_EDIT_KrajProd.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_kraj_produkcji_filmu,1001);
        tab_iof->TAB_IOF_EDIT_KW_Nazwa.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_KODEK_nazwa,201);
        tab_iof->TAB_IOF_EDIT_KW_Typ.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_KODEK_typ,201);
        tab_iof->TAB_IOF_EDIT_KW_Wersja.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_KODEK_wersja,201);
        tab_iof->TAB_IOF_EDIT_SD_Nazwa.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_DZWIEK_nazwa,201);
        tab_iof->TAB_IOF_EDIT_SD_Typ.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_DZWIEK_typ,201);
        tab_iof->TAB_IOF_EDIT_SD_Wersja.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_DZWIEK_wersja,201);
        tab_iof->TAB_IOF_EDIT_Z_Nazwa.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_ZABEZP_nazwa,201);
        tab_iof->TAB_IOF_EDIT_Z_Typ.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_ZABEZP_typ,201);
        tab_iof->TAB_IOF_EDIT_Z_Wersja.GetWindowTextW((LPTSTR)flm.film_tbl.IOF_ZABEZP_wersja,201);
}
void MainWindow::ClearCtrls(bool all)
{
// Clear Form

    F_EDIT_ID.SetSel(0,-1);
    F_EDIT_ID.Clear();

    F_EDIT_Tytul.SetSel(0,-1);
    F_EDIT_Tytul.Clear();

    F_EDIT_TytulOryg.SetSel(0,-1);
    F_EDIT_TytulOryg.Clear();

    Frm_F_ComboBox_Gatunek.SetCurSel(-1);
    //TAB OCENA

    tab_oc->TAB_O_Edit_SD.Clear();
    tab_oc->TAB_O_Edit_Obsada.Clear();
    tab_oc->TAB_O_Edit_Zdjecia.Clear();
    tab_oc->TAB_O_Edit_WArt.Clear();
    tab_oc->TAB_O_Edit_Calosc.Clear();

    tab_oc->ClearOcena(); // czyszczenie listctrl

    // TAB OBSADA
    tab_ob->TAB_OB_Edit_Rez_ImieNazw.Clear();
    tab_ob->TAB_OB_Edit_Rez_Narod.Clear();
    tab_ob->TAB_OB_Edit_Scen_ImieNazw.Clear();
    tab_ob->TAB_OB_Edit_Scen_Narod.Clear();
    tab_ob->TAB_OB_Edit_Zdj_ImieNazw.Clear();
    tab_ob->TAB_OB_Edit_Zdj_Narod.Clear();
    tab_ob->TAB_OB_Edit_Muz_ImieNazw.Clear();
    tab_ob->TAB_OB_Edit_Muz_Narod.Clear();

    tab_ob->ClearObsada(); // czyszczenie listctrl;

    // TAB PRODUKCJA

    tab_p->ClearProd();  // czyszczenie listctrl

    // TAB DOE
    tab_doe->TAB_DOE_EDIT_W_Imie.Clear();
    tab_doe->TAB_DOE_EDIT_W_Nazw.Clear();
    tab_doe->TAB_DOE_EDIT_W_Adres.Clear();
    tab_doe->TAB_DOE_EDIT_MN_Nazwa.Clear();
    tab_doe->TAB_DOE_EDIT_MN_Adres.Clear();
    tab_doe->TAB_DOE_EDIT_MN_WWW.Clear();
    tab_doe->TAB_DOE_EDIT_MN_Tel.Clear();
    tab_doe->TAB_DOE_EDIT_MN_Fax.Clear();
    tab_doe->TAB_DOE_EDIT_MN_Email.Clear();
    tab_doe->TAB_DOE_EDIT_Cena.Clear();
    tab_doe->TAB_DOE_EDIT_WAkt.Clear();
    tab_doe->TAB_DOE_EDIT_DataZak.Clear();
    tab_doe->TAB_DOE_EDIT_DataUtr.Clear();
    tab_doe->TAB_DOE_EDIT_DataSkat.Clear();
    tab_doe->TAB_DOE_EDIT_NrKat.Clear();
    tab_doe->Frm_F_DOE_ComboBox_RodzNosn.Clear();
    // TAB IOF
    tab_iof->TAB_IOF_EDIT_RokProd.Clear();
    tab_iof->TAB_IOF_EDIT_DataPrem.Clear();
    tab_iof->TAB_IOF_EDIT_CzasTrw.Clear();
    tab_iof->TAB_IOF_EDIT_FormWysw.Clear();
    tab_iof->TAB_IOF_EDIT_SysKodObr.Clear();
    tab_iof->TAB_IOF_EDIT_JezLekt.Clear();
    tab_iof->TAB_IOF_EDIT_JezNap.Clear();
    tab_iof->TAB_IOF_EDIT_KrajProd.Clear();
    tab_iof->TAB_IOF_EDIT_KW_Nazwa.Clear();
    tab_iof->TAB_IOF_EDIT_KW_Typ.Clear();
    tab_iof->TAB_IOF_EDIT_KW_Wersja.Clear();
    tab_iof->TAB_IOF_EDIT_SD_Nazwa.Clear();
    tab_iof->TAB_IOF_EDIT_SD_Typ.Clear();
    tab_iof->TAB_IOF_EDIT_SD_Wersja.Clear();
    tab_iof->TAB_IOF_EDIT_Z_Nazwa.Clear();
    tab_iof->TAB_IOF_EDIT_Z_Typ.Clear();
    tab_iof->TAB_IOF_EDIT_Z_Wersja.Clear();

    tab_iof->ClearIOF(); // czyszczenie listctrl;

    // TAB Bibliotekarz
    tab_b->ClearBIBLIO(); // czyszczenie listctrl

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
                plik.close();

                plik.rename(L"BF_PDB.bf0");

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
            if (status.m_size == 0)
                {

                    this->F_EDIT_RecCount.SetWindowTextW(_TEXT("0"));
                    this->F_EDIT_RecPos.SetWindowTextW(_TEXT("0"));
                    return true;
                }
            else
                {
                    if (flm.sort)
                    {
                            wchar_t crec_txt[34];
                            wchar_t recc_txt[34];
                            _itow((sort_idx + 1),crec_txt,10);
                            _itow(flm.film_tbl_wsk.GetCount(),recc_txt,10);
                            F_EDIT_RecPos.SetWindowTextW(crec_txt);
                            F_EDIT_RecCount.SetWindowTextW(recc_txt);
                    }
                    else
                    {
                            // policz rekordy w trybie niesortowanym i wypełnij Film_tab_wsk
                        CFile plik;
                        struct Film film_test;
                        plik.Open(flm.pths.BF_PDB,CFile::modeRead);
                        LONGLONG stop = 0;
                        stop = plik.SeekToEnd();
                        LONGLONG i = 0;
                        int cur_rec = 0;
                        int rec_count = 0;
                        wchar_t crec_txt[34];
                        wchar_t recc_txt[34];
                        for (i = 0; i < stop; )
                        {
                            plik.Seek(i,CFile::begin);
                            plik.Read(&film_test,sizeof(film_test));
                            rec_count = rec_count + 1;
                            if (flm.film_tbl.ID == film_test.ID)
                            {
                                cur_rec = rec_count;
                            }

                            i = i + sizeof(film_test);
                        }
                            _itow(cur_rec,crec_txt,10);
                            _itow(rec_count,recc_txt,10);
                            F_EDIT_RecPos.SetWindowTextW(crec_txt);
                            F_EDIT_RecCount.SetWindowTextW(recc_txt);

                    }


                    return false;

                }
        }
}
void CBibliotekaFilmówDlg::Read_Settings()
{
//TODO : Napisać odczytywanie ustawień, jak nie ma utworzyc plik z domyślnymi

}

void CBibliotekaFilmówDlg::SetDBFNPaths(bool cust, wchar_t* cust_path)
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

void CBibliotekaFilmówDlg::Disable_BTNS_NOREC()
{
    this->TAB_DOE_BUTTON_OklP_Otw.EnableWindow(FALSE);
    this->TAB_DOE_BUTTON_OklP_Usun.EnableWindow(FALSE);
    this->TAB_DOE_BUTTON_OklT_Otw.EnableWindow(FALSE);
    this->TAB_DOE_BUTTON_OklT_Usun.EnableWindow(FALSE);
    tab_oc->FRM_F_Oc_BUTTON_Nowy.EnableWindow(FALSE);
    tab_oc->FRM_F_Oc_BUTTON_Usun.EnableWindow(FALSE);
    tab_oc->FRM_F_Oc_BUTTON_Zapisz.EnableWindow(FALSE);
    tab_oc->FRM_F_Oc_BUTTON_Zatwierdz.EnableWindow(FALSE);
    tab_oc->FRM_F_OC_EDYTUJ.EnableWindow(FALSE);
    tab_ob->FRM_F_BUTTON_OB_EDYTUJ.EnableWindow(FALSE);
    tab_ob->FRM_F_BUTTON_OB_NOWY.EnableWindow(FALSE);
    tab_ob->FRM_F_BUTTON_OB_USUN.EnableWindow(FALSE);
    tab_ob->FRM_F_BUTTON_OB_ZAPISZ.EnableWindow(FALSE);
    tab_ob->FRM_F_BUTTON_OB_ZATWIERDZ.EnableWindow(FALSE);
    tab_b->FRM_F_B_WI_BTN_EDYTUJ.EnableWindow(FALSE);
    tab_b->FRM_F_B_WI_BTN_NOWY.EnableWindow(FALSE);
    tab_b->FRM_F_B_WI_BTN_USUN.EnableWindow(FALSE);
    tab_b->FRM_F_B_WI_BTN_ZAPISZ.EnableWindow(FALSE);
    tab_b->FRM_F_B_WI_BTN_ZATWIERDZ.EnableWindow(FALSE);
    tab_b->FRM_F_B_WO_BTN_EDYTUJ.EnableWindow(FALSE);
    tab_b->FRM_F_B_WO_BTN_NOWY.EnableWindow(FALSE);
    tab_b->FRM_F_B_WO_BTN_USUN.EnableWindow(FALSE);
    tab_b->FRM_F_B_WO_BTN_ZAPISZ.EnableWindow(FALSE);
    tab_b->FRM_F_B_WO_BTN_ZATWIERDZ.EnableWindow(FALSE);
    tab_p->FRM_F_BUTTON_PD_EDYTUJ.EnableWindow(FALSE);
    tab_p->FRM_F_BUTTON_PD_NOWY.EnableWindow(FALSE);
    tab_p->FRM_F_BUTTON_PD_USUN.EnableWindow(FALSE);
    tab_p->FRM_F_BUTTON_PD_ZAPISZ.EnableWindow(FALSE);
    tab_p->FRM_F_BUTTON_pd_ZATWIERDZ.EnableWindow(FALSE);
    tab_p->FRM_F_BUTTON_Pp_Edytuj.EnableWindow(FALSE);
    tab_p->FRM_F_BUTTON_Pp_Nowy.EnableWindow(FALSE);
    tab_p->FRM_F_BUTTON_Pp_Usun.EnableWindow(FALSE);
    tab_p->FRM_F_BUTTON_Pp_Zapisz.EnableWindow(FALSE);
    tab_p->FRM_F_BUTTON_pp_ZATWIERDZ.EnableWindow(FALSE);
    tab_iof->FRM_F_BUTTON_IOF_Edytuj.EnableWindow(FALSE);
    tab_iof->FRM_F_BUTTON_IOF_Nowy.EnableWindow(FALSE);
    tab_iof->FRM_F_BUTTON_IOF_Usun.EnableWindow(FALSE);
    tab_iof->FRM_F_BUTTON_IOF_Zapisz.EnableWindow(FALSE);
    tab_iof->FRM_F_BUTTON_IOF_Zatwierdz.EnableWindow(FALSE);


}

void CBibliotekaFilmówDlg::Enable_BTNS_NOREC()
{
    this->TAB_DOE_BUTTON_OklP_Otw.EnableWindow(TRUE);
    this->TAB_DOE_BUTTON_OklP_Usun.EnableWindow(TRUE);
    this->TAB_DOE_BUTTON_OklT_Otw.EnableWindow(TRUE);
    this->TAB_DOE_BUTTON_OklT_Usun.EnableWindow(TRUE);
    tab_oc->FRM_F_Oc_BUTTON_Nowy.EnableWindow(TRUE);
    tab_oc->FRM_F_Oc_BUTTON_Usun.EnableWindow(TRUE);
    tab_oc->FRM_F_Oc_BUTTON_Zapisz.EnableWindow(TRUE);
    tab_oc->FRM_F_Oc_BUTTON_Zatwierdz.EnableWindow(TRUE);
    tab_oc->FRM_F_OC_EDYTUJ.EnableWindow(TRUE);
    tab_ob->FRM_F_BUTTON_OB_EDYTUJ.EnableWindow(TRUE);
    tab_ob->FRM_F_BUTTON_OB_NOWY.EnableWindow(TRUE);
    tab_ob->FRM_F_BUTTON_OB_USUN.EnableWindow(TRUE);
    tab_ob->FRM_F_BUTTON_OB_ZAPISZ.EnableWindow(TRUE);
    tab_ob->FRM_F_BUTTON_OB_ZATWIERDZ.EnableWindow(TRUE);
    tab_b->FRM_F_B_WI_BTN_EDYTUJ.EnableWindow(TRUE);
    tab_b->FRM_F_B_WI_BTN_NOWY.EnableWindow(TRUE);
    tab_b->FRM_F_B_WI_BTN_USUN.EnableWindow(TRUE);
    tab_b->FRM_F_B_WI_BTN_ZAPISZ.EnableWindow(TRUE);
    tab_b->FRM_F_B_WI_BTN_ZATWIERDZ.EnableWindow(TRUE);
    tab_b->FRM_F_B_WO_BTN_EDYTUJ.EnableWindow(TRUE);
    tab_b->FRM_F_B_WO_BTN_NOWY.EnableWindow(TRUE);
    tab_b->FRM_F_B_WO_BTN_USUN.EnableWindow(TRUE);
    tab_b->FRM_F_B_WO_BTN_ZAPISZ.EnableWindow(TRUE);
    tab_b->FRM_F_B_WO_BTN_ZATWIERDZ.EnableWindow(TRUE);
    tab_p->FRM_F_BUTTON_PD_EDYTUJ.EnableWindow(TRUE);
    tab_p->FRM_F_BUTTON_PD_NOWY.EnableWindow(TRUE);
    tab_p->FRM_F_BUTTON_PD_USUN.EnableWindow(TRUE);
    tab_p->FRM_F_BUTTON_PD_ZAPISZ.EnableWindow(TRUE);
    tab_p->FRM_F_BUTTON_pd_ZATWIERDZ.EnableWindow(TRUE);
    tab_p->FRM_F_BUTTON_Pp_Edytuj.EnableWindow(TRUE);
    tab_p->FRM_F_BUTTON_Pp_Nowy.EnableWindow(TRUE);
    tab_p->FRM_F_BUTTON_Pp_Usun.EnableWindow(TRUE);
    tab_p->FRM_F_BUTTON_Pp_Zapisz.EnableWindow(TRUE);
    tab_p->FRM_F_BUTTON_pp_ZATWIERDZ.EnableWindow(TRUE);
    tab_iof->FRM_F_BUTTON_IOF_Edytuj.EnableWindow(TRUE);
    tab_iof->FRM_F_BUTTON_IOF_Nowy.EnableWindow(TRUE);
    tab_iof->FRM_F_BUTTON_IOF_Usun.EnableWindow(TRUE);
    tab_iof->FRM_F_BUTTON_IOF_Zapisz.EnableWindow(TRUE);
    tab_iof->FRM_F_BUTTON_IOF_Zatwierdz.EnableWindow(TRUE);

}
bool CBibliotekaFilmówDlg::CheckOLDDB()
{
    bool test[9];
    CFileStatus status;
    if (CFile::GetStatus(_TEXT("BF.bf"),status))
    {
        test[0] = true;
    }
    else
    {
        test[0] = false;
    }

    if (CFile::GetStatus(_TEXT("BF_PDB.bf"),status))
    {
        test[1] = true;
    }
    else
    {
        test[1] = false;
    }

    if (CFile::GetStatus(_TEXT("BF_OC.bf"),status))
    {
        test[2] = true;
    }
    else
    {
        test[2] = false;
    }

    if (CFile::GetStatus(_TEXT("BF_OB.bf"),status))
    {
        test[3] = true;
    }
    else
    {
        test[3] = false;
    }

    if (CFile::GetStatus(_TEXT("BF_PRB.bf"),status))
    {
        test[4] = true;
    }
    else
    {
        test[4] = false;
    }

    if (CFile::GetStatus(_TEXT("BF_PRD.bf"),status))
    {
        test[5] = true;
    }
    else
    {
        test[5] = false;
    }

    if (CFile::GetStatus(_TEXT("BF_LZ.bf"),status))
    {
        test[6] = true;
    }
    else
    {
        test[6] = false;
    }

    if (CFile::GetStatus(_TEXT("BF_WI.bf"),status))
    {
        test[7] = true;
    }
    else
    {
        test[7] = false;
    }

    if (CFile::GetStatus(_TEXT("BF_WO.bf"),status))
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

void CBibliotekaFilmówDlg::KopiujOLDDB()
{
    CString buff_path;
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

void CBibliotekaFilmówDlg::SetBTNIcons()
{
    HANDLE bt_new, bt_del, bt_save;
    bt_new = LoadImage(theApp.m_hInstance,MAKEINTRESOURCE(IDI_ICON2),IMAGE_ICON,NULL,NULL,NULL);
    bt_save = LoadImage(theApp.m_hInstance,MAKEINTRESOURCE(IDI_ICON3),IMAGE_ICON,NULL,NULL,NULL);
    bt_del = LoadImage(theApp.m_hInstance,MAKEINTRESOURCE(IDI_ICON4),IMAGE_ICON,NULL,NULL,NULL);

    this->FRM_F_New_BUTTON.SendMessageW(BM_SETIMAGE,(WPARAM)IMAGE_ICON,(LPARAM)bt_new);
    this->FRM_F_Save_BUTTON.SendMessageW(BM_SETIMAGE,(WPARAM)IMAGE_ICON,(LPARAM)bt_save);
    this->FRM_F_Del_BUTTON.SendMessageW(BM_SETIMAGE,(WPARAM)IMAGE_ICON,(LPARAM)bt_del);

}

void CBibliotekaFilmówDlg::OnOperacjeOtw32776()
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

void CBibliotekaFilmówDlg::OnOperacjeEksportuj()
{
    Eksport_Wizard *eks_wiz = new Eksport_Wizard(this);
    eks_wiz->Create(Eksport_Wizard::IDD,this);
    eks_wiz->ShowWindow(SW_SHOW);
}
void CBibliotekaFilmówDlg::OnBnClickedButtonFrmFDoeOklprzodOtworz()
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

void CBibliotekaFilmówDlg::OnBnClickedButtonFrmFDoeOklprzodUsun()
{
    if (!(CBibliotekaFilmówDlg::Licz_Rec()))
    {
        _tcscpy(flm.film_tbl.skan_przod_path,_TEXT(""));
        CBibliotekaFilmówDlg::OnBnClickedButtonFrmFSave();

    }
}

void CBibliotekaFilmówDlg::OnBnClickedButtonFrmFDoeOkltylOtworz()
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
        _tcscpy(flm.film_tbl.skan_tyl_path,buff);
        CBibliotekaFilmówDlg::OnBnClickedButtonFrmFSave();
    }

}

void CBibliotekaFilmówDlg::OnBnClickedButtonFrmFDoeOkltylUsun()
{
    if (!(CBibliotekaFilmówDlg::Licz_Rec()))
    {
        _tcscpy(flm.film_tbl.skan_tyl_path,_TEXT(""));
        CBibliotekaFilmówDlg::OnBnClickedButtonFrmFSave();
    }
}
void TAB_BIBLIO::ClearBIBLIO(void)
{
TAB_BIBLIO_LIST_WypIn.DeleteAllItems();
TAB_BIBLIO_LIST_WypOdIn.DeleteAllItems();


}

void TAB_BIBLIO::Fill_Wi(void)
{
CFile plik;
plik.Open(flm_b.pths.BF_WI,CFile::modeRead);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();


TAB_BIBLIO_LIST_WypIn.DeleteAllItems();
wi_arr.RemoveAll();



for (i = 0;i<stop ; )
{
    plik.Seek(i,CFile::begin);
    plik.Read(&wi,sizeof(wi));
    if (wi.IDPDB == flm_b.film_tbl.ID)
    {
        wi_arr.Add(wi);

    }
    i = i + sizeof(wi);
}
plik.Close();

Refresh_Wi();


}

void TAB_BIBLIO::Fill_Wo(void)
{
CFile plik;
plik.Open(flm_b.pths.BF_WO,CFile::modeRead);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();


TAB_BIBLIO_LIST_WypOdIn.DeleteAllItems();
wo_arr.RemoveAll();



for (i = 0;i<stop ; )
{
    plik.Seek(i,CFile::begin);
    plik.Read(&wo,sizeof(wo));
    if (wo.IDPDB == flm_b.film_tbl.ID)
    {
        wo_arr.Add(wo);

    }
    i = i + sizeof(wo);
}
plik.Close();

Refresh_Wo();


}
void TAB_BIBLIO::OnBnClickedButtonFrmFBWiNowy()
{
    Save_Wi();
    Add_New_WI(Get_Hi_ID_WI());
    add_new_wi = true;
}

void TAB_BIBLIO::OnBnClickedButtonFrmFBWiEdytuj()
{
    TAB_BIBLIO::FRM_F_B_WI_BTN_NOWY.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WI_BTN_USUN.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WI_BTN_ZAPISZ.EnableWindow(FALSE);
    TAB_BIBLIO::TAB_BIBLIO_LIST_WypIn.EnableWindow(FALSE);

    TAB_BIBLIO::FRM_F_B_WI_EDT_DataWyp.EnableWindow(TRUE);
    TAB_BIBLIO::FRM_F_B_WI_EDT_StanPWyp.EnableWindow(TRUE);
    TAB_BIBLIO::FRM_F_B_WI_EDT_DataOdd.EnableWindow(TRUE);
    TAB_BIBLIO::FRM_F_B_WI_EDT_StanPOdd.EnableWindow(TRUE);
    TAB_BIBLIO::FRM_F_B_WI_EDT_Osoba.EnableWindow(TRUE);
    TAB_BIBLIO::FRM_F_B_WI_EDT_NrKat.EnableWindow(TRUE);

    TAB_BIBLIO::FRM_F_B_WI_BTN_ZATWIERDZ.EnableWindow(TRUE);


wchar_t buff[34];

int item;
item = TAB_BIBLIO_LIST_WypIn.GetNextItem(-1,LVIS_SELECTED);
if (item != -1)
{
    wchar_t buff201[201];
    wchar_t buff501[501];
    TAB_BIBLIO_LIST_WypIn.GetItemText(item,0,buff501,21);
    TAB_BIBLIO::FRM_F_B_WI_EDT_DataWyp.SetWindowTextW(buff501);

    TAB_BIBLIO_LIST_WypIn.GetItemText(item,1,buff501,21);
    TAB_BIBLIO::FRM_F_B_WI_EDT_StanPWyp.SetWindowTextW(buff501);

    TAB_BIBLIO_LIST_WypIn.GetItemText(item,2,buff501,501);
    TAB_BIBLIO::FRM_F_B_WI_EDT_DataOdd.SetWindowTextW(buff501);

    TAB_BIBLIO_LIST_WypIn.GetItemText(item,3,buff501,501);
    TAB_BIBLIO::FRM_F_B_WI_EDT_StanPOdd.SetWindowTextW(buff501);

    TAB_BIBLIO_LIST_WypIn.GetItemText(item,4,buff201,501);
    TAB_BIBLIO::FRM_F_B_WI_EDT_Osoba.SetWindowTextW(buff501);

    TAB_BIBLIO_LIST_WypIn.GetItemText(item,5,buff501,501);
    TAB_BIBLIO::FRM_F_B_WI_EDT_NrKat.SetWindowTextW(buff501);

    TAB_BIBLIO_LIST_WypIn.GetItemText(item,6,buff,34);
    wi.ID = _wtoi(buff);
    TAB_BIBLIO_LIST_WypIn.GetItemText(item,7,buff,34);
    wi.IDPDB = _wtoi(buff);
}
}

void TAB_BIBLIO::OnBnClickedButtonfrmFBWiZapisz()
{
    Save_Wi();
}

void TAB_BIBLIO::OnBnClickedButtonFrmFBWiUsun()
{
wchar_t buff[34];
LVITEM lvitm;
int delitem = 0;
int delID = 0;
delitem = TAB_BIBLIO_LIST_WypIn.GetNextItem(-1,LVNI_SELECTED);
TAB_BIBLIO_LIST_WypIn.GetItemText(delitem,6,(LPTSTR)buff,34);
delID = _wtoi(buff);

CFile plik;
plik.Open(flm_b.pths.BF_WI,CFile::modeRead | CFile::shareDenyNone);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
for (i=0;i<stop; )
{
    plik.Seek(i,CFile::begin);
    plik.Read(&wi,sizeof(wi));
    if (delID == wi.ID)
    {
    plik.Close();
    Usun_Rec_WI(i);
    break;
    }
    i = i + sizeof(wi);
}
if (plik.m_hFile != CFile::hFileNull)
{
    plik.Close();
}
}

void TAB_BIBLIO::OnBnClickedButtonFrmFBWiZatwierdz()
{
    TAB_BIBLIO::FRM_F_B_WI_EDT_DataWyp.GetWindowTextW(wi.data_wypozyczenia,21);
    TAB_BIBLIO::FRM_F_B_WI_EDT_StanPWyp.GetWindowTextW(wi.stan_przed_wypozycz,21);
    TAB_BIBLIO::FRM_F_B_WI_EDT_DataOdd.GetWindowTextW(wi.data_oddania,501);
    TAB_BIBLIO::FRM_F_B_WI_EDT_StanPOdd.GetWindowTextW(wi.stan_po_oddaniu,501);
    TAB_BIBLIO::FRM_F_B_WI_EDT_Osoba.GetWindowTextW(wi.osoba,501);
    TAB_BIBLIO::FRM_F_B_WI_EDT_NrKat.GetWindowTextW(wi.Nr_kat,501);



int item;
item = TAB_BIBLIO_LIST_WypIn.GetNextItem(-1,LVIS_SELECTED);
if (item != -1)
{
struct Wypozycz_Innym& wi_buff = wi_arr.ElementAt(item);

wi_buff = wi;
Refresh_Wi();
}


    TAB_BIBLIO::FRM_F_B_WI_BTN_NOWY.EnableWindow(TRUE);
    TAB_BIBLIO::FRM_F_B_WI_BTN_USUN.EnableWindow(TRUE);
    TAB_BIBLIO::FRM_F_B_WI_BTN_ZAPISZ.EnableWindow(TRUE);
    TAB_BIBLIO::TAB_BIBLIO_LIST_WypIn.EnableWindow(TRUE);

    TAB_BIBLIO::FRM_F_B_WI_EDT_DataWyp.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WI_EDT_StanPWyp.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WI_EDT_DataOdd.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WI_EDT_StanPOdd.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WI_EDT_Osoba.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WI_EDT_NrKat.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WI_BTN_ZATWIERDZ.EnableWindow(FALSE);
}

void TAB_BIBLIO::OnBnClickedButtonFrmFBWoiNowy()
{
    Save_Wo();
    Add_New_WO(Get_Hi_ID_WO());
    add_new_wo = true;
}

void TAB_BIBLIO::OnBnClickedButtonFrmFBWoiEdytuj()
{
    TAB_BIBLIO::FRM_F_B_WO_BTN_NOWY.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WO_BTN_USUN.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WO_BTN_ZAPISZ.EnableWindow(FALSE);
    TAB_BIBLIO::TAB_BIBLIO_LIST_WypIn.EnableWindow(FALSE);

    TAB_BIBLIO::FRM_F_B_WO_EDT_DataWyp.EnableWindow(TRUE);
    TAB_BIBLIO::FRM_F_B_WO_EDT_StanPWyp.EnableWindow(TRUE);
    TAB_BIBLIO::FRM_F_B_WO_EDT_DataOdd.EnableWindow(TRUE);
    TAB_BIBLIO::FRM_F_B_WO_EDT_StanPOdd.EnableWindow(TRUE);
    TAB_BIBLIO::FRM_F_B_WO_EDT_Osoba.EnableWindow(TRUE);
    TAB_BIBLIO::FRM_F_B_WO_EDT_NrKat.EnableWindow(TRUE);

    TAB_BIBLIO::FRM_F_B_WO_BTN_ZATWIERDZ.EnableWindow(TRUE);


wchar_t buff[34];

int item;
item = TAB_BIBLIO_LIST_WypOdIn.GetNextItem(-1,LVIS_SELECTED);
if (item != -1)
{
    wchar_t buff201[201];
    wchar_t buff501[501];
    TAB_BIBLIO_LIST_WypOdIn.GetItemText(item,0,buff501,21);
    TAB_BIBLIO::FRM_F_B_WO_EDT_DataWyp.SetWindowTextW(buff501);

    TAB_BIBLIO_LIST_WypOdIn.GetItemText(item,1,buff501,21);
    TAB_BIBLIO::FRM_F_B_WO_EDT_StanPWyp.SetWindowTextW(buff501);

    TAB_BIBLIO_LIST_WypOdIn.GetItemText(item,2,buff501,501);
    TAB_BIBLIO::FRM_F_B_WO_EDT_DataOdd.SetWindowTextW(buff501);

    TAB_BIBLIO_LIST_WypOdIn.GetItemText(item,3,buff501,501);
    TAB_BIBLIO::FRM_F_B_WO_EDT_StanPOdd.SetWindowTextW(buff501);

    TAB_BIBLIO_LIST_WypOdIn.GetItemText(item,4,buff201,501);
    TAB_BIBLIO::FRM_F_B_WO_EDT_Osoba.SetWindowTextW(buff501);

    TAB_BIBLIO_LIST_WypOdIn.GetItemText(item,5,buff501,501);
    TAB_BIBLIO::FRM_F_B_WO_EDT_NrKat.SetWindowTextW(buff501);

    TAB_BIBLIO_LIST_WypOdIn.GetItemText(item,6,buff,34);
    wo.ID = _wtoi(buff);
    TAB_BIBLIO_LIST_WypOdIn.GetItemText(item,7,buff,34);
    wo.IDPDB = _wtoi(buff);
}
}

void TAB_BIBLIO::OnBnClickedButtonFrmFBWoiZapisz()
{
    Save_Wo();
}

void TAB_BIBLIO::OnBnClickedButtonFrmFBWoiUsun()
{
wchar_t buff[34];
LVITEM lvitm;
int delitem = 0;
int delID = 0;
delitem = TAB_BIBLIO_LIST_WypOdIn.GetNextItem(-1,LVNI_SELECTED);
TAB_BIBLIO_LIST_WypOdIn.GetItemText(delitem,6,(LPTSTR)buff,34);
delID = _wtoi(buff);

CFile plik;
plik.Open(flm_b.pths.BF_WO,CFile::modeRead | CFile::shareDenyNone);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
for (i=0;i<stop; )
{
    plik.Seek(i,CFile::begin);
    plik.Read(&wo,sizeof(wo));
    if (delID == wo.ID)
    {
    plik.Close();
    Usun_Rec_WO(i);
    break;
    }
    i = i + sizeof(wo);
}
if (plik.m_hFile != CFile::hFileNull)
{
    plik.Close();
}
}

void TAB_BIBLIO::OnBnClickedButtonFrmFBWoiZatwierdz()
{
    TAB_BIBLIO::FRM_F_B_WO_EDT_DataWyp.GetWindowTextW(wo.data_wypozyczenia,21);
    TAB_BIBLIO::FRM_F_B_WO_EDT_StanPWyp.GetWindowTextW(wo.stan_przed_wypozycz,21);
    TAB_BIBLIO::FRM_F_B_WO_EDT_DataOdd.GetWindowTextW(wo.data_oddania,501);
    TAB_BIBLIO::FRM_F_B_WO_EDT_StanPOdd.GetWindowTextW(wo.stan_po_oddaniu,501);
    TAB_BIBLIO::FRM_F_B_WO_EDT_Osoba.GetWindowTextW(wo.osoba,501);
    TAB_BIBLIO::FRM_F_B_WO_EDT_NrKat.GetWindowTextW(wo.Nr_kat,501);



int item;
item = TAB_BIBLIO_LIST_WypOdIn.GetNextItem(-1,LVIS_SELECTED);
if (item != -1)
{
struct Wypozycz_Od_Innych& wo_buff = wo_arr.ElementAt(item);

wo_buff = wo;
Refresh_Wo();
}


    TAB_BIBLIO::FRM_F_B_WO_BTN_NOWY.EnableWindow(TRUE);
    TAB_BIBLIO::FRM_F_B_WO_BTN_USUN.EnableWindow(TRUE);
    TAB_BIBLIO::FRM_F_B_WO_BTN_ZAPISZ.EnableWindow(TRUE);
    TAB_BIBLIO::TAB_BIBLIO_LIST_WypIn.EnableWindow(TRUE);

    TAB_BIBLIO::FRM_F_B_WO_EDT_DataWyp.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WO_EDT_StanPWyp.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WO_EDT_DataOdd.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WO_EDT_StanPOdd.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WO_EDT_Osoba.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WO_EDT_NrKat.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WO_BTN_ZATWIERDZ.EnableWindow(FALSE);
}

void TAB_BIBLIO::Refresh_Wi(void)
{
TAB_BIBLIO_LIST_WypIn.DeleteAllItems();

    int x;
    for (x=0;x<wi_arr.GetCount(); x++)
    {
        LVITEM lvitm;
        lvitm.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
        lvitm.iItem = x;
        lvitm.iSubItem = 0;
        lvitm.state = 0;
        lvitm.stateMask = 0;
        lvitm.lParam = (LPARAM) &wi_arr.GetAt(x);
        lvitm.pszText = LPSTR_TEXTCALLBACK;
        TAB_BIBLIO_LIST_WypIn.InsertItem(&lvitm);
    }


}

void TAB_BIBLIO::Refresh_Wo(void)
{
TAB_BIBLIO_LIST_WypOdIn.DeleteAllItems();

    int x;
    for (x=0;x<wo_arr.GetCount(); x++)
    {
        LVITEM lvitm;
        lvitm.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
        lvitm.iItem = x;
        lvitm.iSubItem = 0;
        lvitm.state = 0;
        lvitm.stateMask = 0;
        lvitm.lParam = (LPARAM) &wo_arr.GetAt(x);
        lvitm.pszText = LPSTR_TEXTCALLBACK;
        TAB_BIBLIO_LIST_WypOdIn.InsertItem(&lvitm);
    }



}
void TAB_BIBLIO::OnLvnGetdispinfoListFrmFBWypin(NMHDR *pNMHDR, LRESULT *pResult)
{
    wchar_t buff[34];

    NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);


    int x;
    x = pDispInfo->item.iItem;

    switch (pDispInfo->item.iSubItem)
    {
    case 0:
        wcscpy(pDispInfo->item.pszText,wi_arr.GetAt(x).data_wypozyczenia);
        break;
    case 1:
        wcscpy(pDispInfo->item.pszText,wi_arr.GetAt(x).stan_przed_wypozycz);
        break;
    case 2:
        wcscpy(pDispInfo->item.pszText,wi_arr.GetAt(x).data_oddania);
        break;
    case 3:
        wcscpy(pDispInfo->item.pszText,wi_arr.GetAt(x).stan_po_oddaniu);
        break;
    case 4:
        wcscpy(pDispInfo->item.pszText,wi_arr.GetAt(x).osoba);
        break;
    case 5:
        wcscpy(pDispInfo->item.pszText,wi_arr.GetAt(x).Nr_kat);
        break;
    case 6:
        _itow(wi_arr.GetAt(x).ID ,buff,10);
        wcscpy(pDispInfo->item.pszText,buff); // ID
        break;
    case 7:
        _itow(wi_arr.GetAt(x).IDPDB ,buff,10);
        wcscpy(pDispInfo->item.pszText,buff);  //IDPDB
        break;
    }


    *pResult = 0;
}

void TAB_BIBLIO::OnLvnGetdispinfoListFrmFBWypodin(NMHDR *pNMHDR, LRESULT *pResult)
{
    wchar_t buff[34];

    NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);


    int x;
    x = pDispInfo->item.iItem;

    switch (pDispInfo->item.iSubItem)
    {
    case 0:
        wcscpy(pDispInfo->item.pszText,wo_arr.GetAt(x).data_wypozyczenia);
        break;
    case 1:
        wcscpy(pDispInfo->item.pszText,wo_arr.GetAt(x).stan_przed_wypozycz);
        break;
    case 2:
        wcscpy(pDispInfo->item.pszText,wo_arr.GetAt(x).data_oddania);
        break;
    case 3:
        wcscpy(pDispInfo->item.pszText,wo_arr.GetAt(x).stan_po_oddaniu);
        break;
    case 4:
        wcscpy(pDispInfo->item.pszText,wo_arr.GetAt(x).osoba);
        break;
    case 5:
        wcscpy(pDispInfo->item.pszText,wo_arr.GetAt(x).Nr_kat);
        break;
    case 6:
        _itow(wo_arr.GetAt(x).ID ,buff,10);
        wcscpy(pDispInfo->item.pszText,buff); // ID
        break;
    case 7:
        _itow(wo_arr.GetAt(x).IDPDB ,buff,10);
        wcscpy(pDispInfo->item.pszText,buff);  //IDPDB
        break;
    }



    *pResult = 0;
}

void TAB_BIBLIO::Set_BIBLIO(void)
{

    TAB_BIBLIO_LIST_WypIn.InsertColumn(0,L"Data wypożyczenia",LVCFMT_LEFT,100,1);
    TAB_BIBLIO_LIST_WypIn.InsertColumn(1,L"Stan przed wypożyczeniem",LVCFMT_LEFT,150,2);
    TAB_BIBLIO_LIST_WypIn.InsertColumn(2,L"Data oddania",LVCFMT_LEFT,100,3);
    TAB_BIBLIO_LIST_WypIn.InsertColumn(3,L"Stan po oddaniu",LVCFMT_LEFT,150,4);
    TAB_BIBLIO_LIST_WypIn.InsertColumn(4,L"Osoba",LVCFMT_LEFT,150,5);
    TAB_BIBLIO_LIST_WypIn.InsertColumn(5,L"Nr katalogowy filmu",LVCFMT_LEFT,150,6);
    TAB_BIBLIO_LIST_WypIn.InsertColumn(6,L"ID",LVCFMT_LEFT,150,7);
    TAB_BIBLIO_LIST_WypIn.InsertColumn(7,L"IDPDB",LVCFMT_LEFT,150,8);
    TAB_BIBLIO_LIST_WypIn.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

    TAB_BIBLIO::FRM_F_B_WI_EDT_DataOdd.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WI_EDT_DataWyp.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WI_EDT_NrKat.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WI_EDT_Osoba.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WI_EDT_StanPOdd.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WI_EDT_StanPWyp.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WI_BTN_ZATWIERDZ.EnableWindow(FALSE);

    TAB_BIBLIO_LIST_WypOdIn.InsertColumn(0,L"Data wypożyczenia",LVCFMT_LEFT,100,1);
    TAB_BIBLIO_LIST_WypOdIn.InsertColumn(1,L"Stan przed wypożyczeniem",LVCFMT_LEFT,150,2);
    TAB_BIBLIO_LIST_WypOdIn.InsertColumn(2,L"Data oddania",LVCFMT_LEFT,100,3);
    TAB_BIBLIO_LIST_WypOdIn.InsertColumn(3,L"Stan po oddaniu",LVCFMT_LEFT,150,4);
    TAB_BIBLIO_LIST_WypOdIn.InsertColumn(4,L"Osoba",LVCFMT_LEFT,150,5);
    TAB_BIBLIO_LIST_WypOdIn.InsertColumn(5,L"Nr katalogowy filmu",LVCFMT_LEFT,150,6);
    TAB_BIBLIO_LIST_WypOdIn.InsertColumn(6,L"ID",LVCFMT_LEFT,150,7);
    TAB_BIBLIO_LIST_WypOdIn.InsertColumn(7,L"IDPDB",LVCFMT_LEFT,150,8);
    TAB_BIBLIO_LIST_WypOdIn.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

    TAB_BIBLIO::FRM_F_B_WO_EDT_DataOdd.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WO_EDT_DataWyp.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WO_EDT_NrKat.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WO_EDT_Osoba.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WO_EDT_StanPOdd.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WO_EDT_StanPWyp.EnableWindow(FALSE);
    TAB_BIBLIO::FRM_F_B_WO_BTN_ZATWIERDZ.EnableWindow(FALSE);

}

void TAB_BIBLIO::Save_Wi(void)
{
    CFile plik;
    struct Wypozycz_Innym wi_buf;
    plik.Open(flm_b.pths.BF_WI,CFile::modeReadWrite | CFile::shareDenyNone);

    LONGLONG stop;
    LONGLONG i;
    int y;

    wchar_t buff[34];
    stop = plik.SeekToEnd();

    for (y=0;y<wi_arr.GetCount() ;y++ )
    {
        if (GetRecC_WI() == 0)
            {
                plik.Seek(0,CFile::begin);
                plik.Write(&wi_arr.GetAt(y),sizeof(wi));

            }
        else if (GetRecC_WI() > 0)
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
                        plik.Read(&wi_buf,sizeof(wi_buf));
                            if (wi_arr.GetAt(y).ID == wi_buf.ID)
                            {
                                plik.Seek(i,CFile::begin);
                                plik.Write(&wi_arr.GetAt(y),sizeof(wi));
                            }

                        i = i + sizeof(wi);
                    }
                    if (add_new_wi)
                    {

                        int x;
                        x = (wi_arr.GetCount()-1);
                        plik.Seek((plik.SeekToEnd()),CFile::begin);
                        plik.Write(&wi_arr.GetAt(x),sizeof(wi));
                        add_new_wi = false;
                    }
                }
            }

    }

    plik.Close();


}

void TAB_BIBLIO::Save_Wo(void)
{
    CFile plik;
    struct Wypozycz_Od_Innych wo_buf;
    plik.Open(flm_b.pths.BF_WO,CFile::modeReadWrite | CFile::shareDenyNone);

    LONGLONG stop;
    LONGLONG i;
    int y;

    wchar_t buff[34];
    stop = plik.SeekToEnd();

    for (y=0;y<wo_arr.GetCount() ;y++ )
    {
        if (GetRecC_WO() == 0)
            {
                plik.Seek(0,CFile::begin);
                plik.Write(&wo_arr.GetAt(y),sizeof(wo));

            }
        else if (GetRecC_WO() > 0)
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
                        plik.Read(&wo_buf,sizeof(wo_buf));
                            if (wo_arr.GetAt(y).ID == wo_buf.ID)
                            {
                                plik.Seek(i,CFile::begin);
                                plik.Write(&wo_arr.GetAt(y),sizeof(wo));
                            }

                        i = i + sizeof(wo);
                    }
                    if (add_new_wo)
                    {

                        int x;
                        x = (wo_arr.GetCount()-1);
                        plik.Seek((plik.SeekToEnd()),CFile::begin);
                        plik.Write(&wo_arr.GetAt(x),sizeof(wo));
                        add_new_wo = false;
                    }
                }
            }

    }

    plik.Close();
}

int TAB_BIBLIO::GetRecC_WI(void)
{
CFile plik;
plik.Open(flm_b.pths.BF_WI,CFile::modeRead | CFile::shareDenyNone);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
int rec_count = 0;
struct Wypozycz_Innym wi_t;
if (stop == 0)
{
    plik.Close();
    return 0;
}
    for (i = 0; i <stop; )
    {
        plik.Seek(i,CFile::begin);
        plik.Read(&wi_t,sizeof(wi_t));
        rec_count = rec_count + 1;
        i = i + sizeof(wi_t);
    }
    plik.Close();
return rec_count;

}

int TAB_BIBLIO::GetRecC_WO(void)
{
CFile plik;
plik.Open(flm_b.pths.BF_WO,CFile::modeRead | CFile::shareDenyNone);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
int rec_count = 0;
struct Wypozycz_Od_Innych wo_t;
if (stop == 0)
{
    plik.Close();
    return 0;
}
    for (i = 0; i <stop; )
    {
        plik.Seek(i,CFile::begin);
        plik.Read(&wo_t,sizeof(wo_t));
        rec_count = rec_count + 1;
        i = i + sizeof(wo_t);
    }
    plik.Close();
return rec_count;


}

int TAB_BIBLIO::Get_Hi_ID_WI(void)
{
if (GetRecC_WI() == 0)
{
    return 0;
}


CFile plik;
plik.Open(flm_b.pths.BF_WI,CFile::modeRead);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
for (i=0;i<stop; )
{
    plik.Seek(i,CFile::begin);
    if (i == (stop - sizeof(wi)))
    {
        plik.Read(&wi,sizeof(wi));
        plik.Close();
        return wi.ID;
    }
    i = i + sizeof(wi);
}

}

int TAB_BIBLIO::Get_Hi_ID_WO(void)
{
if (GetRecC_WO() == 0)
{
    return 0;
}


CFile plik;
plik.Open(flm_b.pths.BF_WO,CFile::modeRead);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
for (i=0;i<stop; )
{
    plik.Seek(i,CFile::begin);
    if (i == (stop - sizeof(wo)))
    {
        plik.Read(&wo,sizeof(wo));
        plik.Close();
        return wo.ID;
    }
    i = i + sizeof(wo);
}

}

void TAB_BIBLIO::Add_New_WI(int id)
{
int id_new;
id_new = id + 1;

// Metoda callbacku
wi.ID = id_new;
wi.IDPDB = flm_b.film_tbl.ID;
wcscpy(wi.data_wypozyczenia,L"Wpisz tutaj coś");
wcscpy(wi.stan_przed_wypozycz,L"Wpisz tutaj coś");
wcscpy(wi.data_oddania,L"Wpisz tutaj coś");
wcscpy(wi.stan_po_oddaniu,L"Wpisz tutaj coś");
wcscpy(wi.osoba,L"Wpisz tutaj coś");
wcscpy(wi.Nr_kat,L"Wpisz tutaj coś");

wi_arr.Add(wi);

Refresh_Wi();


}

void TAB_BIBLIO::Add_New_WO(int id)
{
int id_new;
id_new = id + 1;

// Metoda callbacku
wo.ID = id_new;
wo.IDPDB = flm_b.film_tbl.ID;
wcscpy(wo.data_wypozyczenia,L"Wpisz tutaj coś");
wcscpy(wo.stan_przed_wypozycz,L"Wpisz tutaj coś");
wcscpy(wo.data_oddania,L"Wpisz tutaj coś");
wcscpy(wo.stan_po_oddaniu,L"Wpisz tutaj coś");
wcscpy(wo.osoba,L"Wpisz tutaj coś");
wcscpy(wo.Nr_kat,L"Wpisz tutaj coś");

wo_arr.Add(wo);

Refresh_Wo();

}

void TAB_BIBLIO::Usun_Rec_WI(LONGLONG pos)
{
        struct Wypozycz_Innym wi_src;
        wi.ID = 0;
        CFile plik;
        plik.Open(flm_b.pths.BF_WI,CFile::modeWrite | CFile::shareDenyNone);
        plik.Seek(pos,CFile::begin);
        plik.Write(&wi,sizeof(wi));
        plik.Close();

        CFile::Rename(flm_b.pths.BF_WI,(LPCTSTR)"BF_WI.bf0");

        plik.Open(flm_b.pths.BF_WI,CFile::modeCreate);
        plik.Close();
        CFile src_file;
        src_file.Open((LPCTSTR)"BF_WI.bf0",CFile::modeRead);
        plik.Open(flm_b.pths.BF_WI,CFile::modeWrite);
        LONGLONG i;
        for (i = 0; i <(src_file.SeekToEnd()) ; )
        {
            src_file.Seek(i,CFile::begin);
            src_file.Read(&wi_src,sizeof(wi_src));
            if (wi_src.ID == 0)
            {
                i = i + sizeof(wi_src);
            }
            else
            {
                plik.Write(&wi_src,sizeof(wi_src));
                i = i + sizeof(wi_src);
            }
        }
        plik.Close();
        src_file.Close();
        CFile::Remove((LPCTSTR)"BF_WI.bf0");
        Fill_Wi();


}

void TAB_BIBLIO::Usun_Rec_WO(LONGLONG pos)
{

        struct Wypozycz_Od_Innych wo_src;
        wo.ID = 0;
        CFile plik;
        plik.Open(flm_b.pths.BF_WO,CFile::modeWrite | CFile::shareDenyNone);
        plik.Seek(pos,CFile::begin);
        plik.Write(&wo,sizeof(wo));
        plik.Close();

        CFile::Rename(flm_b.pths.BF_WO,(LPCTSTR)"BF_WO.bf0");

        plik.Open(flm_b.pths.BF_WO,CFile::modeCreate);
        plik.Close();
        CFile src_file;
        src_file.Open((LPCTSTR)"BF_WO.bf0",CFile::modeRead);
        plik.Open(flm_b.pths.BF_WO,CFile::modeWrite);
        LONGLONG i;
        for (i = 0; i <(src_file.SeekToEnd()) ; )
        {
            src_file.Seek(i,CFile::begin);
            src_file.Read(&wo_src,sizeof(wo_src));
            if (wo_src.ID == 0)
            {
                i = i + sizeof(wo_src);
            }
            else
            {
                plik.Write(&wo_src,sizeof(wo_src));
                i = i + sizeof(wo_src);
            }
        }
        plik.Close();
        src_file.Close();
        CFile::Remove((LPCTSTR)"BF_WO.bf0");
        Fill_Wo();


}
void TAB_BIBLIO::OnNMDblclkListFrmFBWypin(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    if (wi_arr.GetCount() > 0)
    {
        OnBnClickedButtonFrmFBWiEdytuj();
    }
    *pResult = 0;
}

void TAB_BIBLIO::OnNMDblclkListFrmFBWypodin(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    if (wo_arr.GetCount() > 0)
    {
        OnBnClickedButtonFrmFBWoiEdytuj();
    }
    *pResult = 0;
}
void TAB_IOF::ClearIOF(void)
{
    TAB_IOF::TAB_IOF_Lokalizacje.DeleteAllItems();


}

void TAB_IOF::Fill_Lz(void)
{

CFile plik;
plik.Open(flm_i.pths.BF_LZ,CFile::modeRead);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();


TAB_IOF_Lokalizacje.DeleteAllItems();
lz_arr.RemoveAll();



for (i = 0;i<stop ; )
{
    plik.Seek(i,CFile::begin);
    plik.Read(&lz,sizeof(lz));
    if (lz.IDPDB == flm_i.film_tbl.ID)
    {
        lz_arr.Add(lz);

    }
    i = i + sizeof(lz);
}
plik.Close();

Refresh_Lz();

}
void TAB_IOF::OnLvnGetdispinfoListFrmFIofLokzdj(NMHDR *pNMHDR, LRESULT *pResult)
{
    wchar_t buff[34];

    NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);


    int x;
    x = pDispInfo->item.iItem;

    switch (pDispInfo->item.iSubItem)
    {
    case 0:
        wcscpy(pDispInfo->item.pszText,lz_arr.GetAt(x).nazwa_obiektu);
        break;
    case 1:
        wcscpy(pDispInfo->item.pszText,lz_arr.GetAt(x).kraj);
        break;
    case 2:
        wcscpy(pDispInfo->item.pszText,lz_arr.GetAt(x).miejscowosc);
        break;
    case 3:
        wcscpy(pDispInfo->item.pszText,lz_arr.GetAt(x).region);
        break;
    case 4:
        wcscpy(pDispInfo->item.pszText,lz_arr.GetAt(x).pora_roku);
        break;
    case 5:
        wcscpy(pDispInfo->item.pszText,lz_arr.GetAt(x).data);
        break;
    case 6:
        _itow(lz_arr.GetAt(x).ID ,buff,10);
        wcscpy(pDispInfo->item.pszText,buff); // ID
        break;
    case 7:
        _itow(lz_arr.GetAt(x).IDPDB ,buff,10);
        wcscpy(pDispInfo->item.pszText,buff);  //IDPDB
        break;
    }


    *pResult = 0;
}

void TAB_IOF::OnBnClickedButtonFrmFIofLzNowy(void)
{
    Save_Lz();
    Add_New_LZ(Get_Hi_ID_LZ());
    add_new_lz = true;
}

void TAB_IOF::OnBnClickedButtonFrmFIofEdytuj(void)
{
    TAB_IOF::FRM_F_BUTTON_IOF_Nowy.EnableWindow(FALSE);
    TAB_IOF::FRM_F_BUTTON_IOF_Usun.EnableWindow(FALSE);
    TAB_IOF::FRM_F_BUTTON_IOF_Zapisz.EnableWindow(FALSE);
    TAB_IOF::TAB_IOF_Lokalizacje.EnableWindow(FALSE);

    TAB_IOF::FRM_F_EDIT_IOF_NazwaObiektu.EnableWindow(TRUE);
    TAB_IOF::FRM_F_EDIT_IOF_Kraj.EnableWindow(TRUE);
    TAB_IOF::FRM_F_EDIT_IOF_Miejscowosc.EnableWindow(TRUE);
    TAB_IOF::FRM_F_EDIT_IOF_Region.EnableWindow(TRUE);
    TAB_IOF::FRM_F_EDIT_IOF_PoraRoku.EnableWindow(TRUE);
    TAB_IOF::FRM_F_EDIT_IOF_Data.EnableWindow(TRUE);
    TAB_IOF::FRM_F_BUTTON_IOF_Zatwierdz.EnableWindow(TRUE);


wchar_t buff[34];

int item;
item = TAB_IOF_Lokalizacje.GetNextItem(-1,LVIS_SELECTED);
if (item != -1)
{
    wchar_t buff201[201];
    wchar_t buff501[501];
    TAB_IOF_Lokalizacje.GetItemText(item,0,buff501,501);
    TAB_IOF::FRM_F_EDIT_IOF_NazwaObiektu.SetWindowTextW(buff501);

    TAB_IOF_Lokalizacje.GetItemText(item,1,buff501,501);
    TAB_IOF::FRM_F_EDIT_IOF_Kraj.SetWindowTextW(buff501);

    TAB_IOF_Lokalizacje.GetItemText(item,2,buff501,501);
    TAB_IOF::FRM_F_EDIT_IOF_Miejscowosc.SetWindowTextW(buff501);

    TAB_IOF_Lokalizacje.GetItemText(item,3,buff501,501);
    TAB_IOF::FRM_F_EDIT_IOF_Region.SetWindowTextW(buff501);

    TAB_IOF_Lokalizacje.GetItemText(item,4,buff201,501);
    TAB_IOF::FRM_F_EDIT_IOF_PoraRoku.SetWindowTextW(buff501);

    TAB_IOF_Lokalizacje.GetItemText(item,5,buff201,21);
    TAB_IOF::FRM_F_EDIT_IOF_Data.SetWindowTextW(buff201);

    TAB_IOF_Lokalizacje.GetItemText(item,6,buff,34);
    lz.ID = _wtoi(buff);
    TAB_IOF_Lokalizacje.GetItemText(item,7,buff,34);
    lz.IDPDB = _wtoi(buff);
}
}

void TAB_IOF::OnBnClickedButtonFrmFIofLzZapisz(void)
{
    Save_Lz();
}

void TAB_IOF::OnBnClickedButtonFrmFIofLzUsun(void)
{
wchar_t buff[34];
LVITEM lvitm;
int delitem = 0;
int delID = 0;
delitem = TAB_IOF_Lokalizacje.GetNextItem(-1,LVNI_SELECTED);
TAB_IOF_Lokalizacje.GetItemText(delitem,6,(LPTSTR)buff,34);
delID = _wtoi(buff);

CFile plik;
plik.Open(flm_i.pths.BF_LZ,CFile::modeRead | CFile::shareDenyNone);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
for (i=0;i<stop; )
{
    plik.Seek(i,CFile::begin);
    plik.Read(&lz,sizeof(lz));
    if (delID == lz.ID)
    {
    plik.Close();
    Usun_Rec_LZ(i);
    break;
    }
    i = i + sizeof(lz);
}
if (plik.m_hFile != CFile::hFileNull)
{
    plik.Close();
}
}

void TAB_IOF::OnBnClickedButtonFrmFIofLzZatwierdz(void)
{
    TAB_IOF::FRM_F_EDIT_IOF_NazwaObiektu.GetWindowTextW(lz.nazwa_obiektu,501);
    TAB_IOF::FRM_F_EDIT_IOF_Kraj.GetWindowTextW(lz.kraj,501);
    TAB_IOF::FRM_F_EDIT_IOF_Miejscowosc.GetWindowTextW(lz.miejscowosc,501);
    TAB_IOF::FRM_F_EDIT_IOF_Region.GetWindowTextW(lz.region,501);
    TAB_IOF::FRM_F_EDIT_IOF_PoraRoku.GetWindowTextW(lz.pora_roku,501);
    TAB_IOF::FRM_F_EDIT_IOF_Data.GetWindowTextW(lz.data,21);



int item;
item = TAB_IOF_Lokalizacje.GetNextItem(-1,LVIS_SELECTED);
if (item != -1)
{
struct Lok_zdjeciowe& lz_buff = lz_arr.ElementAt(item);

lz_buff = lz;
Refresh_Lz();
}


    TAB_IOF::FRM_F_BUTTON_IOF_Nowy.EnableWindow(TRUE);
    TAB_IOF::FRM_F_BUTTON_IOF_Usun.EnableWindow(TRUE);
    TAB_IOF::FRM_F_BUTTON_IOF_Zapisz.EnableWindow(TRUE);
    TAB_IOF::TAB_IOF_Lokalizacje.EnableWindow(TRUE);

    TAB_IOF::FRM_F_EDIT_IOF_NazwaObiektu.EnableWindow(FALSE);
    TAB_IOF::FRM_F_EDIT_IOF_Kraj.EnableWindow(FALSE);
    TAB_IOF::FRM_F_EDIT_IOF_Miejscowosc.EnableWindow(FALSE);
    TAB_IOF::FRM_F_EDIT_IOF_Region.EnableWindow(FALSE);
    TAB_IOF::FRM_F_EDIT_IOF_PoraRoku.EnableWindow(FALSE);
    TAB_IOF::FRM_F_EDIT_IOF_Data.EnableWindow(FALSE);
    TAB_IOF::FRM_F_BUTTON_IOF_Zatwierdz.EnableWindow(FALSE);
}

void TAB_IOF::Refresh_Lz(void)
{
    TAB_IOF_Lokalizacje.DeleteAllItems();

    int x;
    for (x=0;x<lz_arr.GetCount(); x++)
    {
        LVITEM lvitm;
        lvitm.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
        lvitm.iItem = x;
        lvitm.iSubItem = 0;
        lvitm.state = 0;
        lvitm.stateMask = 0;
        lvitm.lParam = (LPARAM) &lz_arr.GetAt(x);
        lvitm.pszText = LPSTR_TEXTCALLBACK;
        TAB_IOF_Lokalizacje.InsertItem(&lvitm);
    }

}

void TAB_IOF::Set_IOF(void)
{
    TAB_IOF_Lokalizacje.InsertColumn(0,L"Nazwa obiektu",LVCFMT_LEFT,150,1);
    TAB_IOF_Lokalizacje.InsertColumn(1,L"Kraj",LVCFMT_LEFT,150,2);
    TAB_IOF_Lokalizacje.InsertColumn(2,L"Miejscowość",LVCFMT_LEFT,150,3);
    TAB_IOF_Lokalizacje.InsertColumn(3,L"Region",LVCFMT_LEFT,150,4);
    TAB_IOF_Lokalizacje.InsertColumn(4,L"Pora roku",LVCFMT_LEFT,150,5);
    TAB_IOF_Lokalizacje.InsertColumn(5,L"Data",LVCFMT_LEFT,100,6);
    TAB_IOF_Lokalizacje.InsertColumn(6,L"ID",LVCFMT_LEFT,150,7);
    TAB_IOF_Lokalizacje.InsertColumn(7,L"IDPDB",LVCFMT_LEFT,150,8);
    TAB_IOF_Lokalizacje.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

    TAB_IOF::FRM_F_BUTTON_IOF_Zatwierdz.EnableWindow(FALSE);
    TAB_IOF::FRM_F_EDIT_IOF_Data.EnableWindow(FALSE);
    TAB_IOF::FRM_F_EDIT_IOF_Kraj.EnableWindow(FALSE);
    TAB_IOF::FRM_F_EDIT_IOF_Miejscowosc.EnableWindow(FALSE);
    TAB_IOF::FRM_F_EDIT_IOF_NazwaObiektu.EnableWindow(FALSE);
    TAB_IOF::FRM_F_EDIT_IOF_PoraRoku.EnableWindow(FALSE);
    TAB_IOF::FRM_F_EDIT_IOF_Region.EnableWindow(FALSE);

}

void TAB_IOF::Save_Lz(void)
{
    CFile plik;
    struct Lok_zdjeciowe lz_buf;
    plik.Open(flm_i.pths.BF_LZ,CFile::modeReadWrite | CFile::shareDenyNone);

    LONGLONG stop;
    LONGLONG i;
    int y;

    wchar_t buff[34];
    stop = plik.SeekToEnd();

    for (y=0;y<lz_arr.GetCount() ;y++ )
    {
        if (GetRecC_LZ() == 0)
            {
                plik.Seek(0,CFile::begin);
                plik.Write(&lz_arr.GetAt(y),sizeof(lz));

            }
        else if (GetRecC_LZ() > 0)
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
                        plik.Read(&lz_buf,sizeof(lz_buf));
                            if (lz_arr.GetAt(y).ID == lz_buf.ID)
                            {
                                plik.Seek(i,CFile::begin);
                                plik.Write(&lz_arr.GetAt(y),sizeof(lz));
                            }

                        i = i + sizeof(lz);
                    }
                    if (add_new_lz)
                    {

                        int x;
                        x = (lz_arr.GetCount()-1);
                        plik.Seek((plik.SeekToEnd()),CFile::begin);
                        plik.Write(&lz_arr.GetAt(x),sizeof(lz));
                        add_new_lz = false;
                    }
                }
            }

    }

    plik.Close();

}

int TAB_IOF::GetRecC_LZ(void)
{
CFile plik;
plik.Open(flm_i.pths.BF_LZ,CFile::modeRead | CFile::shareDenyNone);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
int rec_count = 0;
struct Lok_zdjeciowe lz_t;
if (stop == 0)
{
    plik.Close();
    return 0;
}
    for (i = 0; i <stop; )
    {
        plik.Seek(i,CFile::begin);
        plik.Read(&lz_t,sizeof(lz_t));
        rec_count = rec_count + 1;
        i = i + sizeof(lz_t);
    }
    plik.Close();
return rec_count;



}

int TAB_IOF::Get_Hi_ID_LZ(void)
{
if (GetRecC_LZ() == 0)
{
    return 0;
}


CFile plik;
plik.Open(flm_i.pths.BF_LZ,CFile::modeRead);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
for (i=0;i<stop; )
{
    plik.Seek(i,CFile::begin);
    if (i == (stop - sizeof(lz)))
    {
        plik.Read(&lz,sizeof(lz));
        plik.Close();
        return lz.ID;
    }
    i = i + sizeof(lz);
}


}

void TAB_IOF::Add_New_LZ(int id)
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

lz_arr.Add(lz);

Refresh_Lz();

}

void TAB_IOF::Usun_Rec_LZ(LONGLONG pos)
{
        struct Lok_zdjeciowe lz_src;
        lz.ID = 0;
        CFile plik;
        plik.Open(flm_i.pths.BF_LZ,CFile::modeWrite | CFile::shareDenyNone);
        plik.Seek(pos,CFile::begin);
        plik.Write(&lz,sizeof(lz));
        plik.Close();

        CFile::Rename(flm_i.pths.BF_LZ,(LPCTSTR)"BF_LZ.bf0");

        plik.Open(flm_i.pths.BF_LZ,CFile::modeCreate);
        plik.Close();
        CFile src_file;
        src_file.Open((LPCTSTR)"BF_LZ.bf0",CFile::modeRead);
        plik.Open(flm_i.pths.BF_LZ,CFile::modeWrite);
        LONGLONG i;
        for (i = 0; i <(src_file.SeekToEnd()) ; )
        {
            src_file.Seek(i,CFile::begin);
            src_file.Read(&lz_src,sizeof(lz_src));
            if (lz_src.ID == 0)
            {
                i = i + sizeof(lz_src);
            }
            else
            {
                plik.Write(&lz_src,sizeof(lz_src));
                i = i + sizeof(lz_src);
            }
        }
        plik.Close();
        src_file.Close();
        CFile::Remove((LPCTSTR)"BF_LZ.bf0");
        Fill_Lz();


}

void TAB_IOF::OnNMDblclkListFrmFIofLokzdj(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    if (lz_arr.GetCount() > 0)
    {
        OnBnClickedButtonFrmFIofEdytuj();
    }
    *pResult = 0;
}
void TAB_Obsada::ClearObsada(void)
{

    TAB_OB_LIST_Obsada.DeleteAllItems();

}

void TAB_Obsada::Fill_Ob(void)
{
CFile plik;
plik.Open(flm_ob.pths.BF_OB,CFile::modeRead);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();


TAB_OB_LIST_Obsada.DeleteAllItems();
ob_arr.RemoveAll();



for (i = 0;i<stop ; )
{
    plik.Seek(i,CFile::begin);
    plik.Read(&ob,sizeof(ob));
    if (ob.IDPDB == flm_ob.film_tbl.ID)
    {
        ob_arr.Add(ob);

    }
    i = i + sizeof(ob);
}
plik.Close();

Refresh_Ob();



}

void TAB_Obsada::Save_Ob(void)
{
    CFile plik;
    struct Obsada ob_buf;
    plik.Open(flm_ob.pths.BF_OB,CFile::modeReadWrite | CFile::shareDenyNone);
    int rec_count = 0;
    LONGLONG stop;
    LONGLONG i;
    int y;
    int stop_item = TAB_OB_LIST_Obsada.GetItemCount();
    wchar_t buff[34];
    stop = plik.SeekToEnd();

    for (y=0;y<ob_arr.GetCount() ;y++ )
    {
        if (GetRecC() == 0)
            {
                plik.Seek(0,CFile::begin);
                plik.Write(&ob_arr.GetAt(y),sizeof(ob));

            }
        else if (GetRecC() > 0)
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
                        plik.Read(&ob_buf,sizeof(ob_buf));
                            if (ob_arr.GetAt(y).ID == ob_buf.ID)
                            {
                                plik.Seek(i,CFile::begin);
                                plik.Write(&ob_arr.GetAt(y),sizeof(ob));
                            }

                        i = i + sizeof(ob);
                    }
                    if (add_new_ob)
                    {

                        int x;
                        x = (ob_arr.GetCount()-1);
                        plik.Seek((plik.SeekToEnd()),CFile::begin);
                        plik.Write(&ob_arr.GetAt(x),sizeof(ob));
                        add_new_ob = false;
                    }
                }
            }

    }

    plik.Close();



}

void TAB_Obsada::Set_Obsada(void)
{
TAB_OB_LIST_Obsada.InsertColumn(0,L"Imię i Nazwisko",LVCFMT_LEFT,150,1);
TAB_OB_LIST_Obsada.InsertColumn(1,L"Rola",LVCFMT_LEFT,150,2);
TAB_OB_LIST_Obsada.InsertColumn(2,L"ID",LVCFMT_LEFT,150,3);
TAB_OB_LIST_Obsada.InsertColumn(3,L"IDPDB",LVCFMT_LEFT,150,4);
TAB_OB_LIST_Obsada.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

TAB_Obsada::FRM_F_EDIT_ImieNazw.EnableWindow(FALSE);
TAB_Obsada::FRM_F_EDIT_Rola.EnableWindow(FALSE);
TAB_Obsada::FRM_F_BUTTON_OB_ZATWIERDZ.EnableWindow(FALSE);



}
void TAB_Obsada::OnBnClickedFButtonObEdytuj()
{
    TAB_Obsada::FRM_F_BUTTON_OB_NOWY.EnableWindow(FALSE);
    TAB_Obsada::FRM_F_BUTTON_OB_USUN.EnableWindow(FALSE);
    TAB_Obsada::FRM_F_BUTTON_OB_ZAPISZ.EnableWindow(FALSE);
    TAB_Obsada::TAB_OB_LIST_Obsada.EnableWindow(FALSE);

    TAB_Obsada::FRM_F_EDIT_ImieNazw.EnableWindow(TRUE);
    TAB_Obsada::FRM_F_EDIT_Rola.EnableWindow(TRUE);
    TAB_Obsada::FRM_F_BUTTON_OB_ZATWIERDZ.EnableWindow(TRUE);

wchar_t buff[34];

int item;
item = TAB_OB_LIST_Obsada.GetNextItem(-1,LVIS_SELECTED);
if (item != -1)
{
    wchar_t buff201[201];
    wchar_t buff501[501];
    TAB_OB_LIST_Obsada.GetItemText(item,0,buff501,501);
    TAB_Obsada::FRM_F_EDIT_ImieNazw.SetWindowTextW(buff501);

    TAB_OB_LIST_Obsada.GetItemText(item,1,buff201,201);
    TAB_Obsada::FRM_F_EDIT_Rola.SetWindowTextW(buff201);

    TAB_OB_LIST_Obsada.GetItemText(item,2,buff,34);
    ob.ID = _wtoi(buff);

    TAB_OB_LIST_Obsada.GetItemText(item,3,buff,34);
    ob.IDPDB = _wtoi(buff);
}


}

void TAB_Obsada::OnBnClickedFButtonObZatwierdz()
{
    TAB_Obsada::FRM_F_EDIT_ImieNazw.GetWindowTextW(ob.imie_nazw,501);
    TAB_Obsada::FRM_F_EDIT_Rola.GetWindowTextW(ob.rola,201);


int item;
item = TAB_OB_LIST_Obsada.GetNextItem(-1,LVIS_SELECTED);
if (item != -1)
{
struct Obsada& ob_buff = ob_arr.ElementAt(item);

ob_buff = ob;
Refresh_Ob();
}


TAB_Obsada::FRM_F_BUTTON_OB_NOWY.EnableWindow(TRUE);
TAB_Obsada::FRM_F_BUTTON_OB_USUN.EnableWindow(TRUE);
TAB_Obsada::FRM_F_BUTTON_OB_ZAPISZ.EnableWindow(TRUE);
TAB_Obsada::TAB_OB_LIST_Obsada.EnableWindow(TRUE);

TAB_Obsada::FRM_F_EDIT_ImieNazw.EnableWindow(FALSE);
TAB_Obsada::FRM_F_EDIT_Rola.EnableWindow(FALSE);

TAB_Obsada::FRM_F_BUTTON_OB_ZATWIERDZ.EnableWindow(FALSE);


}

void TAB_Obsada::OnBnClickedButtonFrmFObNowy()
{
    Save_Ob();
    Add_New_Ob(Get_Hi_ID());
    add_new_ob = true;

}

void TAB_Obsada::OnBnClickedButtonFrmFObZapisz()
{
    Save_Ob();
}

void TAB_Obsada::OnBnClickedButtonFrmFObUsun()
{
wchar_t buff[34];
LVITEM lvitm;
int delitem = 0;
int delID = 0;
delitem = TAB_OB_LIST_Obsada.GetNextItem(-1,LVNI_SELECTED);
TAB_OB_LIST_Obsada.GetItemText(delitem,2,(LPTSTR)buff,34);
delID = _wtoi(buff);

CFile plik;
plik.Open(flm_ob.pths.BF_OB,CFile::modeRead | CFile::shareDenyNone);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
for (i=0;i<stop; )
{
    plik.Seek(i,CFile::begin);
    plik.Read(&ob,sizeof(ob));
    if (delID == ob.ID)
    {
    plik.Close();
    Usun_Rec(i);
    break;
    }
    i = i + sizeof(ob);
}
if (plik.m_hFile != CFile::hFileNull)
{
    plik.Close();
}

}

void TAB_Obsada::Add_New_Ob(int id)
{

int id_new;
id_new = id + 1;
int itemcount = 0;
wchar_t buff[34];


// Metoda callbacku
ob.ID = id_new;
ob.IDPDB = flm_ob.film_tbl.ID;
wcscpy(ob.imie_nazw,L"Wpisz tutaj coś");
wcscpy(ob.rola,L"Wpisz tutaj coś");

ob_arr.Add(ob);

Refresh_Ob();


}

int TAB_Obsada::Get_Hi_ID(void)
{

if (GetRecC() == 0)
{
    return 0;
}


CFile plik;
plik.Open(flm_ob.pths.BF_OB,CFile::modeRead);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
for (i=0;i<stop; )
{
    plik.Seek(i,CFile::begin);
    if (i == (stop - sizeof(ob)))
    {
        plik.Read(&ob,sizeof(ob));
        plik.Close();
        return ob.ID;
    }
    i = i + sizeof(ob);
}
plik.Close();

}

int TAB_Obsada::GetRecC(void)
{
CFile plik;
plik.Open(flm_ob.pths.BF_OB,CFile::modeRead | CFile::shareDenyNone);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
int rec_count = 0;
struct Obsada ob_t;
if (stop == 0)
{
    plik.Close();
    return 0;
}
    for (i = 0; i <stop; )
    {
        plik.Seek(i,CFile::begin);
        plik.Read(&ob_t,sizeof(ob_t));
        rec_count = rec_count + 1;
        i = i + sizeof(ob_t);
    }
    plik.Close();
return rec_count;
}

void TAB_Obsada::Refresh_Ob(void)
{

    TAB_OB_LIST_Obsada.DeleteAllItems();

    int x;
    for (x=0;x<ob_arr.GetCount(); x++)
    {
        LVITEM lvitm;
        lvitm.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
        lvitm.iItem = x;
        lvitm.iSubItem = 0;
        lvitm.state = 0;
        lvitm.stateMask = 0;
        lvitm.lParam = (LPARAM) &ob_arr.GetAt(x);
        lvitm.pszText = LPSTR_TEXTCALLBACK;
        TAB_OB_LIST_Obsada.InsertItem(&lvitm);
    }
}
void TAB_Obsada::OnLvnGetdispinfoListFrmFObObsada(NMHDR *pNMHDR, LRESULT *pResult)
{
    wchar_t buff[34];

    NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
    int x;
    x = pDispInfo->item.iItem;

    switch (pDispInfo->item.iSubItem)
    {
    case 0:
        wcscpy(pDispInfo->item.pszText,ob_arr.GetAt(x).imie_nazw);
        break;
    case 1:
        wcscpy(pDispInfo->item.pszText,ob_arr.GetAt(x).rola);
        break;
    case 2:
        _itow(ob_arr.GetAt(x).ID ,buff,10);
        wcscpy(pDispInfo->item.pszText,buff); // ID
        break;
    case 3:
        _itow(ob_arr.GetAt(x).IDPDB ,buff,10);
        wcscpy(pDispInfo->item.pszText,buff);  //IDPDB
        break;
    }

    *pResult = 0;
}

void TAB_Obsada::Usun_Rec(LONGLONG pos)
{

        struct Obsada ob_src;
        ob.ID = 0;
        CFile plik;
        plik.Open(flm_ob.pths.BF_OB,CFile::modeWrite | CFile::shareDenyNone);
        plik.Seek(pos,CFile::begin);
        plik.Write(&ob,sizeof(ob));
        plik.Close();

        CFile::Rename(flm_ob.pths.BF_OB,(LPCTSTR)"BF_OB.bf0");

        plik.Open(flm_ob.pths.BF_OB,CFile::modeCreate);
        plik.Close();
        CFile src_file;
        src_file.Open((LPCTSTR)"BF_OB.bf0",CFile::modeRead);
        plik.Open(flm_ob.pths.BF_OB,CFile::modeWrite);
        LONGLONG i;
        for (i = 0; i <(src_file.SeekToEnd()) ; )
        {
            src_file.Seek(i,CFile::begin);
            src_file.Read(&ob_src,sizeof(ob_src));
            if (ob_src.ID == 0)
            {
                i = i + sizeof(ob_src);
            }
            else
            {
                plik.Write(&ob_src,sizeof(ob_src));
                i = i + sizeof(ob_src);
            }
        }
        plik.Close();
        src_file.Close();
        CFile::Remove((LPCTSTR)"BF_OB.bf0");
        Fill_Ob();

}

void TAB_Obsada::OnNMDblclkListFrmFObObsada(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    if (ob_arr.GetCount() > 0)
    {
        OnBnClickedFButtonObEdytuj();
    }
    *pResult = 0;
}
void TAB_Oocena::OnBnClickedButtonFrmFONowy()
{

    // na podstawie statycznej skałdowej klasy Ftbl - bedacej struktura typu Film - film_tbl nalezy utworzyc nowy rekord w pliku "BF_OC.bf"

    Save_Oc();
    Add_New_Oc(Get_Hi_ID());
    add_new = true;



}

void TAB_Oocena::Save_Oc(void)
{
    // ta i podobne procedury zapisuja do danego pliku tabele struktur zawierajacych dane z pól list w form. film.
// w przypadku nadpisywania danych wyszukuja najpierw czy rekord o danym id istnieje w pliku, potem jesli tak nad-
// -pisuja go, a jesli nie dodaja na koncu, i tak dla kazdej komorki tabeli struktur.


    CFile plik;
    struct Ocena oc_buf;
    plik.Open(flm_o.pths.BF_OC,CFile::modeReadWrite | CFile::shareDenyNone);
    int rec_count = 0;
    LONGLONG stop;
    LONGLONG i;
    int y;
    int stop_item = TAB_O_Zasoby.GetItemCount();
    wchar_t buff[34];
    stop = plik.SeekToEnd();

    for (y=0;y<oc_arr.GetCount() ;y++ )
    {
        if (GetRecC() == 0)
            {
                plik.Seek(0,CFile::begin);
                plik.Write(&oc_arr.GetAt(y),sizeof(oc));

            }
        else if (GetRecC() > 0)
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
                        plik.Read(&oc_buf,sizeof(oc_buf));
                            if (oc_arr.GetAt(y).ID == oc_buf.ID)
                            {
                                plik.Seek(i,CFile::begin);
                                plik.Write(&oc_arr.GetAt(y),sizeof(oc));
                            }

                        i = i + sizeof(oc);
                    }
                    if (add_new)
                    {

                        int x;
                        x = (oc_arr.GetCount()-1);
                        plik.Seek((plik.SeekToEnd()),CFile::begin);
                        plik.Write(&oc_arr.GetAt(x),sizeof(oc));
                        add_new = false;
                    }
                }
            }

    }

    plik.Close();

//Fill_Oc(false);

}

void TAB_Oocena::Fill_Oc(bool nie_kas)
{
// ta i podobne procedury odczytuja plik bd danej tabeli i sprawdzaja czy idpdb sie zgadza z polem if flm_o.film_tbl
// a jesli tak to pobieraja z pliku do tabeli struktur zawierajacej dane z jednego pola listy form. film dla jednego
// rekordu, jesli nie ida dalej wzdluz pliku do jego konca..

CFile plik;
plik.Open(flm_o.pths.BF_OC,CFile::modeRead);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();


TAB_O_Zasoby.DeleteAllItems();
oc_arr.RemoveAll();



for (i = 0;i<stop ; )
{
    plik.Seek(i,CFile::begin);
    plik.Read(&oc,sizeof(oc));
    if (oc.IDPDB == flm_o.film_tbl.ID)
    {
        oc_arr.Add(oc);

    }
    i = i + sizeof(oc);
}
plik.Close();

Refresh_Oc();



}

void TAB_Oocena::OnBnClickedButtonFrmFOZapisz()
{
Save_Oc();

}

void TAB_Oocena::ClearOcena(void)
{
        TAB_O_Zasoby.DeleteAllItems();

}

int TAB_Oocena::Get_Hi_ID(void)
{

if (GetRecC() == 0)
{
    return 0;
}


CFile plik;
plik.Open(flm_o.pths.BF_OC,CFile::modeRead);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
for (i=0;i<stop; )
{
    plik.Seek(i,CFile::begin);
    if (i == (stop - sizeof(oc)))
    {
        plik.Read(&oc,sizeof(oc));
        plik.Close();
        return oc.ID;
    }
    i = i + sizeof(oc);
}
plik.Close();

}

void TAB_Oocena::Add_New_Oc(int id)
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


oc_arr.Add(oc);

Refresh_Oc();


}

void TAB_Oocena::OnBnClickedButtonFrmFOUsun()
{

wchar_t buff[34];
LVITEM lvitm;
int delitem = 0;
int delID = 0;
delitem = TAB_O_Zasoby.GetNextItem(-1,LVNI_SELECTED);
TAB_O_Zasoby.GetItemText(delitem,5,(LPTSTR)buff,34);
delID = _wtoi(buff);

CFile plik;
plik.Open(flm_o.pths.BF_OC,CFile::modeRead | CFile::shareDenyNone);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
for (i=0;i<stop; )
{
    plik.Seek(i,CFile::begin);
    plik.Read(&oc,sizeof(oc));
    if (delID == oc.ID)
    {
    plik.Close();
    Usun_Rec(i);
    break;
    }
    i = i + sizeof(oc);
}
if (plik.m_hFile != CFile::hFileNull)
{
    plik.Close();
}

}

int TAB_Oocena::GetRecC(void)
{
CFile plik;
plik.Open(flm_o.pths.BF_OC,CFile::modeRead | CFile::shareDenyNone);
LONGLONG i;
LONGLONG stop;
stop = plik.SeekToEnd();
int rec_count = 0;
struct Ocena oc_t;
if (stop == 0)
{
    plik.Close();
    return 0;
}
    for (i = 0; i <stop; )
    {
        plik.Seek(i,CFile::begin);
        plik.Read(&oc_t,sizeof(oc_t));
        rec_count = rec_count + 1;
        i = i + sizeof(oc_t);
    }
    plik.Close();
return rec_count;
}

void TAB_Oocena::Usun_Rec(LONGLONG pos)
{

        struct Ocena oc_src;
        oc.ID = 0;
        CFile plik;
        plik.Open(flm_o.pths.BF_OC,CFile::modeWrite | CFile::shareDenyNone);
        plik.Seek(pos,CFile::begin);
        plik.Write(&oc,sizeof(oc));
        plik.Close();

        CFile::Rename(flm_o.pths.BF_OC,(LPCTSTR)"BF_OC.bf0");

        plik.Open(flm_o.pths.BF_OC,CFile::modeCreate);
        plik.Close();
        CFile src_file;
        src_file.Open((LPCTSTR)"BF_OC.bf0",CFile::modeRead);
        plik.Open(flm_o.pths.BF_OC,CFile::modeWrite);
        LONGLONG i;
        for (i = 0; i <(src_file.SeekToEnd()) ; )
        {
            src_file.Seek(i,CFile::begin);
            src_file.Read(&oc_src,sizeof(oc_src));
            if (oc_src.ID == 0)
            {
                i = i + sizeof(oc_src);
            }
            else
            {
                plik.Write(&oc_src,sizeof(oc_src));
                i = i + sizeof(oc_src);
            }
        }
        plik.Close();
        src_file.Close();
        CFile::Remove((LPCTSTR)"BF_OC.bf0");
        Fill_Oc(false);

}

void TAB_Oocena::SetZasoby(void)
{
    TAB_O_Zasoby.InsertColumn(0,L"Nazwa",LVCFMT_LEFT,150,1);
    TAB_O_Zasoby.InsertColumn(1,L"Tytuł tekstu",LVCFMT_LEFT,150,2);
    TAB_O_Zasoby.InsertColumn(2,L"Autor tekstu",LVCFMT_LEFT,150,3);
    TAB_O_Zasoby.InsertColumn(3,L"Strona WWW",LVCFMT_LEFT,150,4);
    TAB_O_Zasoby.InsertColumn(4,L"Ocena krytyka",LVCFMT_LEFT,150,5);
    TAB_O_Zasoby.InsertColumn(5,L"ID",LVCFMT_LEFT,150,6);
    TAB_O_Zasoby.InsertColumn(6,L"IDPDB",LVCFMT_LEFT,150,7);
    TAB_O_Zasoby.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

TAB_Oocena::FRM_F_Oc_EDIT_Autor.EnableWindow(FALSE);
TAB_Oocena::FRM_F_Oc_EDIT_Nazwa.EnableWindow(FALSE);
TAB_Oocena::FRM_F_Oc_EDIT_Ocena.EnableWindow(FALSE);
TAB_Oocena::FRM_F_Oc_EDIT_Tytul.EnableWindow(FALSE);
TAB_Oocena::FRM_F_Oc_EDIT_WWW.EnableWindow(FALSE);
TAB_Oocena::FRM_F_Oc_BUTTON_Zatwierdz.EnableWindow(FALSE);


}
void TAB_Oocena::OnLvnGetdispinfoListFrmFOOcena(NMHDR *pNMHDR, LRESULT *pResult)
{
    wchar_t buff[34];

    NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);

    int x;
    x = pDispInfo->item.iItem;

    switch (pDispInfo->item.iSubItem)
    {
    case 0:
        wcscpy(pDispInfo->item.pszText,oc_arr.GetAt(x).nazwa);
        break;
    case 1:
        wcscpy(pDispInfo->item.pszText,oc_arr.GetAt(x).tytul_tekstu);
        break;
    case 2:
        wcscpy(pDispInfo->item.pszText,oc_arr.GetAt(x).autor_tekstu);
        break;
    case 3:
        wcscpy(pDispInfo->item.pszText,oc_arr.GetAt(x).strona_www);
        break;
    case 4:
        wcscpy(pDispInfo->item.pszText,oc_arr.GetAt(x).ocena_krytyka);
        break;
    case 5:
        _itow(oc_arr.GetAt(x).ID ,buff,10);
        wcscpy(pDispInfo->item.pszText,buff); // ID
        break;
    case 6:
        _itow(oc_arr.GetAt(x).IDPDB ,buff,10);
        wcscpy(pDispInfo->item.pszText,buff);  //IDPDB
        break;
    }

    *pResult = 0;

}

void TAB_Oocena::OnBnClickedButtonFrmFOcZatwierdz()
{
    TAB_Oocena::FRM_F_Oc_EDIT_Nazwa.GetWindowTextW(oc.nazwa,201);
    TAB_Oocena::FRM_F_Oc_EDIT_Tytul.GetWindowTextW(oc.tytul_tekstu,201);
    TAB_Oocena::FRM_F_Oc_EDIT_Autor.GetWindowTextW(oc.autor_tekstu,201);
    TAB_Oocena::FRM_F_Oc_EDIT_WWW.GetWindowTextW(oc.strona_www,501);
    TAB_Oocena::FRM_F_Oc_EDIT_Ocena.GetWindowTextW(oc.ocena_krytyka,501);




int item;
item = TAB_O_Zasoby.GetNextItem(-1,LVIS_SELECTED);
if (item != -1)
{
struct Ocena& oc_buff = oc_arr.ElementAt(item);

oc_buff = oc;
Refresh_Oc();
}


TAB_Oocena::FRM_F_Oc_BUTTON_Nowy.EnableWindow(TRUE);
TAB_Oocena::FRM_F_Oc_BUTTON_Usun.EnableWindow(TRUE);
TAB_Oocena::FRM_F_Oc_BUTTON_Zapisz.EnableWindow(TRUE);
TAB_Oocena::TAB_O_Zasoby.EnableWindow(TRUE);

TAB_Oocena::FRM_F_Oc_EDIT_Autor.EnableWindow(FALSE);
TAB_Oocena::FRM_F_Oc_EDIT_Nazwa.EnableWindow(FALSE);
TAB_Oocena::FRM_F_Oc_EDIT_Ocena.EnableWindow(FALSE);
TAB_Oocena::FRM_F_Oc_EDIT_Tytul.EnableWindow(FALSE);
TAB_Oocena::FRM_F_Oc_EDIT_WWW.EnableWindow(FALSE);
TAB_Oocena::FRM_F_Oc_BUTTON_Zatwierdz.EnableWindow(FALSE);


}

void TAB_Oocena::OnBnClickedButtonFrmFOcZEdytuj()
{
TAB_Oocena::FRM_F_Oc_BUTTON_Nowy.EnableWindow(FALSE);
TAB_Oocena::FRM_F_Oc_BUTTON_Usun.EnableWindow(FALSE);
TAB_Oocena::FRM_F_Oc_BUTTON_Zapisz.EnableWindow(FALSE);
TAB_Oocena::TAB_O_Zasoby.EnableWindow(FALSE);

TAB_Oocena::FRM_F_Oc_EDIT_Autor.EnableWindow(TRUE);
TAB_Oocena::FRM_F_Oc_EDIT_Nazwa.EnableWindow(TRUE);
TAB_Oocena::FRM_F_Oc_EDIT_Ocena.EnableWindow(TRUE);
TAB_Oocena::FRM_F_Oc_EDIT_Tytul.EnableWindow(TRUE);
TAB_Oocena::FRM_F_Oc_EDIT_WWW.EnableWindow(TRUE);
TAB_Oocena::FRM_F_Oc_BUTTON_Zatwierdz.EnableWindow(TRUE);



wchar_t buff[34];

int item;
item = TAB_O_Zasoby.GetNextItem(-1,LVIS_SELECTED);
if (item != -1)
{
    wchar_t buff201[201];
    wchar_t buff501[501];
    TAB_O_Zasoby.GetItemText(item,0,buff201,201);
    TAB_Oocena::FRM_F_Oc_EDIT_Nazwa.SetWindowTextW(buff201);
    TAB_O_Zasoby.GetItemText(item,1,buff201,201);
    TAB_Oocena::FRM_F_Oc_EDIT_Tytul.SetWindowTextW(buff201);
    TAB_O_Zasoby.GetItemText(item,2,buff201,201);
    TAB_Oocena::FRM_F_Oc_EDIT_Autor.SetWindowTextW(buff201);
    TAB_O_Zasoby.GetItemText(item,3,buff501,501);
    TAB_Oocena::FRM_F_Oc_EDIT_WWW.SetWindowTextW(buff501);
    TAB_O_Zasoby.GetItemText(item,4,buff201,201);
    TAB_Oocena::FRM_F_Oc_EDIT_Ocena.SetWindowTextW(buff201);
    TAB_O_Zasoby.GetItemText(item,5,buff,34);
    oc.ID = _wtoi(buff);
    TAB_O_Zasoby.GetItemText(item,6,buff,34);
    oc.IDPDB = _wtoi(buff);
}

}

void TAB_Oocena::Refresh_Oc(void)
{

    TAB_O_Zasoby.DeleteAllItems();

    int x;
    for (x=0;x<oc_arr.GetCount(); x++)
    {
        LVITEM lvitm;
        lvitm.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
        lvitm.iItem = x;
        lvitm.iSubItem = 0;
        lvitm.state = 0;
        lvitm.stateMask = 0;
        lvitm.lParam = (LPARAM) &oc_arr.GetAt(x);
        lvitm.pszText = LPSTR_TEXTCALLBACK;
        TAB_O_Zasoby.InsertItem(&lvitm);
    }
}
void TAB_Oocena::OnNMDblclkListFrmFOOcena(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    if (oc_arr.GetCount() > 0)
    {
        OnBnClickedButtonFrmFOcZEdytuj();
    }
    *pResult = 0;
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

void TAB_Produkcja::Set_Prod(void)
{


    //ListCtrl Produkcja
TAB_Prod_LIST_Prod.InsertColumn(0,L"Nazwa firmy",LVCFMT_LEFT,150,1);
TAB_Prod_LIST_Prod.InsertColumn(1,L"Adres",LVCFMT_LEFT,150,2);
TAB_Prod_LIST_Prod.InsertColumn(2,L"Telefon",LVCFMT_LEFT,100,3);
TAB_Prod_LIST_Prod.InsertColumn(3,L"Fax",LVCFMT_LEFT,100,4);
TAB_Prod_LIST_Prod.InsertColumn(4,L"E-Mail",LVCFMT_LEFT,150,5);
TAB_Prod_LIST_Prod.InsertColumn(5,L"Strona WWW",LVCFMT_LEFT,150,6);
TAB_Prod_LIST_Prod.InsertColumn(6,L"Narodowość",LVCFMT_LEFT,150,7);
TAB_Prod_LIST_Prod.InsertColumn(7,L"ID",LVCFMT_LEFT,150,8);
TAB_Prod_LIST_Prod.InsertColumn(8,L"IDPDB",LVCFMT_LEFT,150,9);
TAB_Prod_LIST_Prod.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

TAB_Produkcja::FRM_F_EDIT_PP_NAZWAF.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_PP_ADRES.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_PP_TEL.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_PP_FAX.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_PP_EMAIL.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pp_WWW.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pp_NAROD.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_BUTTON_pp_ZATWIERDZ.EnableWindow(FALSE);


// ListCtrl Dystrybucja

TAB_Prod_LIST_Dystr.InsertColumn(0,L"Nazwa firmy",LVCFMT_LEFT,150,1);
TAB_Prod_LIST_Dystr.InsertColumn(1,L"Adres",LVCFMT_LEFT,150,2);
TAB_Prod_LIST_Dystr.InsertColumn(2,L"Telefon",LVCFMT_LEFT,150,3);
TAB_Prod_LIST_Dystr.InsertColumn(3,L"Fax",LVCFMT_LEFT,150,4);
TAB_Prod_LIST_Dystr.InsertColumn(4,L"E-mail",LVCFMT_LEFT,150,5);
TAB_Prod_LIST_Dystr.InsertColumn(5,L"Strona WWW",LVCFMT_LEFT,150,6);
TAB_Prod_LIST_Dystr.InsertColumn(6,L"Narodowość",LVCFMT_LEFT,150,7);
TAB_Prod_LIST_Dystr.InsertColumn(7,L"ID",LVCFMT_LEFT,150,8);
TAB_Prod_LIST_Dystr.InsertColumn(8,L"IDPDB",LVCFMT_LEFT,150,9);
TAB_Prod_LIST_Dystr.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

TAB_Produkcja::FRM_F_EDIT_pd_NAZWAF.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pd_ADRES.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pd_TEL.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pd_FAX.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pd_EMAIL.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pd_WWW.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pd_NAROD.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_BUTTON_pd_ZATWIERDZ.EnableWindow(FALSE);

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

void TAB_Produkcja::OnBnClickedFButtonPpEdytuj()
{
    TAB_Produkcja::FRM_F_BUTTON_Pp_Nowy.EnableWindow(FALSE);
    TAB_Produkcja::FRM_F_BUTTON_Pp_Usun.EnableWindow(FALSE);
    TAB_Produkcja::FRM_F_BUTTON_Pp_Zapisz.EnableWindow(FALSE);
    TAB_Produkcja::TAB_Prod_LIST_Prod.EnableWindow(FALSE);

    TAB_Produkcja::FRM_F_EDIT_PP_NAZWAF.EnableWindow(TRUE);
    TAB_Produkcja::FRM_F_EDIT_PP_ADRES.EnableWindow(TRUE);
    TAB_Produkcja::FRM_F_EDIT_PP_TEL.EnableWindow(TRUE);
    TAB_Produkcja::FRM_F_EDIT_PP_FAX.EnableWindow(TRUE);
    TAB_Produkcja::FRM_F_EDIT_PP_EMAIL.EnableWindow(TRUE);
    TAB_Produkcja::FRM_F_EDIT_pp_WWW.EnableWindow(TRUE);
    TAB_Produkcja::FRM_F_EDIT_pp_NAROD.EnableWindow(TRUE);
    TAB_Produkcja::FRM_F_BUTTON_pp_ZATWIERDZ.EnableWindow(TRUE);


wchar_t buff[34];

int item;
item = TAB_Prod_LIST_Prod.GetNextItem(-1,LVIS_SELECTED);
if (item != -1)
{
    wchar_t buff201[201];
    wchar_t buff501[501];
    TAB_Prod_LIST_Prod.GetItemText(item,0,buff501,501);
    TAB_Produkcja::FRM_F_EDIT_PP_NAZWAF.SetWindowTextW(buff501);

    TAB_Prod_LIST_Prod.GetItemText(item,1,buff501,501);
    TAB_Produkcja::FRM_F_EDIT_PP_ADRES.SetWindowTextW(buff501);

    TAB_Prod_LIST_Prod.GetItemText(item,2,buff201,31);
    TAB_Produkcja::FRM_F_EDIT_PP_TEL.SetWindowTextW(buff201);

    TAB_Prod_LIST_Prod.GetItemText(item,3,buff201,31);
    TAB_Produkcja::FRM_F_EDIT_PP_FAX.SetWindowTextW(buff201);

    TAB_Prod_LIST_Prod.GetItemText(item,4,buff201,201);
    TAB_Produkcja::FRM_F_EDIT_PP_EMAIL.SetWindowTextW(buff201);

    TAB_Prod_LIST_Prod.GetItemText(item,5,buff501,501);
    TAB_Produkcja::FRM_F_EDIT_pp_WWW.SetWindowTextW(buff501);

    TAB_Prod_LIST_Prod.GetItemText(item,6,buff201,201);
    TAB_Produkcja::FRM_F_EDIT_pp_NAROD.SetWindowTextW(buff201);


    TAB_Prod_LIST_Prod.GetItemText(item,7,buff,34);
    pp.ID = _wtoi(buff);
    TAB_Prod_LIST_Prod.GetItemText(item,8,buff,34);
    pp.IDPDB = _wtoi(buff);
}






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

void TAB_Produkcja::OnBnClickedFButtonPpZatwierdz()
{
    TAB_Produkcja::FRM_F_EDIT_PP_NAZWAF.GetWindowTextW(pp.nazwa_firmy,501);
    TAB_Produkcja::FRM_F_EDIT_PP_ADRES.GetWindowTextW(pp.adres,501);
    TAB_Produkcja::FRM_F_EDIT_PP_TEL.GetWindowTextW(pp.telefon,31);
    TAB_Produkcja::FRM_F_EDIT_PP_FAX.GetWindowTextW(pp.fax,31);
    TAB_Produkcja::FRM_F_EDIT_PP_EMAIL.GetWindowTextW(pp.email,201);
    TAB_Produkcja::FRM_F_EDIT_pp_WWW.GetWindowTextW(pp.strona_www,501);
    TAB_Produkcja::FRM_F_EDIT_pp_NAROD.GetWindowTextW(pp.narodowosc,201);


int item;
item = TAB_Prod_LIST_Prod.GetNextItem(-1,LVIS_SELECTED);
if (item != -1)
{
struct Producent& pp_buff = pp_arr.ElementAt(item);

pp_buff = pp;
Refresh_PP();
}


TAB_Produkcja::FRM_F_BUTTON_Pp_Nowy.EnableWindow(TRUE);
TAB_Produkcja::FRM_F_BUTTON_Pp_Usun.EnableWindow(TRUE);
TAB_Produkcja::FRM_F_BUTTON_Pp_Zapisz.EnableWindow(TRUE);
TAB_Produkcja::TAB_Prod_LIST_Prod.EnableWindow(TRUE);

TAB_Produkcja::FRM_F_EDIT_PP_NAZWAF.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_PP_ADRES.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_PP_TEL.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_PP_FAX.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_PP_EMAIL.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pp_WWW.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pp_NAROD.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_BUTTON_pp_ZATWIERDZ.EnableWindow(FALSE);


}

void TAB_Produkcja::OnBnClickedButtonFrmFPDystrNowy()
{

    Save_PD();
    Add_New_PD(Get_Hi_ID_PD());
    add_new_pd = true;
}

void TAB_Produkcja::OnBnClickedFButtonPdEdytuj()
{
    TAB_Produkcja::FRM_F_BUTTON_PD_NOWY.EnableWindow(FALSE);
    TAB_Produkcja::FRM_F_BUTTON_PD_USUN.EnableWindow(FALSE);
    TAB_Produkcja::FRM_F_BUTTON_PD_ZAPISZ.EnableWindow(FALSE);
    TAB_Produkcja::TAB_Prod_LIST_Dystr.EnableWindow(FALSE);

    TAB_Produkcja::FRM_F_EDIT_pd_NAZWAF.EnableWindow(TRUE);
    TAB_Produkcja::FRM_F_EDIT_pd_ADRES.EnableWindow(TRUE);
    TAB_Produkcja::FRM_F_EDIT_pd_TEL.EnableWindow(TRUE);
    TAB_Produkcja::FRM_F_EDIT_pd_FAX.EnableWindow(TRUE);
    TAB_Produkcja::FRM_F_EDIT_pd_EMAIL.EnableWindow(TRUE);
    TAB_Produkcja::FRM_F_EDIT_pd_WWW.EnableWindow(TRUE);
    TAB_Produkcja::FRM_F_EDIT_pd_NAROD.EnableWindow(TRUE);
    TAB_Produkcja::FRM_F_BUTTON_pd_ZATWIERDZ.EnableWindow(TRUE);


wchar_t buff[34];

int item;
item = TAB_Prod_LIST_Dystr.GetNextItem(-1,LVIS_SELECTED);
if (item != -1)
{
    wchar_t buff201[201];
    wchar_t buff501[501];
    TAB_Prod_LIST_Dystr.GetItemText(item,0,buff501,501);
    TAB_Produkcja::FRM_F_EDIT_pd_NAZWAF.SetWindowTextW(buff501);

    TAB_Prod_LIST_Dystr.GetItemText(item,1,buff501,501);
    TAB_Produkcja::FRM_F_EDIT_pd_ADRES.SetWindowTextW(buff501);

    TAB_Prod_LIST_Dystr.GetItemText(item,2,buff201,31);
    TAB_Produkcja::FRM_F_EDIT_pd_TEL.SetWindowTextW(buff201);

    TAB_Prod_LIST_Dystr.GetItemText(item,3,buff201,31);
    TAB_Produkcja::FRM_F_EDIT_pd_FAX.SetWindowTextW(buff201);

    TAB_Prod_LIST_Dystr.GetItemText(item,4,buff201,201);
    TAB_Produkcja::FRM_F_EDIT_pd_EMAIL.SetWindowTextW(buff201);

    TAB_Prod_LIST_Dystr.GetItemText(item,5,buff501,501);
    TAB_Produkcja::FRM_F_EDIT_pd_WWW.SetWindowTextW(buff501);

    TAB_Prod_LIST_Dystr.GetItemText(item,6,buff201,201);
    TAB_Produkcja::FRM_F_EDIT_pd_NAROD.SetWindowTextW(buff201);


    TAB_Prod_LIST_Dystr.GetItemText(item,7,buff,34);
    pd.ID = _wtoi(buff);
    TAB_Prod_LIST_Dystr.GetItemText(item,8,buff,34);
    pd.IDPDB = _wtoi(buff);
}
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

void TAB_Produkcja::OnBnClickedFButtonPdZatwierdz()
{
    TAB_Produkcja::FRM_F_EDIT_pd_NAZWAF.GetWindowTextW(pd.nazwa_firmy,501);
    TAB_Produkcja::FRM_F_EDIT_pd_ADRES.GetWindowTextW(pd.adres,501);
    TAB_Produkcja::FRM_F_EDIT_pd_TEL.GetWindowTextW(pd.telefon,31);
    TAB_Produkcja::FRM_F_EDIT_pd_FAX.GetWindowTextW(pd.fax,31);
    TAB_Produkcja::FRM_F_EDIT_pd_EMAIL.GetWindowTextW(pd.email,201);
    TAB_Produkcja::FRM_F_EDIT_pd_WWW.GetWindowTextW(pd.strona_www,501);
    TAB_Produkcja::FRM_F_EDIT_pd_NAROD.GetWindowTextW(pd.narodowosc,201);


int item;
item = TAB_Prod_LIST_Dystr.GetNextItem(-1,LVIS_SELECTED);
if (item != -1)
{
struct Dystrybutor& pd_buff = pd_arr.ElementAt(item);

pd_buff = pd;
Refresh_PD();
}


TAB_Produkcja::FRM_F_BUTTON_PD_NOWY.EnableWindow(TRUE);
TAB_Produkcja::FRM_F_BUTTON_PD_USUN.EnableWindow(TRUE);
TAB_Produkcja::FRM_F_BUTTON_PD_ZAPISZ.EnableWindow(TRUE);
TAB_Produkcja::TAB_Prod_LIST_Dystr.EnableWindow(TRUE);

TAB_Produkcja::FRM_F_EDIT_pd_NAZWAF.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pd_ADRES.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pd_TEL.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pd_FAX.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pd_EMAIL.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pd_WWW.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_EDIT_pd_NAROD.EnableWindow(FALSE);
TAB_Produkcja::FRM_F_BUTTON_pd_ZATWIERDZ.EnableWindow(FALSE);

}

void TAB_Produkcja::OnLvnGetdispinfoListFrmFPProd(NMHDR *pNMHDR, LRESULT *pResult)
{
    wchar_t buff[34];

    NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);


    int x;
    x = pDispInfo->item.iItem;

    switch (pDispInfo->item.iSubItem)
    {
    case 0:
        wcscpy(pDispInfo->item.pszText,pp_arr.GetAt(x).nazwa_firmy);
        break;
    case 1:
        wcscpy(pDispInfo->item.pszText,pp_arr.GetAt(x).adres);
        break;
    case 2:
        wcscpy(pDispInfo->item.pszText,pp_arr.GetAt(x).telefon);
        break;
    case 3:
        wcscpy(pDispInfo->item.pszText,pp_arr.GetAt(x).fax);
        break;
    case 4:
        wcscpy(pDispInfo->item.pszText,pp_arr.GetAt(x).email);
        break;
    case 5:
        wcscpy(pDispInfo->item.pszText,pp_arr.GetAt(x).strona_www);
        break;
    case 6:
        wcscpy(pDispInfo->item.pszText,pp_arr.GetAt(x).narodowosc);
        break;
    case 7:
        _itow(pp_arr.GetAt(x).ID ,buff,10);
        wcscpy(pDispInfo->item.pszText,buff); // ID
        break;
    case 8:
        _itow(pp_arr.GetAt(x).IDPDB ,buff,10);
        wcscpy(pDispInfo->item.pszText,buff);  //IDPDB
        break;
    }



    *pResult = 0;
}

void TAB_Produkcja::OnLvnGetdispinfoListFrmFPDystr(NMHDR *pNMHDR, LRESULT *pResult)
{
    wchar_t buff[34];

    NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);

    int x;
    x = pDispInfo->item.iItem;

    switch (pDispInfo->item.iSubItem)
    {
    case 0:
        wcscpy(pDispInfo->item.pszText,pd_arr.GetAt(x).nazwa_firmy);
        break;
    case 1:
        wcscpy(pDispInfo->item.pszText,pd_arr.GetAt(x).adres);
        break;
    case 2:
        wcscpy(pDispInfo->item.pszText,pd_arr.GetAt(x).telefon);
        break;
    case 3:
        wcscpy(pDispInfo->item.pszText,pd_arr.GetAt(x).fax);
        break;
    case 4:
        wcscpy(pDispInfo->item.pszText,pd_arr.GetAt(x).email);
        break;
    case 5:
        wcscpy(pDispInfo->item.pszText,pd_arr.GetAt(x).strona_www);
        break;
    case 6:
        wcscpy(pDispInfo->item.pszText,pd_arr.GetAt(x).narodowosc);
        break;
    case 7:
        _itow(pd_arr.GetAt(x).ID ,buff,10);
        wcscpy(pDispInfo->item.pszText,buff); // ID
        break;
    case 8:
        _itow(pd_arr.GetAt(x).IDPDB ,buff,10);
        wcscpy(pDispInfo->item.pszText,buff);  //IDPDB
        break;
    }
        *pResult = 0;
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

void TAB_Produkcja::OnNMDblclkListFrmFPProd(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    if (pp_arr.GetCount() > 0)
    {
        OnBnClickedFButtonPpEdytuj();
    }
    *pResult = 0;
}

void TAB_Produkcja::OnNMDblclkListFrmFPDystr(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    if (pd_arr.GetCount() > 0)
    {
        OnBnClickedFButtonPdEdytuj();
    }
    *pResult = 0;
}


void MainWindow::on_actionOtw_rz_Utw_rz_baze_danych_triggered()
{

}

void MainWindow::on_actionEksportuj_triggered()
{

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
