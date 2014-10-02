#ifndef IMPBFNETWIZHP1164_H
#define IMPBFNETWIZHP1164_H

#include <QDialog>
#include <QMainWindow>
#include <QLocale>
#include <QTranslator>
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
#include <QTextStream>
#include <QTextCodec>


namespace Ui {
class ImpBFNETWiz;
}

class ImpBFNETWiz : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImpBFNETWiz(QDialog *parent = 0);
    ~ImpBFNETWiz();


public slots:
	void BTN_IMP_CLICKED();
	void BTN_CANCEL_CLICKED();
	void BTN_SEL_PATH_CLICKED();


private:
    Ui::ImpBFNETWiz *ui;
};

#endif // IMPBFNETWIZHP1164_H
