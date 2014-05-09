/********************************************************************************
** Form generated from reading UI file 'oprogHp5116.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef OPROGHP5116_H
#define OPROGHP5116_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OProg
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *OProg)
    {
        if (OProg->objectName().isEmpty())
            OProg->setObjectName(QString::fromUtf8("OProg"));
        OProg->resize(400, 315);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/MK_LOGO.ico"), QSize(), QIcon::Normal, QIcon::Off);
        OProg->setWindowIcon(icon);
        pushButton = new QPushButton(OProg);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(168, 282, 75, 23));
        label = new QLabel(OProg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(118, 17, 154, 16));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(OProg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(116, 97, 215, 109));

        retranslateUi(OProg);

        QMetaObject::connectSlotsByName(OProg);
    } // setupUi

    void retranslateUi(QWidget *OProg)
    {
        OProg->setWindowTitle(QApplication::translate("OProg", "Biblioteka Film\303\263w - O Programie", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("OProg", "OK", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("OProg", "<html><head/><body><p><span style=\" color:#ff5500;\">Biblioteka Film\303\263w</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("OProg", "<html><head/><body><p>Copyright 2005 - 2014 Marcin Ka\305\202at</p><p>Strona autora programu : http://mkalat.pl</p><p>This program uses Qt 5.2.1 library </p><p>licensed under terms of GNU LGPL v. 2.1</p><p><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OProg: public Ui_OProg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // OPROGHP5116_H
