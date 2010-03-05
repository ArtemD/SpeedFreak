/*
 * Calculate class to process accelerometer data
 *
 * @author      Kai Rasilainen 
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef CALCULATE_H
#define CALCULATE_H

#include <QObject>
#include <QTime>

class Calculate : public QObject
{
    Q_OBJECT

public:
    Calculate();
    ~Calculate();

    void reset();
    void calculateParameters(double currentAcceleration, double seconds);
    void accelStoppedCheck(double currentAcceleration);

    double getAverageSpeed();
    void setAverageSpeed(double value);

    double getCurrentSpeed();
    void setCurrentSpeed(double value);

    double getDistanceTraveled();
    void setDistanceTraveled(double value);

    double getLastAcceleration();
    void setLastAcceleration(double value);

    double getLastCheckpoint();
    void setLastCheckpoint(double value);

    double getLastDistance();
    void setLastDistance(double value);

    double getLastSpeed();
    void setLastSpeed(double value);

    long getNumOfIterations();
    void setNumOfIterations(long value);

    double getTotalTime();
    void setTotalTime(double value);

private:
    double averageSpeed;
    double currentSpeed;
    double distanceTraveled;
    double lastAcceleration;
    double lastCheckpoint;
    double lastDistance;
    double lastSpeed;
    long numOfIterations;
    double totalTime;
    int count;

};

#endif // CALCULATE_H
