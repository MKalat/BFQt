/********************************************************************************
** Form generated from reading UI file 'eksportujHp3728.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef EKSPORTUJHP3728_H
#define EKSPORTUJHP3728_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Eksportuj
{
public:
    QLineEdit *lineEdit_Eks_path;
    QPushButton *pushButton_GetPath;
    QLabel *label;
    QCheckBox *checkBox_AllRec;
    QGroupBox *groupBox;
    QCheckBox *checkBox_MainFilm;
    QCheckBox *checkBox_TabObsada;
    QCheckBox *checkBox_TabOcena;
    QCheckBox *checkBox_TabLZ;
    QCheckBox *checkBox_TabPD;
    QCheckBox *checkBox_TabW;
    QPushButton *pushButton_Eksport;
    QPushButton *pushButton_Anuluj;

    void setupUi(QWidget *Eksportuj)
    {
        if (Eksportuj->objectName().isEmpty())
            Eksportuj->setObjectName(QStringLiteral("Eksportuj"));
        Eksportuj->resize(376, 327);
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/MK_LOGO.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Eksportuj->setWindowIcon(icon);
        lineEdit_Eks_path = new QLineEdit(Eksportuj);
        lineEdit_Eks_path->setObjectName(QStringLiteral("lineEdit_Eks_path"));
        lineEdit_Eks_path->setGeometry(QRect(12, 18, 310, 20));
        pushButton_GetPath = new QPushButton(Eksportuj);
        pushButton_GetPath->setObjectName(QStringLiteral("pushButton_GetPath"));
        pushButton_GetPath->setGeometry(QRect(324, 18, 49, 23));
        label = new QLabel(Eksportuj);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(9, 3, 307, 16));
        checkBox_AllRec = new QCheckBox(Eksportuj);
        checkBox_AllRec->setObjectName(QStringLiteral("checkBox_AllRec"));
        checkBox_AllRec->setGeometry(QRect(15, 51, 265, 17));
        groupBox = new QGroupBox(Eksportuj);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(15, 75, 352, 181));
        checkBox_MainFilm = new QCheckBox(groupBox);
        checkBox_MainFilm->setObjectName(QStringLiteral("checkBox_MainFilm"));
        checkBox_MainFilm->setGeometry(QRect(12, 21, 151, 17));
        checkBox_MainFilm->setCheckable(true);
        checkBox_MainFilm->setChecked(true);
        checkBox_TabObsada = new QCheckBox(groupBox);
        checkBox_TabObsada->setObjectName(QStringLiteral("checkBox_TabObsada"));
        checkBox_TabObsada->setGeometry(QRect(12, 45, 121, 17));
        checkBox_TabOcena = new QCheckBox(groupBox);
        checkBox_TabOcena->setObjectName(QStringLiteral("checkBox_TabOcena"));
        checkBox_TabOcena->setGeometry(QRect(12, 69, 94, 17));
        checkBox_TabLZ = new QCheckBox(groupBox);
        checkBox_TabLZ->setObjectName(QStringLiteral("checkBox_TabLZ"));
        checkBox_TabLZ->setGeometry(QRect(12, 93, 163, 17));
        checkBox_TabPD = new QCheckBox(groupBox);
        checkBox_TabPD->setObjectName(QStringLiteral("checkBox_TabPD"));
        checkBox_TabPD->setGeometry(QRect(12, 117, 181, 17));
        checkBox_TabW = new QCheckBox(groupBox);
        checkBox_TabW->setObjectName(QStringLiteral("checkBox_TabW"));
        checkBox_TabW->setGeometry(QRect(12, 141, 124, 17));
        pushButton_Eksport = new QPushButton(Eksportuj);
        pushButton_Eksport->setObjectName(QStringLiteral("pushButton_Eksport"));
        pushButton_Eksport->setGeometry(QRect(180, 273, 106, 28));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton_Eksport->setFont(font);
        pushButton_Anuluj = new QPushButton(Eksportuj);
        pushButton_Anuluj->setObjectName(QStringLiteral("pushButton_Anuluj"));
        pushButton_Anuluj->setGeometry(QRect(291, 273, 75, 28));

        retranslateUi(Eksportuj);

        QMetaObject::connectSlotsByName(Eksportuj);
    } // setupUi

    void retranslateUi(QWidget *Eksportuj)
    {
        Eksportuj->setWindowTitle(QApplication::translate("Eksportuj", "Biblioteka Film\303\263w - Kreator Eksportu", 0));
        pushButton_GetPath->setText(QApplication::translate("Eksportuj", "...", 0));
        label->setText(QApplication::translate("Eksportuj", "Podaj \305\233cie\305\274k\304\231 do pliku, do kt\303\263rego chesz wyekportowa\304\207 dane", 0));
        checkBox_AllRec->setText(QApplication::translate("Eksportuj", "Eksportuj wszystkie rekordy filmow z bazy danych", 0));
        groupBox->setTitle(QApplication::translate("Eksportuj", "Wybierz jakie dane maj\304\205 by\304\207 eksportowane", 0));
        checkBox_MainFilm->setText(QApplication::translate("Eksportuj", "Podstawowe dane o filmie", 0));
        checkBox_TabObsada->setText(QApplication::translate("Eksportuj", "Tabela Obsada", 0));
        checkBox_TabOcena->setText(QApplication::translate("Eksportuj", "Tabela Ocena", 0));
        checkBox_TabLZ->setText(QApplication::translate("Eksportuj", "Tabela Lokalizacje zdj\304\231ciowe", 0));
        checkBox_TabPD->setText(QApplication::translate("Eksportuj", "Tabele Produkcja i Dystrybucja", 0));
        checkBox_TabW->setText(QApplication::translate("Eksportuj", "Tabele Wypo\305\274ycze\305\204", 0));
        pushButton_Eksport->setText(QApplication::translate("Eksportuj", "Eksportuj", 0));
        pushButton_Anuluj->setText(QApplication::translate("Eksportuj", "Anuluj", 0));
    } // retranslateUi

};

namespace Ui {
    class Eksportuj: public Ui_Eksportuj {};
} // namespace Ui

QT_END_NAMESPACE

#endif // EKSPORTUJHP3728_H
