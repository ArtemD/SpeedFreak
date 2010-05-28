/*
 * Maemo5Location
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

//#ifdef Q_WS_MAEMO_5
#include "maemo5locationprivate.h"
#include "maemo5location.h"
#include <QDebug>

/**
  * Default constructor of this class.
  *
  * @param QObject pointer to parent object. By default the value is NULL.
  */
Maemo5Location::Maemo5Location(QObject* parent):QObject(parent)
{
    qDebug() << "__Maemo5Location";
    ptr = new Maemo5LocationPrivate(this);

    connect(ptr, SIGNAL(agnss()), this, SIGNAL(agnss()));
    connect(ptr, SIGNAL(awcp()), this, SIGNAL(awcp()));
    connect(ptr, SIGNAL(locationUpdated()), this, SIGNAL(locationUpdated()));
    connect(ptr, SIGNAL(gps_connected()), this, SIGNAL(gps_connected()));
    connect(ptr, SIGNAL(gps_disconnected()), this, SIGNAL(gps_disconnected()));
    connect(ptr, SIGNAL(gps_error(int)), this, SIGNAL(gps_error(int)));
    connect(ptr, SIGNAL(gpsd_running()), this, SIGNAL(gpsd_running()));
    connect(ptr, SIGNAL(gpsd_stopped()), this, SIGNAL(gpsd_stopped()));
}

/**
  * Destructor of this class. Should be used to release all allocated resources.
  */
Maemo5Location::~Maemo5Location()
{
    qDebug() << "__~Maemo5Location";
    if(ptr)
        delete ptr;
}

/**
  * Start polling gps.
  */
void Maemo5Location::startPollingGPS()
{
    qDebug() << "__Maemo5Location: startPollingGPS";
    ptr->get_agnss();
}

/**
  * Stop polling gps.
  */
void Maemo5Location::stopPollingGPS()
{
    qDebug() << "__Maemo5Location: stopPollingGPS";
    ptr->stop();
}

/**
  * Get number of satellites in use.
  *
  * @return int satellites in use
  */
int Maemo5Location::getSatellitesInUse()
{
    return ptr->get_satellites_in_use();
}

/**
  * Get number of satellites in view.
  *
  * @return int satellites in view
  */
int Maemo5Location::getSatellitesInView()
{
    return ptr->get_satellites_in_view();
}

/**
  * Get average signal strength of satellites which are in use.
  *
  * @return int signal strength
  */
int Maemo5Location::getSignalStrength()
{
    return ptr->get_signal_strength();
}

/**
  * Get gps online.
  *
  * @return bool gps online
  */
bool Maemo5Location::getGpsOnline()
{
    return ptr->get_gps_online();
}

/**
  * Get latitude.
  *
  * @return double latitude
  */
double Maemo5Location::getLatitude()
{
    return ptr->get_lat();
}

/**
  * Get longitude.
  *
  * @return double longitude
  */
double Maemo5Location::getLongitude()
{
    return ptr->get_lon();
}

/**
  * Get timestamp of the update in seconds.
  *
  * @return double time
  */
double Maemo5Location::getTime()
{
    return ptr->get_time();
}

/**
  * Get time accuracy in seconds.
  *
  * @return double ept
  */
double Maemo5Location::getEpt()
{
    return ptr->get_ept();
}

/**
  * Get horizontal position accuracy in cm.
  *
  * @return double eph
  */
double Maemo5Location::getEph()
{
    return ptr->get_eph();
}

/**
  * Get fix altitude in meters.
  *
  * @return double altitude
  */
double Maemo5Location::getAltitude()
{
    return ptr->get_altitude();
}

/**
  * Get altitude accuracy in meters.
  *
  * @return double epv
  */
double Maemo5Location::getEpv()
{
    return ptr->get_epv();
}

/**
  * Get direction of motion in degrees(0-359).
  *
  * @return double track
  */
double Maemo5Location::getTrack()
{
    return ptr->get_track();
}

/**
  * Get track accuracy in degrees.
  *
  * @return double epd
  */
double Maemo5Location::getEpd()
{
    return ptr->get_epd();
}

/**
  * Get current speed in km/h.
  *
  * @return double speed
  */
double Maemo5Location::getSpeed()
{
    return ptr->get_speed();
}

/**
  * Get speed accuracy in km/h.
  *
  * @return double eps
  */
double Maemo5Location::getEps()
{
    return ptr->get_eps();
}

/**
  * Get current rate of climb in m/s.
  *
  * @return double climb
  */
double Maemo5Location::getClimb()
{
    return ptr->get_climb();
}

/**
  * Get climb accuracy in m/s.
  *
  * @return double epc
  */
double Maemo5Location::getEpc()
{
    return ptr->get_epc();
}

/**
  * Get distance between two points in kilometers.
  *
  * @param double latitude of first point
  * @param double longitude of first point
  * @param double latitude of second point
  * @param double longitude of second point
  * @return double distance
  */
double Maemo5Location::distance_between_two_points(double latitude_s, double longitude_s, double latitude_f, double longitude_f)
{
    return ptr->distance_between_two_points(latitude_s, longitude_s, latitude_f, longitude_f);
}
