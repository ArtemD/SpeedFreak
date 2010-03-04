#include "carmainwindow.h"
#include "ui_carmainwindow.h"
#include "stringlistmodel.h"
#include "loginwindow.h"
#include <QStandardItemModel>
#include <QStringList>
#include <QString>
#include <QNetworkRequest>

/**
  *Constructor of this class.
  *@param QWidget pointer to parent object. By default the value is NULL.
  */
CarMainWindow::CarMainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::CarMainWindow)
{
    ui->setupUi(this);
    result = new ResultDialog();
    measure = new MeasureDialog();

    initUnitCompoBox();
    initSpeedListView();
    initCategoryCompoBox();

    myLogin = new LoginWindow(this);
    myRegistration = new Registration(this);
    manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(networkResponse(QNetworkReply*)));

}

/**
  *Destructor of this class. Should be used to release all allocated resources.
  */
CarMainWindow::~CarMainWindow()
{
    delete ui;
    delete result;
    delete measure;
}

/**
  *This function is used to .
  *@param
  */
void CarMainWindow::changeEvent(QEvent *e)
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

/**
  *This slot function is called when ever list view is update.
  *@param QModelIndex index.
  */
void CarMainWindow::on_listView_clicked(QModelIndex index)
{
    QString str = index.data().toString();
    QStringList list = str.split("-");
    QStringList list2 = list[1].split(" ");

    ui->minLineEdit->setText(list[0]);
    ui->maxLineEdit->setText(list2[0]);
    updateUnitCompoBox(list2[1]);
}

/**
  *This slot function is called when ever auto start button clicked.
  */
void CarMainWindow::on_autoStartButton_clicked()
{

    delete measure;
    measure = NULL;
    measure = new MeasureDialog();

    connect(measure, SIGNAL(speedAchieved()), this, SLOT(openResultView()));
    // Show measure dialog.
    measure->show();
}

/**
  *This slot function is called when ever list view is update.
  *@param QString unit.
  */
void CarMainWindow::updateUnitCompoBox(QString unit)
{
    ui->unitComboBox->setCurrentIndex(ui->unitComboBox->findText(unit, Qt::MatchExactly));
}

/**
  *This function is used to init unit combobox.
  */
void CarMainWindow::initUnitCompoBox()
{
    units << "km/h" << "km" << "h" << "m" << "min" << "mil" << "in" << "ft" << "yrd";
    ui->unitComboBox->addItems(units);
}

/**
  *This function is used to set items to unit combobox.
  *@param QStringlist numbers
  */
void CarMainWindow::setUnitCompoBox(QStringList units)
{
    ui->unitComboBox->addItems(units);
}

/**
  *This function is used to init speed listview.
  */
void CarMainWindow::initSpeedListView()
{
    numbers << "0-40 km/h" << "0-1/4 mil" << "0-50 km" << "50-100 mil" << "0-100 m" << "0-50 ft" << "0-50 yrd" << "0-500 in";
    QAbstractItemModel *model = new StringListModel(numbers);
    ui->listView->setModel(model);
}

/**
<<<<<<< HEAD:Client/carmainwindow.cpp
  *This function is used to set items to speed listview.
  *@param QStringlist numbers
  */
void CarMainWindow::setSpeedListView(QStringList numbers)
{
    QAbstractItemModel *model = new StringListModel(numbers);
    ui->listView->setModel(model);
}

/**
  *This function is used to init category combobox.
  */
void CarMainWindow::initCategoryCompoBox()
{
    categories << "Top 10 1/4 mile" << "Top 10 0-100 km/h" << "Top 10 car";
    ui->comboBoxTopCategory->addItems(categories);
}

/**
  *This function is used to set items to category combobox.
  *@param QStringlist categories
  */
void CarMainWindow::setCategoryCompoBox(QStringList categories)
{
    ui->comboBoxTopCategory->addItems(categories);
}

/**
  *This slot function is called when ever categories combobox is update.
  *@param QString category
  */
void CarMainWindow::on_comboBoxTopCategory_activated(QString category)
{
    //TODO: get top list

    QStringList topList;
    topList << "1. Pertti 7,5s" << "2. Ville 10,2s";

    QAbstractItemModel *model = new StringListModel(topList);
    ui->listViewTopList->setModel(model);
}

/**
  *This slot function is called when speed is achieved in measure dialog. Opens result dialog.
  */
void CarMainWindow::openResultView()
{
    result->saveMeasuresToArray(measure->measures);
    // Show result dialog.
    result->show();
}

/**
  *This slot function is called when the server has finished guery.
  */
void CarMainWindow::networkResponse(QNetworkReply *reply)
{
}

/**
  *This slot function is called when the user will to send data to server.
  */
void CarMainWindow::on_pushButton_clicked()
{
     QNetworkRequest postData;
     postData.setUrl(QString("http://weather.yahooapis.com/forecastrss?p=FIXX0013&u=c"));
     manager->get(postData);

}

/**
  *This slot function is called when login/logout button is clicked.
  */
void CarMainWindow::on_loginLogoutButton_clicked()
{
    //LoginWindow myLogin;

    myLogin->show();
    //ui->loginLogoutButton->setText("logout");
}

/**
  *This slot function is called when registrate button is clicked.
  */
void CarMainWindow::on_registratePushButton_clicked()
{
    myRegistration->show();
}
