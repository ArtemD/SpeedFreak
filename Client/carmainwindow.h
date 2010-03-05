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

    void setUnitCompoBox(QStringList units);    //Start-tab
    void setSpeedListView(QStringList numbers); //Start-tab
    void setListViewTopList(QString category);  //Top-tab
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
    void initCategoryCompoBox();
    void initUnitCompoBox();    //Start-tab
    void initSpeedListView();   //Start-tab

private:
    QStringList numbers; //Start-tab
    QStringList units;  //Start-tab
    QStringList categories; //Top-tab

private slots:
    void on_registratePushButton_clicked();
    void on_loginLogoutButton_clicked();
    void on_comboBoxTopCategory_activated(QString );
    void on_pushButton_clicked();
    void networkResponse(QNetworkReply*);
    void on_comboBoxTopCategory_currentIndexChanged(QString category); //Top-tab
    void on_listView_clicked(QModelIndex index); //Start-tab
    void updateUnitCompoBox(QString unit);  //Start-tab
    void openResultView();
    void on_buttonTopRefresh_clicked(); //Top-tab: button
    void on_autoStartButton_clicked();  //Start-tab: button
};

#endif // CARMAINWINDOW_H
