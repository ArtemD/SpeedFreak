/*
 * Accelerometer class to access the device accelerometer
 *
 * @author      Rikhard Kuutti <rikhard.kuutti@fudeco.com>
 * @author      Kai Rasilainen 
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "accelerometer.h"

#include "math.h"

#include <QFile>
#include <QString>
#include <QRegExp>
#include <QTimer>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusPendingReply>

#define kFilteringFactor    0.2

static int sampleIndex = 0;

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
    //calibrate();
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
    qreal sampleX, sampleY, sampleZ;

    do {

        getAcceleration(sampleX, sampleY, sampleZ);

        calibrationX += sampleX; // Accumulate Samples
        calibrationY += sampleY; // for all axes.
        calibrationZ += sampleZ;

        iteration++;

    } while(iteration != 1024);        // 1024 times

    calibrationX = calibrationX/1024;  // division by 1024
    calibrationY = calibrationY/1024;
    calibrationZ = calibrationZ/1024;

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
 * Processes Accelerometer data
 *
 * Opens the accelerometer value file for reading and reads and parses accelerometer values.
 * Forwards data to Calculate class for processing
 *
 */
/*
void Accelerometer::processData()
{
    getAcceleration(accelerationX, accelerationY, accelerationZ);
    //smoothData(accelerationX, accelerationY, accelerationZ);

    // Apply calibration
    accelerationX = accelerationX - calibrationX;
    accelerationY = accelerationY - calibrationY;
    accelerationZ = accelerationZ - calibrationZ;

    // If the function is run the first time, make sure that there
    // are no differences with previous and current acceleration
    if (firstRun) {
        previousAccelerationX = accelerationX;
        previousAccelerationY = accelerationY;
        previousAccelerationZ = accelerationZ;
        firstRun = false;
    }

    // Calculate the current acceleration for each axis
    trueAccelerationX = (accelerationX - previousAccelerationX);
    trueAccelerationY = (accelerationY - previousAccelerationY);
    trueAccelerationZ = (accelerationZ - previousAccelerationZ);

    previousAccelerationX = accelerationX;
    previousAccelerationY = accelerationY;
    previousAccelerationZ = accelerationZ;

    currentAcceleration = sqrt((trueAccelerationX * trueAccelerationX) +
                               (trueAccelerationY * trueAccelerationY) +
                               (trueAccelerationZ * trueAccelerationZ));

    // Discrimination window for currentAcceleration
    if ( fabs(currentAcceleration) < 0.10 ) { currentAcceleration = 0; }

    // Measure time interval
    intervalTime = now.restart();
    intervalTime = intervalTime/1000; // millisecs to secs
    totalTime = totalTime + intervalTime;

    // Using calculate class to calculate velocity and distance etc.
    calculate->calculateParameters(currentAcceleration,intervalTime );

    currentSpeed = calculate->getCurrentSpeed();
    distanceTraveled = calculate->getDistanceTraveled();
}
*/
/**
 * Smooths Accelerometer data
 *
 * @param x accelerometer's x-axis input
 * @param y accelerometer's y-axis input
 * @param z accelerometer's z-axis input
 */
void Accelerometer::smoothData(qreal &x, qreal &y, qreal &z)
{
    accelerationX = x;
    accelerationY = y;
    accelerationZ = z;

    if (sampleIndex > 0)
    {
        accelerationX = ((previousAccelerationX) * (1-kFilteringFactor)) + (accelerationX * kFilteringFactor);
        accelerationY = ((previousAccelerationY) * (1-kFilteringFactor)) + (accelerationY * kFilteringFactor);
        accelerationZ = ((previousAccelerationZ) * (1-kFilteringFactor)) + (accelerationZ * kFilteringFactor);
    }
    sampleIndex++;
}

void Accelerometer::getAcceleration(qreal &x, qreal &y, qreal &z)
{
    QDBusConnection connection(QDBusConnection::systemBus());
    if (connection.isConnected()) {
        QDBusInterface interface("com.nokia.mce", "/com/nokia/icd", QString(), connection);
        QDBusPendingReply<QString, QString, QString, int, int, int> reply;
        reply = interface.asyncCall("get_device_orientation");
        reply.waitForFinished();
        x = static_cast<qreal>(reply.argumentAt<3>()) / 1000;
        y = static_cast<qreal>(reply.argumentAt<4>()) / 1000;
        z = static_cast<qreal>(reply.argumentAt<5>()) / 1000;
    }
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

qreal Accelerometer::getCalibrationX()
{
    return calibrationX;
}

qreal Accelerometer::getCalibrationY()
{
    return calibrationY;
}

qreal Accelerometer::getCalibrationZ()
{
    return calibrationZ;
}
