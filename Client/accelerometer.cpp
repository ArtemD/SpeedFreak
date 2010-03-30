/*
 * Accelerometer class to access the device accelerometer
 *
 * @author      Rikhard Kuutti <rikhard.kuutti@fudeco.com>
 * @author      Kai Rasilainen <kai.rasilainen@fudeco.com>
 * @author      Jukka Kurttila <jukka.kurttila@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "accelerometer.h"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusPendingReply>

#define kFilteringFactor 0.2
#define kIterations      1024

/**
 * Default constructor for Accelerometer class
 *
 */
Accelerometer::Accelerometer()
{
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
 * Init class members
 *
 */
void Accelerometer::initValues()
{
    previousAccelerationX = 0;
    previousAccelerationY = 0;
    previousAccelerationZ = 0;
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

    calibrateDialog = new CalibrateDialog();
    calibrateDialog->show();
    calibrateDialog->resetProgressValue();

    do {
        calibrateDialog->setProgressValue(iteration);

        getAcceleration(sampleX, sampleY, sampleZ);

        calibrationX += sampleX; // Accumulate Samples
        calibrationY += sampleY; // for all axes.
        calibrationZ += sampleZ;

        iteration++;

    } while(iteration != kIterations);        // kIterations times

    calibrationX = calibrationX/kIterations;  // division by kIterations
    calibrationY = calibrationY/kIterations;
    calibrationZ = calibrationZ/kIterations;

    calibrateDialog->hide();
}

/**
 * Smooths Accelerometer data by applying a low pass filter to data
 *
 * @param x accelerometer's x-axis input
 * @param y accelerometer's y-axis input
 * @param z accelerometer's z-axis input
 */
void Accelerometer::smoothData(qreal &x, qreal &y, qreal &z)
{
    x = (previousAccelerationX * (1 - kFilteringFactor)) + (x * kFilteringFactor);
    y = (previousAccelerationY * (1 - kFilteringFactor)) + (y * kFilteringFactor);
    z = (previousAccelerationZ * (1 - kFilteringFactor)) + (z * kFilteringFactor);

    previousAccelerationX = x;
    previousAccelerationY = y;
    previousAccelerationZ = z;
}

/**
 * Gets the raw acceleration data from accelerometer
 *
 * @param x accelerometer's x-axis input
 * @param y accelerometer's y-axis input
 * @param z accelerometer's z-axis input
 */
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
 * Get the x calibration component
 *
 * @return calibrationX x calibration component
 */
qreal Accelerometer::getCalibrationX()
{
    return calibrationX;
}

/**
 * Get the y calibration component
 *
 * @return calibrationY y calibration component
 */
qreal Accelerometer::getCalibrationY()
{
    return calibrationY;
}

/**
 * Get the z calibration component
 *
 * @return calibrationZ z calibration component
 */
qreal Accelerometer::getCalibrationZ()
{
    return calibrationZ;
}
