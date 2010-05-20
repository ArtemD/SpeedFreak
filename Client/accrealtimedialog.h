/*
 * Acceleration info in real time dialog
 *
 * @author      Jukka Kurttila  <jukka.kurttila@fudeco.com>
 * @author      Toni Jussila 	<toni.jussila@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */
#ifndef ACCREALTIMEDIALOG_H
#define ACCREALTIMEDIALOG_H

#include <QDialog>
#include <QTimer>
#include "accelerometer.h"
#include "movingaverage.h"
#include "resultdialog.h"


namespace Ui {
    class AccRealTimeDialog;
}

class AccRealTimeDialog : public QDialog {
    Q_OBJECT
public:
    AccRealTimeDialog(QWidget *parent = 0);
    ~AccRealTimeDialog();
    ResultDialog* resultDialog;
    void Calibrate();
    void startAccelerationMeasure();
    void SetStopMeasureSpeed(double speed);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AccRealTimeDialog *ui;
    void resetAccelerometerMeasurements();

    QTimer *accelerometerTimer;
    QTime elapsedTime;
    Accelerometer* accelerometer;
    Calculate *calculate;
    MovingAverage* movingAverageZ;
    MovingAverage* movingAverageY;

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

private slots:
    void on_buttonAbort_clicked();
    void readAccelerometerData();
    void sendResult(double);
    void killResultDialog();

signals:
    void sendresult(double);
};

#endif // ACCREALTIMEDIALOG_H
