/********************************************************************************
** Form generated from reading UI file 'resultdialog.ui'
**
** Created: Wed Mar 17 10:18:14 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTDIALOG_H
#define UI_RESULTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ResultDialog
{
public:
    QLabel *labelResult10kmh;
    QLabel *labelResult40kmh;
    QLabel *labelResult20kmh;
    QLabel *labelResult30kmh;
    QLabel *labelY2;
    QLabel *labelY6;
    QLabel *labelY1;
    QLabel *labelY10;
    QLabel *labelY3;
    QLabel *labelYLine;
    QLabel *labelY4;
    QLabel *labelY7;
    QLabel *labelY8;
    QLabel *labelY5;
    QLabel *labelY9;
    QLabel *labelX1;
    QLabel *labelX3;
    QLabel *labelX5;
    QLabel *labelX9;
    QLabel *labelX7;
    QLabel *labelX2;
    QLabel *labelX6;
    QLabel *labelX8;
    QLabel *labelXLine;
    QLabel *labelX10;
    QLabel *labelX4;
    QPushButton *pushButtonSend;

    void setupUi(QDialog *ResultDialog)
    {
        if (ResultDialog->objectName().isEmpty())
            ResultDialog->setObjectName(QString::fromUtf8("ResultDialog"));
        ResultDialog->resize(800, 480);
        labelResult10kmh = new QLabel(ResultDialog);
        labelResult10kmh->setObjectName(QString::fromUtf8("labelResult10kmh"));
        labelResult10kmh->setGeometry(QRect(410, 230, 191, 31));
        labelResult40kmh = new QLabel(ResultDialog);
        labelResult40kmh->setObjectName(QString::fromUtf8("labelResult40kmh"));
        labelResult40kmh->setGeometry(QRect(410, 90, 191, 31));
        labelResult20kmh = new QLabel(ResultDialog);
        labelResult20kmh->setObjectName(QString::fromUtf8("labelResult20kmh"));
        labelResult20kmh->setGeometry(QRect(410, 180, 191, 31));
        labelResult30kmh = new QLabel(ResultDialog);
        labelResult30kmh->setObjectName(QString::fromUtf8("labelResult30kmh"));
        labelResult30kmh->setGeometry(QRect(410, 140, 191, 31));
        labelY2 = new QLabel(ResultDialog);
        labelY2->setObjectName(QString::fromUtf8("labelY2"));
        labelY2->setGeometry(QRect(20, 280, 31, 17));
        QFont font;
        font.setFamily(QString::fromUtf8("Bitstream Charter"));
        font.setPointSize(8);
        labelY2->setFont(font);
        labelY6 = new QLabel(ResultDialog);
        labelY6->setObjectName(QString::fromUtf8("labelY6"));
        labelY6->setGeometry(QRect(20, 160, 31, 17));
        labelY6->setFont(font);
        labelY1 = new QLabel(ResultDialog);
        labelY1->setObjectName(QString::fromUtf8("labelY1"));
        labelY1->setGeometry(QRect(20, 310, 31, 17));
        labelY1->setFont(font);
        labelY10 = new QLabel(ResultDialog);
        labelY10->setObjectName(QString::fromUtf8("labelY10"));
        labelY10->setGeometry(QRect(20, 40, 31, 17));
        labelY10->setFont(font);
        labelY3 = new QLabel(ResultDialog);
        labelY3->setObjectName(QString::fromUtf8("labelY3"));
        labelY3->setGeometry(QRect(20, 250, 31, 17));
        labelY3->setFont(font);
        labelYLine = new QLabel(ResultDialog);
        labelYLine->setObjectName(QString::fromUtf8("labelYLine"));
        labelYLine->setGeometry(QRect(5, 10, 171, 17));
        labelYLine->setFont(font);
        labelY4 = new QLabel(ResultDialog);
        labelY4->setObjectName(QString::fromUtf8("labelY4"));
        labelY4->setGeometry(QRect(20, 220, 31, 17));
        labelY4->setFont(font);
        labelY7 = new QLabel(ResultDialog);
        labelY7->setObjectName(QString::fromUtf8("labelY7"));
        labelY7->setGeometry(QRect(20, 130, 31, 17));
        labelY7->setFont(font);
        labelY8 = new QLabel(ResultDialog);
        labelY8->setObjectName(QString::fromUtf8("labelY8"));
        labelY8->setGeometry(QRect(20, 100, 31, 17));
        labelY8->setFont(font);
        labelY5 = new QLabel(ResultDialog);
        labelY5->setObjectName(QString::fromUtf8("labelY5"));
        labelY5->setGeometry(QRect(20, 190, 31, 17));
        labelY5->setFont(font);
        labelY9 = new QLabel(ResultDialog);
        labelY9->setObjectName(QString::fromUtf8("labelY9"));
        labelY9->setGeometry(QRect(20, 70, 31, 17));
        labelY9->setFont(font);
        labelX1 = new QLabel(ResultDialog);
        labelX1->setObjectName(QString::fromUtf8("labelX1"));
        labelX1->setGeometry(QRect(70, 350, 31, 17));
        labelX1->setFont(font);
        labelX3 = new QLabel(ResultDialog);
        labelX3->setObjectName(QString::fromUtf8("labelX3"));
        labelX3->setGeometry(QRect(130, 350, 31, 17));
        labelX3->setFont(font);
        labelX5 = new QLabel(ResultDialog);
        labelX5->setObjectName(QString::fromUtf8("labelX5"));
        labelX5->setGeometry(QRect(190, 350, 31, 17));
        labelX5->setFont(font);
        labelX9 = new QLabel(ResultDialog);
        labelX9->setObjectName(QString::fromUtf8("labelX9"));
        labelX9->setGeometry(QRect(310, 350, 31, 17));
        labelX9->setFont(font);
        labelX7 = new QLabel(ResultDialog);
        labelX7->setObjectName(QString::fromUtf8("labelX7"));
        labelX7->setGeometry(QRect(250, 350, 31, 17));
        labelX7->setFont(font);
        labelX2 = new QLabel(ResultDialog);
        labelX2->setObjectName(QString::fromUtf8("labelX2"));
        labelX2->setGeometry(QRect(100, 350, 31, 17));
        labelX2->setFont(font);
        labelX6 = new QLabel(ResultDialog);
        labelX6->setObjectName(QString::fromUtf8("labelX6"));
        labelX6->setGeometry(QRect(220, 350, 31, 17));
        labelX6->setFont(font);
        labelX8 = new QLabel(ResultDialog);
        labelX8->setObjectName(QString::fromUtf8("labelX8"));
        labelX8->setGeometry(QRect(280, 350, 31, 17));
        labelX8->setFont(font);
        labelXLine = new QLabel(ResultDialog);
        labelXLine->setObjectName(QString::fromUtf8("labelXLine"));
        labelXLine->setGeometry(QRect(50, 360, 170, 17));
        labelXLine->setFont(font);
        labelX10 = new QLabel(ResultDialog);
        labelX10->setObjectName(QString::fromUtf8("labelX10"));
        labelX10->setGeometry(QRect(340, 350, 31, 17));
        labelX10->setFont(font);
        labelX4 = new QLabel(ResultDialog);
        labelX4->setObjectName(QString::fromUtf8("labelX4"));
        labelX4->setGeometry(QRect(160, 350, 31, 17));
        labelX4->setFont(font);
        pushButtonSend = new QPushButton(ResultDialog);
        pushButtonSend->setObjectName(QString::fromUtf8("pushButtonSend"));
        pushButtonSend->setGeometry(QRect(402, 330, 101, 27));

        retranslateUi(ResultDialog);

        QMetaObject::connectSlotsByName(ResultDialog);
    } // setupUi

    void retranslateUi(QDialog *ResultDialog)
    {
        ResultDialog->setWindowTitle(QApplication::translate("ResultDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        labelResult10kmh->setText(QApplication::translate("ResultDialog", "0 - 10 km/h: 5,6 s", 0, QApplication::UnicodeUTF8));
        labelResult40kmh->setText(QApplication::translate("ResultDialog", "0 - 40 km/h: 9,8 s", 0, QApplication::UnicodeUTF8));
        labelResult20kmh->setText(QApplication::translate("ResultDialog", "0 - 20 km/h: 6,9 s", 0, QApplication::UnicodeUTF8));
        labelResult30kmh->setText(QApplication::translate("ResultDialog", "0 - 30 km/h: 8,6 s", 0, QApplication::UnicodeUTF8));
        labelY2->setText(QApplication::translate("ResultDialog", "20", 0, QApplication::UnicodeUTF8));
        labelY6->setText(QApplication::translate("ResultDialog", "60", 0, QApplication::UnicodeUTF8));
        labelY1->setText(QApplication::translate("ResultDialog", "10", 0, QApplication::UnicodeUTF8));
        labelY10->setText(QApplication::translate("ResultDialog", "100", 0, QApplication::UnicodeUTF8));
        labelY3->setText(QApplication::translate("ResultDialog", "30", 0, QApplication::UnicodeUTF8));
        labelYLine->setText(QApplication::translate("ResultDialog", "Y", 0, QApplication::UnicodeUTF8));
        labelY4->setText(QApplication::translate("ResultDialog", "40", 0, QApplication::UnicodeUTF8));
        labelY7->setText(QApplication::translate("ResultDialog", "70", 0, QApplication::UnicodeUTF8));
        labelY8->setText(QApplication::translate("ResultDialog", "80", 0, QApplication::UnicodeUTF8));
        labelY5->setText(QApplication::translate("ResultDialog", "50", 0, QApplication::UnicodeUTF8));
        labelY9->setText(QApplication::translate("ResultDialog", "90", 0, QApplication::UnicodeUTF8));
        labelX1->setText(QApplication::translate("ResultDialog", "1", 0, QApplication::UnicodeUTF8));
        labelX3->setText(QApplication::translate("ResultDialog", "3", 0, QApplication::UnicodeUTF8));
        labelX5->setText(QApplication::translate("ResultDialog", "5", 0, QApplication::UnicodeUTF8));
        labelX9->setText(QApplication::translate("ResultDialog", "9", 0, QApplication::UnicodeUTF8));
        labelX7->setText(QApplication::translate("ResultDialog", "7", 0, QApplication::UnicodeUTF8));
        labelX2->setText(QApplication::translate("ResultDialog", "2", 0, QApplication::UnicodeUTF8));
        labelX6->setText(QApplication::translate("ResultDialog", "6", 0, QApplication::UnicodeUTF8));
        labelX8->setText(QApplication::translate("ResultDialog", "8", 0, QApplication::UnicodeUTF8));
        labelXLine->setText(QApplication::translate("ResultDialog", "X", 0, QApplication::UnicodeUTF8));
        labelX10->setText(QApplication::translate("ResultDialog", "10", 0, QApplication::UnicodeUTF8));
        labelX4->setText(QApplication::translate("ResultDialog", "4", 0, QApplication::UnicodeUTF8));
        pushButtonSend->setText(QApplication::translate("ResultDialog", "Send results", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ResultDialog: public Ui_ResultDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTDIALOG_H
