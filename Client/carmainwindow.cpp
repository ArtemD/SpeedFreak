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

#include "carmainwindow.h"

/**
  *Constructor of this class.
  *@param QWidget pointer to parent object. By default the value is NULL.
  */
CarMainWindow::CarMainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::CarMainWindow)
{
    ui->setupUi(this);
    result = new ResultDialog();
    measure = new MeasureDialog();
    xmlreader = new XmlReader();

    initComboBoxStartTabUnits();
    initListViewStartTabAccelerationCategories();

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
    delete xmlreader;
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
  *This slot function is called when ever list view is update. Start-tab view.
  */
void CarMainWindow::on_listViewStartTabAccelerationCategories_clicked(QModelIndex index)
{
    QString str = index.data().toString();
    QStringList list = str.split("-");
    QStringList list2 = list[1].split(" ");

    ui->lineEditStartTabMin->setText(list[0]);
    ui->lineEditStartTabMax->setText(list2[0]);
    updateComboBoxStartTabUnits(list2[1]);
}

/**
  *This slot function is called when ever auto start button clicked. Start-tab view.
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
  *This slot function is called when ever list view is update. Start-tab view.
  *@param QString unit.
  */
void CarMainWindow::updateComboBoxStartTabUnits(QString unit)
{
    ui->comboBoxStartTabUnits->setCurrentIndex(ui->comboBoxStartTabUnits->findText(unit, Qt::MatchExactly));
}

/**
  *This function is used to init unit combobox. Start-tab view.
  */
void CarMainWindow::initComboBoxStartTabUnits()
{
    units << "km/h" << "km" << "h" << "m" << "min" << "Mile" << "Mph" << "in" << "ft" << "yrd";
    ui->comboBoxStartTabUnits->addItems(units);
}

/**
  *This function is used to set items to unit combobox. Start-tab view.
  *@param QStringlist units
  */
void CarMainWindow::setComboBoxStartTabUnits(QStringList units)
{
    ui->comboBoxStartTabUnits->addItems(units);
}

/**
  *This function is used to init listViewStartTabAccelerationCategories. Start-tab view.
  */
void CarMainWindow::initListViewStartTabAccelerationCategories()
{
    accelerationCategoriesStartTab << "0-40 km/h" << "0-100 km/h"; //<< "0-1/4 Mile" << "0-1/8 Mile" << "0-50 km" << "50-100 Mile" << "0-60 Mph" << "0-100 m" << "0-50 ft" << "0-50 yrd" << "0-500 in";
    QAbstractItemModel *model = new StringListModel(accelerationCategoriesStartTab);
    ui->listViewStartTabAccelerationCategories->setModel(model);
}

/**
  *This function is used to set items to listViewStartTabAccelerationCategories. Start-tab view.
  *@param QStringlist accelerationCategoriesStartTab
  */
void CarMainWindow::setListViewStartTabAccelerationCategories(QStringList accelerationCategoriesStartTab)
{
    QAbstractItemModel *model = new StringListModel(accelerationCategoriesStartTab);
    ui->listViewStartTabAccelerationCategories->setModel(model);
}

/**
  *This function is used to set items to category combobox. Top-tab view.
  *@param
  */
void CarMainWindow::setCategoryCompoBox()
{
    ui->comboBoxTopCategory->addItems(xmlreader->getTop10List());
}

/**
  *This function is used to set items to labelTopList. Top-tab view.
  *@param QString category
  */
void CarMainWindow::setListViewTopList(QString category)
{
    QString topList;

    if (category == "acceleration-0-100")
    {
        topList.append(xmlreader->getTop10AccelerationList());
    }

    else if (category == "Speed")
    {
        topList.append(xmlreader->getTop10SpeedList());
    }

    else if (category == "G-force")
    {
        topList.append(xmlreader->getTop10GforceList());
    }
    ui->labelTopList->setText(topList);
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

/**
  *This slot function is called when ever refresh button clicked. Top-tab view.
  */
void CarMainWindow::on_buttonTopRefresh_clicked()
{
    setCategoryCompoBox();
}

/**
  *This slot function is called when ever category combobox current index changed. Top-tab view.
  *@param QString category
  */
void CarMainWindow::on_comboBoxTopCategory_currentIndexChanged(QString category)
{
    setListViewTopList(category);
}

/**
  *This slot function is called when ever category combobox activated. Top-tab view.
  *@param QString category
  */
void CarMainWindow::on_comboBoxTopCategory_activated(QString category)
{
    setListViewTopList(category);
}

/**
  *This slot function is called when set/change user button is clicked.
  */
void CarMainWindow::on_setUserPushButton_clicked()
{
    myLogin->show();

    ui->userNameLabel->setText( "User: " + myLogin->getUserName());
    ui->setUserPushButton->setText( "Change User");
}
