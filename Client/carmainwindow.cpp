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

#include "carmainwindow.h"
#include "math.h"

#define kAccelerometerSampleRate    50
#define kFilteringFactor            0.2
#define kSecondsInHour              3600

/**
  *Constructor of this class.
  *@param QWidget pointer to parent object. By default the value is NULL.
  */
CarMainWindow::CarMainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::CarMainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentWidget(this->ui->StartTab);
    result = new ResultDialog();
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
    connect(myLogin,SIGNAL(userNameChanged()),this,SLOT(userLogin()));
    myRoute = new RouteDialog( this);

    //GPS
    location = new Maemo5Location(this);
    gpsData = new GPSData(location);
    connect(location,SIGNAL(agnss()),this,SLOT(gpsStatus()));
    gpsTime = new QDateTime();

    time = 0;
    speed = 0;
    timer = new QTimer();

    // Accelerometer
    accelerometer = new Accelerometer();

    reverseAccelerationFlag = false;
    vehicleStartedMoving = false;
    isNewRun = true;
    isSetup = false;
    stopTime = 0;
    accelerationStartThreshold = 0.02;

    QTimer *accelerometerTimer = new QTimer(this);
    connect(accelerometerTimer, SIGNAL(timeout()), this, SLOT(readAccelerometerData()));
    accelerometerTimer->start(kAccelerometerSampleRate);

    // Calculate
    calculate = new Calculate();
    //connect(calculate, SIGNAL(checkPointReached()), this, SLOT(handleCheckPoint()));

    resetAccelerometerMeasurements();

    measures = new Measures();
    this->initializeMeasures();

    timer->setInterval(300);

    connect(this->timer, SIGNAL(timeout()), this, SLOT(after_timeout()));
    connect(myLogin, SIGNAL( userNameChanged()), this, SLOT(updateUserName()));

    ui->labelMeasureTabResult->hide();

    this->setWindowTitle("Speed Freak");

}

/**
  *Destructor of this class. Deletes all dynamic objects and sets them to NULL.
  */
