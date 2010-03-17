/*
 * Maemo5LocationPrivate
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "maemo5locationprivate.h"

/**
  *Default constructor of this class.
  *@param Maemo5Location pointer to public interface.
  */
Maemo5LocationPrivate::Maemo5LocationPrivate(Maemo5Location* location):QObject(location)
{
    //Initialize variables
    gps_online = false;
    usegps = -1;
    resetAll();
    //Get gps control object
    control = location_gpsd_control_get_default();
    //create gps device
    device = (LocationGPSDevice*) g_object_new(LOCATION_TYPE_GPS_DEVICE, NULL);

    g_signal_connect(device, "changed", G_CALLBACK(gps_data_changed), this);
    g_signal_connect(device, "connected", G_CALLBACK(gps_connected_func), this);
    g_signal_connect(device, "disconnected", G_CALLBACK(gps_disconnected_func), this);

    g_signal_connect(control, "error-verbose", G_CALLBACK(gps_error_func), this);
    g_signal_connect(control, "gpsd_running", G_CALLBACK(gpsd_running_func), this);
    g_signal_connect(control, "gpsd_stopped", G_CALLBACK(gpsd_running_func), this);

}
/**
  *Destructor of this class. Should be used to release all allocated resources.
  */
Maemo5LocationPrivate::~Maemo5LocationPrivate()
{
    delete device;
    delete control;
}

/**
  *This function is used to start to poll with gprs
  */
void Maemo5LocationPrivate::get_acwp()
{
    g_object_set(G_OBJECT(control), "preferred-method", LOCATION_METHOD_ACWP, NULL);
    usegps = 0;
    restart();
}

/**
  *This function starts to poll via gps interface
  */
void Maemo5LocationPrivate::get_agnss()
{
    g_object_set(G_OBJECT(control), "preferred-method", LOCATION_METHOD_AGNSS, NULL);
    usegps = 1;
    restart();
}

/**
  *Stop pollling
  */
void Maemo5LocationPrivate::stop()
{
    location_gpsd_control_stop(control);
}

/**
  *Stop and restart polling
  */
void Maemo5LocationPrivate::restart()
{
    location_gpsd_control_stop(control);
    location_gpsd_control_start(control);
}

/**
  *This function is called when device managed to connect to the lcoation server.
  *Function emits gps_connected signal.
  *@param Pointer to LocationGPSDevice class
  *@param Pointer to Maemo5LocationPrivate class
  */
void gps_connected_func(LocationGPSDevice *device, Maemo5LocationPrivate *gps)
{
    emit gps->gps_connected();
}

/**
  *This function is called when device is disconnected from the location server.
  *Function emits gps_disconnected signal.
  *Also this function resets all arguments of Maemo5LcoationPrivate class.
  *@param Pointer to LocationGPSDevice class
  *@param Pointer to Maemo5LocationPrivate class
  */
void gps_disconnected_func(LocationGPSDevice *device, Maemo5LocationPrivate *gps)
{
    gps->resetAll();
    emit gps->gps_disconnected();
}

/**
  *This function is called after the location_gpsd_control_stop has been called.
  *@param Pointer to LocationGPSDControl class
  *@param Pointer to Maemo5LocationPrivate class
  */
void gpsd_stopped_func(LocationGPSDControl *control, Maemo5LocationPrivate *gps)
{
    emit gps->gpsd_stopped();
}

/**
  *This function is called when an error has occurred.
  *@param Pointer to LocationGPSDControl class
  *@param error code
  *@param Pointer to Maemo5LocationPrivate class
  */
void gps_error_func(LocationGPSDControl *control, gint error, Maemo5LocationPrivate *gps)
{

    switch (error) {
      case LOCATION_ERROR_USER_REJECTED_DIALOG:
        emit gps->gps_err(0);
        g_debug("User didn't enable requested methods");
        break;
      case LOCATION_ERROR_USER_REJECTED_SETTINGS:
        emit gps->gps_err(1);
        g_debug("User changed settings, which disabled location");
        break;
      case LOCATION_ERROR_BT_GPS_NOT_AVAILABLE:
        emit gps->gps_err(2);
        g_debug("Problems with BT GPS");
        break;
      case LOCATION_ERROR_METHOD_NOT_ALLOWED_IN_OFFLINE_MODE:
        emit gps->gps_err(3);
        g_debug("Requested method is not allowed in offline mode");
        break;
      case LOCATION_ERROR_SYSTEM:
        emit gps->gps_err(4);
        g_debug("System error");
        break;
      }
}

