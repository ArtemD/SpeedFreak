/*
 * Accelerometer class to access the device accelerometer
 *
 * @author      Rikhard Kuutti <rikhard.kuutti@fudeco.com>
 * @author      Kai Rasilainen 
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <QObject>
#include <QTime>
#include <QTimer>
#include <QFile>

#include "calculate.h"

class Accelerometer : public QObject
{
    Q_OBJECT
public:
    Accelerometer();
    Accelerometer(int p_SampleRate);
    ~Accelerometer();

    void getAcceleration(qreal &x, qreal &y, qreal &z);
    void smoothData(qreal &x, qreal &y, qreal &z);
    void calibrate();

    void start();
    void stop();

    void initValues();

    void setSampleRate(int pSampleRate);
    int getSampleRate();

    qreal getTrueAccelerationX();
    qreal getTrueAccelerationY();
    qreal getTrueAccelerationZ();

    qreal getPreviousSpeed();
    qreal getCurrentSpeed();

    qreal getDistanceTraveled();
    qreal getLastDistanceTraveled();
    qreal getAverageSpeed();

    qreal getCurrentAcceleration();
    qreal getTotalAcceleration();
    qreal getPreviousTotalAcceleration();

    qreal getCalibrationX();
    qreal getCalibrationY();
    qreal getCalibrationZ();

    qreal getIntervalTime();
    qreal getTotalTime();

    Calculate *calculate;

private slots:
    //void processData();


private:
    qreal accelerationX, accelerationY, accelerationZ;
    qreal trueAccelerationX,trueAccelerationY,trueAccelerationZ;
    qreal previousAccelerationX,previousAccelerationY,previousAccelerationZ;
    qreal previousSpeed, currentSpeed;
    qreal currentAcceleration, previousAcceleration, totalAcceleration;
    qreal calibrationX, calibrationY, calibrationZ;

    QTime now;
    QTimer *timer;

    double intervalTime;
    double totalTime;
    double distanceTraveled;
    double lastDistanceTraveled;
    double averageSpeed;
    double sampleRate;

    bool firstRun;

};

#endif // ACCELEROMETER_H

