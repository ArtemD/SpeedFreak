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
GPSData::GPSData(Maemo5Location *maemo5location)
{
    location = maemo5location;

    connect(location,SIGNAL(agnss()),this,SLOT(agnss()));
    connect(location,SIGNAL(awcp()),this,SLOT(awcp()));
    connect(location,SIGNAL(locationUpdated()),this,SLOT(locationUpdated()));
    connect(location,SIGNAL(gps_connected()),this,SLOT(gpsConnected()));
    connect(location,SIGNAL(gps_disconnected()),this,SLOT(gpsDisconnected()));
    connect(location,SIGNAL(gps_error(int)),this,SLOT(gpsError()));
    connect(location,SIGNAL(gpsd_running()),this,SLOT(gpsdRunning()));
    connect(location,SIGNAL(gpsd_stopped()),this,SLOT(gpsdStopped()));
}

/**
  *Destructor of this class. Deletes all dynamic objects and sets them to NULL.
  */
GPSData::~GPSData()
{
    delete location;
    location = NULL;
}

void GPSData::resetAll()
{
    satellitesInUse = 0;
    satellitesInView = 0;
    signalStrength = 0;
    latitude = 0;
    longitude = 0;
    time = 0;
    ept = 0;
    eph = 0;
    altitude = 0;
    epv = 0;
    track = 0;
    epd = 0;
    speed = 0;
    eps = 0;
    climb = 0;
    epc = 0;

    recordingStatus = false;
    roundCounter = 0;
}

/**
  *This slot function is called when GPS update location.
  */
void GPSData::agnss()
{
    //satellitesInUse = QString::number(location->getSatellitesInUse());  //Returns number of satellites in use.
    //satellitesInView = QString::number(location->getSatellitesInView());//Returns number of satellites in view.
    //signalStrength = QString::number(location->getSignalStrength());    //Returns average signal strength of satellites which are in use.
    //gpsOnline = QString::number(location->getGpsOnline());              //Returns gsp online                     
    //ept = QString::number(location->getEpt());                          //Returns time accuracy in seconds.
    //eph = QString::number(location->getEph());                          //Returns horizontal position accuracy in cm.
    //epv = QString::number(location->getEpv());                          //Returns altitude accuracy in meters.
    //track = QString::number(location->getTrack());                      //Returns direction of motion in degrees(0-359).
    //epd = QString::number(location->getEpd());                          //Returns track accuracy in degrees.
    //eps = QString::number(location->getEps());                          //Returns speed accuracy in km/h.
    //climb = QString::number(location->getClimb());                      //Returns current rate of climb in m/s.
    //epc = QString::number(location->getEpc());                          //Returns climb accuracy in m/s.
    //location->distance_between_two_points(double latitude_s, double longitude_s, double latitude_f, double longitude_f);
    //time = location->getTime();//Returns timestamp of the update in seconds.

    latitude    = location->getLatitude();  //Returns latitude.
    longitude   = location->getLongitude(); //Returns longitude.
    altitude    = location->getAltitude();  //Returns fix altitude in meters.
    speed       = location->getSpeed();     //Returns current speed in km/h.

    latitudeNow.sprintf("%.4f", latitude);  //Latitude now to string
    longitudeNow.sprintf("%.4f", longitude);//Longitude now to string
    latitudePrevious.sprintf("%.4f", gpsDataArray[roundCounter-1][0]);  //Previous latitude to string
    longitudePrevious.sprintf("%.4f", gpsDataArray[roundCounter-1][1]); //Previous longitude to string

    if ( recordingStatus == true )
    {
        if ( roundCounter == 0 || latitudeNow != latitudePrevious || longitudeNow != longitudePrevious )
        {
            gpsDataArray[roundCounter][0] = latitude;
            gpsDataArray[roundCounter][1] = longitude;
            gpsDataArray[roundCounter][2] = altitude;
            gpsDataArray[roundCounter][3] = speed;
            roundCounter ++;
        }
    }
}

/**
  *This slot function is called when gprs update location.
  */
void GPSData::awcp()
{

}

/**
  *This slot function is called when .
  */
void GPSData::locationUpdated()
{

}

/**
  *This slot function is called when .
  */
void GPSData::gpsConnected()
{

}

/**
  *This slot function is called when .
  */
void GPSData::gpsDisconnected()
{

}

/**
  *This slot function is called when .
  */
void GPSData::gpsError()
{

}

/**
  *This slot function is called when .
  */
void GPSData::gpsdRunning()
{

}

/**
  *This slot function is called when .
  */
void GPSData::gpsdStopped()
{

}

void GPSData::startRouteRecording(QString time)
{
    if (recordingStatus == false)
    {
        routeStartTime = time;
        recordingStatus = true;
        roundCounter = 0;
    }
}

void GPSData::stopRouteRecording(QString time)
{
    routeStopTime = time;
    saveRoute();
    if (recordingStatus == true)
    {
        recordingStatus = false;
        roundCounter = 0;
    }
}

void GPSData::saveRoute()
{
    QFile file("testroute.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream route(&file);

    route << "Start: " << routeStartTime << "\n";
    for (int i = 0 ; i <= roundCounter ; i++)
    {
        route << " lat: " << gpsDataArray[i][0]
              << " lon: " << gpsDataArray[i][1]
              << " alt: " << gpsDataArray[i][2]
              << " spe: " << gpsDataArray[i][3]
              << "\n";
    }
    route << "Stop: " << routeStopTime << "\n";
    file.close();
}
