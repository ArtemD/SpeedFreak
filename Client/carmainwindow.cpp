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

#include "carmainwindow.h"
#include "math.h"

/**
  *Constructor of this class.
  *@param QWidget pointer to parent object. By default the value is NULL.
  */
CarMainWindow::CarMainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::CarMainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentWidget(this->ui->StartTab);
    //result = new ResultDialog();
    //measure = new MeasureDialog();
    welcomeDialog = new WelcomeDialog();
    welcomeDialog->show();

    initComboBoxStartTabUnits();
    initListViewStartTabAccelerationCategories();

    myLogin = new LoginWindow(this);
    categorylist = new CategoryList();
    myHttpClient = new HttpClient(this);
    myRegistration = new Registration(this);
    connect(myRegistration,SIGNAL(sendregistration()),this,SLOT(regUserToServer()));

    time = 0;
    speed = 0;
    timer = new QTimer();

    accelerometer = new Accelerometer();
    accelerometer->setSampleRate(100);

    measures = new Measures();
    this->initializeMeasures();

    timer->setInterval(300);

    connect(this->timer, SIGNAL(timeout()), this, SLOT(after_timeout()));
    connect(myLogin, SIGNAL( userNameChanged()), this, SLOT(updateUserName()));

    ui->labelMeasureTabResult->hide();

    this->setWindowTitle("Speed Freak");

}

/**
  *Destructor of this class. Should be used to release all allocated resources.
  */
CarMainWindow::~CarMainWindow()
{
    delete ui;
    //delete result;
    //delete measure;
    delete categorylist;
    delete welcomeDialog;
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

    //delete measure;
    //measure = NULL;
    //measure = new MeasureDialog();
   // connect(measure, SIGNAL(speedAchieved()), this, SLOT(openResultView()));
    accelerometer->start();
    timer->start();
    // Show measure dialog.
    //measure->show();
    ui->tabWidget->setCurrentWidget(this->ui->tabMeasureResult);
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
    ui->comboBoxTopCategory->addItems(categorylist->getCategoryList());
}

/**
  *This function is used to set items to labelTopList. Top-tab view.
  *@param QString category
  */
void CarMainWindow::setListViewTopList(QString category, int size)
{
    QString topList;
    topList.append( categorylist->getTopList(category, size));
    ui->labelTopList->setText(topList);
}

/**
  *This slot function is called when speed is achieved in measure dialog. Opens result dialog.
  */
void CarMainWindow::openResultView()
{
    //result->saveMeasuresToArray(measure->measures);
    // Show result dialog.
    //result->show();
    ui->pushButtonSendResult->setEnabled(true);
    QString timeInteger;
    timeInteger.setNum(this->measures->getTime40kmh());
    //time = "0 - 40 km/h: ";
    //time.append(timeInteger);
    //ui->labelResult40kmh->setText(time);
    ui->labelMeasureTabResult->show();
    ui->labelMeasureTabResult->setText(timeInteger);
    //ui->tabWidget->setCurrentWidget(this->ui->tabMeasureResult);
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
    myHttpClient->requestCategories();
    setCategoryCompoBox();
}

/**
  *This slot function is called when ever category combobox current index changed. Top-tab view.
  *@param QString category
  *@todo Check where limitNr is taken.
  */
void CarMainWindow::on_comboBoxTopCategory_currentIndexChanged(QString category)
{
    int limitNr = 5;                    //replace with real value?
    QString limit = QString::number(limitNr);
    category = "acceleration-0-100";    //replace with real value from category list/top window
    myHttpClient->requestTopList(category, limit);
    setListViewTopList(category,10);
}

/**
  *This slot function is called when ever category combobox activated. Top-tab view.
  *@param QString category
  */
void CarMainWindow::on_comboBoxTopCategory_activated(QString category)
{
    setListViewTopList(category,10);
}

/**
  *This slot function is called when set/change user button is clicked.
  */
void CarMainWindow::on_setUserPushButton_clicked()
{
    myLogin->show();
}

