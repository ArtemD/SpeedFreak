/**
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
#include <QStandardItemModel>
#include <QNetworkRequest>
#include "resultdialog.h"
#include "measuredialog.h"
#include "loginwindow.h"
#include "registration.h"
#include "xmlreader.h"
#include "ui_carmainwindow.h"
#include "stringlistmodel.h"

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
    ResultDialog *result;
    MeasureDialog *measure;
    XmlReader *xmlreader;
    QNetworkAccessManager* manager;
    LoginWindow *myLogin;
    Registration *myRegistration;
    //void initCategoryCompoBox();    //
    void initComboBoxStartTabUnits();    //Start-tab view
    void initListViewStartTabAccelerationCategories();   //Start-tab view

private:
    QStringList accelerationCategoriesStartTab; //Start-tab view
    QStringList units;  //Start-tab view
    QStringList categories; //Top-tab view

private slots:
    void on_registratePushButton_clicked();
    void on_loginLogoutButton_clicked();
    void on_comboBoxTopCategory_activated(QString );
    void on_pushButton_clicked();
    void networkResponse(QNetworkReply*);
    void on_comboBoxTopCategory_currentIndexChanged(QString category); //Top-tab view
    void on_listViewStartTabAccelerationCategories_clicked(QModelIndex index); //Start-tab view
    void updateComboBoxStartTabUnits(QString unit);  //Start-tab view
    void openResultView();
    void on_buttonTopRefresh_clicked(); //Top-tab view: button
    void on_autoStartButton_clicked();  //Start-tab view: button
};

#endif // CARMAINWINDOW_H
