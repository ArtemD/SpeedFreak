/********************************************************************************
** Form generated from reading ui file 'carmainwindow.ui'
**
** Created: Fri Feb 26 11:59:25 2010
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
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CarMainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *StartTab;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *autoStartButton;
    QPushButton *manualStartButton;
    QListView *listView;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *startLabel;
    QLineEdit *minLineEdit;
    QLabel *stopLabel;
    QLineEdit *maxLineEdit;
    QLabel *unitLabel;
    QComboBox *unitComboBox;
    QWidget *settingsTab;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *view1Button;
    QPushButton *view2Button;
    QPushButton *view3Button;
    QPushButton *view4Button;
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
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 0, 781, 365));
        StartTab = new QWidget();
        StartTab->setObjectName(QString::fromUtf8("StartTab"));
        layoutWidget = new QWidget(StartTab);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(590, 220, 171, 91));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setMargin(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        autoStartButton = new QPushButton(layoutWidget);
        autoStartButton->setObjectName(QString::fromUtf8("autoStartButton"));
        QFont font;
        font.setFamily(QString::fromUtf8("Bitstream Charter"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        autoStartButton->setFont(font);

        verticalLayout->addWidget(autoStartButton);

        manualStartButton = new QPushButton(layoutWidget);
        manualStartButton->setObjectName(QString::fromUtf8("manualStartButton"));
        manualStartButton->setFont(font);

        verticalLayout->addWidget(manualStartButton);

        listView = new QListView(StartTab);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(0, 10, 261, 301));
        widget = new QWidget(StartTab);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(270, 10, 311, 301));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setMargin(11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        startLabel = new QLabel(widget);
        startLabel->setObjectName(QString::fromUtf8("startLabel"));

        verticalLayout_2->addWidget(startLabel);

        minLineEdit = new QLineEdit(widget);
        minLineEdit->setObjectName(QString::fromUtf8("minLineEdit"));

        verticalLayout_2->addWidget(minLineEdit);

        stopLabel = new QLabel(widget);
        stopLabel->setObjectName(QString::fromUtf8("stopLabel"));

        verticalLayout_2->addWidget(stopLabel);

        maxLineEdit = new QLineEdit(widget);
        maxLineEdit->setObjectName(QString::fromUtf8("maxLineEdit"));

        verticalLayout_2->addWidget(maxLineEdit);

        unitLabel = new QLabel(widget);
        unitLabel->setObjectName(QString::fromUtf8("unitLabel"));

        verticalLayout_2->addWidget(unitLabel);

        unitComboBox = new QComboBox(widget);
        unitComboBox->setObjectName(QString::fromUtf8("unitComboBox"));

        verticalLayout_2->addWidget(unitComboBox);

        tabWidget->addTab(StartTab, QString());
        settingsTab = new QWidget();
        settingsTab->setObjectName(QString::fromUtf8("settingsTab"));
        tabWidget->addTab(settingsTab, QString());
        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(10, 370, 781, 41));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setMargin(11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        view1Button = new QPushButton(widget1);
        view1Button->setObjectName(QString::fromUtf8("view1Button"));

        horizontalLayout->addWidget(view1Button);

        view2Button = new QPushButton(widget1);
        view2Button->setObjectName(QString::fromUtf8("view2Button"));

        horizontalLayout->addWidget(view2Button);

        view3Button = new QPushButton(widget1);
        view3Button->setObjectName(QString::fromUtf8("view3Button"));

        horizontalLayout->addWidget(view3Button);

        view4Button = new QPushButton(widget1);
        view4Button->setObjectName(QString::fromUtf8("view4Button"));

        horizontalLayout->addWidget(view4Button);

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

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CarMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CarMainWindow)
    {
        CarMainWindow->setWindowTitle(QApplication::translate("CarMainWindow", "CarMainWindow", 0, QApplication::UnicodeUTF8));
        autoStartButton->setText(QApplication::translate("CarMainWindow", "Auto start", 0, QApplication::UnicodeUTF8));
        manualStartButton->setText(QApplication::translate("CarMainWindow", "Manual start", 0, QApplication::UnicodeUTF8));
        startLabel->setText(QApplication::translate("CarMainWindow", "Start:", 0, QApplication::UnicodeUTF8));
        stopLabel->setText(QApplication::translate("CarMainWindow", "Stop:", 0, QApplication::UnicodeUTF8));
        unitLabel->setText(QApplication::translate("CarMainWindow", "Unit:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(StartTab), QApplication::translate("CarMainWindow", "Start", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(settingsTab), QApplication::translate("CarMainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        view1Button->setText(QApplication::translate("CarMainWindow", "View1", 0, QApplication::UnicodeUTF8));
        view2Button->setText(QApplication::translate("CarMainWindow", "View2", 0, QApplication::UnicodeUTF8));
        view3Button->setText(QApplication::translate("CarMainWindow", "View3", 0, QApplication::UnicodeUTF8));
        view4Button->setText(QApplication::translate("CarMainWindow", "View4", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CarMainWindow);
    } // retranslateUi

};

namespace Ui {
    class CarMainWindow: public Ui_CarMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARMAINWINDOW_H