/**
  *@brief Just for development, for the real button is not shown until
  *measurin started and there are results.
  *@todo Implement with real code and yet leave sendXml in the bottom in use.
  */
void CarMainWindow::on_manualStartButton_clicked()
{

}

/**
  * This slot function is called when timer gives timeout signal. Checks current speed
  * and stores times in measure class.
  */
void CarMainWindow::after_timeout()
{
    QString timeString, speedString;
    //time++;
    time = accelerometer->getTotalTime();
    speed = accelerometer->getCurrentSpeed();
    //speed = speed +10;

    if (floor(speed) == 10)
    {
        measures->setTime10kmh(time);
    }

    else if (floor(speed) == 20)
    {
        measures->setTime20kmh(time);
    }

    else if (floor(speed) == 30)
    {
        measures->setTime30kmh(time);
    }

    else if (floor(speed) == 40)
    {
        measures->setTime40kmh(time);
    }

    else if (floor(speed) == 50)
    {
        measures->setTime50kmh(time);
    }

    else if (floor(speed) == 60)
    {
        measures->setTime60kmh(time);
    }

    else if (floor(speed) == 70)
    {
        measures->setTime70kmh(time);
    }

    else if (floor(speed) == 80)
    {
        measures->setTime80kmh(time);
    }

    else if (floor(speed) == 90)
    {
        measures->setTime90kmh(time);
    }

    else if (floor(speed) == 100)
    {
        measures->setTime100kmh(time);
    }

    else
    {

    }

    // If speed is over 40 km/h emits speedAchieved() signal and close this dialog.
    if (speed >= 40.0)
    {
        timer->stop();
        accelerometer->stop();
        time = 0;
        speed = 0;
        //emit this->speedAchieved();
        this->openResultView();
        //this->close();

    }

    // Updates speed and time.
    else
    {
        timeString.setNum(time);
        speedString.setNum(speed);
        ui->labelMeasureTabTime->setText(timeString);
        ui->labelMeasureTabSpeed->setText(speedString);

        timer->start();
    }

}

/**
  * Initializes measures class's member variables.
  */
void CarMainWindow::initializeMeasures()
{
    measures->setTime10kmh(0);
    measures->setTime20kmh(0);
    measures->setTime30kmh(0);
    measures->setTime40kmh(0);
    measures->setTime50kmh(0);
    measures->setTime60kmh(0);
    measures->setTime70kmh(0);
    measures->setTime80kmh(0);
    measures->setTime90kmh(0);
    measures->setTime100kmh(0);
}

/**
  * This slot function is called when Abort button is clicked.
  */
void CarMainWindow::on_pushButtonMeasureTabAbort_clicked()
{
    measures->setTime10kmh(0);
    measures->setTime20kmh(0);
    measures->setTime30kmh(0);
    measures->setTime40kmh(0);
    measures->setTime50kmh(0);
    measures->setTime60kmh(0);
    measures->setTime70kmh(0);
    measures->setTime80kmh(0);
    measures->setTime90kmh(0);
    measures->setTime100kmh(0);
    timer->stop();
    accelerometer->stop();
    time = 0;
    speed = 0;
    ui->tabWidget->setCurrentWidget(this->ui->StartTab);
    //this->close();
}

void CarMainWindow::on_pushButtonSendResult_clicked()
{
    myHttpClient->sendResultXml();
    ui->pushButtonSendResult->setEnabled(false);
}

void CarMainWindow::updateUserName()
{
    QString newUserName;

    newUserName = myLogin->getUserName();
    ui->userNameLabel->setText( "User: " + newUserName);

    if (newUserName.length())
    {
       ui->setUserPushButton->setText( "Change User");
       this->setWindowTitle("Speed freak - " + newUserName);
    }
    else
    {
        ui->setUserPushButton->setText( "Set User");
        this->setWindowTitle("Speed freak");
    }
}

void CarMainWindow::regUserToServer()
{
    myHttpClient->requestRegistration();
}
