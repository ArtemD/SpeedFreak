/*
 * Mainwindow for speedFreak project
 *
 * @author      Rikhard Kuutti 	<rikhard.kuutti@fudeco.com>
 * @author      Toni Jussila 	<toni.jussila@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QUrl>
#include <QSettings>
#include <QDebug>
#include "usersettings.h"

/**
  *
  */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("Fudeco Oy");
    QCoreApplication::setOrganizationDomain("fudeco.com");
    QCoreApplication::setApplicationName("Speed Freak");

    helpDialog = NULL;
    accstart = NULL;
    routeSaveDialog = NULL;
    topResultDialog = NULL;

    settingsDialog = new SettingsDialog;
    connect(settingsDialog, SIGNAL(sendregistration()), this, SLOT(clientRegUserToServer()));
    connect(settingsDialog, SIGNAL(userNameChanged()),  this, SLOT(clientUserLogin()));
    connect(settingsDialog, SIGNAL(logout()),           this, SLOT(setUsernameToMainPanel()));
    connect(settingsDialog, SIGNAL(saveprofile()),      this, SLOT(saveProfile()));

    httpClient = new HttpClient(this);
    connect(httpClient->myXmlreader, SIGNAL(receivedCategoryList()), this, SLOT(setCategoryCompoBox()));
    connect(httpClient->myXmlreader, SIGNAL(receivedTop10List()), this, SLOT(showTop10()));    

    welcomeDialog = new WelcomeDialog;
    welcomeDialog->show();

    this->setUsernameToMainPanel();

    //Create icon for acceleration start button
    QIcon* icon = new QIcon();
    icon->addFile(QString(":/new/prefix1/Graphics/Speedometer.png"), QSize(125,125), QIcon::Normal, QIcon::Off);
    icon->addFile(QString(":/new/prefix1/Graphics/Speedometer2.png"), QSize(125,125), QIcon::Normal, QIcon::On);

    //Acceleration start button

    customButtonAccelerate = new CustomButton(this,icon);
    delete icon;

    int buttons_x = 50,buttons_y = 165;
    customButtonAccelerate->setGeometry(buttons_x,buttons_y,130,130);
    connect(customButtonAccelerate, SIGNAL(OpenDialog()), this, SLOT(OpenAccStartDialog()));
    customButtonAccelerate->show();

    //Create icon for route dialog button
    icon = new QIcon();
    icon->addFile(QString(":/new/prefix1/Graphics/route.png"), QSize(125,125), QIcon::Normal, QIcon::Off);
    icon->addFile(QString(":/new/prefix1/Graphics/route_selected.png"), QSize(125,125), QIcon::Normal, QIcon::On);

    //Route dialog button

    customButtonRoute = new CustomButton(this,icon);
    delete icon;

    buttons_x += 140;
    customButtonRoute->setGeometry(buttons_x,buttons_y,130,130);
    connect(customButtonRoute, SIGNAL(OpenDialog()), this, SLOT(OpenRouteDialog()));
    customButtonRoute->show();

    //Create icon for results dialog button
    icon = new QIcon();
    icon->addFile(QString(":/new/prefix1/Graphics/trophy_gold.png"), QSize(125,125), QIcon::Normal, QIcon::Off);
    icon->addFile(QString(":/new/prefix1/Graphics/trophy_gold_selected.png"), QSize(125,125), QIcon::Normal, QIcon::On);

    //Results dialog button

    customButtonResults = new CustomButton(this,icon);
    delete icon;

    buttons_x += 140;
    customButtonResults->setGeometry(buttons_x,buttons_y,130,130);
    connect(customButtonResults, SIGNAL(OpenDialog()), this, SLOT(OpenResultDialog()));
    customButtonResults->show();
    //Create icon for settings dialog button
    icon = new QIcon();
    icon->addFile(QString(":/new/prefix1/Graphics/settings.png"), QSize(125,125), QIcon::Normal, QIcon::Off);
    icon->addFile(QString(":/new/prefix1/Graphics/settings_selected.png"), QSize(125,125), QIcon::Normal, QIcon::On);

    //Settings dialog button

    customButtonSettings = new CustomButton(this,icon);
    delete icon;

    buttons_x += 140;
    customButtonSettings->setGeometry(buttons_x,buttons_y,130,130);
    connect(customButtonSettings, SIGNAL(OpenDialog()), this, SLOT(OpenSettingsDialog()));
    customButtonSettings->show();

    //Create icon for www page button
    icon = new QIcon();
    icon->addFile(QString(":/new/prefix1/Graphics/applications_internet.png"), QSize(125,125), QIcon::Normal, QIcon::Off);
    icon->addFile(QString(":/new/prefix1/Graphics/applications_internet_selected.png"), QSize(125,125), QIcon::Normal, QIcon::On);

    //WWW page button

    customButtonWWW = new CustomButton(this,icon);
    delete icon;

    buttons_x += 140;
    customButtonWWW->setGeometry(buttons_x,buttons_y,130,130);
    connect(customButtonWWW, SIGNAL(OpenDialog()), this, SLOT(OpenWWWPage()));
    customButtonWWW->show();

    //Create icon for help dialog button
    icon = new QIcon();
    icon->addFile(QString(":/new/prefix1/Graphics/info.png"), QSize(105,105), QIcon::Normal, QIcon::Off);
    icon->addFile(QString(":/new/prefix1/Graphics/info_selected.png"), QSize(105,105), QIcon::Normal, QIcon::On);

    //Help dialog button

    customButtonHelp = new CustomButton(this,icon);
    delete icon;

    customButtonHelp->setGeometry(670,10,105,105);
    connect(customButtonHelp, SIGNAL(OpenDialog()), this, SLOT(OpenHelpDialog()));
    customButtonHelp->show();
}

