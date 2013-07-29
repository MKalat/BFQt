/********************************************************************************
** Form generated from reading UI file 'wyszukaj.ui'
**
** Created: Mon 29. Jul 15:30:44 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WYSZUKAJ_H
#define UI_WYSZUKAJ_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Wyszukaj
{
public:
    QLabel *label;
    QLineEdit *lineEdit_Fraza;
    QPushButton *pushButton_Search;
    QLabel *label_2;
    QComboBox *comboBox_Pole;
    QTableWidget *tableWidget_Wyniki;
    QPushButton *pushButton_Cancel;

    void setupUi(QWidget *Wyszukaj)
    {
        if (Wyszukaj->objectName().isEmpty())
            Wyszukaj->setObjectName(QString::fromUtf8("Wyszukaj"));
        Wyszukaj->resize(373, 418);
        label = new QLabel(Wyszukaj);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(9, 6, 76, 16));
        lineEdit_Fraza = new QLineEdit(Wyszukaj);
        lineEdit_Fraza->setObjectName(QString::fromUtf8("lineEdit_Fraza"));
        lineEdit_Fraza->setGeometry(QRect(90, 6, 265, 20));
        pushButton_Search = new QPushButton(Wyszukaj);
        pushButton_Search->setObjectName(QString::fromUtf8("pushButton_Search"));
        pushButton_Search->setGeometry(QRect(204, 57, 85, 25));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton_Search->setFont(font);
        label_2 = new QLabel(Wyszukaj);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(9, 33, 46, 13));
        comboBox_Pole = new QComboBox(Wyszukaj);
        comboBox_Pole->setObjectName(QString::fromUtf8("comboBox_Pole"));
        comboBox_Pole->setGeometry(QRect(90, 30, 208, 22));
        tableWidget_Wyniki = new QTableWidget(Wyszukaj);
        if (tableWidget_Wyniki->columnCount() < 3)
            tableWidget_Wyniki->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_Wyniki->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_Wyniki->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_Wyniki->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget_Wyniki->setObjectName(QString::fromUtf8("tableWidget_Wyniki"));
        tableWidget_Wyniki->setGeometry(QRect(9, 90, 355, 319));
        tableWidget_Wyniki->setEditTriggers(QAbstractItemView::DoubleClicked);
        tableWidget_Wyniki->setTabKeyNavigation(false);
        tableWidget_Wyniki->setDragDropOverwriteMode(false);
        tableWidget_Wyniki->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_Wyniki->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButton_Cancel = new QPushButton(Wyszukaj);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(294, 57, 75, 25));

        retranslateUi(Wyszukaj);

        QMetaObject::connectSlotsByName(Wyszukaj);
    } // setupUi

    void retranslateUi(QWidget *Wyszukaj)
    {
        Wyszukaj->setWindowTitle(QApplication::translate("Wyszukaj", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Wyszukaj", "Szukana fraza", 0, QApplication::UnicodeUTF8));
        pushButton_Search->setText(QApplication::translate("Wyszukaj", "Szukaj", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Wyszukaj", "Pole", 0, QApplication::UnicodeUTF8));
        comboBox_Pole->clear();
        comboBox_Pole->insertItems(0, QStringList()
         << QApplication::translate("Wyszukaj", "Tytu\305\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Oryginalny tytu\305\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Gatunek", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "W\305\202asna ocena filmu - \305\233cie\305\274ka d\305\272wi\304\231kowa", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "W\305\202asna ocena filmu - zdj\304\231cia", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "W\305\202asna ocena filmu - obsada", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "W\305\202asna ocena filmu - warto\305\233\304\207 artystyczna", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "W\305\202asna ocena filmu - ca\305\202o\305\233\304\207", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Obsada - imi\304\231 i nazwisko re\305\274ysera", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Obsada - narodowo\305\233\304\207 re\305\274ysera", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Obsada - operator imi\304\231 i nazwisko", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Obsada - opreator narodowo\305\233\304\207", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Obsada - muzyka imi\304\231 i nazwisko", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Obsada - muzyka narodowo\305\233\304\207", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Obsada - scenariusz imie i nazwisko", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Obsada - scenariusz narodowo\305\233\304\207", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Dane o Egzemplarzu - W\305\202a\305\233ciciel - Imie i nazwisko", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Dane o Egzemplarzu - W\305\202a\305\233ciciel - Adres", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Dane o Egzemplarzu - Sklep - Nazwa", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Dane o Egzemplarzu - Sklep - Adres", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Dane o Egzemplarzu - Sklep - Telefon", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Dane o Egzemplarzu - Sklep - Fax", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Dane o Egzemplarzu - Sklep - Email", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Dane o Egzemplarzu - Sklep - WWW", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Dane o Egzemplarzu - Cena", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Dane o Egzemplarzu - Data zakupu", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Dane o Egzemplarzu - Data skatalogowania", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Dane o Egzemplarzu - Warto\305\233\304\207 aktualna", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Dane o Egzemplarzu - Data Utraty", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Dane o Egzemplarzu - Nr katalogowy", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Dane o Egzemplarzu - Rodzaj no\305\233nika", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - Rok produkcji", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - Data Premiery", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - Czas projekcji", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - Format wy\305\233wietlania", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - System kodowania obrazu", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - J\304\231zyk lektora", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - J\304\231zyk napis\303\263w", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - Kodek wideo - nazwa", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - Kodek Wideo - typ", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - Kodek wideo - wersja", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - Kodek audio - nazwa", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - Kodek audio - typ", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - Kodek audio - wersja", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - Zabezpieczenia - nazwa", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - Zabezpieczenia - typ", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - Zabezpieczenia - wersja", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Wyszukaj", "Info o Filmie - Kraj produkcji", 0, QApplication::UnicodeUTF8)
        );
        QTableWidgetItem *___qtablewidgetitem = tableWidget_Wyniki->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Wyszukaj", "Tytu\305\202", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_Wyniki->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Wyszukaj", "Gatunek", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_Wyniki->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Wyszukaj", "Premiera", 0, QApplication::UnicodeUTF8));
        pushButton_Cancel->setText(QApplication::translate("Wyszukaj", "Anuluj", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Wyszukaj: public Ui_Wyszukaj {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WYSZUKAJ_H
