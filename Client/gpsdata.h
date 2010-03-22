/*
 * GPS data
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef GPSDATA_H
#define GPSDATA_H

#include <QObject>
#include <maemo5location.h>
#include <QFile>
#include <QTextStream>

class GPSData : public QObject
{
    Q_OBJECT
public:
    GPSData(Maemo5Location *maemo5location);
    ~GPSData();
    void startRouteRecording(QString time);
    void stopRouteRecording(QString time);
    int roundCounter; //testing, move private!!!

private:
    Maemo5Location *location;
    void resetAll();
    void saveRoute();

    int satellitesInUse; //Number of satellites in use.
    int satellitesInView;//Number of satellites in view.
    int signalStrength;  //Average signal strength of satellites which are in use.
    double latitude;     //Latitude.
    double longitude;    //Longitude.
    double time;         //Timestamp of the update in seconds.
    double ept;          //Time accuracy in seconds.
    double eph;          //Horizontal position accuracy in cm.
    double altitude;     //Fix altitude in meters.
    double epv;          //Altitude accuracy in meters.
    double track;        //Direction of motion in degrees(0-359).
    double epd;          //Track accuracy in degrees.
    double speed;        //Current speed in km/h.
    double eps;          //Speed accuracy in km/h.
    double climb;        //Current rate of climb in m/s.
    double epc;          //Climb accuracy in m/s.
    QString routeStartTime;
    QString routeStopTime;
    QString latitudeNow;
    QString longitudeNow;
    QString latitudePrevious;
    QString longitudePrevious;

    bool recordingStatus;
    //int roundCounter;
    double gpsDataArray[100][4];

private slots:
    void agnss();
    void awcp();
    void locationUpdated();
    void gpsConnected();
    void gpsDisconnected();
    void gpsError();
    void gpsdRunning();
    void gpsdStopped();

};

#endif // GPSDATA_H
