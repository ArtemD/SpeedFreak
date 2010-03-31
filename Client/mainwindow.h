/*
 * Mainwindow for speedFreak project
 *
 * @author      Rikhard Kuutti <rikhard.kuutti@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include "creditsdialog.h"
#include "routesavedialog.h"
#include "welcomedialog.h"
#include "settingsdialog.h"
#include "accelerationstart.h"
#include "topresultdialog.h"
#include "httpclient.h"
#include "routedialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    CreditsDialog *creditsDialog;
    RouteSaveDialog *routeSaveDialog;
    WelcomeDialog *welcomeDialog;
    SettingsDialog *settingsDialog;
    accelerationstart* accstart;
    TopResultDialog *topResultDialog;
    HttpClient *httpClient;
    RouteDialog *routeDialog;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    void setListViewTopList(QString category, int size);

private slots:
    void on_pushButtonResults_clicked();
    void on_pushButtonAccelerate_clicked();
    void on_pushButtonSettings_clicked();
    void on_pushButtonRoute_clicked();
    void on_pushButtonCredits_clicked();
    void on_pushButtonWWW_clicked();
    void clientRequestCategoryList();
    void clientRequestTopList(int index);
    void setCategoryCompoBox();
    void showTop10();
    void regUserToServer();
    void userLogin();
};

#endif // MAINWINDOW_H
