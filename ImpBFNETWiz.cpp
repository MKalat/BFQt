#include "ImpBFNETWiz.h"
#include "ui_ImpBFNETWiz.h"

#include "film_ftbl_class.h"

#include <windows.h>
#include <iostream>
#include <direct.h>

Ftbl flm_impbf;

ImpBFNETWiz::ImpBFNETWiz(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::ImpBFNETWiz)
{
    ui->setupUi(this);
}

ImpBFNETWiz::~ImpBFNETWiz()
{
	delete ui;
}

void ImpBFNETWiz::BTN_IMP_CLICKED()
{
    if (QFile::exists(ui->lineEdit_csv_BFNET->text()))
    {
        QFile file(ui->lineEdit_csv_BFNET->text());
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString line = file.readLine();
            line = file.readLine();
            line = file.readLine();
            line = file.readLine();
            line = file.readLine();
            while (!file.atEnd())
            {
                line = file.readLine();
                QStringList strings = line.split(",");
                wchar_t *buff;
                strings.value(0).toWCharArray(buff);
                wcscpy(flm_impbf.film_tbl.tytul,buff);
                strings.value(2).toWCharArray(buff);
                wcscpy(flm_impbf.film_tbl.gatunek_filmu,buff);

                if (ui->checkBox_Obsada->isChecked())
                {


                }
                if (ui->checkBox_Ocena->isChecked())
                {


                }
                if (ui->checkBox_Dyst->isChecked())
                {


                }
                if (ui->checkBox_Prod->isChecked())
                {


                }
                if (ui->checkBox_LZ->isChecked())
                {


                }
                if (ui->checkBox_Wyp->isChecked())
                {

                }

            }
            file.close();
        }


    }


}
void ImpBFNETWiz::BTN_CANCEL_CLICKED()
{
	this->close();
}
void ImpBFNETWiz::BTN_SEL_PATH_CLICKED()
{
	QFileDialog fdlg(this);
	fdlg.setFileMode(QFileDialog::AnyFile);
    fdlg.setViewMode(QFileDialog::Detail);
    fdlg.setNameFilter(tr("Comma Separated Values file (*.csv )"));
	fdlg.setAcceptMode(QFileDialog::AcceptOpen);
    if (fdlg.exec())
    {
        QString dir_path = fdlg.selectedFiles().at(0);
		ui->lineEdit_csv_BFNET->setText(dir_path);
    }

}

