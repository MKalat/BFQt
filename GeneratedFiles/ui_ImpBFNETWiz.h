/********************************************************************************
** Form generated from reading UI file 'ImpBFNETWiz.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPBFNETWIZ_H
#define UI_IMPBFNETWIZ_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ImpBFNETWiz
{
public:
    QLabel *label;
    QLineEdit *lineEdit_csv_BFNET;
    QPushButton *pushButton_Sel_BFNET;
    QGroupBox *groupBox;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *ImpBFNETWiz)
    {
        if (ImpBFNETWiz->objectName().isEmpty())
            ImpBFNETWiz->setObjectName(QString::fromUtf8("ImpBFNETWiz"));
        ImpBFNETWiz->resize(625, 210);
        label = new QLabel(ImpBFNETWiz);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(8, 4, 317, 16));
        lineEdit_csv_BFNET = new QLineEdit(ImpBFNETWiz);
        lineEdit_csv_BFNET->setObjectName(QString::fromUtf8("lineEdit_csv_BFNET"));
        lineEdit_csv_BFNET->setGeometry(QRect(8, 20, 533, 20));
        pushButton_Sel_BFNET = new QPushButton(ImpBFNETWiz);
        pushButton_Sel_BFNET->setObjectName(QString::fromUtf8("pushButton_Sel_BFNET"));
        pushButton_Sel_BFNET->setGeometry(QRect(552, 16, 49, 23));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton_Sel_BFNET->setFont(font);
        groupBox = new QGroupBox(ImpBFNETWiz);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(8, 48, 529, 85));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(12, 20, 105, 17));
        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(136, 20, 125, 17));
        checkBox_3 = new QCheckBox(groupBox);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(272, 20, 165, 17));
        checkBox_4 = new QCheckBox(groupBox);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(12, 44, 101, 17));
        checkBox_5 = new QCheckBox(groupBox);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setGeometry(QRect(136, 44, 117, 17));
        checkBox_6 = new QCheckBox(groupBox);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setGeometry(QRect(272, 44, 125, 17));
        pushButton = new QPushButton(ImpBFNETWiz);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(340, 144, 93, 33));
        pushButton->setFont(font);
        pushButton_2 = new QPushButton(ImpBFNETWiz);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(456, 144, 75, 33));

        retranslateUi(ImpBFNETWiz);
        QObject::connect(pushButton, SIGNAL(clicked()), ImpBFNETWiz, SLOT(BTN_IMP_CLICKED()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), ImpBFNETWiz, SLOT(BTN_CANCEL_CLICKED()));
        QObject::connect(pushButton_Sel_BFNET, SIGNAL(clicked()), ImpBFNETWiz, SLOT(BTN_SEL_PATH_CLICKED()));

        QMetaObject::connectSlotsByName(ImpBFNETWiz);
    } // setupUi

    void retranslateUi(QDialog *ImpBFNETWiz)
    {
        ImpBFNETWiz->setWindowTitle(QApplication::translate("ImpBFNETWiz", "Biblioteka Film\303\263w - Kreator importu z BF NET", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ImpBFNETWiz", "Podaj \305\233cie\305\274k\304\231 do pliku csv pochodzacego z Biblioteki Film\303\263w NET", 0, QApplication::UnicodeUTF8));
        pushButton_Sel_BFNET->setText(QApplication::translate("ImpBFNETWiz", "...", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ImpBFNETWiz", "Wybierz co zaimportowa\304\207", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("ImpBFNETWiz", "Tabela Obsada", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("ImpBFNETWiz", "Tabele Wypozycze\305\204", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("ImpBFNETWiz", "Tabela Lokalizacje zdj\304\231ciowe", 0, QApplication::UnicodeUTF8));
        checkBox_4->setText(QApplication::translate("ImpBFNETWiz", "Tabela Ocena", 0, QApplication::UnicodeUTF8));
        checkBox_5->setText(QApplication::translate("ImpBFNETWiz", "Tabela Producent", 0, QApplication::UnicodeUTF8));
        checkBox_6->setText(QApplication::translate("ImpBFNETWiz", "Tabela Dystrybutor", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ImpBFNETWiz", "Zaimportuj", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("ImpBFNETWiz", "Anuluj", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImpBFNETWiz: public Ui_ImpBFNETWiz {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPBFNETWIZ_H
