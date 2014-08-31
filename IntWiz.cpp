#include "IntWiz.h"
#include "ui_IntWiz.h"

#include "film_ftbl_class.h"
#include "Unmngd.h"

Ftbl flm_IntWiz;


IntWiz::IntWiz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntWiz)
{
    ui->setupUi(this);
	
}

IntWiz::~IntWiz()
{
    delete ui;
}

void IntWiz::on_pushButton_GetData_clicked()
{


}
void IntWiz::on_pushButton_Search_clicked()
{

}