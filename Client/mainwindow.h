/*
 * Mainwindow for speedFreak project
 *
 * @author      Rikhard Kuutti  <rikhard.kuutti@fudeco.com>
 * @author      Toni Jussila 	<toni.jussila@fudeco.com>
 * @author      Janne Änäkkälä  <janne.anakkala@fudeco.com>
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
//#include "creditsdialog.h"
#include "routesavedialog.h"
#include "routedialog.h"
#include "welcomedialog.h"
#include "settingsdialog.h"
#include "accelerationstart.h"
#include "topresultdialog.h"
#include "httpclient.h"
#include "routedialog.h"
#include "resultdialog.h"
#include "helpdialog.h"
#include "custombutton.h"
#include "usersdialog.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //CreditsDialog *creditsDialog;
    RouteSaveDialog *routeSaveDialog;
    //RouteDialog *routeDialog;
    WelcomeDialog *welcomeDialog;
    SettingsDialog *settingsDialog;
    accelerationstart* accstart;
    TopResultDialog *topResultDialog;
    HttpClient *httpClient;
    HelpDialog *helpDialog;
    UsersDialog *usersDialog;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    void setListViewTopList(QString category, int size);

    CustomButton* customButtonAccelerate;
    CustomButton* customButtonRoute;
    CustomButton* customButtonResults;
    CustomButton* customButtonSettings;
    CustomButton* customButtonWWW;
    CustomButton* customButtonHelp;
    CustomButton* customButtonUsers;

private slots:    
    void clientRequestCategoryList();
    void clientRequestTopList(int index);
    void clientSendRoute(QString,QString,int);
    void clientRegUserToServer();
    void clientUserLogin();
    void clientSendResult(QString category, double result);
    void setCategoryCompoBox();
    void showTop10();
    void killDialog();
    void setUsernameToMainPanel();
    void OpenAccStartDialog();
    void OpenRouteDialog();
    void OpenResultDialog();
    void saveProfile();
    void OpenWWWPage();
    void OpenHelpDialog();
    void OpenSettingsDialog();
    void requestGetUserInfo(QString);
    void requestGetUsers();
    void openUsersDialog();
};

#endif // MAINWINDOW_H
