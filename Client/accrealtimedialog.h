#ifndef ACCREALTIMEDIALOG_H
#define ACCREALTIMEDIALOG_H

#include <QDialog>
#include <QTimer>
#include "accelerometer.h"
#include "movingaverage.h"

namespace Ui {
    class AccRealTimeDialog;
}

class AccRealTimeDialog : public QDialog {
    Q_OBJECT
public:
    AccRealTimeDialog(QWidget *parent = 0);
    ~AccRealTimeDialog();
    void Calibrate();
    void startAccelerationMeasure();
    void SetStopMeasureSpeed(double speed);

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_buttonAbort_clicked();
    void readAccelerometerData();

private:
    Ui::AccRealTimeDialog *ui;
    void resetAccelerometerMeasurements();

    QTimer *accelerometerTimer;
    QTime elapsedTime;
    Accelerometer* accelerometer;
    Calculate *calculate;
    MovingAverage* movingAverageZ;

    int updateScreenCounter;
    double accelerationStartThreshold;
    double currentAcceleration;
    double currentTime;
    double previousTime;
    double time;
    double speed;
    double stopMeasureSpeed;
    bool vehicleStartedMoving;
    bool isNewRun;

    QString currentSpeed;
    QString totalTime;
};

#endif // ACCREALTIMEDIALOG_H
