/*
 * GPS data
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "gpsdata.h"
#include <QDebug>

/**
  *Default constructor of this class.
  */
GPSData::GPSData(Maemo5Location *maemo5location)
{
    qDebug() << "__GPSData";
    location = maemo5location;

    connect(location,SIGNAL(agnss()),this,SLOT(agnss()));
    connect(location,SIGNAL(awcp()),this,SLOT(awcp()));
    connect(location,SIGNAL(locationUpdated()),this,SLOT(locationUpdated()));
    connect(location,SIGNAL(gps_connected()),this,SLOT(gpsConnected()));
    connect(location,SIGNAL(gps_disconnected()),this,SLOT(gpsDisconnected()));
    connect(location,SIGNAL(gps_error(int)),this,SLOT(gpsError()));
    connect(location,SIGNAL(gpsd_running()),this,SLOT(gpsdRunning()));
    connect(location,SIGNAL(gpsd_stopped()),this,SLOT(gpsdStopped()));

    gpsDateTime = new QDateTime();
    resetAll();
}

/**
  *Destructor of this class. Deletes all dynamic objects and sets them to NULL.
  */
GPSData::~GPSData()
{
    qDebug() << "__~GPSData";
    location = NULL;

    if(gpsDateTime)
        delete gpsDateTime;
}

/**
  * This function reset all variables
  */
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
    latitudePrevious = 0;
    longitudePrevious = 0;
    sLatitudeNow = "";
    sLongitudeNow = "";
    sLatitudePrevious = "";
    sLongitudePrevious = "";
    routeStartTime = "";
    routeStopTime = "";
    recordingStatus = false;
    roundCounter = 0;
}

/**
  *This slot function is called when GPS update location.
  */
void GPSData::agnss()
{
    //satellitesInUse   = location->getSatellitesInUse());  //Returns number of satellites in use.
    //satellitesInView  = location->getSatellitesInView();  //Returns number of satellites in view.
    //signalStrength    = location->getSignalStrength();    //Returns average signal strength of satellites which are in use.
    //gpsOnline         = location->getGpsOnline();         //Returns gsp online
    //ept               = location->getEpt();               //Returns time accuracy in seconds.
    //eph               = location->getEph();               //Returns horizontal position accuracy in cm.
    //track             = location->getTrack();             //Returns direction of motion in degrees(0-359).
    //epd               = location->getEpd();               //Returns track accuracy in degrees.
    //climb             = location->getClimb();             //Returns current rate of climb in m/s.
    //epc               = location->getEpc();               //Returns climb accuracy in m/s.
    //time              = location->getTime();              //Returns timestamp of the update in seconds.
    //epv               = location->getEpv();               //Returns altitude accuracy in meters.
    //eps               = location->getEps();               //Returns speed accuracy in km/h.
    //distance          = location->distance_between_two_points(double latitude_s, double longitude_s, double latitude_f, double longitude_f);

    //If route recording true
    if ( recordingStatus == true )
    {
        latitudePrevious = latitude;
        longitudePrevious = longitude;
        latitude    = location->getLatitude();  //Returns latitude.
        longitude   = location->getLongitude(); //Returns longitude.
        altitude    = location->getAltitude();  //Returns fix altitude in meters.
        speed       = location->getSpeed();     //Returns current speed in km/h.

        QFile routeTempFile("routetemp.xml");//Temp xml.

        //If GPS find 4 or more satellite and signal stregth is 30 or more.
        if (location->getSatellitesInUse() >= 4 && location->getSignalStrength() >= 30)
        {
            //If first round
            if (roundCounter == 0)
            {
                if (!routeTempFile.open(QIODevice::WriteOnly | QIODevice::Text))
                    return;
                writeRouteXml(&routeTempFile, 0);
                routeTempFile.close();
                roundCounter ++;
            }

            //Points writing round.
            else
            {
                sLatitudeNow.sprintf("%.4f", latitude);  //Latitude now to string
                sLongitudeNow.sprintf("%.4f", longitude);//Longitude now to string
                sLatitudePrevious.sprintf("%.4f", latitudePrevious);  //Previous latitude to string
                sLongitudePrevious.sprintf("%.4f", longitudePrevious); //Previous longitude to string

                //If latitude or longitude change
                if ( sLatitudeNow != sLatitudePrevious || sLongitudeNow != sLongitudePrevious )
                {
                    if (!routeTempFile.open(QIODevice::Append | QIODevice::Text))
                        return;

                    writeRouteXml(&routeTempFile, 0);
                    roundCounter ++;
                    routeTempFile.close();
                }
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
void GPSData::startRouteRecording()
{
    if (recordingStatus == false)
    {
        //Get start time and start recording.
        gpsDateTime->setTime_t(location->getTime());
        routeStartTime = gpsDateTime->toString("dd.MM.yyyy hh:mm:ss");
        recordingStatus = true;
        roundCounter = 0;
    }
}

/**
  *This function stop route recording.
  *@param QString time recording stop time.
  */
void GPSData::stopRouteRecording()
{
    if (recordingStatus == true)
    {
        //Get stop time and stop recording.
        gpsDateTime->setTime_t(location->getTime());
        routeStopTime = gpsDateTime->toString("dd.MM.yyyy hh:mm:ss");
        recordingStatus = false;

        //Write final xml.
        QFile file("route.xml");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        writeRouteXml(&file, 1);
        file.close();
        roundCounter = 0;
    }
}

/**
  *This function write route to .xml file.
  */
void GPSData::writeRouteXml(QIODevice *device, int round)
{
    xmlwriter.setDevice(device);

    //Write temp xml (routetemp.xml).
    if ( round == 0 )
    {
        xmlwriter.writeStartElement("Point");
        xmlwriter.writeAttribute("Latitude", QString::number(latitude));
        xmlwriter.writeAttribute("Longitude", QString::number(longitude));
        xmlwriter.writeAttribute("Altitude", QString::number(altitude));
        xmlwriter.writeAttribute("Speed", QString::number(speed));
        xmlwriter.writeEndElement();//Point
    }

    //Write final xml (route.xml).
    else if ( round == 1 )
    {
        xmlwriter.writeStartDocument();
        xmlwriter.writeStartElement("Route");
        xmlwriter.writeAttribute("Start-time", routeStartTime);
        xmlwriter.writeAttribute("Stop-time", routeStopTime);
        xmlwriter.writeAttribute("Points", QString::number(roundCounter));

        //Open temp xml and read points
        QFile tempFile("routetemp.xml");
        if (!tempFile.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream readRoute(&tempFile);
        QTextStream writeRoute(device);
        writeRoute << readRoute.readLine();
        tempFile.close();//Close temp xml

        xmlwriter.writeEndElement();//Route
        xmlwriter.writeEndDocument();     
    }
}
