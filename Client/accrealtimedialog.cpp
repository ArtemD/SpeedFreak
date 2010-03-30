#include "accrealtimedialog.h"
#include "ui_accrealtimedialog.h"
#include <math.h>

AccRealTimeDialog::AccRealTimeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccRealTimeDialog)
{
    ui->setupUi(this);

    accelerometer = new Accelerometer();
    movingAverageZ = new MovingAverage(10);
    calculate = new Calculate();
    accelerationStartThreshold = 0.1;

    accelerometerTimer = new QTimer(this);
    connect(accelerometerTimer, SIGNAL(timeout()), this, SLOT(readAccelerometerData()));
    isNewRun = true;
    updateScreenCounter = 0;
    resetAccelerometerMeasurements();

    //Load image
    QPixmap pixMap("back.png",0,Qt::AutoColor);
    ui->pictureLabel->setPixmap(pixMap);
}

AccRealTimeDialog::~AccRealTimeDialog()
{
    delete ui;
    delete accelerometer;
    delete accelerometerTimer;
    delete calculate;
    delete movingAverageZ;
}

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
  *This function is called to read (and process) data from the accelerometer
  */
void AccRealTimeDialog::readAccelerometerData()
{
    QString s;
    double changeInAcceleration = 0;
    qreal x, y, z;

    accelerometer->getAcceleration(x, y, z);

    //  keep the following line as close to the SetKinematicsProperties method as possible
    currentTime = elapsedTime.elapsed();

    //accelerometer->smoothData(x, y, z);

    //Calculate average
    movingAverageZ->Enqueue(z);
    z = movingAverageZ->Average();

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
    if( speed > stopMeasureSpeed )
    {
        this->accelerometerTimer->stop();
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
void AccRealTimeDialog::Calibrate()
{
    accelerometer->calibrate();
}

void AccRealTimeDialog::on_buttonAbort_clicked()
{
    accelerometerTimer->stop();
    resetAccelerometerMeasurements();
    this->close();
}
void AccRealTimeDialog::startAccelerationMeasure()
{
    accelerometerTimer->start(40);
}
void AccRealTimeDialog::SetStopMeasureSpeed(double speed)
{
    stopMeasureSpeed = speed;
}
