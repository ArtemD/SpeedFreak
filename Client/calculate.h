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
    void CalculateParameters(double currentAcceleration, double seconds);

    double AverageSpeed();
    void AverageSpeed(double value);

    double CurrentSpeed();
    void CurrentSpeed(double value);

    double DistanceTraveled();
    void DistanceTraveled(double value);

    double LastAcceleration();
    void LastAcceleration(double value);

    double LastCheckpoint();
    void LastCheckpoint(double value);

    double LastDistance();
    void LastDistance(double value);

    double LastSpeed();
    void LastSpeed(double value);

    long NumOfIterations();
    void NumOfIterations(long value);

    double TotalTime();
    void TotalTime(double value);

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


};

#endif // CALCULATE_H
