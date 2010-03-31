/*
 * Mainwindow for speedFreak project
 *
 * @author      Rikhard Kuutti <rikhard.kuutti@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QUrl>
#include <QSettings>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("Fudeco Oy");
    QCoreApplication::setOrganizationDomain("fudeco.com");
    QCoreApplication::setApplicationName("Speed Freak");

    accstart = NULL;

    creditsDialog = new CreditsDialog;
    routeSaveDialog = new RouteSaveDialog;
    routeDialog = new RouteDialog;
    connect(routeDialog,SIGNAL(sendroute()),this,SLOT(clientSendRoute()));
    settingsDialog = new SettingsDialog;
    connect(settingsDialog,SIGNAL(sendregistration()),this,SLOT(clientRegUserToServer()));
    connect(settingsDialog,SIGNAL(userNameChanged()),this,SLOT(clientUserLogin()));
    topResultDialog = new TopResultDialog;
    connect(topResultDialog, SIGNAL(refreshCategoryList()), this, SLOT(clientRequestCategoryList()));
    connect(topResultDialog, SIGNAL(refreshTopList(int)), this, SLOT(clientRequestTopList(int)));
    httpClient = new HttpClient(this);
    connect(httpClient->myXmlreader, SIGNAL(receivedCategoryList()), this, SLOT(setCategoryCompoBox()));
    connect(httpClient->myXmlreader, SIGNAL(receivedTop10List()), this, SLOT(showTop10()));
    resultDialog = new ResultDialog;
    connect(resultDialog, SIGNAL(sendResult(double)), this, SLOT(clientSendResult(double)));

    welcomeDialog = new WelcomeDialog;
    welcomeDialog->show();
}

MainWindow::~MainWindow()
{
    delete ui;

    delete routeSaveDialog;

    if(!accstart)
        delete accstart;
}

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

void MainWindow::on_pushButtonWWW_clicked()
{
    QDesktopServices::openUrl(QUrl("http://garage.maemo.org/projects/speedfreak/"));
}

void MainWindow::on_pushButtonCredits_clicked()
{
    creditsDialog->show();
}

void MainWindow::on_pushButtonRoute_clicked()
{
    routeSaveDialog->show();
}

void MainWindow::on_pushButtonSettings_clicked()
{
    settingsDialog->show();
}

void MainWindow::on_pushButtonAccelerate_clicked()
{
    if(!accstart)
        accstart = new accelerationstart(this);
    accstart->show();
}

void MainWindow::on_pushButtonResults_clicked()
{
    topResultDialog->show();
}

/**
  *This slot function is called when ever mytTopResultDialog emits signal refreshCategoryList button clicked.
  */
void MainWindow::clientRequestCategoryList()
{
    httpClient->requestCategories();
}

/**
  *This slot function is called when ever mytTopResultDialog emits signal refreshTopList button clicked.
  */
void MainWindow::clientRequestTopList(int index)
{
    QString limit = QString::number(topResultDialog->getLimitNr());
    httpClient->requestTopList(httpClient->myXmlreader->myCategoryList->getRecentCategory(index), limit);
}

/**
  *This function is used to set items to category combobox. Top-tab view.
  *@param
  */
void MainWindow::setCategoryCompoBox()
{
    topResultDialog->setCompoBoxCategories(httpClient->myXmlreader->myCategoryList->getCategoryList());
}

/**
  *This function prcesses UI updating after a new top10List has been received.
  *@todo Check where limitNr is taken, fixed or user input, see on_comboBoxTopCategory_currentIndexChanged.
  */
void MainWindow::showTop10()
{
    int ind = topResultDialog->getRecentCategoryIndex();
    setListViewTopList(httpClient->myXmlreader->myCategoryList->getRecentCategory(ind), topResultDialog->getLimitNr());
}

/**
  *This function is used to set items to labelTopList. Top-tab view.
  *@param Category
  *@param Size, number of results.
  */
void MainWindow::setListViewTopList(QString category, int size)
{
    QString topList;
    topList.append(httpClient->myXmlreader->myCategoryList->getTopList(category, size));
    topResultDialog->showTopList(topList);
}

void MainWindow::clientRegUserToServer()
{
    httpClient->requestRegistration();
}

void MainWindow::clientUserLogin()
{
    httpClient->checkLogin();
}

void MainWindow::clientSendRoute()
{
    httpClient->sendRouteXml();
}

void MainWindow::clientSendResult(double result)
{
    if(accstart) {
        httpClient->sendResultXml(accstart->getMeasureCategory(), result);
    }
}