/**
  *
  */
MainWindow::~MainWindow()
{
    delete ui;

    if(routeSaveDialog)
        delete routeSaveDialog;

    if(accstart)
        delete accstart;

    if(topResultDialog)
        delete topResultDialog;

    if(settingsDialog)
        delete settingsDialog;

    if(welcomeDialog)
        delete welcomeDialog;

    if(httpClient)
        delete httpClient;

    if(helpDialog)
        delete helpDialog;

    if(customButtonAccelerate)
        delete customButtonAccelerate;
    if(customButtonRoute)
        delete customButtonRoute;
    if(customButtonResults)
        delete customButtonResults;
    if(customButtonSettings)
        delete customButtonSettings;
    if(customButtonWWW)
        delete customButtonWWW;
    if(customButtonHelp)
        delete customButtonHelp;
}


/**
  *
  */
void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/**
  *This slot function is called when ever mytTopResultDialog emits signal refreshCategoryList button clicked.
  */
void MainWindow::clientRequestCategoryList()
{
    if(httpClient)
        httpClient->requestCategories();
}

/**
  *This slot function is called when ever mytTopResultDialog emits signal refreshTopList button clicked.
  */
void MainWindow::clientRequestTopList(int index)
{
    QString limit;

    if(topResultDialog && httpClient->myXmlreader->myCategoryList)
    {
        limit = QString::number(topResultDialog->getLimitNr());
        httpClient->requestTopList(httpClient->myXmlreader->myCategoryList->getRecentCategory(index), limit);
    }
}

/**
  *This function is used to set items to category combobox. Top-tab view.
  *@param
  */
void MainWindow::setCategoryCompoBox()
{
    if(topResultDialog && httpClient->myXmlreader->myCategoryList)
        topResultDialog->setCompoBoxCategories(httpClient->myXmlreader->myCategoryList->getCategoryList());
}

/**
  *This function prcesses UI updating after a new top10List has been received.
  *@todo Check where limitNr is taken, fixed or user input, see on_comboBoxTopCategory_currentIndexChanged.
  */
void MainWindow::showTop10()
{
    int ind;

    if(topResultDialog && httpClient->myXmlreader->myCategoryList && topResultDialog)
    {
        ind = topResultDialog->getRecentCategoryIndex();
        setListViewTopList(httpClient->myXmlreader->myCategoryList->getRecentCategory(ind), topResultDialog->getLimitNr());
    }
}

/**
  *This function is used to set items to labelTopList. Top-tab view.
  *@param Category
  *@param Size, number of results.
  */
void MainWindow::setListViewTopList(QString category, int size)
{
    QString topList;

    if(httpClient->myXmlreader->myCategoryList && topResultDialog)
    {
        topList.append(httpClient->myXmlreader->myCategoryList->getTopList(category, size));
        topResultDialog->showTopList(topList);
    }
}

