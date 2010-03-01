#include "accelerometer.h"
#include "math.h"

#include <QFile>
#include <QString>
#include <QRegExp>
#include <QTimer>

#define kFilteringFactor    0.1
#define kGravity            9.81

static int sampleIndex=0;

Accelerometer::Accelerometer()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(processData()));
    sampleRate = 100;
    timer->start(sampleRate);
    now.restart();

    initValues();
}

Accelerometer::~Accelerometer() {
}

void Accelerometer::start() {
    timer->start(sampleRate);
    now.restart();
}

void Accelerometer::initValues() {
    accelerationX=0;
    accelerationY=0;
    accelerationZ=0;
    trueAccelerationX=0;
    trueAccelerationY=0;
    trueAccelerationZ=0;
    previousAccelerationX=0;
    previousAccelerationY=0;
    previousAccelerationZ=0;
    previousSpeed=0;
    currentSpeed=0;
    currentAcceleration=0;
    previousAcceleration=0;
    totalAcceleration=0;
    intervalTime=0;
    totalTime=0;
    distanceTraveled=0;
    lastDistanceTraveled=0;
    averageSpeed=0;
    sampleRate=0;
}

void Accelerometer::stop() {
    timer->stop();
}

void Accelerometer::setSampleRate(int pSampleRate) {
    sampleRate = pSampleRate;
}

int Accelerometer::getSampleRate() {
    return sampleRate;
}

qreal Accelerometer::getCurrentAcceleration() {
    return currentAcceleration;
}

qreal Accelerometer::getPreviousTotalAcceleration() {
    return previousAcceleration;
}

qreal Accelerometer::getTotalAcceleration() {
    return totalAcceleration;
}

qreal Accelerometer::getDistanceTraveled() {
    return distanceTraveled;
}

qreal Accelerometer::getLastDistanceTraveled() {
    return lastDistanceTraveled;
}

qreal Accelerometer::getAverageSpeed() {
    return averageSpeed;
}

qreal Accelerometer::getTrueAccelerationX() {
    return trueAccelerationX;
}

qreal Accelerometer::getTrueAccelerationY() {
    return trueAccelerationY;
}

qreal Accelerometer::getTrueAccelerationZ() {
    return trueAccelerationZ;
}

qreal Accelerometer::getPreviousSpeed() {
    return previousSpeed;
}

qreal Accelerometer::getCurrentSpeed() {
    return currentSpeed;
}

qreal Accelerometer::getintervalTime() {
    return intervalTime;
}

/**
 * Processes Accelerometer data
 *
 */
void Accelerometer::processData()
{
    QFile file("/sys/class/i2c-adapter/i2c-3/3-001d/coord");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    // Read data, parse with regular expressions and process it
    QByteArray line = file.readLine();
    QRegExp rx("([0-9-]+) ([0-9-]+) ([0-9-]+)");
    rx.indexIn(line);

    smoothData(rx.cap(1).toInt(), rx.cap(2).toInt(), rx.cap(3).toInt());

    trueAccelerationX = (accelerationX - previousAccelerationX)/1000*kGravity;
    trueAccelerationY = (accelerationY - previousAccelerationY)/1000*kGravity;
    trueAccelerationZ = (accelerationZ - previousAccelerationZ)/1000*kGravity;

    previousAccelerationX = accelerationX;
    previousAccelerationY = accelerationY;
    previousAccelerationZ = accelerationZ;

    currentAcceleration = sqrt(trueAccelerationX * trueAccelerationX +
                           trueAccelerationY * trueAccelerationY +
                           trueAccelerationZ * trueAccelerationZ );

    totalAcceleration = currentAcceleration - previousAcceleration;

    totalAcceleration = fabs(totalAcceleration);

    previousAcceleration = currentAcceleration;

    // v = v0 + at
    // x = x0 + v0t + (at^2)/2
    // v = (v + v0)/2

    intervalTime = now.restart();
    intervalTime = intervalTime/1000; // millisecs to secs
    totalTime = totalTime + intervalTime;

    // filter noise
    // TODO: do this in smoothdata: implement a better filter.
    if (totalAcceleration > 0.02) {
        currentSpeed = ( previousSpeed + ( totalAcceleration * intervalTime ) / 2 );
    } else {
        currentSpeed = 0;
    }

    // filter noise
    if (currentSpeed > 0.02) {
        distanceTraveled = ( lastDistanceTraveled + ( ( currentSpeed + previousSpeed ) * intervalTime) / 2 );
    } else {
        //distanceTraveled = 0;
    }

    averageSpeed = distanceTraveled / totalTime;

    previousSpeed = currentSpeed;
    lastDistanceTraveled = distanceTraveled;

    file.close();
}

/**
 * Smooths Accelerometer data
 *
 * @param x Accelerometers x-axis raw input
 * @param y Accelerometers y-axis raw input
 * @param z Accelerometers z-axis raw input
 */
void Accelerometer::smoothData(qreal x, qreal y, qreal z) {
    accelerationX = x;
    accelerationY = y;
    accelerationZ = z;
    if(sampleIndex>0) {
        accelerationX = previousAccelerationX + (accelerationX-previousAccelerationX) * kFilteringFactor;
        accelerationY = previousAccelerationY + (accelerationY-previousAccelerationY) * kFilteringFactor;
        accelerationZ = previousAccelerationZ + (accelerationZ-previousAccelerationZ) * kFilteringFactor;
    }
    sampleIndex++;
}
