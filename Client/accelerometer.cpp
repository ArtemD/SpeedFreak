#include "accelerometer.h"
#include "math.h"

#include <QFile>
#include <QString>
#include <QRegExp>
#include <QTimer>

#define kFilteringFactor    0.1
#define kGravity            9.81
#define kFileName           "/sys/class/i2c-adapter/i2c-3/3-001d/coord"

static int sampleIndex=0;

/**
 * Default constructor for Accelerometer class
 *
 */
Accelerometer::Accelerometer()
{
    calculate = new Calculate();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(processData()));
    sampleRate = 40;
    initValues();
}

/**
 * Constructor for Accelerometer class that takes accelerometer sample rate as parameter
 *
 * @param p_SampleRate the desired sample rate of accelerometer in milliseconds
 */
Accelerometer::Accelerometer(int p_SampleRate)
{
    calculate = new Calculate();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(processData()));
    sampleRate = p_SampleRate;
    initValues();
}

/**
 * Default destructor for Accelerometer class
 *
 */
Accelerometer::~Accelerometer()
{
}

/**
 * Start measuring
 *
 */
void Accelerometer::start()
{
    initValues();
    calibrate();
    timer->start(sampleRate);
    now.restart();
}

/**
 * Init class members
 *
 */
void Accelerometer::initValues()
{
    calculate->reset();
    accelerationX = 0;
    accelerationY = 0;
    accelerationZ = 0;
    trueAccelerationX = 0;
    trueAccelerationY = 0;
    trueAccelerationZ = 0;
    previousAccelerationX = 0;
    previousAccelerationY = 0;
    previousAccelerationZ = 0;
    previousSpeed = 0;
    currentSpeed = 0;
    currentAcceleration = 0;
    previousAcceleration = 0;
    totalAcceleration = 0;
    intervalTime = 0;
    totalTime = 0;
    distanceTraveled = 0;
    lastDistanceTraveled = 0;
    averageSpeed = 0;
    sampleRate = 0;
    firstRun = true;
    calibrationX = 0;
    calibrationY = 0;
    calibrationZ = 0;
}

/**
  * Calibrate. Purpose of this function is to calibrate
  * accelerometer when stationary.
  *
  */
void Accelerometer::calibrate(void)
{
    unsigned int iteration = 0;

    do {
        // Opening the file must be done inside the loop
        // or else the values obtained from file.readLine();
        // will be empty for all but the first iteration
        QFile file(kFileName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return;
        }

        QByteArray line;
        QRegExp rx("([0-9-]+) ([0-9-]+) ([0-9-]+)");

        // Read data, parse with regular expressions and process it
        line = file.readLine();
        rx.indexIn(line);

        int sampleX = rx.cap(1).toInt();
        int sampleY = rx.cap(2).toInt();
        int sampleZ = rx.cap(3).toInt();

        calibrationX = calibrationX + sampleX; // Accumulate Samples
        calibrationY = calibrationY + sampleY; // for all axes.
        calibrationZ = calibrationZ + sampleZ;

        iteration++;

        file.close();
    } while(iteration != 1024);       // 1024 times

    calibrationX = calibrationX>>10;  // division by 1024
    calibrationY = calibrationY>>10;
    calibrationZ = calibrationZ>>10;
}

/**
 * Stop measuring
 *
 */
void Accelerometer::stop()
{
    timer->stop();
}

/**
 * Set the sample rate of accelerometer
 *
 * @param pSampleRate desired sample rate
 */
void Accelerometer::setSampleRate(int pSampleRate)
{
    sampleRate = pSampleRate;
}

/**
 * Get the sample rate of accelerometer
 *
 * @return sampleRate the sample rate of the accelerometer in milliseconds
 */
int Accelerometer::getSampleRate()
{
    return sampleRate;
}

qreal Accelerometer::getCurrentAcceleration()
{
    return currentAcceleration;
}

qreal Accelerometer::getPreviousTotalAcceleration()
{
    return previousAcceleration;
}

qreal Accelerometer::getTotalAcceleration()
{
    return totalAcceleration;
}

qreal Accelerometer::getDistanceTraveled()
{
    return distanceTraveled;
}

qreal Accelerometer::getLastDistanceTraveled()
{
    return lastDistanceTraveled;
}

qreal Accelerometer::getAverageSpeed()
{
    return averageSpeed;
}

qreal Accelerometer::getTrueAccelerationX()
{
    return trueAccelerationX;
}

