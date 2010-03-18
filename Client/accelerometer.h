/*
 * Accelerometer class to access the device accelerometer
 *
 * @author      Rikhard Kuutti <rikhard.kuutti@fudeco.com>
 * @author      Kai Rasilainen
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

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
    ~Accelerometer();

    void getAcceleration(qreal &x, qreal &y, qreal &z);
    void smoothData(qreal &x, qreal &y, qreal &z);
    void calibrate();
    void initValues();

    qreal getCalibrationX();
    qreal getCalibrationY();
    qreal getCalibrationZ();

private:
    qreal previousAccelerationX, previousAccelerationY, previousAccelerationZ;
    qreal calibrationX, calibrationY, calibrationZ;
};

#endif // ACCELEROMETER_H
