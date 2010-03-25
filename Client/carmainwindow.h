/*
 * CarMainWindow main class
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @author     Janne Änäkkälä <janne.anakkala@fudeco.com>
 * @author     Tiina Kivilinna-Korhola <tiina.kivilinna-korhola@fudeco.com>
 * @author     Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
 * @author     Rikhard Kuutti <rikhard.kuutti@fudeco.com>
 * @author     Kai Rasilainen <kai.rasilainen@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef CARMAINWINDOW_H
#define CARMAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QStringList>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QBuffer>
#include <QByteArray>
#include <QDebug>
#include <qdatetime.h>
#include "resultdialog.h"
//#include "measuredialog.h"
#include "welcomedialog.h"
#include "loginwindow.h"
#include "registration.h"
#include "xmlwriter.h"
#include "xmlreader.h"
#include "ui_carmainwindow.h"
#include "stringlistmodel.h"
#include "measures.h"
#include "accelerometer.h"
#include "categorylist.h"
#include "httpclient.h"
#include "routedialog.h"
#include "calculate.h"
#include "gpsdata.h"
#include <maemo5location.h>

namespace Ui {
    class CarMainWindow;
}

class CarMainWindow : public QMainWindow {
    Q_OBJECT
public:
    CarMainWindow(QWidget *parent = 0);
    ~CarMainWindow();
    Registration *myRegistration;       //Check if this should be public or private
    LoginWindow *myLogin;
    GPSData *gpsData;

    void setComboBoxStartTabUnits(QStringList units);       //Start-tab view
    void setListViewStartTabAccelerationCategories(QStringList numbers); //Start-tab view
    void setLabelInfoToUser(QString infoText);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CarMainWindow *ui;
    ResultDialog *result;
    //MeasureDialog *measure;
    WelcomeDialog *welcomeDialog;
    CategoryList *myCategorylist;
    HttpClient *myHttpClient;
    RouteDialog *myRoute;
    Maemo5Location *location;
    //void initCategoryCompoBox();
    void initComboBoxStartTabUnits();                   //Start-tab view
    void initListViewStartTabAccelerationCategories();  //Start-tab view
    void setListViewTopList(QString category, int size);    //Top-tab view
    void resetAccelerometerMeasurements();
    void calibrateAccelerometer();
    void setTimeAxisGapAndShowResult(double pTime);

private:
    QStringList accelerationCategoriesStartTab;         //Start-tab view
    QStringList units;                                  //Start-tab view
    QString recentCategory;

    QTimer *timer;
    Accelerometer *accelerometer;
    double time;
    double speed;
    Measures *measures;

    QModelIndex choice;
    int choiceInt;
    QStringList catList;

    Calculate *calculate;

    bool reverseAccelerationFlag;
    bool vehicleStartedMoving;
    bool isNewRun;
    bool isSetup;

    double stopTime;
    double accelerationStartThreshold;
    double currentAcceleration;
    double currentTime;
    double previousTime;
    double firstAcceleration;

    QTimer *accelerometerTimer;
    QTime stopWatch;

    QString currentAccelerationString;
    QString currentSpeed;
    QString distanceTraveled;
    QString horsepower;
    QString totalTime;

    QDateTime *gpsTime;
    QTimer *gpsTimer;
    double gpsSpeedNow;     //Route-tab view
    double gpsSpeedPrevious;//Route-tab view
    double gpsAcceleration; //Route-tab view
    double timeFromGps;     //Route-tab view
    double gpsSpeed;        //Route-tab view
    int gpsUpdateTime;      //Route-tab view

    int counterForSaveResults;

signals:
    void speedAchieved();
    void userNameChanged();

private slots:
    void gpsTimerTimeout();                             //Route-tab view
    void on_startRecPushButton_clicked();               //Route-tab view
    void on_pushButtonShowResultDialog_clicked();
    void on_gpsOnCheckBox_stateChanged(int GPSState);   //Route-tab view
    void gpsStatus();                                   //Route-tab view
    void on_drawRoutePushButton_clicked();
    void on_pushButtonSendResult_clicked();
    void on_pushButtonMeasureTabAbort_clicked();
    void on_manualStartButton_clicked();
    void on_setUserPushButton_clicked();
    void on_registratePushButton_clicked();
    void on_comboBoxTopCategory_currentIndexChanged(QString category);          //Top-tab view
    void on_listViewStartTabAccelerationCategories_clicked(QModelIndex index);  //Start-tab view
    void updateComboBoxStartTabUnits(QString unit);     //Start-tab view
    void openResultView();
    void on_buttonTopRefresh_clicked();                 //Top-tab view: button
    void on_autoStartButton_clicked();                  //Start-tab view: button
    void after_timeout();
    void updateUserName();
    void regUserToServer();
    void userLogin();
    void readAccelerometerData();
    void handleCheckPoint(double totalTime, double currentSpeed);
    void setCategoryCompoBox();                         //Top-tab
    void showTop10();

};

#endif // CARMAINWINDOW_H
