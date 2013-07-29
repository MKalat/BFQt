#ifndef DRUKUJ_H
#define DRUKUJ_H

#include <QWidget>
#include <QPrinter>
#include <QFile>
#include <QTextStream>
#include <QTextDocument>
#include <QPrintDialog>

namespace Ui {
class Drukuj;
}

class Drukuj : public QWidget
{
    Q_OBJECT
    
public:
    explicit Drukuj(QWidget *parent = 0);
    ~Drukuj();
	void print_doc();
    
private slots:
    void on_pushButton_Print_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::Drukuj *ui;
};

#endif // DRUKUJ_H
