/********************************************************************************
** Form generated from reading ui file 'carmainwindow.ui'
**
** Created: Wed Mar 10 10:48:38 2010
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
    QListView *listViewStartTabAccelerationCategories;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *startLabel;
    QLineEdit *lineEditStartTabMin;
    QLabel *stopLabel;
    QLineEdit *lineEditStartTabMax;
    QLabel *unitLabel;
    QComboBox *comboBoxStartTabUnits;
    QPushButton *autoStartButton;
    QPushButton *manualStartButton;
    QWidget *tabTop;
    QPushButton *buttonTopRefresh;
    QListView *listViewTopList;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelCategory;
    QComboBox *comboBoxTopCategory;
    QLabel *labelTopList;
    QWidget *settingsTab;
    QLabel *userNameLabel;
    QPushButton *setUserPushButton;
    QWidget *tabMeasureResult;
    QPushButton *pushButtonMeasureTabAbort;
    QLabel *labelMeasureTabHeader;
    QLabel *labelMeasureTabResultHeader;
    QPushButton *pushButtonSendResult;
    QLabel *labelMeasureTabTimeHeader;
    QLabel *labelMeasureTabTime;
    QLabel *labelMeasureTabSpeedHeader;
    QLabel *labelMeasureTabSpeed;
    QLabel *labelMeasureTabResultHeader_2;
    QLabel *labelMeasureTabResult;
    QPushButton *registratePushButton;
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
        tabWidget->setGeometry(QRect(0, 0, 781, 361));
        StartTab = new QWidget();
        StartTab->setObjectName(QString::fromUtf8("StartTab"));
        listViewStartTabAccelerationCategories = new QListView(StartTab);
        listViewStartTabAccelerationCategories->setObjectName(QString::fromUtf8("listViewStartTabAccelerationCategories"));
        listViewStartTabAccelerationCategories->setGeometry(QRect(0, 10, 151, 301));
        layoutWidget = new QWidget(StartTab);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(160, 10, 311, 301));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setMargin(11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        startLabel = new QLabel(layoutWidget);
        startLabel->setObjectName(QString::fromUtf8("startLabel"));

        verticalLayout_2->addWidget(startLabel);

        lineEditStartTabMin = new QLineEdit(layoutWidget);
        lineEditStartTabMin->setObjectName(QString::fromUtf8("lineEditStartTabMin"));

        verticalLayout_2->addWidget(lineEditStartTabMin);

        stopLabel = new QLabel(layoutWidget);
        stopLabel->setObjectName(QString::fromUtf8("stopLabel"));

        verticalLayout_2->addWidget(stopLabel);

        lineEditStartTabMax = new QLineEdit(layoutWidget);
        lineEditStartTabMax->setObjectName(QString::fromUtf8("lineEditStartTabMax"));

        verticalLayout_2->addWidget(lineEditStartTabMax);

        unitLabel = new QLabel(layoutWidget);
        unitLabel->setObjectName(QString::fromUtf8("unitLabel"));

        verticalLayout_2->addWidget(unitLabel);

        comboBoxStartTabUnits = new QComboBox(layoutWidget);
        comboBoxStartTabUnits->setObjectName(QString::fromUtf8("comboBoxStartTabUnits"));

        verticalLayout_2->addWidget(comboBoxStartTabUnits);

        autoStartButton = new QPushButton(StartTab);
        autoStartButton->setObjectName(QString::fromUtf8("autoStartButton"));
        autoStartButton->setGeometry(QRect(520, 40, 201, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("Bitstream Charter"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        autoStartButton->setFont(font);
        manualStartButton = new QPushButton(StartTab);
        manualStartButton->setObjectName(QString::fromUtf8("manualStartButton"));
        manualStartButton->setGeometry(QRect(520, 180, 201, 71));
        manualStartButton->setFont(font);
        tabWidget->addTab(StartTab, QString());
        tabTop = new QWidget();
        tabTop->setObjectName(QString::fromUtf8("tabTop"));
        buttonTopRefresh = new QPushButton(tabTop);
        buttonTopRefresh->setObjectName(QString::fromUtf8("buttonTopRefresh"));
        buttonTopRefresh->setGeometry(QRect(20, 206, 221, 71));
        buttonTopRefresh->setFont(font);
        listViewTopList = new QListView(tabTop);
        listViewTopList->setObjectName(QString::fromUtf8("listViewTopList"));
        listViewTopList->setGeometry(QRect(360, 10, 411, 311));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bitstream Charter"));
        font1.setPointSize(10);
        listViewTopList->setFont(font1);
        listViewTopList->setFlow(QListView::LeftToRight);
        layoutWidget1 = new QWidget(tabTop);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 341, 141));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setMargin(11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        labelCategory = new QLabel(layoutWidget1);
        labelCategory->setObjectName(QString::fromUtf8("labelCategory"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Bitstream Charter"));
        font2.setPointSize(16);
        labelCategory->setFont(font2);

        verticalLayout_3->addWidget(labelCategory);

        comboBoxTopCategory = new QComboBox(layoutWidget1);
        comboBoxTopCategory->setObjectName(QString::fromUtf8("comboBoxTopCategory"));

        verticalLayout_3->addWidget(comboBoxTopCategory);

        labelTopList = new QLabel(tabTop);
        labelTopList->setObjectName(QString::fromUtf8("labelTopList"));
        labelTopList->setGeometry(QRect(380, 10, 371, 311));
        QFont font3;
        font3.setPointSize(9);
        labelTopList->setFont(font3);
        labelTopList->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidget->addTab(tabTop, QString());
        settingsTab = new QWidget();
        settingsTab->setObjectName(QString::fromUtf8("settingsTab"));
        userNameLabel = new QLabel(settingsTab);
        userNameLabel->setObjectName(QString::fromUtf8("userNameLabel"));
        userNameLabel->setGeometry(QRect(20, 30, 531, 71));
        setUserPushButton = new QPushButton(settingsTab);
        setUserPushButton->setObjectName(QString::fromUtf8("setUserPushButton"));
        setUserPushButton->setGeometry(QRect(20, 140, 201, 71));
        tabWidget->addTab(settingsTab, QString());
        tabMeasureResult = new QWidget();
        tabMeasureResult->setObjectName(QString::fromUtf8("tabMeasureResult"));
        pushButtonMeasureTabAbort = new QPushButton(tabMeasureResult);
        pushButtonMeasureTabAbort->setObjectName(QString::fromUtf8("pushButtonMeasureTabAbort"));
        pushButtonMeasureTabAbort->setGeometry(QRect(20, 230, 160, 71));
        labelMeasureTabHeader = new QLabel(tabMeasureResult);
        labelMeasureTabHeader->setObjectName(QString::fromUtf8("labelMeasureTabHeader"));
        labelMeasureTabHeader->setGeometry(QRect(40, 10, 261, 41));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Bitstream Charter"));
        font4.setBold(true);
        font4.setWeight(75);
        labelMeasureTabHeader->setFont(font4);
        labelMeasureTabResultHeader = new QLabel(tabMeasureResult);
        labelMeasureTabResultHeader->setObjectName(QString::fromUtf8("labelMeasureTabResultHeader"));
        labelMeasureTabResultHeader->setGeometry(QRect(470, 10, 101, 41));
        labelMeasureTabResultHeader->setFont(font4);
        pushButtonSendResult = new QPushButton(tabMeasureResult);
        pushButtonSendResult->setObjectName(QString::fromUtf8("pushButtonSendResult"));
        pushButtonSendResult->setEnabled(false);
        pushButtonSendResult->setGeometry(QRect(470, 230, 160, 71));
        pushButtonSendResult->setCheckable(false);
        labelMeasureTabTimeHeader = new QLabel(tabMeasureResult);
        labelMeasureTabTimeHeader->setObjectName(QString::fromUtf8("labelMeasureTabTimeHeader"));
        labelMeasureTabTimeHeader->setGeometry(QRect(25, 70, 60, 41));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Bitstream Charter"));
        font5.setPointSize(14);
        labelMeasureTabTimeHeader->setFont(font5);
        labelMeasureTabTime = new QLabel(tabMeasureResult);
        labelMeasureTabTime->setObjectName(QString::fromUtf8("labelMeasureTabTime"));
        labelMeasureTabTime->setGeometry(QRect(129, 60, 71, 61));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Bitstream Charter"));
        font6.setPointSize(14);
        font6.setBold(true);
        font6.setWeight(75);
        labelMeasureTabTime->setFont(font6);
        labelMeasureTabSpeedHeader = new QLabel(tabMeasureResult);
        labelMeasureTabSpeedHeader->setObjectName(QString::fromUtf8("labelMeasureTabSpeedHeader"));
        labelMeasureTabSpeedHeader->setGeometry(QRect(25, 160, 81, 41));
        labelMeasureTabSpeedHeader->setFont(font5);
        labelMeasureTabSpeed = new QLabel(tabMeasureResult);
        labelMeasureTabSpeed->setObjectName(QString::fromUtf8("labelMeasureTabSpeed"));
        labelMeasureTabSpeed->setGeometry(QRect(129, 160, 51, 41));
        labelMeasureTabSpeed->setFont(font6);
        labelMeasureTabResultHeader_2 = new QLabel(tabMeasureResult);
        labelMeasureTabResultHeader_2->setObjectName(QString::fromUtf8("labelMeasureTabResultHeader_2"));
        labelMeasureTabResultHeader_2->setGeometry(QRect(470, 60, 71, 61));
        labelMeasureTabResultHeader_2->setFont(font5);
        labelMeasureTabResult = new QLabel(tabMeasureResult);
        labelMeasureTabResult->setObjectName(QString::fromUtf8("labelMeasureTabResult"));
        labelMeasureTabResult->setGeometry(QRect(570, 60, 61, 61));
        labelMeasureTabResult->setFont(font6);
        tabWidget->addTab(tabMeasureResult, QString());
        registratePushButton = new QPushButton(centralWidget);
        registratePushButton->setObjectName(QString::fromUtf8("registratePushButton"));
        registratePushButton->setGeometry(QRect(520, 370, 231, 41));
        CarMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CarMainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 25));
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
        CarMainWindow->setWindowTitle(QApplication::translate("CarMainWindow", "Speed freak", 0, QApplication::UnicodeUTF8));
        startLabel->setText(QApplication::translate("CarMainWindow", "Start:", 0, QApplication::UnicodeUTF8));
        stopLabel->setText(QApplication::translate("CarMainWindow", "Stop:", 0, QApplication::UnicodeUTF8));
        unitLabel->setText(QApplication::translate("CarMainWindow", "Unit:", 0, QApplication::UnicodeUTF8));
        autoStartButton->setText(QApplication::translate("CarMainWindow", "Auto start", 0, QApplication::UnicodeUTF8));
        manualStartButton->setText(QApplication::translate("CarMainWindow", "Manual start", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(StartTab), QApplication::translate("CarMainWindow", "Start", 0, QApplication::UnicodeUTF8));
        buttonTopRefresh->setText(QApplication::translate("CarMainWindow", "Refresh list", 0, QApplication::UnicodeUTF8));
        labelCategory->setText(QApplication::translate("CarMainWindow", "Category:", 0, QApplication::UnicodeUTF8));
        labelTopList->setText(QApplication::translate("CarMainWindow", "TopList", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabTop), QApplication::translate("CarMainWindow", "Top", 0, QApplication::UnicodeUTF8));
        userNameLabel->setText(QApplication::translate("CarMainWindow", "User:", 0, QApplication::UnicodeUTF8));
        setUserPushButton->setText(QApplication::translate("CarMainWindow", "Set User", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(settingsTab), QApplication::translate("CarMainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        pushButtonMeasureTabAbort->setText(QApplication::translate("CarMainWindow", "Abort", 0, QApplication::UnicodeUTF8));
        labelMeasureTabHeader->setText(QApplication::translate("CarMainWindow", "Accelerate to 40 km/h", 0, QApplication::UnicodeUTF8));
        labelMeasureTabResultHeader->setText(QApplication::translate("CarMainWindow", "Results:", 0, QApplication::UnicodeUTF8));
        pushButtonSendResult->setText(QApplication::translate("CarMainWindow", "Send result", 0, QApplication::UnicodeUTF8));
        labelMeasureTabTimeHeader->setText(QApplication::translate("CarMainWindow", "Time:", 0, QApplication::UnicodeUTF8));
        labelMeasureTabTime->setText(QApplication::translate("CarMainWindow", "0", 0, QApplication::UnicodeUTF8));
        labelMeasureTabSpeedHeader->setText(QApplication::translate("CarMainWindow", "Speed:", 0, QApplication::UnicodeUTF8));
        labelMeasureTabSpeed->setText(QApplication::translate("CarMainWindow", "0", 0, QApplication::UnicodeUTF8));
        labelMeasureTabResultHeader_2->setText(QApplication::translate("CarMainWindow", "Time:", 0, QApplication::UnicodeUTF8));
        labelMeasureTabResult->setText(QApplication::translate("CarMainWindow", "0", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabMeasureResult), QApplication::translate("CarMainWindow", "Measure", 0, QApplication::UnicodeUTF8));
        registratePushButton->setText(QApplication::translate("CarMainWindow", "Registrate", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CarMainWindow);
    } // retranslateUi

};

namespace Ui {
    class CarMainWindow: public Ui_CarMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARMAINWINDOW_H
