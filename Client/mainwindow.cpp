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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    creditsDialog = new CreditsDialog;
    routeSaveDialog = new RouteSaveDialog;

    //Button settings
    ui->pushButtonAccelerate->setAutoFillBackground(true);
    ui->pushButtonAccelerate->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");
    ui->pushButtonRoute->setAutoFillBackground(true);
    ui->pushButtonRoute->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");
    ui->pushButtonResults->setAutoFillBackground(true);
    ui->pushButtonResults->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");
    ui->pushButtonSettings->setAutoFillBackground(true);
    ui->pushButtonSettings->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");
    ui->pushButtonWWW->setAutoFillBackground(true);
    ui->pushButtonWWW->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete routeSaveDialog;
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
