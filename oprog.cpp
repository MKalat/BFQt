#include "oprog.h"
#include "ui_oprog.h"

OProg::OProg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OProg)
{
    ui->setupUi(this);
}

OProg::~OProg()
{
    delete ui;
}

void OProg::on_pushButton_clicked()
{
    this->close();
}
