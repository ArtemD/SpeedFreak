/*
 * Calculate class to process accelerometer data
 *
 * @author      Kai Rasilainen
 * @author      Jukka Kurttila <jukka.kurttila@fudeco.com>
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

}


/**
  * This is a main function for calculating various parameters. Accelerometer
  * provides currentAcceleration and calling function measures time (seconds).
  * This function should be called 20-30 times/second to minimize
  * calculation error.

  * To be added: ---
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

double Calculate::getCurrentPower()
{
    return currentPower;
}

void Calculate::setCurrentPower(double value)
{
    currentPower = value;
}

double Calculate::getPeakPower()
{
    return peakPower;
}

void Calculate::setPeakPower(double value)
{
    peakPower = value;
}

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

void Calculate::setAveragePower(double value)
{
    averagePower = value;
}

double Calculate::getMaxSpeed()
{
    return maxSpeed;
}

void Calculate::setMaxSpeed(double value)
{
    maxSpeed = value;
}

QMap<int,double> Calculate::getValuesMap()
{
    return valuesMap;
}
