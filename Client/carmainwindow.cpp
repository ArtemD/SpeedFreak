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

#define kAccelerometerSampleRate    40
#define kFilteringFactor            0.1
#define kSecondsInHour              3600

/**
  *Constructor of this class.
  *@param QWidget pointer to parent object. By default the value is NULL.
  */
CarMainWindow::CarMainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::CarMainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentWidget(this->ui->StartTab);

    //Disable start buttons before calibration
    ui->autoStartButton->setEnabled(false);
    ui->manualStartButton->setEnabled(false);

    result = new ResultDialog();
    //measure = new MeasureDialog();
    welcomeDialog = new WelcomeDialog();
    welcomeDialog->show();

    initComboBoxStartTabUnits();
    initListViewStartTabAccelerationCategories();

    myLogin = new LoginWindow(this);
    myCategorylist = new CategoryList();
    myHttpClient = new HttpClient(this);
    myRegistration = new Registration(this);
    connect(myRegistration,SIGNAL(sendregistration()),this,SLOT(regUserToServer()));
    connect(myLogin,SIGNAL(userNameChanged()),this,SLOT(userLogin()));
    connect(myHttpClient->myXmlreader, SIGNAL(receivedCategoryList()), this, SLOT(setCategoryCompoBox()));
    connect(myHttpClient->myXmlreader, SIGNAL(receivedTop10List()), this, SLOT(showTop10()));
    myRoute = new RouteDialog( this);

    //GPS
    location = new Maemo5Location(this);
    gpsData = new GPSData(location);
    connect(location,SIGNAL(agnss()),this,SLOT(gpsStatus()));
    gpsTime = new QDateTime();
    gpsTimer = new QTimer();
    connect(gpsTimer, SIGNAL(timeout()),this, SLOT(gpsTimerTimeout()));
    gpsSpeedNow = 0.0;
    gpsSpeedPrevious = 0.0;
    gpsAcceleration = 0.0;
    timeFromGps = 0.0; //Measure-tab view.
    gpsSpeed = 0.0;

    this->time = 0;
    this->speed = 0;
    counterForSaveResults = 0;
    timer = new QTimer();

    // Accelerometer
    accelerometer = new Accelerometer();

    reverseAccelerationFlag = false;
    vehicleStartedMoving = false;
    isNewRun = true;
    isSetup = false;
    stopTime = 0;
    accelerationStartThreshold = 0.1;

    accelerometerTimer = new QTimer(this);
    connect(accelerometerTimer, SIGNAL(timeout()), this, SLOT(readAccelerometerData()));
    //accelerometerTimer->start(kAccelerometerSampleRate);

    // Calculate
    calculate = new Calculate();
    connect(calculate, SIGNAL(checkPointReached()), this, SLOT(handleCheckPoint()));

    resetAccelerometerMeasurements();

    measures = new Measures();
    this->initializeMeasures();

    this->timer->setInterval(100);

    connect(this->timer, SIGNAL(timeout()), this, SLOT(after_timeout()));
    connect(myLogin, SIGNAL( userNameChanged()), this, SLOT(updateUserName()));

    ui->labelMeasureTabResult->hide();
    ui->pushButtonShowResultDialog->setEnabled(false);
    ui->pushButtonShowResultDialog->setEnabled(false);

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
    delete myCategorylist;
    myCategorylist = NULL;
    delete welcomeDialog;
    welcomeDialog = NULL;
    delete myRoute;
    myRoute = NULL;
    delete gpsData;
    gpsData = NULL;
    delete gpsTime;
    gpsTime = NULL;

    //Route-tab view
    gpsSpeedNow = 0.0;
    gpsSpeedPrevious = 0.0;
    gpsAcceleration = 0.0;
    timeFromGps = 0.0;
    gpsSpeed = 0.0;
    gpsUpdateTime = 0;
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
  *@todo Check setDiagramGapStem(100) <- (choiceInt == 2)
  */
