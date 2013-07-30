/********************************************************************************
** Form generated from reading UI file 'drukuj.ui'
**
** Created: Tue 30. Jul 08:41:06 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRUKUJ_H
#define UI_DRUKUJ_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Drukuj
{
public:
    QGroupBox *groupBox;
    QRadioButton *radioButton_Akt;
    QRadioButton *radioButton_All;
    QGroupBox *groupBox_2;
    QCheckBox *checkBox_Main;
    QCheckBox *checkBox_OC;
    QCheckBox *checkBox_OB;
    QCheckBox *checkBox_PROD;
    QCheckBox *checkBox_DYSTR;
    QCheckBox *checkBox_LZ;
    QCheckBox *checkBox_WYPIN;
    QCheckBox *checkBox_WYPODIN;
    QPushButton *pushButton_Print;
    QPushButton *pushButton_Cancel;

    void setupUi(QWidget *Drukuj)
    {
        if (Drukuj->objectName().isEmpty())
            Drukuj->setObjectName(QString::fromUtf8("Drukuj"));
        Drukuj->resize(443, 387);
        groupBox = new QGroupBox(Drukuj);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(6, 9, 424, 52));
        radioButton_Akt = new QRadioButton(groupBox);
        radioButton_Akt->setObjectName(QString::fromUtf8("radioButton_Akt"));
        radioButton_Akt->setGeometry(QRect(87, 18, 82, 17));
        radioButton_All = new QRadioButton(groupBox);
        radioButton_All->setObjectName(QString::fromUtf8("radioButton_All"));
        radioButton_All->setGeometry(QRect(243, 18, 82, 17));
        groupBox_2 = new QGroupBox(Drukuj);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(9, 69, 421, 259));
        checkBox_Main = new QCheckBox(groupBox_2);
        checkBox_Main->setObjectName(QString::fromUtf8("checkBox_Main"));
        checkBox_Main->setGeometry(QRect(12, 27, 157, 17));
        checkBox_OC = new QCheckBox(groupBox_2);
        checkBox_OC->setObjectName(QString::fromUtf8("checkBox_OC"));
        checkBox_OC->setGeometry(QRect(12, 54, 100, 17));
        checkBox_OB = new QCheckBox(groupBox_2);
        checkBox_OB->setObjectName(QString::fromUtf8("checkBox_OB"));
        checkBox_OB->setGeometry(QRect(12, 81, 127, 17));
        checkBox_PROD = new QCheckBox(groupBox_2);
        checkBox_PROD->setObjectName(QString::fromUtf8("checkBox_PROD"));
        checkBox_PROD->setGeometry(QRect(12, 108, 115, 17));
        checkBox_DYSTR = new QCheckBox(groupBox_2);
        checkBox_DYSTR->setObjectName(QString::fromUtf8("checkBox_DYSTR"));
        checkBox_DYSTR->setGeometry(QRect(12, 138, 121, 17));
        checkBox_LZ = new QCheckBox(groupBox_2);
        checkBox_LZ->setObjectName(QString::fromUtf8("checkBox_LZ"));
        checkBox_LZ->setGeometry(QRect(12, 168, 166, 17));
        checkBox_WYPIN = new QCheckBox(groupBox_2);
        checkBox_WYPIN->setObjectName(QString::fromUtf8("checkBox_WYPIN"));
        checkBox_WYPIN->setGeometry(QRect(12, 198, 199, 17));
        checkBox_WYPODIN = new QCheckBox(groupBox_2);
        checkBox_WYPODIN->setObjectName(QString::fromUtf8("checkBox_WYPODIN"));
        checkBox_WYPODIN->setGeometry(QRect(12, 225, 205, 17));
        pushButton_Print = new QPushButton(Drukuj);
        pushButton_Print->setObjectName(QString::fromUtf8("pushButton_Print"));
        pushButton_Print->setGeometry(QRect(213, 336, 100, 31));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton_Print->setFont(font);
        pushButton_Cancel = new QPushButton(Drukuj);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(354, 336, 75, 31));

        retranslateUi(Drukuj);

        QMetaObject::connectSlotsByName(Drukuj);
    } // setupUi

    void retranslateUi(QWidget *Drukuj)
    {
        Drukuj->setWindowTitle(QApplication::translate("Drukuj", "Biblioteka Film\303\263w - Kreator wydruku", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Drukuj", "Wybierz ile film\303\263w wydrukowa\304\207", 0, QApplication::UnicodeUTF8));
        radioButton_Akt->setText(QApplication::translate("Drukuj", "Aktualny", 0, QApplication::UnicodeUTF8));
        radioButton_All->setText(QApplication::translate("Drukuj", "Wszystkie", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("Drukuj", "Wybierz co wydrukowa\304\207", 0, QApplication::UnicodeUTF8));
        checkBox_Main->setText(QApplication::translate("Drukuj", "Podstawowe dane o filmie", 0, QApplication::UnicodeUTF8));
        checkBox_OC->setText(QApplication::translate("Drukuj", "Tabela Ocena", 0, QApplication::UnicodeUTF8));
        checkBox_OB->setText(QApplication::translate("Drukuj", "Tabela Obsada", 0, QApplication::UnicodeUTF8));
        checkBox_PROD->setText(QApplication::translate("Drukuj", "Tabela Produkcja", 0, QApplication::UnicodeUTF8));
        checkBox_DYSTR->setText(QApplication::translate("Drukuj", "Tabela Dystrybucja", 0, QApplication::UnicodeUTF8));
        checkBox_LZ->setText(QApplication::translate("Drukuj", "Tabela Lokalizacje zdj\304\231ciowe", 0, QApplication::UnicodeUTF8));
        checkBox_WYPIN->setText(QApplication::translate("Drukuj", "Tabela Wypo\305\274yczenia innym osobom", 0, QApplication::UnicodeUTF8));
        checkBox_WYPODIN->setText(QApplication::translate("Drukuj", "Tabela wypo\305\274yczenia od innych os\303\263b", 0, QApplication::UnicodeUTF8));
        pushButton_Print->setText(QApplication::translate("Drukuj", "Drukuj", 0, QApplication::UnicodeUTF8));
        pushButton_Cancel->setText(QApplication::translate("Drukuj", "Anuluj", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Drukuj: public Ui_Drukuj {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRUKUJ_H
