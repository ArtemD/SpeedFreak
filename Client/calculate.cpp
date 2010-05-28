/*
 * Calculate class to process accelerometer data
 *
 * @author      Kai Rasilainen <kai.rasilainen@fudeco.com>
 * @author      Jukka Kurttila <jukka.kurttila@fudeco.com>
 * @author      Toni Jussila   <toni.jussila@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "calculate.h"
#include <math.h>
#include <QFile>
#include <QString>
#include <QTimer>
#include <QRegExp>

const double G_ACCELERATION = 9.80665;
const double SECONDS_IN_HOUR = 3600;
const double AIR_DENSITY = 1.225;
const double WATTS_PER_HORSEPOWER = 745.69987158227025;
const double carFrontalArea = 1.5;
const double dragCoefficient = 0.31;
const int carWeight = 850;

/**
  * Default constructor for Calculate class.
  */
Calculate::Calculate()
{
    this->reset();
}

/**
  * Default destructor for Calculate class.
  * Deletes all dynamic objects and sets them to NULL.
  */
Calculate::~Calculate()
{

}

/**
  * This function reset all variables.
  */
void Calculate::reset()
{
    averageSpeed = 0;
    averagePower = 0;
    peakPower = 0;
    currentPower = 0;
    currentSpeed = 0;
    maxSpeed = 0;
    distanceTraveled = 0;
    lastAcceleration = 0;
    lastDistance = 0;
    lastSpeed = 0;
    numOfIterations = 0;
    totalTime = 0;
    count = 0;

    if(speedCheckPoints.count() == 0)
    {
        speedCheckPoints.append(10);
        speedCheckPoints.append(20);
        speedCheckPoints.append(30);
        speedCheckPoints.append(40);
        speedCheckPoints.append(50);
        speedCheckPoints.append(60);
        speedCheckPoints.append(70);
        speedCheckPoints.append(80);
        speedCheckPoints.append(90);
        speedCheckPoints.append(100);
    }
    checkPointCounter = 0;
    checkPoint = speedCheckPoints[checkPointCounter];
    valuesMap.clear();
}

/**
  * This is a main function for calculating various parameters. Accelerometer
  * provides currentAcceleration and calling function measures time (seconds).
  * This function should be called 20-30 times/second to minimize
  * calculation error.
  *
  * @param double current acceleration
  * @param double seconds
  */
void Calculate::calculateParameters(double currentAcceleration, double seconds)
{
    double force, power1, power2;

    currentAcceleration *= G_ACCELERATION;
    numOfIterations++;
    totalTime = (totalTime + seconds);

    // v=v0 + a*t
    // v(n) = v(n-1)+(a(n) + a(n-1))*(seconds)/2

    // First integration of acceleration provides speed
    currentSpeed = (lastSpeed + (((currentAcceleration + lastAcceleration) * seconds) / 2));

    // Update maximum speed
    if (currentSpeed > maxSpeed)
        maxSpeed = currentSpeed;

    // Second integration: distance.
    distanceTraveled = (lastDistance + (((currentSpeed + lastSpeed) * seconds) / 2));

    // Average speed
    averageSpeed = (distanceTraveled / totalTime);

    // F=ma
    force = (carWeight * currentAcceleration);

    power1 = (force * currentSpeed);

    power2 = ((AIR_DENSITY * (pow(currentSpeed, 3)
             * (carFrontalArea * dragCoefficient))) / 2);

    currentPower = ((power1 + power2) / WATTS_PER_HORSEPOWER);

    // Save peak power
    if ((currentPower > peakPower))
    {
        peakPower = currentPower;
    }

    if ((currentPower > 0))
    {
        averagePower = (averagePower + currentPower);
    }
    else
    {
        numOfIterations--;
    }

    if( (checkPoint > 0) && (currentSpeed*3.6 > checkPoint) )
    {
        //Update checkPoint
        if( checkPointCounter <= speedCheckPoints.count() )
        {
            //Save time
            valuesMap.insert( checkPoint, totalTime );
            if( checkPointCounter < speedCheckPoints.count() )
            {
                checkPoint = speedCheckPoints[checkPointCounter];
            }
            else
            {
                checkPoint = 0;
            }
            checkPointCounter++;
        }
    }

    // Check for movement
    //accelStoppedCheck(currentAcceleration);

    lastSpeed = currentSpeed;
    lastAcceleration = currentAcceleration;
    lastDistance = distanceTraveled;
}

