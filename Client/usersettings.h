/*
 * UserSettings class
 *
 * @author     Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QObject>

class UserSettings : public QObject
{
public:
    UserSettings();
    void readLoginSettings( QString *userName, QString *password);
    void writeLoginSettings( QString userName, QString password);
};

bool loginSaved( void);
void saveLogin( QString userName, QString password);
void getLoginInfo( QString *userName, QString *password);

#endif // USERSETTINGS_H
