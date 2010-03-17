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

class GPSData : public QObject
{
public:
    GPSData();
    ~GPSData();

private:
    Maemo5Location *location;

private slots:
    void agnss();
    void awcp();
    void locationUpdated();
    void gpsConnected();
    void gpsDisconnected();
    void gps_error(int error);
    void gpsd_running();
    void gpsd_stopped();
};

#endif // GPSDATA_H
