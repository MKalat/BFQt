#ifndef DRUKUJ_H
#define DRUKUJ_H

#include <QWidget>

namespace Ui {
class Drukuj;
}

class Drukuj : public QWidget
{
    Q_OBJECT
    
public:
    explicit Drukuj(QWidget *parent = 0);
    ~Drukuj();
    
private slots:
    void on_pushButton_Print_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::Drukuj *ui;
};

#endif // DRUKUJ_H
