#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
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
