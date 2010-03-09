/********************************************************************************
** Form generated from reading ui file 'carmainwindow.ui'
**
** Created: Mon Mar 8 15:04:52 2010
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
    QListView *listViewStartTabAccelerationCategories;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *startLabel;
    QLineEdit *lineEditStartTabMin;
    QLabel *stopLabel;
    QLineEdit *lineEditStartTabMax;
    QLabel *unitLabel;
    QComboBox *comboBoxStartTabUnits;
    QWidget *tabTop;
    QPushButton *buttonTopRefresh;
    QListView *listViewTopList;
    QWidget *layoutWidget2;
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
    QWidget *widget;
    QHBoxLayout *horizontalLayoutMeasureTabTime;
    QLabel *labelMeasureTabTimeHeader;
    QLabel *labelMeasureTabTime;
    QWidget *widget1;
    QHBoxLayout *horizontalLayoutMeasureTabSpeed;
    QLabel *labelMeasureTabSpeedHeader;
    QLabel *labelMeasureTabSpeed;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelMeasureTabResultHeader_2;
    QLabel *labelMeasureTabResult;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout;
    QPushButton *view1Button;
    QPushButton *view2Button;
    QPushButton *view3Button;
    QPushButton *view4Button;
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
        tabWidget->setGeometry(QRect(10, 0, 781, 361));
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

        listViewStartTabAccelerationCategories = new QListView(StartTab);
        listViewStartTabAccelerationCategories->setObjectName(QString::fromUtf8("listViewStartTabAccelerationCategories"));
        listViewStartTabAccelerationCategories->setGeometry(QRect(0, 10, 261, 301));
        layoutWidget1 = new QWidget(StartTab);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(270, 10, 311, 301));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setMargin(11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        startLabel = new QLabel(layoutWidget1);
        startLabel->setObjectName(QString::fromUtf8("startLabel"));

        verticalLayout_2->addWidget(startLabel);

        lineEditStartTabMin = new QLineEdit(layoutWidget1);
        lineEditStartTabMin->setObjectName(QString::fromUtf8("lineEditStartTabMin"));

        verticalLayout_2->addWidget(lineEditStartTabMin);

        stopLabel = new QLabel(layoutWidget1);
        stopLabel->setObjectName(QString::fromUtf8("stopLabel"));

        verticalLayout_2->addWidget(stopLabel);

        lineEditStartTabMax = new QLineEdit(layoutWidget1);
        lineEditStartTabMax->setObjectName(QString::fromUtf8("lineEditStartTabMax"));

        verticalLayout_2->addWidget(lineEditStartTabMax);

        unitLabel = new QLabel(layoutWidget1);
        unitLabel->setObjectName(QString::fromUtf8("unitLabel"));

        verticalLayout_2->addWidget(unitLabel);

        comboBoxStartTabUnits = new QComboBox(layoutWidget1);
        comboBoxStartTabUnits->setObjectName(QString::fromUtf8("comboBoxStartTabUnits"));

        verticalLayout_2->addWidget(comboBoxStartTabUnits);

        tabWidget->addTab(StartTab, QString());
        tabTop = new QWidget();
        tabTop->setObjectName(QString::fromUtf8("tabTop"));
        buttonTopRefresh = new QPushButton(tabTop);
        buttonTopRefresh->setObjectName(QString::fromUtf8("buttonTopRefresh"));
        buttonTopRefresh->setGeometry(QRect(20, 270, 169, 37));
        buttonTopRefresh->setFont(font);
        listViewTopList = new QListView(tabTop);
        listViewTopList->setObjectName(QString::fromUtf8("listViewTopList"));
        listViewTopList->setGeometry(QRect(360, 10, 411, 311));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bitstream Charter"));
        font1.setPointSize(10);
        listViewTopList->setFont(font1);
        listViewTopList->setFlow(QListView::LeftToRight);
        layoutWidget2 = new QWidget(tabTop);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 10, 341, 141));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setMargin(11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        labelCategory = new QLabel(layoutWidget2);
        labelCategory->setObjectName(QString::fromUtf8("labelCategory"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Bitstream Charter"));
        font2.setPointSize(16);
        labelCategory->setFont(font2);

        verticalLayout_3->addWidget(labelCategory);

        comboBoxTopCategory = new QComboBox(layoutWidget2);
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
        userNameLabel->setGeometry(QRect(20, 30, 141, 17));
        setUserPushButton = new QPushButton(settingsTab);
        setUserPushButton->setObjectName(QString::fromUtf8("setUserPushButton"));
        setUserPushButton->setGeometry(QRect(20, 60, 93, 27));
        tabWidget->addTab(settingsTab, QString());
        tabMeasureResult = new QWidget();
        tabMeasureResult->setObjectName(QString::fromUtf8("tabMeasureResult"));
        pushButtonMeasureTabAbort = new QPushButton(tabMeasureResult);
        pushButtonMeasureTabAbort->setObjectName(QString::fromUtf8("pushButtonMeasureTabAbort"));
        pushButtonMeasureTabAbort->setGeometry(QRect(40, 240, 161, 51));
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
        labelMeasureTabResultHeader->setGeometry(QRect(370, 10, 101, 41));
        labelMeasureTabResultHeader->setFont(font4);
        pushButtonSendResult = new QPushButton(tabMeasureResult);
        pushButtonSendResult->setObjectName(QString::fromUtf8("pushButtonSendResult"));
        pushButtonSendResult->setGeometry(QRect(370, 240, 161, 51));
        widget = new QWidget(tabMeasureResult);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(40, 60, 171, 61));
        horizontalLayoutMeasureTabTime = new QHBoxLayout(widget);
        horizontalLayoutMeasureTabTime->setSpacing(6);
        horizontalLayoutMeasureTabTime->setMargin(11);
        horizontalLayoutMeasureTabTime->setObjectName(QString::fromUtf8("horizontalLayoutMeasureTabTime"));
        horizontalLayoutMeasureTabTime->setContentsMargins(0, 0, 0, 0);
        labelMeasureTabTimeHeader = new QLabel(widget);
        labelMeasureTabTimeHeader->setObjectName(QString::fromUtf8("labelMeasureTabTimeHeader"));

        horizontalLayoutMeasureTabTime->addWidget(labelMeasureTabTimeHeader);

        labelMeasureTabTime = new QLabel(widget);
        labelMeasureTabTime->setObjectName(QString::fromUtf8("labelMeasureTabTime"));

        horizontalLayoutMeasureTabTime->addWidget(labelMeasureTabTime);

        widget1 = new QWidget(tabMeasureResult);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(40, 160, 171, 61));
        horizontalLayoutMeasureTabSpeed = new QHBoxLayout(widget1);
        horizontalLayoutMeasureTabSpeed->setSpacing(6);
        horizontalLayoutMeasureTabSpeed->setMargin(11);
        horizontalLayoutMeasureTabSpeed->setObjectName(QString::fromUtf8("horizontalLayoutMeasureTabSpeed"));
        horizontalLayoutMeasureTabSpeed->setContentsMargins(0, 0, 0, 0);
        labelMeasureTabSpeedHeader = new QLabel(widget1);
        labelMeasureTabSpeedHeader->setObjectName(QString::fromUtf8("labelMeasureTabSpeedHeader"));

        horizontalLayoutMeasureTabSpeed->addWidget(labelMeasureTabSpeedHeader);

        labelMeasureTabSpeed = new QLabel(widget1);
        labelMeasureTabSpeed->setObjectName(QString::fromUtf8("labelMeasureTabSpeed"));

        horizontalLayoutMeasureTabSpeed->addWidget(labelMeasureTabSpeed);

        widget2 = new QWidget(tabMeasureResult);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(370, 60, 151, 61));
        horizontalLayout_2 = new QHBoxLayout(widget2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setMargin(11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        labelMeasureTabResultHeader_2 = new QLabel(widget2);
        labelMeasureTabResultHeader_2->setObjectName(QString::fromUtf8("labelMeasureTabResultHeader_2"));

        horizontalLayout_2->addWidget(labelMeasureTabResultHeader_2);

        labelMeasureTabResult = new QLabel(widget2);
        labelMeasureTabResult->setObjectName(QString::fromUtf8("labelMeasureTabResult"));

        horizontalLayout_2->addWidget(labelMeasureTabResult);

        tabWidget->addTab(tabMeasureResult, QString());
        layoutWidget3 = new QWidget(centralWidget);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 380, 781, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setMargin(11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        view1Button = new QPushButton(layoutWidget3);
        view1Button->setObjectName(QString::fromUtf8("view1Button"));

        horizontalLayout->addWidget(view1Button);

        view2Button = new QPushButton(layoutWidget3);
        view2Button->setObjectName(QString::fromUtf8("view2Button"));

        horizontalLayout->addWidget(view2Button);

        view3Button = new QPushButton(layoutWidget3);
        view3Button->setObjectName(QString::fromUtf8("view3Button"));

        horizontalLayout->addWidget(view3Button);

        view4Button = new QPushButton(layoutWidget3);
        view4Button->setObjectName(QString::fromUtf8("view4Button"));

        horizontalLayout->addWidget(view4Button);

        registratePushButton = new QPushButton(centralWidget);
        registratePushButton->setObjectName(QString::fromUtf8("registratePushButton"));
        registratePushButton->setGeometry(QRect(690, 0, 93, 27));
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

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(CarMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CarMainWindow)
    {
        CarMainWindow->setWindowTitle(QApplication::translate("CarMainWindow", "Speed freak", 0, QApplication::UnicodeUTF8));
        autoStartButton->setText(QApplication::translate("CarMainWindow", "Auto start", 0, QApplication::UnicodeUTF8));
        manualStartButton->setText(QApplication::translate("CarMainWindow", "Manual start", 0, QApplication::UnicodeUTF8));
        startLabel->setText(QApplication::translate("CarMainWindow", "Start:", 0, QApplication::UnicodeUTF8));
        stopLabel->setText(QApplication::translate("CarMainWindow", "Stop:", 0, QApplication::UnicodeUTF8));
        unitLabel->setText(QApplication::translate("CarMainWindow", "Unit:", 0, QApplication::UnicodeUTF8));
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
        view1Button->setText(QApplication::translate("CarMainWindow", "View1", 0, QApplication::UnicodeUTF8));
        view2Button->setText(QApplication::translate("CarMainWindow", "View2", 0, QApplication::UnicodeUTF8));
        view3Button->setText(QApplication::translate("CarMainWindow", "View3", 0, QApplication::UnicodeUTF8));
        view4Button->setText(QApplication::translate("CarMainWindow", "View4", 0, QApplication::UnicodeUTF8));
        registratePushButton->setText(QApplication::translate("CarMainWindow", "Registrate", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CarMainWindow);
    } // retranslateUi

};

namespace Ui {
    class CarMainWindow: public Ui_CarMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARMAINWINDOW_H