/**
  * This function register user to server.
  */
void MainWindow::clientRegUserToServer()
{
    if(httpClient)
        httpClient->requestRegistration();
}

/**
  * This function performs login to server.
  */
void MainWindow::clientUserLogin()
{
    
    if(httpClient)
    {
	connect(httpClient, SIGNAL(loginOK()), this, SLOT(setUsernameToMainPanel()));
        httpClient->checkLogin();
    }
}

/**
  * This function send route data to server.
  */
void MainWindow::clientSendRoute()
{
    if(httpClient)
        httpClient->sendRouteXml();
}

/**
  * This function send acceleration data to server.
  */
void MainWindow::clientSendResult(QString category, double result)
{
    qDebug() << "__clientSendResult";
    if(accstart) {
        qDebug() << "_clientSendResult, calling server";
        if(httpClient)
            httpClient->sendResultXml(category, result);
    }
}

/**
  * This slot function called when ever dialog rejected.
  */
void MainWindow::killDialog()
{
    if(topResultDialog)
    {
        qDebug() << "__MW kill: topResultDialog";
        delete topResultDialog;
        topResultDialog = NULL;
    }
    if(routeSaveDialog)
    {
        //qDebug() << "__MW kill: routeSaveDialog";
        //delete routeSaveDialog;
        //routeSaveDialog = NULL;
    }
    if(accstart)
    {
        qDebug() << "__MW kill: accstart";
        delete accstart;
        accstart = NULL;
    }
    if(welcomeDialog)
    {
        qDebug() << "__MW kill: welcomeDialog";
        delete welcomeDialog;
        welcomeDialog = NULL;
    }
    if(helpDialog)
    {
        qDebug() << "__MW kill: helpDialog";
        delete helpDialog;
        helpDialog = NULL;
    }
}

/**
  *
  */
void MainWindow::setUsernameToMainPanel()
{
    if (loginSaved())
    {
        this->setWindowTitle("SpeedFreak - " + settingsDialog->getUserName());
    }
    else
    {
        this->setWindowTitle("SpeedFreak - Not logged");
    }
}
/**
  * This slot function opens acceleration start dialog.
  */
void MainWindow::OpenAccStartDialog()
{
    if(!accstart)
        accstart = new accelerationstart(this);

    connect(accstart, SIGNAL(sendresult(QString, double)), this, SLOT(clientSendResult(QString, double)));
    connect(accstart, SIGNAL(rejected()), this, SLOT(killDialog()));
    accstart->show();
}
/**
  * This slot function opens the route save dialog
  */
void MainWindow::OpenRouteDialog()
{
    if(!routeSaveDialog)
        routeSaveDialog = new RouteSaveDialog;

    connect(routeSaveDialog, SIGNAL(sendroute()), this, SLOT(clientSendRoute()));
    connect(routeSaveDialog, SIGNAL(rejected()), this, SLOT(killDialog()));
    routeSaveDialog->show();
}
/**
  * This slot function opens the top results dialog
  */
void MainWindow::OpenResultDialog()
{
    if (!topResultDialog)
        topResultDialog = new TopResultDialog;

    clientRequestCategoryList();
    connect(topResultDialog, SIGNAL(refreshCategoryList()), this, SLOT(clientRequestCategoryList()));
    connect(topResultDialog, SIGNAL(refreshTopList(int)), this, SLOT(clientRequestTopList(int)));
    connect(topResultDialog, SIGNAL(rejected()), this, SLOT(killDialog()));
    topResultDialog->show();
}
/**
  * This slot function opens the settings dialog
  */
void MainWindow::OpenSettingsDialog()
{
    settingsDialog->show();
}
/**
  * This slot function opens browser to project www page.
  */
void MainWindow::OpenWWWPage()
{
    QDesktopServices::openUrl(QUrl("http://garage.maemo.org/projects/speedfreak/"));
}
/**
  * This slot function opens the main help dialog
  */
void MainWindow::OpenHelpDialog()
{
    if(!helpDialog)
        helpDialog = new HelpDialog;

    connect(helpDialog, SIGNAL(rejected()), this, SLOT(killDialog()));
    helpDialog->show();
}

/**
  * This slot function save user profile data to server
  */
void MainWindow::saveProfile()
{
    if(httpClient)
        httpClient->sendProfileXml();
}