CarMainWindow::~CarMainWindow()
{
    delete ui;
    ui = NULL;
    //delete result;
    //delete measure;
    delete categorylist;
    categorylist = NULL;
    delete welcomeDialog;
    welcomeDialog = NULL;
    delete myRoute;
    myRoute = NULL;
    delete gpsData;
    gpsData = NULL;
    delete gpsTime;
    gpsTime = NULL;
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
    choice = ui->listViewStartTabAccelerationCategories->currentIndex();
    choiceInt = choice.row();
    qDebug() << choiceInt;
    if (choiceInt == 0)
    {
        ui->labelMeasureTabHeader->setText("Accelerate to 40 km/h");
        result->setDiagramGapStem(75);
    }

    else if (choiceInt == 1)
    {
        ui->labelMeasureTabHeader->setText("Accelerate to 100 km/h");
        result->setDiagramGapStem(30);
    }

    else
    {
        ui->labelMeasureTabHeader->setText("Accelerate to 80 km/h");
        result->setDiagramGapStem(37.5);
    }
    ui->labelMeasureTabResult->setText("");
    //delete measure;
    //measure = NULL;
    //measure = new MeasureDialog();
   // connect(measure, SIGNAL(speedAchieved()), this, SLOT(openResultView()));
    timer->start();
    // Show measure dialog.
    //measure->show();

    // TODO: Move next if else to the function which is called when target speed
    // has reached.
    if (choiceInt == 0)
    {
        if (floor(this->measures->getTime40kmh()) <= 5)
        {
            result->setDiagramGapHorizontal(80);
        }

        else if (floor(this->measures->getTime40kmh()) <= 10)
        {
            result->setDiagramGapHorizontal(40);
        }

        else
        {
            result->setDiagramGapHorizontal(20);
        }
    }

    else
    {
        if (floor(this->measures->getTime40kmh()) <= 5)
        {
            result->setDiagramGapHorizontal(80);
        }

        else if (floor(this->measures->getTime40kmh()) <= 10)
        {
            result->setDiagramGapHorizontal(40);
        }

        else
        {
            result->setDiagramGapHorizontal(20);
        }
    }

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
    if (choiceInt == 0)
    {
        if (floor(this->measures->getTime40kmh()) <= 5)
        {
            result->setDiagramGapHorizontal(80);
        }

        else if (floor(this->measures->getTime40kmh()) <= 10)
        {
            result->setDiagramGapHorizontal(40);
        }

        else
        {
            result->setDiagramGapHorizontal(20);
        }
    }

    else
    {
        if (floor(this->measures->getTime40kmh()) <= 5)
        {
            result->setDiagramGapHorizontal(80);
        }

        else if (floor(this->measures->getTime40kmh()) <= 10)
        {
            result->setDiagramGapHorizontal(40);
        }

        else
        {
            result->setDiagramGapHorizontal(20);
        }
    }
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
    time++;
    speed = speed +10;

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


void CarMainWindow::on_drawRoutePushButton_clicked()
{
    myRoute->show();
}

/**
  * Opens result dialog when show result button is clicked.
  * Sends measures as parameter to the resultdialogs saveMeasuresToArray-function.
  */
void CarMainWindow::on_pushButtonShowResultDialog_clicked()
{
    Measures meas;
    meas.setTime10kmh(1.3);
    meas.setTime20kmh(2.5);
    meas.setTime30kmh(3.6);
    meas.setTime40kmh(6.7);
    meas.setTime50kmh(7.3);
    meas.setTime60kmh(7.5);
    meas.setTime70kmh(8.6);
    meas.setTime80kmh(8.7);
    meas.setTime90kmh(9.6);
    meas.setTime100kmh(9.9);
    result->setDiagramGapHorizontal(40);
    result->saveMeasuresToArray(&meas);
    this->result->show();
}

void CarMainWindow::userLogin()
{
    myHttpClient->checkLogin();
}

/**
  * Resets Accelerometer measurement variables
  */
void CarMainWindow::resetAccelerometerMeasurements()
{
    currentAcceleration = 0;
    currentAccelerationString = "";
    currentSpeed = "";
    currentTime = 0;
    distanceTraveled = "";
    firstAcceleration = 0;
    //horsepower = null;
    isNewRun = true;
    //lastScreenUpdateInSeconds = 0;
    previousTime = 0;
    reverseAccelerationFlag = false;
    stopWatch.setHMS(0, 0, 0, 0);
    //accelerometer->stop();
    totalTime = "";
    vehicleStartedMoving = false;
    calculate->reset();
}

/**
  * This function is called to handle checkpoints
  *@param totalTime total time elapsed since starting measurements
  *@param currentSpeed current speed of the device
  */
void CarMainWindow::handleCheckPoint(double totalTime, double currentSpeed)
{
    // TODO
    //totalTime;
    //currentSpeed;
    return;
}

/**
  *This function is called to read (and process) data from the accelerometer
  */
void CarMainWindow::readAccelerometerData()
{
    QString s;
    double changeInAcceleration = 0;
    qreal x, y, z;

    accelerometer->getAcceleration(x, y, z);
    accelerometer->smoothData(x, y, z);

    // Apply calibration
    x -= accelerometer->getCalibrationX();
    y -= accelerometer->getCalibrationY();
    z -= accelerometer->getCalibrationZ();

    QString str = QString("acc x: " + QString::number(x) + "\n" +
                          "acc y: " + QString::number(y) + "\n" +
                          "acc z: " + QString::number(z) + "\n");

    if (!vehicleStartedMoving)
    {
        if (isNewRun)
        {
            firstAcceleration = sqrt(x*x + y*y + z*z);
            //firstAcceleration = y; // first read
            isNewRun = false;
        }
    }

    currentAcceleration = sqrt(x*x + y*y + z*z);
    changeInAcceleration = (currentAcceleration - firstAcceleration); // firstAcceleration only gets set once

    if (((abs(changeInAcceleration) <= accelerationStartThreshold)
                && !vehicleStartedMoving))
    {
        return;
    }

    if (reverseAccelerationFlag)
    {
        // will be false until after 1st calculation
        if ((changeInAcceleration <= 0))
        {
            // actually increasing here...
            changeInAcceleration = abs(changeInAcceleration);
        }
        else
        {
            // actually decreasing here...
            changeInAcceleration = (changeInAcceleration * -1);
        }
    }
    if (!vehicleStartedMoving)
    {
        if ((changeInAcceleration < 0))
        {
            // we started to move backwards first time through
            reverseAccelerationFlag = true;
            changeInAcceleration = abs(changeInAcceleration);
        }
        vehicleStartedMoving = true;

        stopWatch.setHMS(0, 0, 0, 0);
        stopWatch.start();
    }
    //  keep the following line as close to the SetKinematicsProperties method as possible
    currentTime = stopWatch.elapsed();
    calculate->calculateParameters(changeInAcceleration, (currentTime - previousTime)/1000);
    previousTime = currentTime;

    s.sprintf("%.2f", changeInAcceleration);
    currentAccelerationString = s;

    speed = 0.0;
    speed = calculate->getCurrentSpeed();
    speed = ((speed*1000)/kSecondsInHour);
    s.sprintf("%.2f", speed);
    currentSpeed = s;

    s.sprintf("%.2f", calculate->getDistanceTraveled());
    distanceTraveled = s;

    // TODO
    //distanceTraveled;
    //horsepower;

    time = calculate->getTotalTime();

    s.sprintf("%.2f", time);
    totalTime = s;

    str.append("ca: " + currentAccelerationString + " G\n" );
    str.append("cspeed: " + currentSpeed + " km/h \n" );
    str.append("dist: " + distanceTraveled + " m \n" );
    str.append("time: " + totalTime + " s \n" );

    if ((stopTime > 0) && (previousTime >= stopTime))
    {
        // we want to end at a stopping point that the user chose
        // output results
        resetAccelerometerMeasurements();
    }
}

/**
  *This function is used to calibrate accelerometer
  */
void CarMainWindow::calibrateAccelerometer()
{
    resetAccelerometerMeasurements();
    accelerometer->calibrate();
}

/**
  *This slot function is called when GPS on checkbox state changed.  Route-tab view.
  *@param int GPSState
  */
void CarMainWindow::on_gpsOnCheckBox_stateChanged(int GPSState)
{
    if (GPSState == 0)
    {
        ui->labelRouteTabGPSStatus->setText("GPS off");//testing
        location->stopPollingGPS();
    }
    else
    {
        ui->labelRouteTabGPSStatus->setText("GPS on");//testing
        location->startPollingGPS();
    }
}

/**
  *This slot function is called when GPS status changed.  Route-tab view.
  */
void CarMainWindow::gpsStatus()
{
    if (ui->gpsOnCheckBox->isChecked())
    {
        if (location->getSatellitesInUse() >= 4)
        {
            //Set status
            //ui->labelRouteTabGPSStatus->setText("GPS ready");
            ui->labelRouteTabGPSStatus->setText(QString::number(gpsData->roundCounter));

            //Set time
            gpsTime->setTime_t(location->getTime());
            ui->labelRouteTabGPSTime->setText(gpsTime->toString());

            //Set latitude & longitude
            ui->labelRouteTabLatitude->setText("Lat: " + QString::number(location->getLatitude()));
            ui->labelRouteTabLongitude->setText("Lon: " + QString::number(location->getLongitude()));
        }

        else
        {
            ui->labelRouteTabGPSStatus->setText("Waiting for GPS");
        }
    }
    ui->labelRouteTabSpeed->setText(QString::number(location->getSpeed()));
}

void CarMainWindow::on_startRecPushButton_clicked()
{
    ui->labelRouteTabRecStatus->setText("Recording started");
    gpsData->startRouteRecording(ui->labelRouteTabGPSTime->text());
}

void CarMainWindow::on_stopRecPushButton_clicked()
{
    ui->labelRouteTabRecStatus->setText("Recording stopped");
    gpsData->stopRouteRecording(ui->labelRouteTabGPSTime->text());
}
