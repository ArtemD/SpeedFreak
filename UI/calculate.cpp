#include "calculate.h"
#include <math.h>

#include <QFile>
#include <QString>
#include <QTimer>
#include <QRegExp>

const double G_ACCELERATION = 9.80665;
const double SECONDS_IN_HOUR = 3600;

Calculate::Calculate() {

    this->reset();

}

Calculate::~Calculate() {
}

void Calculate::reset() {

    averageSpeed = 0;
    currentSpeed = 0;
    distanceTraveled = 0;
    lastAcceleration = 0;
    lastDistance = 0;
    lastSpeed = 0;
    numOfIterations = 0;
    totalTime = 0;
}

/* Getters and setters
   */

double Calculate::AverageSpeed()
{
    return averageSpeed;
}
void Calculate::AverageSpeed(double value)
{
    averageSpeed = value;
}
double Calculate::CurrentSpeed()
{
    return currentSpeed;
}
void Calculate::CurrentSpeed(double value)
{
    currentSpeed = value;
}
double Calculate::DistanceTraveled()
{
    return distanceTraveled;
}
void Calculate::DistanceTraveled(double value)
{
    distanceTraveled = value;
}
double Calculate::LastAcceleration()
{
    return lastAcceleration;
}
void Calculate::LastAcceleration(double value)
{
    lastAcceleration = value;
}
double Calculate::LastDistance()
{
    return lastDistance;
}
void Calculate::LastDistance(double value)
{
    lastDistance = value;
}
double Calculate::LastSpeed()
{
    return lastSpeed;
}
void Calculate::LastSpeed(double value)
{
    lastSpeed = value;
}
long Calculate::NumOfIterations()
{
    return numOfIterations;
}
void Calculate::NumOfIterations(long value)
{
    numOfIterations = value;
}
double Calculate::TotalTime()
{
    return totalTime;
}
void Calculate::TotalTime(double value)
{
    totalTime = value;
}

/*
  This is a main function for calculating various parameters. Accelerometer
  provides currentAcceleration and calling function measures time (seconds).
  This function should be called 20-30 times/second to minimize
  calculation error.

  To be added: params like horsepower.
  */
void Calculate::CalculateParameters(double currentAcceleration, double seconds)
{
    numOfIterations++;
    totalTime = (totalTime + seconds);

    // v=v0 + a*t
    // v(n) = v(n-1)+(a(n) + a(n-1))*(seconds)/2

    /* First integration of acceleration provides speed
       */
    currentSpeed = (lastSpeed + (((currentAcceleration + lastAcceleration) * seconds) / 2));

    /* Second integration: distance.
       */
    distanceTraveled = (lastDistance + (((currentSpeed + lastSpeed) * seconds) / 2));

    /* Average speed
       */
    averageSpeed = (distanceTraveled / totalTime);

    lastSpeed = currentSpeed;
    lastAcceleration = currentAcceleration;
    lastDistance = distanceTraveled;
}






