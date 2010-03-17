/*
 * GPS data
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "gpsdata.h"

/**
  *Default constructor of this class.
  */
GPSData::GPSData()
{
    location = new Maemo5Location(this);

    connect(location,SIGNAL(agnss()),this,SLOT(agnss()));
    connect(location,SIGNAL(awcp()),this,SLOT(awcp()));
    connect(location,SIGNAL(locationUpdated()),this,SLOT(locationUpdated()));
    connect(location,SIGNAL(gps_connected()),this,SLOT(gpsConnected()));
    connect(location,SIGNAL(gps_disconnected()),this,SLOT(gpsDisconnected()));
    connect(location,SIGNAL(gps_error(int error)),this,SLOT(gps_error(int error)));
    connect(location,SIGNAL(gpsd_running()),this,SLOT(gpsd_running()));
    connect(location,SIGNAL(gpsd_stopped()),this,SLOT(gpsd_stopped()));
}

/**
  *Destructor of this class. Deletes all dynamic objects and sets them to NULL.
  */
GPSData::~GPSData()
{
    delete location;
    location = NULL;
}

void GPSData::agnss()
{
    QString satellitesInUse = QString::number(location->getSatellitesInUse());  //Returns number of satellites in use.
    QString satellitesInView = QString::number(location->getSatellitesInView());//Returns number of satellites in view.
    QString signalStrength = QString::number(location->getSignalStrength());    //Returns average signal strength of satellites which are in use.
    QString latitude = QString::number(location->getLatitude());                //Returns latitude.
    QString longitude = QString::number(location->getLongitude());              //Returns longitude.
    QString time = QString::number(location->getTime());                        //Returns timestamp of the update in seconds.
    QString ept = QString::number(location->getEpt());                          //Returns time accuracy in seconds.
    QString eph = QString::number(location->getEph());                          //Returns horizontal position accuracy in cm.
    QString altitude = QString::number(location->getAltitude());                //Returns fix altitude in meters.
    QString epv = QString::number(location->getEpv());                          //Returns altitude accuracy in meters.
    QString track = QString::number(location->getTrack());                      //Returns direction of motion in degrees(0-359).
    QString epd = QString::number(location->getEpd());                          //Returns track accuracy in degrees.
    QString speed = QString::number(location->getSpeed());                      //Returns current speed in km/h.
    QString eps = QString::number(location->getEps());                          //Returns speed accuracy in km/h.
    QString climp = QString::number(location->getClimb());                      //Returns current rate of climb in m/s.
    QString epc = QString::number(location->getEpc());                          //Returns climb accuracy in m/s.
    //location->distance_between_two_points(double latitude_s, double longitude_s, double latitude_f, double longitude_f);
}

void GPSData::awcp()
{

}

void GPSData::locationUpdated()
{

}

void GPSData::gpsConnected()
{

}

void GPSData::gpsDisconnected()
{

}

void GPSData::gps_error(int error)
{

}

void GPSData::gpsd_running()
{

}

void GPSData::gpsd_stopped()
{

}