qreal Accelerometer::getTrueAccelerationY()
{
    return trueAccelerationY;
}

qreal Accelerometer::getTrueAccelerationZ()
{
    return trueAccelerationZ;
}

qreal Accelerometer::getPreviousSpeed()
{
    return previousSpeed;
}

qreal Accelerometer::getCurrentSpeed()
{
    return currentSpeed;
}

qreal Accelerometer::getIntervalTime()
{
    return intervalTime;
}

qreal Accelerometer::getTotalTime()
{
    return totalTime;
}

int Accelerometer::getCalibrationX()
{
    return calibrationX;
}

int Accelerometer::getCalibrationY()
{
    return calibrationY;
}

int Accelerometer::getCalibrationZ()
{
    return calibrationZ;
}

/**
 * Processes Accelerometer data
 *
 * Opens the accelerometer value file for reading and reads and parses accelerometer values.
 * Forwards data to Calculate class for processing
 *
 */
void Accelerometer::processData()
{
    QFile file(kFileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    // Read data, parse with regular expressions and process it
    QByteArray line = file.readLine();
    QRegExp rx("([0-9-]+) ([0-9-]+) ([0-9-]+)");
    rx.indexIn(line);

    smoothData(rx.cap(1).toInt(), rx.cap(2).toInt(), rx.cap(3).toInt());

    // Apply calibration
    accelerationX = accelerationX - calibrationX;
    accelerationX = accelerationY - calibrationY;
    accelerationX = accelerationZ - calibrationZ;

    // If the function is run the first time, make sure that there
    // are no differences with previous and current acceleration
    if (firstRun) {
        previousAccelerationX = accelerationX;
        previousAccelerationY = accelerationY;
        previousAccelerationZ = accelerationZ;
        firstRun = false;
    }

    // Discrimination window for acceleration values
    /*if ( fabs(accelerationX) < 20 ) { accelerationX = 0; }
      if ( fabs(accelerationY) < 20 ) { accelerationY = 0; }
      if ( fabs(accelerationZ) < 20 ) { accelerationZ = 0; }*/

    // Calculate the current acceleration for each axis
    trueAccelerationX = (accelerationX - previousAccelerationX) /*/ 1000 * kGravity*/;
    trueAccelerationY = (accelerationY - previousAccelerationY) /*/ 1000 * kGravity*/;
    trueAccelerationZ = (accelerationZ - previousAccelerationZ) /*/ 1000 * kGravity*/;

    // Discrimination window for acceleration values
    if ( fabs(trueAccelerationX) < 20 ) { trueAccelerationX = 0; }
    if ( fabs(trueAccelerationY) < 20 ) { trueAccelerationY = 0; }
    if ( fabs(trueAccelerationZ) < 20 ) { trueAccelerationZ = 0; }

    previousAccelerationX = accelerationX;
    previousAccelerationY = accelerationY;
    previousAccelerationZ = accelerationZ;

    currentAcceleration = sqrt(trueAccelerationX * trueAccelerationX +
                               trueAccelerationY * trueAccelerationY +
                               trueAccelerationZ * trueAccelerationZ );

    // Discrimination window for currentAcceleration
    if ( fabs(currentAcceleration) < 20 ) { currentAcceleration = 0; }

    // Measure time interval
    intervalTime = now.restart();
    intervalTime = intervalTime/1000; // millisecs to secs
    totalTime = totalTime + intervalTime;

    // Using calculate class to calculate velocity and distance etc.
    calculate->calculateParameters(currentAcceleration,intervalTime );

    currentSpeed = calculate->getCurrentSpeed();
    distanceTraveled = calculate->getDistanceTraveled();

    file.close();
}

/**
 * Smooths Accelerometer data
 *
 * @param x accelerometer's x-axis input
 * @param y accelerometer's y-axis input
 * @param z accelerometer's z-axis input
 */
void Accelerometer::smoothData(qreal x, qreal y, qreal z)
{
    accelerationX = x;
    accelerationY = y;
    accelerationZ = z;
    if (sampleIndex > 0)
    {
        accelerationX = previousAccelerationX + (accelerationX-previousAccelerationX) * kFilteringFactor;
        accelerationY = previousAccelerationY + (accelerationY-previousAccelerationY) * kFilteringFactor;
        accelerationZ = previousAccelerationZ + (accelerationZ-previousAccelerationZ) * kFilteringFactor;
    }
    sampleIndex++;
}

