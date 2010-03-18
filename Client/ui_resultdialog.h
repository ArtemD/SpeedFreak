/********************************************************************************
** Form generated from reading ui file 'resultdialog.ui'
**
** Created: Thu Mar 18 13:34:57 2010
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
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
    QPushButton *pushButtonSend;
    QLabel *labelResult80kmh;
    QLabel *labelResult70kmh;
    QLabel *labelResult60kmh;
    QLabel *labelResult50kmh;
    QLabel *labelResult90kmh;
    QLabel *labelResult100kmh;

    void setupUi(QDialog *ResultDialog)
    {
        if (ResultDialog->objectName().isEmpty())
            ResultDialog->setObjectName(QString::fromUtf8("ResultDialog"));
        ResultDialog->resize(800, 480);
        labelResult10kmh = new QLabel(ResultDialog);
        labelResult10kmh->setObjectName(QString::fromUtf8("labelResult10kmh"));
        labelResult10kmh->setGeometry(QRect(550, 180, 191, 31));
        labelResult40kmh = new QLabel(ResultDialog);
        labelResult40kmh->setObjectName(QString::fromUtf8("labelResult40kmh"));
        labelResult40kmh->setGeometry(QRect(550, 120, 191, 31));
        labelResult20kmh = new QLabel(ResultDialog);
        labelResult20kmh->setObjectName(QString::fromUtf8("labelResult20kmh"));
        labelResult20kmh->setGeometry(QRect(550, 160, 191, 31));
        labelResult30kmh = new QLabel(ResultDialog);
        labelResult30kmh->setObjectName(QString::fromUtf8("labelResult30kmh"));
        labelResult30kmh->setGeometry(QRect(550, 140, 191, 31));
        pushButtonSend = new QPushButton(ResultDialog);
        pushButtonSend->setObjectName(QString::fromUtf8("pushButtonSend"));
        pushButtonSend->setGeometry(QRect(550, 260, 101, 27));
        labelResult80kmh = new QLabel(ResultDialog);
        labelResult80kmh->setObjectName(QString::fromUtf8("labelResult80kmh"));
        labelResult80kmh->setGeometry(QRect(550, 40, 191, 31));
        labelResult70kmh = new QLabel(ResultDialog);
        labelResult70kmh->setObjectName(QString::fromUtf8("labelResult70kmh"));
        labelResult70kmh->setGeometry(QRect(550, 60, 191, 31));
        labelResult60kmh = new QLabel(ResultDialog);
        labelResult60kmh->setObjectName(QString::fromUtf8("labelResult60kmh"));
        labelResult60kmh->setGeometry(QRect(550, 80, 191, 31));
        labelResult50kmh = new QLabel(ResultDialog);
        labelResult50kmh->setObjectName(QString::fromUtf8("labelResult50kmh"));
        labelResult50kmh->setGeometry(QRect(550, 100, 191, 31));
        labelResult90kmh = new QLabel(ResultDialog);
        labelResult90kmh->setObjectName(QString::fromUtf8("labelResult90kmh"));
        labelResult90kmh->setGeometry(QRect(550, 20, 191, 31));
        labelResult100kmh = new QLabel(ResultDialog);
        labelResult100kmh->setObjectName(QString::fromUtf8("labelResult100kmh"));
        labelResult100kmh->setGeometry(QRect(550, 0, 191, 31));

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
        pushButtonSend->setText(QApplication::translate("ResultDialog", "Send results", 0, QApplication::UnicodeUTF8));
        labelResult80kmh->setText(QApplication::translate("ResultDialog", "0 - 80 km/h: 9,8 s", 0, QApplication::UnicodeUTF8));
        labelResult70kmh->setText(QApplication::translate("ResultDialog", "0 - 70 km/h: 8,6 s", 0, QApplication::UnicodeUTF8));
        labelResult60kmh->setText(QApplication::translate("ResultDialog", "0 - 60 km/h: 6,9 s", 0, QApplication::UnicodeUTF8));
        labelResult50kmh->setText(QApplication::translate("ResultDialog", "0 - 50 km/h: 5,6 s", 0, QApplication::UnicodeUTF8));
        labelResult90kmh->setText(QApplication::translate("ResultDialog", "0 - 90 km/h: 8,6 s", 0, QApplication::UnicodeUTF8));
        labelResult100kmh->setText(QApplication::translate("ResultDialog", "0 - 100 km/h: 9,8 s", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ResultDialog);
    } // retranslateUi

};

namespace Ui {
    class ResultDialog: public Ui_ResultDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTDIALOG_H
