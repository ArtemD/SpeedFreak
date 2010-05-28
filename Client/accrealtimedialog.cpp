/*
 * Acceleration info in real time dialog
 *
 * @author      Jukka Kurttila <jukka.kurttila@fudeco.com>
 * @author      Toni Jussila 	<toni.jussila@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "accrealtimedialog.h"
#include "ui_accrealtimedialog.h"
#include <math.h>

/**
  * Default constructor for AccRealTimeDialog class.
  *
  */
AccRealTimeDialog::AccRealTimeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccRealTimeDialog)
{
    ui->setupUi(this);

    accelerometer = new Accelerometer();
    movingAverageZ = new MovingAverage(10);
    movingAverageY = new MovingAverage(10);
    calculate = new Calculate();
    accelerationStartThreshold = 0.1;

    accelerometerTimer = new QTimer(this);
    connect(accelerometerTimer, SIGNAL(timeout()), this, SLOT(readAccelerometerData()));
    isNewRun = true;
    updateScreenCounter = 0;
    resetAccelerometerMeasurements();

    resultDialog = NULL;
}

/**
  * Default destructor for AccRealTimeDialog class.
  * Deletes all dynamic objects and sets them to NULL.
  */
AccRealTimeDialog::~AccRealTimeDialog()
{
    delete ui;
    delete accelerometer;
    delete accelerometerTimer;
    delete calculate;
    delete movingAverageZ;
    delete movingAverageY;
    if(resultDialog)
        delete resultDialog;
}

/**
  *
  */
void AccRealTimeDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/**
  * This function is called to read (and process) data from the accelerometer
  */
void AccRealTimeDialog::readAccelerometerData()
{
    QString s;
    double changeInAcceleration = 0;
    qreal x, y, z;

    accelerometer->getAcceleration(x, y, z);

    // keep the following line as close to the SetKinematicsProperties method as possible
    currentTime = elapsedTime.elapsed();

    // Calculate average for Z
    movingAverageZ->Enqueue(z);
    z = movingAverageZ->Average();
    // Calculate average for Y
    movingAverageY->Enqueue(y);
    y = movingAverageY->Average();

    // Apply calibration
    x -= accelerometer->getCalibrationX();
    y -= accelerometer->getCalibrationY();
    z -= accelerometer->getCalibrationZ();

    qreal calY = accelerometer->getCalibrationY();
    qreal calZ = accelerometer->getCalibrationZ();

    if(calY < 0)
        calY = -calY;
    if(calZ < 0)
        calZ = -calZ;

    // Take acceleration from more affecting axel
    if(calZ < calY)
    {
        z = z*(1+calZ/2);
        currentAcceleration = z;
    }
    else
    {
        y = y*(1+calY/2);
        currentAcceleration = -y;
    }

    //screen up: y = 0, z = -1
    //screen front: y = -1, z = 0

    //QString str = QString("acc x: " + QString::number(x) + "\n" +
    //                      "acc y: " + QString::number(y) + "\n" +
    //                      "acc z: " + QString::number(z) + "\n");

    //currentAcceleration = z;//sqrt(x*x + y*y + z*z);
    //qDebug("y: %f, calibZ: %f, calibY: %f\n",y,accelerometer->getCalibrationZ(),accelerometer->getCalibrationY());
    changeInAcceleration = currentAcceleration;

    if (((fabs(changeInAcceleration) <= accelerationStartThreshold)
                && !vehicleStartedMoving))
    {
        return;
    }
    else if(!vehicleStartedMoving)
    {
        vehicleStartedMoving = true;
        elapsedTime.start();
        previousTime = 0;
        currentTime = 0;
    }

    calculate->calculateParameters(changeInAcceleration, (currentTime - previousTime)/1000);
    previousTime = currentTime;

    //s.sprintf("%.2f", changeInAcceleration);
    //currentAccelerationString = s;

    speed = 0;
    speed = calculate->getCurrentSpeed();
    //Convert to km/h
    speed = speed*3.6;
    s.sprintf("%.1f", speed);
    currentSpeed = s;

    //s.sprintf("%.2f", calculate->getDistanceTraveled());
    //distanceTraveled = s;

    // TODO
    //distanceTraveled;
    //horsepower;

    time = calculate->getTotalTime();

    s.sprintf("%.2f", time);
    totalTime = s;

    //str.append("ca: " + currentAccelerationString + " G\n" );
    //str.append("cspeed: " + currentSpeed + " km/h \n" );
    //str.append("dist: " + distanceTraveled + " m \n" );
    //str.append("time: " + totalTime + " s \n" );

    if( updateScreenCounter == 5 )
    {
        ui->realSpeedLabel->setText( currentSpeed );
        ui->timeLabel->setText( totalTime );
        updateScreenCounter = 0;
    }
    updateScreenCounter++;

    //Open result dialog if target speed reached
    if( (stopMeasureSpeed > 0) && (speed > stopMeasureSpeed) )
    {
        this->accelerometerTimer->stop();
        if(!resultDialog)
        {
            resultDialog = new ResultDialog(this);
            connect(resultDialog, SIGNAL(rejected()), this, SLOT(killResultDialog()));
            connect(resultDialog, SIGNAL(sendresult(double)), this, SLOT(sendResult(double)));
        }
        if(resultDialog)
        {
            resultDialog->setEnd(stopMeasureSpeed);
            //Put all times from all speeds
            QMap<int,double> tempMap = calculate->getValuesMap();

            for( int i = 1 ; i <= tempMap.count() ; i++ )
            {
                resultDialog->setValue(i*10,tempMap[i*10]);
            }
            calculate->reset();
            resultDialog->show();
            this->hide();
        }
    }
}

/**
  * Resets Accelerometer measurement variables
  */
void AccRealTimeDialog::resetAccelerometerMeasurements()
{
    speed = 0;
    currentAcceleration = 0;
    currentSpeed = "";
    currentTime = 0;
    isNewRun = true;
    previousTime = 0;
    elapsedTime.start();
    totalTime = "";
    calculate->reset();
    vehicleStartedMoving = false;
    stopMeasureSpeed = 0;
}

/**
  *
  */
void AccRealTimeDialog::Calibrate()
{
    accelerometer->calibrate();
}

/**
  * This slot function called when ever abort button clicked.
  */
void AccRealTimeDialog::on_buttonAbort_clicked()
{
    accelerometerTimer->stop();
    resetAccelerometerMeasurements();
    this->close();
}

/**
  *
  */
void AccRealTimeDialog::startAccelerationMeasure()
{
    double temp = stopMeasureSpeed;
    resetAccelerometerMeasurements();
    stopMeasureSpeed = temp;
    accelerometerTimer->start(40);
}

/**
  *
  * @param double speed
  */
void AccRealTimeDialog::SetStopMeasureSpeed(double speed)
{
    stopMeasureSpeed = speed;
}

/**
  *This slot function emit accelerationstart sendresult.
  *
  * @param double result
  */
void AccRealTimeDialog::sendResult(double result)
{
    emit sendresult(result);
}

/**
  *This slot function kills resultDialog.
  *
  **/
void AccRealTimeDialog::killResultDialog()
{
    if(resultDialog)
    {
        delete resultDialog;
        resultDialog = NULL;
    }
}
