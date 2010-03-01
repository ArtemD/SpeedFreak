/********************************************************************************
** Form generated from reading ui file 'carmainwindow.ui'
**
** Created: Wed Feb 24 13:07:28 2010
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CARMAINWINDOW_H
#define UI_CARMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CarMainWindow
{
public:
    QWidget *centralWidget;
    QListView *listView;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *autoStartButton;
    QPushButton *manualStartButton;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CarMainWindow)
    {
        if (CarMainWindow->objectName().isEmpty())
            CarMainWindow->setObjectName(QString::fromUtf8("CarMainWindow"));
        CarMainWindow->resize(800, 480);
        centralWidget = new QWidget(CarMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        listView = new QListView(centralWidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(10, 0, 256, 101));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(650, 340, 147, 78));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setMargin(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        autoStartButton = new QPushButton(widget);
        autoStartButton->setObjectName(QString::fromUtf8("autoStartButton"));
        QFont font;
        font.setFamily(QString::fromUtf8("Bitstream Charter"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        autoStartButton->setFont(font);

        verticalLayout->addWidget(autoStartButton);

        manualStartButton = new QPushButton(widget);
        manualStartButton->setObjectName(QString::fromUtf8("manualStartButton"));
        manualStartButton->setFont(font);

        verticalLayout->addWidget(manualStartButton);

        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(340, 6, 146, 201));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setMargin(11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget1);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(widget1);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout_2->addWidget(lineEdit);

        CarMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CarMainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 27));
        CarMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CarMainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CarMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CarMainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CarMainWindow->setStatusBar(statusBar);

        retranslateUi(CarMainWindow);

        QMetaObject::connectSlotsByName(CarMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CarMainWindow)
    {
        CarMainWindow->setWindowTitle(QApplication::translate("CarMainWindow", "CarMainWindow", 0, QApplication::UnicodeUTF8));
        autoStartButton->setText(QApplication::translate("CarMainWindow", "Auto start", 0, QApplication::UnicodeUTF8));
        manualStartButton->setText(QApplication::translate("CarMainWindow", "Manual start", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CarMainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CarMainWindow);
    } // retranslateUi

};

namespace Ui {
    class CarMainWindow: public Ui_CarMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARMAINWINDOW_H
