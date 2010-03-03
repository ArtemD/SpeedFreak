#include "calculate.h"
#include <math.h>

#include <QFile>
#include <QString>
#include <QTimer>
#include <QRegExp>

const double G_ACCELERATION = 9.80665;
const double SECONDS_IN_HOUR = 3600;

Calculate::Calculate()
{
    this->reset();
}

Calculate::~Calculate()
{

}

void Calculate::reset()
{
    averageSpeed = 0;
    currentSpeed = 0;
    distanceTraveled = 0;
    lastAcceleration = 0;
    lastDistance = 0;
    lastSpeed = 0;
    numOfIterations = 0;
    totalTime = 0;
    count = 0;
}

// Getters and setters

double Calculate::getAverageSpeed()
{
    return averageSpeed;
}

void Calculate::setAverageSpeed(double value)
{
    averageSpeed = value;
}

double Calculate::getCurrentSpeed()
{
    return currentSpeed;
}

void Calculate::setCurrentSpeed(double value)
{
    currentSpeed = value;
}

double Calculate::getDistanceTraveled()
{
    return distanceTraveled;
}

void Calculate::setDistanceTraveled(double value)
{
    distanceTraveled = value;
}

double Calculate::getLastAcceleration()
{
    return lastAcceleration;
}

void Calculate::setLastAcceleration(double value)
{
    lastAcceleration = value;
}

double Calculate::getLastDistance()
{
    return lastDistance;
}

void Calculate::setLastDistance(double value)
{
    lastDistance = value;
}

double Calculate::getLastSpeed()
{
    return lastSpeed;
}

void Calculate::setLastSpeed(double value)
{
    lastSpeed = value;
}

long Calculate::getNumOfIterations()
{
    return numOfIterations;
}

void Calculate::setNumOfIterations(long value)
{
    numOfIterations = value;
}

double Calculate::getTotalTime()
{
    return totalTime;
}

void Calculate::setTotalTime(double value)
{
    totalTime = value;
}

/**
  * This is a main function for calculating various parameters. Accelerometer
  * provides currentAcceleration and calling function measures time (seconds).
  * This function should be called 20-30 times/second to minimize
  * calculation error.

  * To be added: params like horsepower.
  */
void Calculate::calculateParameters(double currentAcceleration, double seconds)
{
    numOfIterations++;
    totalTime = (totalTime + seconds);

    // v=v0 + a*t
    // v(n) = v(n-1)+(a(n) + a(n-1))*(seconds)/2

    // First integration of acceleration provides speed
    currentSpeed = (lastSpeed + (((currentAcceleration + lastAcceleration) * seconds) / 2));

    // Second integration: distance.
    distanceTraveled = (lastDistance + (((currentSpeed + lastSpeed) * seconds) / 2));

    // Average speed
    averageSpeed = (distanceTraveled / totalTime);

    // Check for movement
    accelStoppedCheck(currentAcceleration);

    lastSpeed = currentSpeed;
    lastAcceleration = currentAcceleration;
    lastDistance = distanceTraveled;
}

/**
  * This function checks if acceleration has stopped for
  * a short period of time. Velocity is set to zero to avoid
  * distance errors.
  */
void Calculate::accelStoppedCheck(double currentAcceleration)
{

    // counting number of acceleration samples that equals zero
    if (currentAcceleration==0) {
        count++;
    } else {
        count = 0;
    }

    // if count exceeds 25, we assume that velocity is zero
    if (count >= 25)
    {
        currentSpeed=0;
    }
}


