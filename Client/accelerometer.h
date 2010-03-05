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

    int getCalibrationX();
    int getCalibrationY();
    int getCalibrationZ();

    qreal getIntervalTime();
    qreal getTotalTime();

private slots:
    void processData();
    void smoothData(qreal x, qreal y, qreal z);

private:
    Calculate *calculate;

    qreal accelerationX, accelerationY, accelerationZ;
    qreal trueAccelerationX,trueAccelerationY,trueAccelerationZ;
    qreal previousAccelerationX,previousAccelerationY,previousAccelerationZ;
    qreal previousSpeed, currentSpeed;
    qreal currentAcceleration, previousAcceleration, totalAcceleration;

    int calibrationX, calibrationY, calibrationZ;

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