void CarMainWindow::on_autoStartButton_clicked()
{
    initializeMeasures();
    resetAccelerometerMeasurements();
    ui->pushButtonSendResult->setEnabled(false);
    ui->pushButtonShowResultDialog->setEnabled(false);
    choice = ui->listViewStartTabAccelerationCategories->currentIndex();
    choiceInt = choice.row();
    //qDebug() << "choiceInt" << choiceInt << " " << catList.at(choiceInt);
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
    else if (choiceInt == 2)
    {
        ui->labelMeasureTabHeader->setText("Accelerate to 10 km/h");
        result->setDiagramGapStem(100);
    }
    else
    {
        ui->labelMeasureTabHeader->setText("Accelerate to 80 km/h");
        result->setDiagramGapStem(37.5);
    }
    ui->labelMeasureTabResult->setText("");

    this->accelerometerTimer->start(kAccelerometerSampleRate);
    this->timer->start();
    this->time = 0;
    this->speed = 0;
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
  *@todo During development categories index values that are used for measuring are hardcoded
  *@todo and accelerationCategoriesStartTab and catList are used instead of using
  *@todo CategoryList::categoryList and CategoryList::cats.
  */
void CarMainWindow::initListViewStartTabAccelerationCategories()
{
    //Connect the user`s choice fron GUI to a correct variable name
    catList.insert(0,"acceleration-0-40");
    catList.insert(1,"acceleration-0-100");
    catList.insert(2,"acceleration-0-10");

    accelerationCategoriesStartTab << "0-40 km/h" << "0-100 km/h" << "0-10 km/h";
    //<< "0-1/4 Mile" << "0-1/8 Mile" << "50-100 Mile" << "0-60 Mph" << "0-100 m" << "0-50 ft" << "0-50 yrd" << "0-500 in";
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

void CarMainWindow::setLabelInfoToUser(QString infoText)
{
    ui->labelInfoToUser->setText(infoText);
}

/**
  *This function is used to set items to category combobox. Top-tab view.
  *@param
  */
void CarMainWindow::setCategoryCompoBox()
{
    qDebug() << "_setCategoryCompoBox";
    ui->comboBoxTopCategory->addItems(myHttpClient->myXmlreader->myCategoryList->getCategoryList());
}

/**
  *This function prcesses UI updating after a new top10List has been received.
  *@todo Check where limitNr is taken, fixed or user input, see on_comboBoxTopCategory_currentIndexChanged.
  */
void CarMainWindow::showTop10()
{
    int limitNr = 5;
    setListViewTopList(recentCategory, limitNr);
}

/**
  *This function is used to set items to labelTopList. Top-tab view.
  *@param Category
  *@param Size, number of results.
  */
void CarMainWindow::setListViewTopList(QString category, int size)
{
    qDebug() << "_setListViewTopList";
    QString topList;
    topList.append(myHttpClient->myXmlreader->myCategoryList->getTopList(category, size));
    ui->labelTopList->setText(topList);
}

/**
  *This slot function is called when speed is achieved in measure dialog. Opens result dialog.
  */
void CarMainWindow::openResultView()
{

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
}

/**
  *This slot function is called when ever category combobox current index changed. Top-tab view.
  *@param QString category.
  *@todo Check where limitNr is taken, fixed or user input, see showTop10.
  */
void CarMainWindow::on_comboBoxTopCategory_currentIndexChanged(QString category)
{
    qDebug() << "_on_comboBoxTopCategory_currentIndexChanged: " << category;
    recentCategory = category;      //for showTop10()
    int limitNr = 5;
    QString limit = QString::number(limitNr);
    myHttpClient->requestTopList(category, limit);
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
    if ( gpsSpeed > 1.0 )
    {
        timeFromGps += 0.1;
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
    ui->pushButtonSendResult->setEnabled(false);
    ui->pushButtonShowResultDialog->setEnabled(false);
    ui->labelMeasureTabResult->hide();
    ui->labelMeasureTabTime->setText("");
    ui->labelMeasureTabSpeed->setText("");
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
    this->accelerometerTimer->stop();
    this->timer->stop();
    this->time = 0;
    this->speed = 0;
    ui->tabWidget->setCurrentWidget(this->ui->StartTab);
    //this->close();

    //GPS
    gpsSpeed = 0.0;
    timeFromGps = 0.0;
}

/**
  *This slot function is called when pushButtonSendResult is clicked.
  *@todo Use real category value.
  */
void CarMainWindow::on_pushButtonSendResult_clicked()
{
    //Pick up relevant category name and pass it to the server
    myHttpClient->sendResultXml(catList.at(choiceInt));
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
       this->setWindowTitle("Speed Freak - " + newUserName);
    }
    else
    {
        ui->setUserPushButton->setText( "Set User");
        this->setWindowTitle("Speed Freak");
    }
}

void CarMainWindow::regUserToServer()
{
    myHttpClient->requestRegistration();
}


void CarMainWindow::on_drawRoutePushButton_clicked()
{
    QString routeFile = QString("route.txt");
    if (myRoute->readRouteFromFile( routeFile) == true)
    {
        myRoute->show();
    }
}

/**
  * Opens result dialog when show result button is clicked.
  * Sends measures as parameter to the resultdialogs saveMeasuresToArray-function.
  */
void CarMainWindow::on_pushButtonShowResultDialog_clicked()
{
    result->saveMeasuresToArray(measures);
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
    //firstAcceleration = 0;
    //horsepower = null;
    isNewRun = true;
    //lastScreenUpdateInSeconds = 0;
    previousTime = 0;
    reverseAccelerationFlag = false;
    stopWatch.start();
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
    switch (counterForSaveResults)
    {
    case 0:
        measures->setTime10kmh(totalTime);
        break;

    case 1:
        measures->setTime20kmh(totalTime);
        break;

    case 2:
        measures->setTime30kmh(totalTime);
        break;

    case 3:
        measures->setTime40kmh(totalTime);
        break;

    case 4:
        measures->setTime50kmh(totalTime);
        break;

    case 5:
        measures->setTime60kmh(totalTime);
        break;

    case 6:
        measures->setTime70kmh(totalTime);
        break;

    case 7:
        measures->setTime80kmh(totalTime);
        break;

    case 8:
        measures->setTime90kmh(totalTime);
        break;

    case 9:
        measures->setTime100kmh(totalTime);
        break;

    default:
        break;
    }
    counterForSaveResults++;

    if (choiceInt == 0 && measures->getTime40kmh() != 0)
    {
        setTimeAxisGapAndShowResult(measures->getTime40kmh());
        this->timer->stop();
        this->accelerometerTimer->stop();
        this->time = 0;
        this->speed = 0;
        counterForSaveResults = 0;
    }
    else if (choiceInt == 1 && measures->getTime100kmh() != 0)
    {
        setTimeAxisGapAndShowResult(measures->getTime100kmh());
        this->timer->stop();
        this->accelerometerTimer->stop();
        this->time = 0;
        this->speed = 0;
        counterForSaveResults = 0;
    }
    else if (choiceInt == 2 && measures->getTime10kmh() != 0)
    {
        setTimeAxisGapAndShowResult(measures->getTime10kmh());
        this->timer->stop();
        this->accelerometerTimer->stop();
        this->time = 0;
        this->speed = 0;
        counterForSaveResults = 0;
    }
    else if (choiceInt != 1 && choiceInt != 0 && measures->getTime80kmh() != 0)
    {
        setTimeAxisGapAndShowResult(measures->getTime80kmh());
        this->timer->stop();
        this->accelerometerTimer->stop();
        this->time = 0;
        this->speed = 0;
        counterForSaveResults = 0;
    }
    else
    {
        qDebug() << "something wrong in handleCheckPoint()";
    }
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

    //  keep the following line as close to the SetKinematicsProperties method as possible
    currentTime = stopWatch.elapsed();

    //accelerometer->smoothData(x, y, z);

    // Apply calibration
    x -= accelerometer->getCalibrationX();
    y -= accelerometer->getCalibrationY();
    z -= accelerometer->getCalibrationZ();

    QString str = QString("acc x: " + QString::number(x) + "\n" +
                          "acc y: " + QString::number(y) + "\n" +
                          "acc z: " + QString::number(z) + "\n");

    currentAcceleration = z;//sqrt(x*x + y*y + z*z);
    changeInAcceleration = currentAcceleration;

    if (((fabs(changeInAcceleration) <= accelerationStartThreshold)
                && !vehicleStartedMoving))
    {
        return;
    }
    else if(!vehicleStartedMoving)
    {
        vehicleStartedMoving = true;
        stopWatch.start();
        previousTime = 0;
        currentTime = 0;
    }

    calculate->calculateParameters(changeInAcceleration, (currentTime - previousTime)/1000);
    previousTime = currentTime;

    s.sprintf("%.2f", changeInAcceleration);
    currentAccelerationString = s;

    speed = 0.0;
    speed = calculate->getCurrentSpeed();
    speed = speed*3.6;//((speed*1000)/kSecondsInHour);
    s.sprintf("%.1f", speed);
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
  *This slot function is called when GPS on checkbox state changed. Route-tab view.
  *@param int GPSState
  */
void CarMainWindow::on_gpsOnCheckBox_stateChanged(int GPSState)
{
    //Stop polling GPS. Route-tab view.
    if (GPSState == 0)
    {
        ui->labelRouteTabGPSStatus->setText("GPS status: GPS off");
        location->stopPollingGPS();
        gpsUpdateTime = 0;
        gpsTimer->stop();
    }
    //Start polling GPS. Route-tab view.
    else
    {
        ui->labelRouteTabGPSStatus->setText("GPS status: GPS on");
        location->startPollingGPS();
    }
}

/**
  *This slot function is called when GPS status changed. Route- and measure-tab view.
  */
void CarMainWindow::gpsStatus()
{
    //IF GPS checkbox is ON
    if (ui->gpsOnCheckBox->isChecked())
    {
        //If GPS find 4 satellite.
        if (location->getSatellitesInUse() >= 4)
        {
            //Set gps status. Route-tab view.
            ui->labelRouteTabGPSStatus->setText("GPS ready");

            //Set time. Route-tab view.
            gpsTime->setTime_t(location->getTime());
            QString gpsDateNow = gpsTime->toString("dd.MM.yyyy hh:mm:ss");
            ui->labelRouteTabGPSTime->setText("GPS time: " + gpsDateNow);

            //Set latitude & longitude. Route-tab view.
            ui->labelRouteTabLatitude->setText("Latitude: " + QString::number(location->getLatitude()));
            ui->labelRouteTabLongitude->setText("Longitude: " + QString::number(location->getLongitude()));

            //Set rec status. Route-tab view.
            if (ui->startRecPushButton->text() == "Stop recording")
            {
                ui->labelRouteTabRecStatus->setText("Recorded " + QString::number(gpsData->roundCounter) + " point");
            }

            //Get speed. Route- and Measure-tab view.
            gpsSpeed = location->getSpeed();

            //Set speed. Route-tab view.
            ui->labelRouteTabSpeed->setText("Speed:" + QString::number(gpsSpeed) + "km/h +/-" + QString::number(location->getEps()) + "km/h");

            //Measure-tab view.
            if (gpsSpeed < 40.0)
            {              
                ui->labelMeasureTabSpeed->setText(QString::number(gpsSpeed)); //Set speed. //Measure-tab view.
                ui->labelMeasureTabTime->setText(QString::number(timeFromGps)); //Set time. //Measure-tab view.
            }
            //Measure-tab view.
            else
            {
                timer->stop(); //Measure timer
                ui->labelMeasureTabResult->setText(QString::number(timeFromGps));
                ui->labelMeasureTabResult->show();
                ui->pushButtonShowResultDialog->setEnabled(true);
                ui->pushButtonShowResultDialog->setEnabled(true);
            }
        }

        //If GPS find less than 4 satellite.
        else
        {
            ui->labelRouteTabGPSStatus->setText("GPS status: Waiting for GPS");
            gpsTimer->stop();
        }

        gpsUpdateTime = 0;
        gpsTimer->start(10);
    }
}

/**
  *This slot function is called when gps timer timeout(10ms).
  */
void CarMainWindow::gpsTimerTimeout()
{
    int time1000ms;
    time1000ms += 10;

    //IF time is 1 second
    if (time1000ms == 1000)
    {
        //Calculate acceleration 1/s
        gpsSpeedPrevious = gpsSpeedNow; //Previous speed
        gpsSpeedNow = (location->getSpeed())/3.6; //Speed now (m/s)
        gpsAcceleration = (gpsSpeedNow - gpsSpeedPrevious)/1; //Calculate acceleration: speed now - previous speed / 1s.
        //Set acceleration. Route-tab view.
        ui->labelRouteTabAcceleration->setText("Acceleration: " + QString::number( gpsAcceleration ) + " m/s2");
    }

    gpsUpdateTime++;
    //Set GPS update time. Route-tab view.
    ui->labelRouteTabGPSUpdateTime->setText("GPS update time: " + QString::number(gpsUpdateTime) + " ms");
}

/**
  *This slot function is called when start rec push button clicked. Route-tab view.
  */
void CarMainWindow::on_startRecPushButton_clicked()
{
    //Start route recording.
    if (ui->startRecPushButton->text() == "Start recording")
    {
        ui->startRecPushButton->setText("Stop recording");
        ui->labelRouteTabRecStatus->setText("Recording started");
        gpsData->startRouteRecording(ui->labelRouteTabGPSTime->text());
    }

    //Stop route recording.
    else if (ui->startRecPushButton->text() == "Stop recording")
    {
        ui->startRecPushButton->setText("Start recording");
        ui->labelRouteTabRecStatus->setText("Recording stopped");
        gpsData->stopRouteRecording(ui->labelRouteTabGPSTime->text());
    }
}

/**
  *Sets time axis right way in result dialog and shows target speed result.
  *@param double pTime is the target speed result time which is shown to the user.
  */
void CarMainWindow::setTimeAxisGapAndShowResult(double pTime)
{
    ui->pushButtonShowResultDialog->setEnabled(true);
    ui->pushButtonSendResult->setEnabled(true);
    QString timeInteger;
    timeInteger.setNum(pTime);
    ui->labelMeasureTabResult->show();
    ui->labelMeasureTabResult->setText(timeInteger);

    if (floor(pTime) <= 5)
    {
        result->setDiagramGapHorizontal(80);
    }

    else if (floor(pTime) <= 10)
    {
        result->setDiagramGapHorizontal(40);
    }

    else
    {
        result->setDiagramGapHorizontal(20);
    }
}

void CarMainWindow::on_calibrateButton_clicked()
{
    ui->autoStartButton->setEnabled(true);
    ui->manualStartButton->setEnabled(true);

    this->accelerometer->calibrate();
}
