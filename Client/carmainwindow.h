/*
 * CarMainWindow main class
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @author     Janne Änäkkälä <janne.anakkala@fudeco.com>
 * @author     Tiina Kivilinna-Korhola <tiina.kivilinna-korhola@fudeco.com>
 * @author     Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
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
//#include "resultdialog.h"
//#include "measuredialog.h"
#include "loginwindow.h"
#include "registration.h"
#include "xmlwriter.h"
#include "xmlreader.h"
#include "ui_carmainwindow.h"
#include "stringlistmodel.h"
#include "measures.h"
#include "accelerometer.h"

namespace Ui {
    class CarMainWindow;
}

class CarMainWindow : public QMainWindow {
    Q_OBJECT
public:
    CarMainWindow(QWidget *parent = 0);
    ~CarMainWindow();

    void setComboBoxStartTabUnits(QStringList units);    //Start-tab view
    void setListViewStartTabAccelerationCategories(QStringList numbers); //Start-tab view
    void setListViewTopList(QString category);  //Top-tab view
    void setCategoryCompoBox(); //Top-tab

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CarMainWindow *ui;
    //ResultDialog *result;
    //MeasureDialog *measure;
    XmlReader *xmlreader;
    XmlWriter *xmlwriter;
    QNetworkAccessManager* manager;
    LoginWindow *myLogin;
    Registration *myRegistration;
    //void initCategoryCompoBox();    //
    void initComboBoxStartTabUnits();    //Start-tab view
    void initListViewStartTabAccelerationCategories();   //Start-tab view

    void initializeMeasures();

private:
    QStringList accelerationCategoriesStartTab; //Start-tab view
    QStringList units;  //Start-tab view
    QStringList categories; //Top-tab view

    QTimer *timer;
    Accelerometer *accelerometer;
    double time;
    double speed;
    Measures *measures;

signals:
void speedAchieved();
void userNameChanged();

private slots:
    void on_pushButtonSendResult_clicked();
    void on_pushButtonMeasureTabAbort_clicked();
    void on_manualStartButton_clicked();
    void on_setUserPushButton_clicked();
    void on_registratePushButton_clicked();
    void on_comboBoxTopCategory_activated(QString );
    //void on_pushButton_clicked();
    void networkResponse(QNetworkReply*);
    void on_comboBoxTopCategory_currentIndexChanged(QString category); //Top-tab view
    void on_listViewStartTabAccelerationCategories_clicked(QModelIndex index); //Start-tab view
    void updateComboBoxStartTabUnits(QString unit);  //Start-tab view
    void openResultView();
    void on_buttonTopRefresh_clicked(); //Top-tab view: button
    void on_autoStartButton_clicked();  //Start-tab view: button
    void registrate();
    void sendXml();
    void requestTopList();
    void ackOfResult(QNetworkReply* reply);
    void ackOfRegistration(QNetworkReply* reply);
    void errorFromServer(QNetworkReply* reply);

    void after_timeout();
    void updateUserName();
};

#endif // CARMAINWINDOW_H
