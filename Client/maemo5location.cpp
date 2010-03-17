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

/**
  *Default constructor of this class.
  *@param QObject pointer to parent object. By default the value is NULL.
  */
Maemo5Location::Maemo5Location(QObject* parent):QObject(parent)
{
    ptr = new Maemo5LocationPrivate(this);

    connect(ptr,SIGNAL(agnss()),this,SIGNAL(agnss()));
    connect(ptr,SIGNAL(awcp()),this,SIGNAL(awcp()));
    connect(ptr,SIGNAL(locationUpdated()),this,SIGNAL(locationUpdated()));
    connect(ptr, SIGNAL(gps_connected()), this, SIGNAL(gps_connected()));
    connect(ptr, SIGNAL(gps_disconnected()), this, SIGNAL(gps_disconnected()));
    connect(ptr, SIGNAL(gps_err(int)), this, SIGNAL(gps_error(int)));
    connect(ptr, SIGNAL(gpsd_running()), this, SIGNAL(gpsd_running()));
    connect(ptr, SIGNAL(gpsd_stopped()), this, SIGNAL(gpsd_stopped()));

    ptr->get_agnss();
}

/**
  *Destructor of this class. Should be used to release all allocated resources.
  */
Maemo5Location::~Maemo5Location()
{
    delete ptr;
}

/**
  *Returns latitude.
  */
double Maemo5Location::getLatitude()
{
    return ptr->get_lat();
}

/**
  *Returns longitude.
  */
double Maemo5Location::getLongitude()
{
    return ptr->get_lon();
}

/**
  *Returns number of satellites in use.
  */
int Maemo5Location::getSatellitesInUse()
{
    return ptr->get_satellites_in_use();
}

/**
  *Returns number of satellites in view.
  */
int Maemo5Location::getSatellitesInView()
{
    return ptr->get_satellites_in_view();
}

/**
  *Returns average signal strength of satellites which are in use.
  */
int Maemo5Location::getSignalStrength()
{
    return ptr->get_signal_strength();
}

/**
  *Returns timestamp of the update in seconds.
  */
double Maemo5Location::getTime()
{
    return ptr->get_time();
}

/**
  *Returns time accuracy in seconds.
  */
double Maemo5Location::getEpt()
{
    return ptr->get_ept();
}

/**
  *Returns horizontal position accuracy in cm.
  */
double Maemo5Location::getEph()
{
    return ptr->get_eph();
}

/**
  *Returns fix altitude in meters.
  */
double Maemo5Location::getAltitude()
{
    return ptr->get_altitude();
}

/**
  *Returns altitude accuracy in meters.
  */
double Maemo5Location::getEpv()
{
    return ptr->get_epv();
}

/**
  *Returns direction of motion in degrees(0-359).
  */
double Maemo5Location::getTrack()
{
    return ptr->get_track();
}

/**
  *Returns track accuracy in degrees.
  */
double Maemo5Location::getEpd()
{
    return ptr->get_epd();
}

/**
  *Returns current speed in km/h.
  */
double Maemo5Location::getSpeed()
{
    return ptr->get_speed();
}

/**
  *Returns speed accuracy in km/h.
  */
double Maemo5Location::getEps()
{
    return ptr->get_eps();
}

/**
  *Returns current rate of climb in m/s.
  */
double Maemo5Location::getClimb()
{
    return ptr->get_climb();
}

/**
  *Returns climb accuracy in m/s.
  */
double Maemo5Location::getEpc()
{
    return ptr->get_epc();
}

/**
  *Returns distance between two points in kilometers.
  *@param latitude of first point
  *@param longitude of first point
  *@param latitude of second point
  *@param longitude of second point
  */
double Maemo5Location::distance_between_two_points(double latitude_s, double longitude_s, double latitude_f, double longitude_f)
{
    return ptr->distance_between_two_points(latitude_s, longitude_s, latitude_f, longitude_f);
}