/**
  * This function checks if acceleration has stopped for
  * a short period of time. Velocity is set to zero to avoid
  * distance errors.
  *
  * @param double current acceleration
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

/**
  * Get average speed.
  *
  * @return double average speed
  */
double Calculate::getAverageSpeed()
{
    return averageSpeed;
}

/**
  * Set average speed.
  *
  * @param double average speed
  */
void Calculate::setAverageSpeed(double value)
{
    averageSpeed = value;
}

/**
  * Get current speed.
  *
  * @return double current speed
  */
double Calculate::getCurrentSpeed()
{
    return currentSpeed;
}

/**
  * Set current speed.
  *
  * @param double current speed
  */
void Calculate::setCurrentSpeed(double value)
{
    currentSpeed = value;
}

/**
  * Get travelled distance.
  *
  * @return double travelled distance
  */
double Calculate::getDistanceTraveled()
{
    return distanceTraveled;
}

/**
  * Set travelled distance.
  *
  * @param double travelled distance
  */
void Calculate::setDistanceTraveled(double value)
{
    distanceTraveled = value;
}

/**
  * Get last acceleration.
  *
  * @return double last acceleration
  */
double Calculate::getLastAcceleration()
{
    return lastAcceleration;
}

/**
  * Set last acceleration.
  *
  * @param double last acceleration
  */
void Calculate::setLastAcceleration(double value)
{
    lastAcceleration = value;
}

/**
  * Get last distance.
  *
  * @return double last distance
  */
double Calculate::getLastDistance()
{
    return lastDistance;
}

/**
  * Set last distance.
  *
  * @param double last distance
  */
void Calculate::setLastDistance(double value)
{
    lastDistance = value;
}

/**
  * Get last speed.
  *
  * @return double last speed
  */
double Calculate::getLastSpeed()
{
    return lastSpeed;
}

/**
  * Set last speed.
  *
  * @param double last speed
  */
void Calculate::setLastSpeed(double value)
{
    lastSpeed = value;
}

/**
  * Get number of iterations.
  *
  * @return long number of iterations
  */
long Calculate::getNumOfIterations()
{
    return numOfIterations;
}

/**
  * Set number of iterations.
  *
  * @param long number of iterations
  */
void Calculate::setNumOfIterations(long value)
{
    numOfIterations = value;
}

/**
  * Get total time.
  *
  * @return double total time
  */
double Calculate::getTotalTime()
{
    return totalTime;
}

/**
  * Set total time.
  *
  * @param double total time
  */
void Calculate::setTotalTime(double value)
{
    totalTime = value;
}

/**
  * Get current power.
  *
  * @return double current power
  */
double Calculate::getCurrentPower()
{
    return currentPower;
}

/**
  * Set current power.
  *
  * @param double current power
  */
void Calculate::setCurrentPower(double value)
{
    currentPower = value;
}

/**
  * Get peek power.
  *
  * @return double peek power
  */
double Calculate::getPeakPower()
{
    return peakPower;
}

/**
  * Set peek power.
  *
  * @param double peek power
  */
void Calculate::setPeakPower(double value)
{
    peakPower = value;
}

/**
  * Get average power.
  *
  * @return double average power
  */
double Calculate::getAveragePower()
{
    if (numOfIterations > 0)
    {
        return (averagePower/numOfIterations);
    }
    else
    {
        return 0;
    }
}

/**
  * Set average power.
  *
  * @param double average power
  */
void Calculate::setAveragePower(double value)
{
    averagePower = value;
}

/**
  * Get max speed.
  *
  * @return double max speed
  */
double Calculate::getMaxSpeed()
{
    return maxSpeed;
}

/**
  * Set max speed.
  *
  * @param double max speed
  */
void Calculate::setMaxSpeed(double value)
{
    maxSpeed = value;
}

/**
  * Get values map.
  *
  * @return QMap<int,double> values map.
  */
QMap<int,double> Calculate::getValuesMap()
{
    return valuesMap;
}
