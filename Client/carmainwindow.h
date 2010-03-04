#ifndef CARMAINWINDOW_H
#define CARMAINWINDOW_H

/**
  *This class
  *@author Toni Jussila
  *@version 0.0.1
  */

#include <QMainWindow>
#include <QModelIndex>
#include <QStringList>
#include <QNetworkAccessManager>
#include "resultdialog.h"
#include "measuredialog.h"
#include "loginwindow.h"
#include "registration.h"

namespace Ui {
    class CarMainWindow;
}

class CarMainWindow : public QMainWindow {
    Q_OBJECT
public:
    CarMainWindow(QWidget *parent = 0);
    ~CarMainWindow();

    void setUnitCompoBox(QStringList units);
    void setSpeedListView(QStringList numbers);
    void setCategoryCompoBox(QStringList categories);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CarMainWindow *ui;
    ResultDialog *result;
    MeasureDialog *measure;

    QNetworkAccessManager* manager;
    LoginWindow *myLogin;
    Registration *myRegistration;

    void initUnitCompoBox();
    void initSpeedListView();
    void initCategoryCompoBox();

private:
    QStringList numbers;
    QStringList units;
    QStringList categories;

private slots:
    void on_registratePushButton_clicked();
    void on_loginLogoutButton_clicked();
    void on_comboBoxTopCategory_activated(QString );
    void on_autoStartButton_clicked();
    void on_listView_clicked(QModelIndex index);
    void updateUnitCompoBox(QString unit);
    void openResultView();

    void on_pushButton_clicked();
    void networkResponse(QNetworkReply*);
};

#endif // CARMAINWINDOW_H
