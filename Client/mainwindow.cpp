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

    creditsDialog = new CreditsDialog;
    routeSaveDialog = new RouteSaveDialog;
    settingsDialog = new SettingsDialog;
    topResultDialog = new TopResultDialog;
    connect(topResultDialog, SIGNAL(refreshCategoryList()), this, SLOT(clientRequestCategoryList()));
    connect(topResultDialog, SIGNAL(refreshTopList(int)), this, SLOT(clientRequestTopList(int)));
    accstart = NULL;

    httpClient = new HttpClient(this);

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
    qDebug() << "index" << index << httpClient->myXmlreader->myCategoryList->getRecentCategory(index);
    QString limit = QString::number(topResultDialog->getLimitNr());
    httpClient->requestTopList(httpClient->myXmlreader->myCategoryList->getRecentCategory(index), limit);
}
