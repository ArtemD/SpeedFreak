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
#include <QXmlStreamWriter>
#include <qdatetime.h>

class GPSData : public QObject
{
    Q_OBJECT
public:
    GPSData( Maemo5Location *maemo5location );
    ~GPSData();
    void startRouteRecording();
    void stopRouteRecording();
    int roundCounter; //testing, move private!!!

    double getDistanceTraveled();

private:
    Maemo5Location *location;
    void resetAll();
    QXmlStreamWriter xmlwriter;
    void writeRouteXml(QIODevice *device, int round);

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
    double latitudePrevious;
    double longitudePrevious;
    double distance;
    QString routeStartTime;
    QString routeStopTime;
    QString sLatitudeNow;
    QString sLongitudeNow;
    QString sLatitudePrevious;
    QString sLongitudePrevious;
    QDateTime *gpsDateTime;
    bool recordingStatus;
    //int roundCounter;

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
