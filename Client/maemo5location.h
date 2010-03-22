/*
 * Maemo5Location
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef MAEMO5LOCATION_H
#define MAEMO5LOCATION_H

#include <QObject>

class Maemo5LocationPrivate;

class Maemo5Location : public QObject
{
    Q_OBJECT
public:
    Maemo5Location(QObject* parent = 0);
    ~Maemo5Location();

    void startPollingGPS();
    void stopPollingGPS();
    int getSatellitesInUse();
    int getSatellitesInView();
    int getSignalStrength();
    bool getGpsOnline();
    double getLatitude();
    double getLongitude();
    double getTime();
    double getEpt();
    double getEph();
    double getAltitude();
    double getEpv();
    double getTrack();
    double getEpd();
    double getSpeed();
    double getEps();
    double getClimb();
    double getEpc();
    double distance_between_two_points(double latitude_s, double longitude_s, double latitude_f, double longitude_f);

signals:
    void awcp();
    void agnss();
    void locationUpdated();
    void gps_connected();
    void gps_disconnected();
    void gps_error(int);
    void gpsd_running();
    void gpsd_stopped();

private:
    Maemo5LocationPrivate* ptr;
};

#endif // MAEMO5LOCATION_H
