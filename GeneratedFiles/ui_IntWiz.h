/********************************************************************************
** Form generated from reading UI file 'IntWiz.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTWIZ_H
#define UI_INTWIZ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_IntWiz
{
public:
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QGroupBox *groupBox;
    QCheckBox *checkBox_main;
    QCheckBox *checkBox_obsada;
    QCheckBox *checkBox_okladka;
    QCheckBox *checkBox_askOverwrite;
    QCheckBox *checkBox_reviews;
    QLabel *label_3;
    QPushButton *pushButton_search;
    QTableWidget *tableWidget_Results;
    QPushButton *pushButton_GetData;

    void setupUi(QDialog *IntWiz)
    {
        if (IntWiz->objectName().isEmpty())
            IntWiz->setObjectName(QStringLiteral("IntWiz"));
        IntWiz->resize(641, 555);
        QIcon icon;
        icon.addFile(QStringLiteral("MK_LOGO.ico"), QSize(), QIcon::Normal, QIcon::Off);
        IntWiz->setWindowIcon(icon);
        label = new QLabel(IntWiz);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(8, 4, 77, 16));
        comboBox = new QComboBox(IntWiz);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(92, 4, 169, 22));
        label_2 = new QLabel(IntWiz);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(264, 4, 33, 16));
        lineEdit = new QLineEdit(IntWiz);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(300, 4, 329, 20));
        lineEdit->setReadOnly(true);
        groupBox = new QGroupBox(IntWiz);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(4, 28, 625, 80));
        checkBox_main = new QCheckBox(groupBox);
        checkBox_main->setObjectName(QStringLiteral("checkBox_main"));
        checkBox_main->setGeometry(QRect(12, 20, 117, 17));
        checkBox_obsada = new QCheckBox(groupBox);
        checkBox_obsada->setObjectName(QStringLiteral("checkBox_obsada"));
        checkBox_obsada->setGeometry(QRect(152, 20, 70, 17));
        checkBox_okladka = new QCheckBox(groupBox);
        checkBox_okladka->setObjectName(QStringLiteral("checkBox_okladka"));
        checkBox_okladka->setGeometry(QRect(236, 20, 70, 17));
        checkBox_askOverwrite = new QCheckBox(groupBox);
        checkBox_askOverwrite->setObjectName(QStringLiteral("checkBox_askOverwrite"));
        checkBox_askOverwrite->setGeometry(QRect(12, 48, 201, 17));
        checkBox_reviews = new QCheckBox(groupBox);
        checkBox_reviews->setObjectName(QStringLiteral("checkBox_reviews"));
        checkBox_reviews->setGeometry(QRect(340, 20, 70, 17));
        label_3 = new QLabel(IntWiz);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(8, 136, 89, 16));
        pushButton_search = new QPushButton(IntWiz);
        pushButton_search->setObjectName(QStringLiteral("pushButton_search"));
        pushButton_search->setGeometry(QRect(428, 112, 165, 29));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton_search->setFont(font);
        tableWidget_Results = new QTableWidget(IntWiz);
        if (tableWidget_Results->columnCount() < 5)
            tableWidget_Results->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_Results->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_Results->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_Results->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_Results->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_Results->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget_Results->setObjectName(QStringLiteral("tableWidget_Results"));
        tableWidget_Results->setGeometry(QRect(8, 156, 617, 353));
        tableWidget_Results->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_Results->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_Results->horizontalHeader()->setDefaultSectionSize(150);
        pushButton_GetData = new QPushButton(IntWiz);
        pushButton_GetData->setObjectName(QStringLiteral("pushButton_GetData"));
        pushButton_GetData->setGeometry(QRect(406, 514, 217, 29));
        pushButton_GetData->setFont(font);

        retranslateUi(IntWiz);

        QMetaObject::connectSlotsByName(IntWiz);
    } // setupUi

    void retranslateUi(QDialog *IntWiz)
    {
        IntWiz->setWindowTitle(QApplication::translate("IntWiz", "Biblioteka Film\303\263w - Kreator Pobierania Informacji o filmach z Internetu", 0));
        label->setText(QApplication::translate("IntWiz", "\305\271r\303\263d\305\202o danych", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("IntWiz", "imdb.com", 0)
         << QApplication::translate("IntWiz", "filmweb.pl", 0)
        );
        label_2->setText(QApplication::translate("IntWiz", "Tytu\305\202", 0));
        groupBox->setTitle(QApplication::translate("IntWiz", "Opcje pobierania", 0));
        checkBox_main->setText(QApplication::translate("IntWiz", "Podst. dane o filmie", 0));
        checkBox_obsada->setText(QApplication::translate("IntWiz", "Obsada", 0));
        checkBox_okladka->setText(QApplication::translate("IntWiz", "Ok\305\202adka", 0));
        checkBox_askOverwrite->setText(QApplication::translate("IntWiz", "Pyta\304\207 przed nadpisaniem danych ?", 0));
        checkBox_reviews->setText(QApplication::translate("IntWiz", "Recenzje", 0));
        label_3->setText(QApplication::translate("IntWiz", "Znalezione filmy", 0));
        pushButton_search->setText(QApplication::translate("IntWiz", "Wyszukaj", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_Results->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("IntWiz", "Tytu\305\202", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_Results->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("IntWiz", "Premiera", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_Results->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("IntWiz", "Kraj produkcji", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_Results->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("IntWiz", "Re\305\274yser", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_Results->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("IntWiz", "Rodzaj", 0));
        pushButton_GetData->setText(QApplication::translate("IntWiz", "Pobierz dane zanaczonej pozycji", 0));
    } // retranslateUi

};

namespace Ui {
    class IntWiz: public Ui_IntWiz {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTWIZ_H
