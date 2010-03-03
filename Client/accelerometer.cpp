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
Accelerometer::~Accelerometer() {
}

/**
 * Start measuring
 *
 */
void Accelerometer::start() {
    initValues();
    calibrate();
    timer->start(sampleRate);
    now.restart();
}

/**
 * Init class members
 *
 */
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
    reverseAcceleration = false;
}

/**
  * Calibrate. Purpose of this function is to calibrate
  * accelerometer when stationary.
  *
  */
void Accelerometer::calibrate(void) {
    QFile file(kFileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    unsigned int iteration;
    iteration = 0;
    QByteArray line;
    QRegExp rx("([0-9-]+) ([0-9-]+) ([0-9-]+)");

    do{
        // Read data, parse with regular expressions and process it
        line = file.readLine();
        rx.indexIn(line);

        int Sample_X = rx.cap(1).toInt();
        int Sample_Y = rx.cap(2).toInt();
        int Sample_Z = rx.cap(3).toInt();

        sstatex += Sample_X; // Accumulate Samples
        sstatey += Sample_Y; // for all axes.
        sstatez += Sample_Z;

        iteration++;
    }while(iteration!=1024);       // 1024 times

    sstatex = sstatex>>10;           // division by 1024
    sstatey = sstatey>>10;
    sstatez = sstatez>>10;

    file.close();
}

/**
 * Stop measuring
 *
 */
void Accelerometer::stop() {
    timer->stop();
}

/**
 * Set the sample rate of accelerometer
 *
 * @param int pSampleRate desired sample rate
 */
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

qreal Accelerometer::getIntervalTime() {
    return intervalTime;
}

/**
 * Processes Accelerometer data
 *
 */
void Accelerometer::processData()
{
    QFile file(kFileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    // Read data, parse with regular expressions and process it
    QByteArray line = file.readLine();
    //QByteArray line;
    QRegExp rx("([0-9-]+) ([0-9-]+) ([0-9-]+)");
    rx.indexIn(line);

    smoothData(rx.cap(1).toInt(), rx.cap(2).toInt(), rx.cap(3).toInt());

    // Add calibration
    trueAccelerationX = accelerationX - sstatex;
    trueAccelerationY = accelerationY - sstatey;
    trueAccelerationZ = accelerationZ - sstatez;

    // Discrimination window for acceleration values
    if (trueAccelerationX <= 30 && trueAccelerationX >= -30) { trueAccelerationX = 0; }
    if (trueAccelerationY <= 30 && trueAccelerationY >= -30) { trueAccelerationY = 0; }
    if (trueAccelerationZ <= 30 && trueAccelerationZ >= -30) { trueAccelerationZ = 0; }

    trueAccelerationX = (accelerationX - previousAccelerationX) / 1000 * kGravity;
    trueAccelerationY = (accelerationY - previousAccelerationY) / 1000 * kGravity;
    trueAccelerationZ = (accelerationZ - previousAccelerationZ) / 1000 * kGravity;

    previousAccelerationX = accelerationX;
    previousAccelerationY = accelerationY;
    previousAccelerationZ = accelerationZ;

    currentAcceleration = sqrt(trueAccelerationX * trueAccelerationX +
                               trueAccelerationY * trueAccelerationY +
                               trueAccelerationZ * trueAccelerationZ );

    totalAcceleration = currentAcceleration - previousAcceleration;
    previousAcceleration = currentAcceleration;

    // Measure time interval
    intervalTime = now.restart(); // millisecs to secs
    intervalTime = intervalTime/1000;
    totalTime = totalTime + intervalTime;

    // Filter out acceleration caused by noise.
    if (fabs(currentAcceleration) < 0.09) {
        return;
    }

    // Using calculate class to calculate velocity and distance etc.
    calculate->CalculateParameters(currentAcceleration,intervalTime );

    currentSpeed = calculate->CurrentSpeed();
    distanceTraveled = calculate->DistanceTraveled();
    file.close();
}

/**
 * Smooths Accelerometer data
 *
 * @param qreal x Accelerometers x-axis raw input
 * @param qreal y Accelerometers y-axis raw input
 * @param qreal z Accelerometers z-axis raw input
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
