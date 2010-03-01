/********************************************************************************
** Form generated from reading ui file 'measuredialog.ui'
**
** Created: Fri Feb 26 11:59:25 2010
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MEASUREDIALOG_H
#define UI_MEASUREDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeasureDialog
{
public:
    QLabel *label_7;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButtonAbort;

    void setupUi(QDialog *MeasureDialog)
    {
        if (MeasureDialog->objectName().isEmpty())
            MeasureDialog->setObjectName(QString::fromUtf8("MeasureDialog"));
        MeasureDialog->resize(800, 480);
        label_7 = new QLabel(MeasureDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(130, 40, 361, 51));
        layoutWidget = new QWidget(MeasureDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 120, 271, 151));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_2->addWidget(label_6);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_2->addWidget(label_5);


        horizontalLayout->addLayout(verticalLayout_2);

        pushButtonAbort = new QPushButton(MeasureDialog);
        pushButtonAbort->setObjectName(QString::fromUtf8("pushButtonAbort"));
        pushButtonAbort->setGeometry(QRect(200, 300, 93, 27));

        retranslateUi(MeasureDialog);

        QMetaObject::connectSlotsByName(MeasureDialog);
    } // setupUi

    void retranslateUi(QDialog *MeasureDialog)
    {
        MeasureDialog->setWindowTitle(QApplication::translate("MeasureDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MeasureDialog", "Selected measurement: 0 - 100 km/h", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MeasureDialog", "Time:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MeasureDialog", "Speed:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MeasureDialog", "Distance:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MeasureDialog", "14 s", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MeasureDialog", "86 km/h", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MeasureDialog", "120 m", 0, QApplication::UnicodeUTF8));
        pushButtonAbort->setText(QApplication::translate("MeasureDialog", "Abort", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MeasureDialog);
    } // retranslateUi

};

namespace Ui {
    class MeasureDialog: public Ui_MeasureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEASUREDIALOG_H
