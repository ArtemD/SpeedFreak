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

    gpsTimer = new QTimer();
    gpsTimeMS = 0;
    connect(gpsTimer, SIGNAL(timeout()),this, SLOT(gpsTimerTimeout()));

    resetAll();
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
    //track = QString::number(location->getTrack());                      //Returns direction of motion in degrees(0-359).
    //epd = QString::number(location->getEpd());                          //Returns track accuracy in degrees.
    //climb = QString::number(location->getClimb());                      //Returns current rate of climb in m/s.
    //epc = QString::number(location->getEpc());                          //Returns climb accuracy in m/s.
    //location->distance_between_two_points(double latitude_s, double longitude_s, double latitude_f, double longitude_f);
    //time = location->getTime();//Returns timestamp of the update in seconds.

    //If route recording true
    if ( recordingStatus == true )
    {
        latitude    = location->getLatitude();  //Returns latitude.
        longitude   = location->getLongitude(); //Returns longitude.
        altitude    = location->getAltitude();  //Returns fix altitude in meters.
        epv         = location->getEpv();       //Returns altitude accuracy in meters.
        speed       = location->getSpeed();     //Returns current speed in km/h.
        eps         = location->getEps();       //Returns speed accuracy in km/h.

        gpsTimer->start(1);

        //If first round
        if (roundCounter == 0)
        {
            saveRoute();
        }

        else
        { 
            latitudeNow.sprintf("%.4f", latitude);  //Latitude now to string
            longitudeNow.sprintf("%.4f", longitude);//Longitude now to string
            latitudePrevious.sprintf("%.4f", gpsDataArray[0]);  //Previous latitude to string
            longitudePrevious.sprintf("%.4f", gpsDataArray[1]); //Previous longitude to string

            //If latitude or longitude change
            if ( latitudeNow != latitudePrevious || longitudeNow != longitudePrevious )
            {
                saveRoute();
            }
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

/**
  *This function start route recording.
  *@param QString time recording start time.
  */
void GPSData::startRouteRecording(QString time)
{
    if (recordingStatus == false)
    {
        routeStartTime = time;
        recordingStatus = true;
        roundCounter = 0;
    }
}

/**
  *This function stop route recording.
  *@param QString time recording stop time.
  */
void GPSData::stopRouteRecording(QString time)
{
    if (recordingStatus == true)
    {
        routeStopTime = time;
        recordingStatus = false;
        roundCounter = 0;
        saveRoute();
    }
}

/**
  *This slot function is called when gps timer timeout(10s).
  */
void GPSData::gpsTimerTimeout()
{
    gpsTimeMS++;
}

/**
  *This function save route to .txt file.
  */
void GPSData::saveRoute()
{
    QFile file("route" + routeStartTime + ".txt");
    QTextStream route(&file);

    if ( recordingStatus == true )
    {
        //First round.
        if ( roundCounter == 0 )
        {
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;

            route << "Start: " << routeStartTime << "\n";
        }

        else
        {
            if (!file.open(QIODevice::Append | QIODevice::Text))
                return;
        }

        gpsDataArray[0] = latitude;
        gpsDataArray[1] = longitude;
        gpsDataArray[2] = altitude;
        gpsDataArray[3] = speed;
        roundCounter ++;

        route << " la: " << latitude
              << " \t lo: " << longitude
              << " \t al: " << altitude
              << " \t epv: " << epv
              << " \t sp: " << speed
              << " \t eps: " << eps
              << " \t ms: " << gpsTimeMS
              << "\n";

        gpsTimeMS = 0;
        file.close();
    }

    //Final round.
    else
    {
        if (!file.open(QIODevice::Append | QIODevice::Text))
            return;
        route << "Stop: " << routeStopTime << "\n";
        file.close();
    }
}
