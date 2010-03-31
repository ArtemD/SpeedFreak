/*
 * UserSettings class
 *
 * @author     Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "usersettings.h"
#include <QSettings>

UserSettings::UserSettings()
{
}

void UserSettings::readLoginSettings( QString *userName, QString *password)
{
     QSettings settings("SpeedFreakSoft", "logins");

     // paluu =  settings.status();
     *userName = settings.value("userName").toString();
     *password = settings.value("password").toString();
}

void UserSettings::writeLoginSettings( QString userName, QString password)
{
    // To do multiple logins - if needed later
    /*****
    struct Login {
         QString userName;
         QString password;
     };
     QList<Login> logins;
     ...

    QSettings settings;
    settings.beginWriteArray("logins");
    for (int i = 0; i < logins.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("userName", list.at(i).userName);
        settings.setValue("password", list.at(i).password);
    }
    settings.endArray();
    ******/
    QSettings settings("SpeedFreakSoft", "logins");
    settings.setValue("userName", userName);
    settings.setValue("password", password);
}

void getLoginInfo(QString *userName, QString *password)
{
    UserSettings myLogin;
    myLogin.readLoginSettings( userName, password);
}

void saveLogin( QString userName, QString password)
{
    UserSettings myLogin;

    myLogin.writeLoginSettings( userName, password);
}

/*
  * Function to test if login info saved.
  * Returns true if so.
  */
bool loginSaved()
{
    UserSettings myLogin;
    QString userName, password;

    myLogin.readLoginSettings( &userName, &password);

    if (userName.length() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