/**
  *This function is called after the location_gpsd_control_start has been called.
  *@param Pointer to LocationGPSDControl class
  *@param Pointer to Maemo5LocationPrivate class
  */
void gpsd_running_func(LocationGPSDControl *control, Maemo5LocationPrivate *gps)
{
    emit gps->gpsd_running();
}

/**
  *Callback function to catch gps signals.
  *@param Pointer to LocationGPSDControl class
  *@param Pointer to Maemo5LocationPrivate class
  */
void gps_data_changed(LocationGPSDevice *device, Maemo5LocationPrivate *gps)
{
    //First check that LocationGpsDeviceFix can be found...this data structure contains the location info.
    if(gps->device->fix)
    {
        //Check that there are fields
        if(gps->device->fix->fields)
        {
            //Store values and emit signal
            if(gps->device->fix->fields & LOCATION_GPS_DEVICE_LATLONG_SET)
            {
                gps->latitude = gps->device->fix->latitude;
                gps->longitude = gps->device->fix->longitude;
                gps->eph = gps->device->fix->eph;
            }


            gps->satellites_in_use = gps->device->satellites_in_use;
            gps->satellites_in_view = gps->device->satellites_in_view;

            if(gps->device->fix->fields & 	 LOCATION_GPS_DEVICE_TIME_SET)
            {
                gps->time = gps->device->fix->time;
                gps->ept = gps->device->fix->ept;
            }

            if(gps->device->fix->fields & LOCATION_GPS_DEVICE_ALTITUDE_SET)
            {
                gps->altitude = gps->device->fix->altitude;
                gps->epv = gps->device->fix->epv;
            }

            if(gps->device->fix->fields & LOCATION_GPS_DEVICE_TRACK_SET)
            {
                gps->track = gps->device->fix->track;
                gps->epd = gps->device->fix->epd;
            }

            if(gps->device->fix->fields & LOCATION_GPS_DEVICE_SPEED_SET)
            {
                gps->speed = gps->device->fix->speed;
                gps->eps = gps->device->fix->eps;
            }

            if(gps->device->fix->fields & LOCATION_GPS_DEVICE_CLIMB_SET)
            {
                gps->climb = gps->device->fix->climb;
                gps->epc = gps->device->fix->epc;
            }


            // Calculate average signal strength of satellites in use
            int temp = 0;
            if(gps->satellites_in_use != 0)
            {
                for(int i=0 ; i < gps->satellites_in_use ; i++)
                {
                    LocationGPSDeviceSatellite * view = (LocationGPSDeviceSatellite*) g_ptr_array_index (gps->device->satellites, i);
                    temp = temp + view->signal_strength;
                }
                gps->signal_strength = (temp / gps->satellites_in_use);
            }


            if(gps->usegps == 0)
            {
                emit gps->awcp();
            }
            else if(gps->usegps == 1)
            {
                emit gps->agnss();
            }
            else
            {
                emit gps->locationUpdated();
            }
        }
    }

}

/**
  *Resets all arguments of Maemo5LocationPrivate class.
  */
void Maemo5LocationPrivate::resetAll()
{
    time = 0;
    latitude = 0;
    longitude = 0;
    satellites_in_view = 0;
    satellites_in_use = 0;
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
}

/**
  *Returns distance between two points in kilometers.
  *@param latitude of first point
  *@param longitude of first point
  *@param latitude of second point
  *@param longitude of second point
  */
double Maemo5LocationPrivate::distance_between_two_points(double latitude_s, double longitude_s, double latitude_f, double longitude_f)
{
    double distance = 0;
    return distance = location_distance_between(latitude_s, longitude_s, latitude_f, longitude_f);
}
