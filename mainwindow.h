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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
