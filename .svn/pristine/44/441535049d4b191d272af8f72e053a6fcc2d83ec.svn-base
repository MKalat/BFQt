#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <direct.h>
#include <QFileInfo>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QList>
#include <QFileDialog>
#include <windows.h>
#include <iostream>
#include <direct.h>
#include <process.h>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots :
    //void SetButtons(void);
    void UpdateCtrls(bool BINDOUT, bool start);
    void Bind_IN_Controls(void);
    void Bind_OUT_Controls(void);
    void ClearCtrls(bool all);
    int CheckbOpenDB(void);
    bool Fill_Full_Film(bool start);
    bool CheckBFVER(void);
    bool Save_Full_Film(void);
    bool Film_DodajRec(bool first, int *new_id);
    unsigned int Search_Last_Pos(unsigned int *pos);
    void Oblicz_NewID(int *new_id);
    // void SetDlgBoxs(int sel);
    //void SetListCtrls(int sel);
    void UtworzDB(bool cust);
    bool Del_Film_Rec(void);
    bool Licz_Rec(void);
    void Read_Settings();
    void SetDBFNPaths(bool cust, wchar_t *cust_path);
    void Disable_BTNS_NOREC();
    void Enable_BTNS_NOREC();
    bool CheckOLDDB();
    void KopiujOLDDB();
    //void SetBTNIcons();
    void ClearBIBLIO(void);
    void Fill_Wi(void);
    void Fill_Wo(void);
    void Save_Wi(void);
    void Save_Wo(void);
    void Refresh_Wi(void);
    void Refresh_Wo(void);
    //void Set_BIBLIO(void);
    int GetRecC_WI(void);
    int GetRecC_WO(void);
    int Get_Hi_ID_WI(int *new_id);
    void Add_New_WI(int id);
    int Get_Hi_ID_WO(int *new_id);
    void Add_New_WO(int id);
    void Usun_Rec_WI(unsigned int pos);
    void Usun_Rec_WO(unsigned int pos);
    void ClearIOF(void);
    void Fill_Lz(void);
    void Save_Lz(void);
    void Refresh_Lz(void);
    //void Set_IOF(void);
    int GetRecC_LZ(void);
    int Get_Hi_ID_LZ(int *new_id);
    void Add_New_LZ(int id);
    void Usun_Rec_LZ(unsigned int pos);
    void ClearObsada(void);
    void Fill_Ob(void);
    void Save_Ob(void);
    //void Set_Obsada(void);
    void Add_New_Ob(int id);
    int Get_Hi_ID_OB(int *new_id);
    int GetRecC_OB(void);
    void Refresh_Ob(void);
    void Usun_Rec_OB(unsigned int pos);
    void Fill_Oc();
    void Save_Oc(void);
    void ClearOcena(void);
    int Get_Hi_ID_OC(int *new_id);
    void Add_New_Oc(int id);
    int GetRecC_OC(void);
    void Usun_Rec_OC(unsigned int pos);
    void Refresh_Oc(void);
    void ClearProd(void);
    void ClearDystr(void);
    void Fill_PP(void);
    void Save_PP(void);
    void Fill_PD(void);
    void Save_PD(void);
    void Refresh_PP(void);
    void Refresh_PD(void);
    int GetRecC_PP(void);
    int GetRecC_PD(void);
    void Add_New_PP(int id);
    void Add_New_PD(int id);
    void Usun_Rec_PP(unsigned int);
    void Usun_Rec_PD(unsigned int);
    int Get_Hi_ID_PP(int *new_id);
    int Get_Hi_ID_PD(int *new_id);
    void Fill_Opis(void);
    void Clear_TABS(void);

    void SetRecAkt(unsigned int id);
    void SetZadanaPozPliku(unsigned int pos);



    
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

    void on_pushButton_OC_New_clicked();

    void on_pushButton_OC_Save_clicked();

    void on_pushButton_OC_Del_clicked();

    void on_pushButto_P_New_clicked();

    void on_pushButton_PRODSave_clicked();

    void on_pushButton_PRODDel_clicked();

    void on_pushButton_D_New_clicked();

    void on_pushButton_DYSTSave_clicked();

    void on_pushButton_DYSTDel_clicked();

    void on_comboBox_GatSel_currentTextChanged(const QString &arg1);
	void on_actionCSV_Biblioteka_Film_w_NET_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
