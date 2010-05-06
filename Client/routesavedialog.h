/*
 * Route save dialog class
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef ROUTESAVEDIALOG_H
#define ROUTESAVEDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <QTimer>
#include <maemo5location.h>
#include "gpsdata.h"
#include "routedialog.h"
#include <helproutingdialog.h>
#include "calibratedialog.h"

namespace Ui {
    class RouteSaveDialog;
}

class RouteSaveDialog : public QDialog {
    Q_OBJECT
public:
    RouteSaveDialog(QWidget *parent = 0);
    ~RouteSaveDialog();
    RouteDialog *routeDialog;
    HelpRoutingDialog *helpRoutingDialog;
    double getAverageSpeed();
    QString getDistanceTraveled();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RouteSaveDialog *ui;
    QTimer *timerSatellitePicture;
    QTimer *timerRoutePicture;
    GPSData *gpsData;
    Maemo5Location *location;
    CalibrateDialog *calibrateDialog;
    QString gpsSpeed;
    QString distanceString;
    QPixmap *pixmapRouteStop;
    QPixmap *pixmapRouteStart;
    QIcon *iconRouteStop;
    QIcon *iconRouteStart;
    bool buttonStatus;
    double averageSpeed;
    double speed;
    double allSpeeds;
    int speedCount;

private slots:
    void on_pushButtonInfo_clicked();
    void on_buttonRouteStartStop_clicked();
    void timerSatellitePictureTimeout();
    void timerRoutePictureTimeout();
    void gpsStatus();
    void sendRoute();
    void killHelpDialog();

signals:
    void sendroute();

};

#endif // ROUTESAVEDIALOG_H
