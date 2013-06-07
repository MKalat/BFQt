#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "film_ftbl_class.h"
#include "Unmngd.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
    bool add_new = false;
    QList <Ocena> oc_arr;

    struct Producent pp;
    struct Dystrybutor pd;
    bool add_new_pp = false;
    bool add_new_pd = false;
    QList <Producent> pp_arr;
    QList <Dystrybutor> pd_arr;
    
private slots:
    void on_pushButton_First_clicked();

    void on_pushButton_Prev_clicked();

    void on_pushButton_Next_clicked();

    void on_pushButton_Last_clicked();

    void on_pushButton_New_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_Del_clicked();

    void on_pushButton_IntWiz_clicked();

    void on_actionOtw_rz_Utw_rz_baze_danych_triggered();

    void on_actionEksportuj_triggered();

    void on_actionWyszukaj_triggered();

    void on_actionKoniec_triggered();

    void on_actionDrukuj_triggered();

    void on_actionSprawd_aktualizacje_triggered();

    void on_actionO_programie_triggered();

    void on_actionPomoc_triggered();

    void on_pushButton_LoadPic_clicked();

    void on_pushButton_DelPic_clicked();

    void on_pushButton_B_WYPIN_New_clicked();

    void on_pushButton_BIBLIOWYPISave_clicked();

    void on_pushButton_BIBLIOWYPINDel_clicked();

    void on_pushButton_B_WYPODIN_New_clicked();

    void on_pushButton_BIBLIOWYPODINSave_clicked();

    void on_pushButton_BIBLIOWYPODINDel_clicked();

    void on_pushButton_LZ_New_clicked();

    void on_pushButton_LZSave_clicked();

    void on_pushButton_LZDel_clicked();

    void on_pushButton_OB_new_clicked();

    void on_pushButton_OBSave_clicked();

    void on_pushButton_OBDel_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
