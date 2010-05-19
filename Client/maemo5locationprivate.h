/*
 * Maemo5LocationPrivate
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef MAEMO5LOCATIONPRIVATE_H
#define MAEMO5LOCATIONPRIVATE_H

//We have to declare these header file inside extern, since these modules are actually c modules not c++
extern "C"
{
#include <location/location-gps-device.h>
#include <location/location-gpsd-control.h>
#include <location/location-distance-utils.h>    
}

#include <QObject>
#include "maemo5location.h"

class Maemo5LocationPrivate : public QObject
{
    Q_OBJECT

public:
    Maemo5LocationPrivate(Maemo5Location* location);
    ~Maemo5LocationPrivate();

    void get_acwp();
    void get_agnss();

    friend void gps_data_changed(LocationGPSDevice *device, Maemo5LocationPrivate *gps);
    friend void gps_connected_func(LocationGPSDevice *device, Maemo5LocationPrivate *gps);
    friend void gps_disconnected_func(LocationGPSDevice *device, Maemo5LocationPrivate *gps);
    friend void gps_error_func(LocationGPSDControl *control, gint error, Maemo5LocationPrivate *gps);
    friend void gpsd_running_func(LocationGPSDControl *control, Maemo5LocationPrivate *gps);
    friend void gpsd_stopped_func(LocationGPSDControl *control, Maemo5LocationPrivate *gps);

    static void handleStatus( LocationGPSDeviceStatus status );

    int get_satellites_in_view() { return satellites_in_view; }
    int get_satellites_in_use() { return satellites_in_use; }
    int get_signal_strength() { return signal_strength; }
    gboolean get_gps_online() { return gps_online; }
    double get_lat() { return latitude; }
    double get_lon() { return longitude; }
    double get_time() { return time; }
    double get_ept() { return ept; }
    double get_eph() { return eph; }
    double get_altitude() { return altitude; }
    double get_epv() { return epv; }
    double get_track() { return track; }
    double get_epd() { return epd; }
    double get_speed() { return speed; }
    double get_eps() { return eps; }
    double get_climb() { return climb; }
    double get_epc() { return epc; }
    double distance_between_two_points(double latitude_s, double longitude_s, double latitude_f, double longitude_f);
    void stop();

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
    void resetAll();
    //void stop();
    void restart();

    int satellites_in_view;
    int satellites_in_use;
    int signal_strength;
    gboolean gps_online;
    double latitude;
    double longitude;
    double time;
    double ept;
    double eph;
    double altitude;
    double epv;
    double track;
    double epd;
    double speed;
    double eps;
    double climb;
    double epc;

    Maemo5Location* d_ptr;
    int usegps;
    LocationGPSDControl *control;
    LocationGPSDevice *device;
};

void gps_data_changed(LocationGPSDevice *device, Maemo5LocationPrivate *gps);
void gps_connected_func(LocationGPSDevice *device, Maemo5LocationPrivate *gps);
void gps_disconnected_func(LocationGPSDevice *device, Maemo5LocationPrivate *gps);
void gps_error_func(LocationGPSDControl *control, gint error, Maemo5LocationPrivate *gps);
void gpsd_running_func(LocationGPSDControl *control, Maemo5LocationPrivate *gps);
void gpsd_stopped_func(LocationGPSDControl *control, Maemo5LocationPrivate *gps);

#endif // MAEMO5LOCATIONPRIVATE_H
