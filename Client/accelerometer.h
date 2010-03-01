#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <QObject>
#include <QTime>
#include <QTimer>

class Accelerometer : public QObject
{
    Q_OBJECT
public:
    Accelerometer();
    ~Accelerometer();

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

    qreal getintervalTime();

private slots:
    void processData();
    void smoothData(qreal x, qreal y, qreal z);

private:
    qreal accelerationX, accelerationY, accelerationZ;
    qreal trueAccelerationX,trueAccelerationY,trueAccelerationZ;
    qreal previousAccelerationX,previousAccelerationY,previousAccelerationZ;
    qreal previousSpeed, currentSpeed;
    qreal currentAcceleration, previousAcceleration, totalAcceleration;
    QTime now;
    QTimer *timer;
    double intervalTime;
    double totalTime;
    double distanceTraveled,lastDistanceTraveled,averageSpeed;
    double sampleRate;
};

#endif // ACCELEROMETER_H
