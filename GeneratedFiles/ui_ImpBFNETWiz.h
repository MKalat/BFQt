/********************************************************************************
** Form generated from reading UI file 'ImpBFNETWiz.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPBFNETWIZ_H
#define UI_IMPBFNETWIZ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ImpBFNETWiz
{
public:
    QLabel *label;
    QLineEdit *lineEdit_csv_BFNET;
    QPushButton *pushButton_Sel_BFNET;
    QGroupBox *groupBox;
    QCheckBox *checkBox_Obsada;
    QCheckBox *checkBox_Wyp;
    QCheckBox *checkBox_LZ;
    QCheckBox *checkBox_Ocena;
    QCheckBox *checkBox_Prod;
    QCheckBox *checkBox_Dyst;
    QPushButton *pushButton_IMP;
    QPushButton *pushButton_CANCEL;

    void setupUi(QDialog *ImpBFNETWiz)
    {
        if (ImpBFNETWiz->objectName().isEmpty())
            ImpBFNETWiz->setObjectName(QStringLiteral("ImpBFNETWiz"));
        ImpBFNETWiz->resize(625, 210);
        label = new QLabel(ImpBFNETWiz);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(8, 4, 317, 16));
        lineEdit_csv_BFNET = new QLineEdit(ImpBFNETWiz);
        lineEdit_csv_BFNET->setObjectName(QStringLiteral("lineEdit_csv_BFNET"));
        lineEdit_csv_BFNET->setGeometry(QRect(8, 20, 533, 20));
        pushButton_Sel_BFNET = new QPushButton(ImpBFNETWiz);
        pushButton_Sel_BFNET->setObjectName(QStringLiteral("pushButton_Sel_BFNET"));
        pushButton_Sel_BFNET->setGeometry(QRect(552, 16, 49, 23));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton_Sel_BFNET->setFont(font);
        groupBox = new QGroupBox(ImpBFNETWiz);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(8, 48, 529, 85));
        checkBox_Obsada = new QCheckBox(groupBox);
        checkBox_Obsada->setObjectName(QStringLiteral("checkBox_Obsada"));
        checkBox_Obsada->setGeometry(QRect(12, 20, 105, 17));
        checkBox_Wyp = new QCheckBox(groupBox);
        checkBox_Wyp->setObjectName(QStringLiteral("checkBox_Wyp"));
        checkBox_Wyp->setGeometry(QRect(136, 20, 125, 17));
        checkBox_LZ = new QCheckBox(groupBox);
        checkBox_LZ->setObjectName(QStringLiteral("checkBox_LZ"));
        checkBox_LZ->setGeometry(QRect(272, 20, 165, 17));
        checkBox_Ocena = new QCheckBox(groupBox);
        checkBox_Ocena->setObjectName(QStringLiteral("checkBox_Ocena"));
        checkBox_Ocena->setGeometry(QRect(12, 44, 101, 17));
        checkBox_Prod = new QCheckBox(groupBox);
        checkBox_Prod->setObjectName(QStringLiteral("checkBox_Prod"));
        checkBox_Prod->setGeometry(QRect(136, 44, 117, 17));
        checkBox_Dyst = new QCheckBox(groupBox);
        checkBox_Dyst->setObjectName(QStringLiteral("checkBox_Dyst"));
        checkBox_Dyst->setGeometry(QRect(272, 44, 125, 17));
        pushButton_IMP = new QPushButton(ImpBFNETWiz);
        pushButton_IMP->setObjectName(QStringLiteral("pushButton_IMP"));
        pushButton_IMP->setGeometry(QRect(340, 144, 93, 33));
        pushButton_IMP->setFont(font);
        pushButton_CANCEL = new QPushButton(ImpBFNETWiz);
        pushButton_CANCEL->setObjectName(QStringLiteral("pushButton_CANCEL"));
        pushButton_CANCEL->setGeometry(QRect(456, 144, 75, 33));

        retranslateUi(ImpBFNETWiz);
        QObject::connect(pushButton_IMP, SIGNAL(clicked()), ImpBFNETWiz, SLOT(BTN_IMP_CLICKED()));
        QObject::connect(pushButton_CANCEL, SIGNAL(clicked()), ImpBFNETWiz, SLOT(BTN_CANCEL_CLICKED()));
        QObject::connect(pushButton_Sel_BFNET, SIGNAL(clicked()), ImpBFNETWiz, SLOT(BTN_SEL_PATH_CLICKED()));

        QMetaObject::connectSlotsByName(ImpBFNETWiz);
    } // setupUi

    void retranslateUi(QDialog *ImpBFNETWiz)
    {
        ImpBFNETWiz->setWindowTitle(QApplication::translate("ImpBFNETWiz", "Biblioteka Film\303\263w - Kreator importu z BF NET", 0));
        label->setText(QApplication::translate("ImpBFNETWiz", "Podaj \305\233cie\305\274k\304\231 do pliku csv pochodzacego z Biblioteki Film\303\263w NET", 0));
        pushButton_Sel_BFNET->setText(QApplication::translate("ImpBFNETWiz", "...", 0));
        groupBox->setTitle(QApplication::translate("ImpBFNETWiz", "Wybierz co zaimportowa\304\207", 0));
        checkBox_Obsada->setText(QApplication::translate("ImpBFNETWiz", "Tabela Obsada", 0));
        checkBox_Wyp->setText(QApplication::translate("ImpBFNETWiz", "Tabele Wypozycze\305\204", 0));
        checkBox_LZ->setText(QApplication::translate("ImpBFNETWiz", "Tabela Lokalizacje zdj\304\231ciowe", 0));
        checkBox_Ocena->setText(QApplication::translate("ImpBFNETWiz", "Tabela Ocena", 0));
        checkBox_Prod->setText(QApplication::translate("ImpBFNETWiz", "Tabela Producent", 0));
        checkBox_Dyst->setText(QApplication::translate("ImpBFNETWiz", "Tabela Dystrybutor", 0));
        pushButton_IMP->setText(QApplication::translate("ImpBFNETWiz", "Zaimportuj", 0));
        pushButton_CANCEL->setText(QApplication::translate("ImpBFNETWiz", "Anuluj", 0));
    } // retranslateUi

};

namespace Ui {
    class ImpBFNETWiz: public Ui_ImpBFNETWiz {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPBFNETWIZ_H
