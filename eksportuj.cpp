#include "eksportuj.h"
#include "ui_eksportuj.h"

Eksportuj::Eksportuj(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Eksportuj)
{
    ui->setupUi(this);
}

Eksportuj::~Eksportuj()
{
    delete ui;
}
