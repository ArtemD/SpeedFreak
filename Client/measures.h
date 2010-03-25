/*
 * CarMainWindow main class
 *
 * @author     Janne Änäkkälä <janne.anakkala@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef MEASURES_H
#define MEASURES_H

#include <QObject>

class Measures
{
public:
    Measures();
    qreal getTime10kmh();
    qreal getTime20kmh();
    qreal getTime30kmh();
    qreal getTime40kmh();
    qreal getTime50kmh();
    qreal getTime60kmh();
    qreal getTime70kmh();
    qreal getTime80kmh();
    qreal getTime90kmh();
    qreal getTime100kmh();

    void setTime10kmh(qreal pTime);
    void setTime20kmh(qreal pTime);
    void setTime30kmh(qreal pTime);
    void setTime40kmh(qreal pTime);
    void setTime50kmh(qreal pTime);
    void setTime60kmh(qreal pTime);
    void setTime70kmh(qreal pTime);
    void setTime80kmh(qreal pTime);
    void setTime90kmh(qreal pTime);
    void setTime100kmh(qreal pTime);

    void initializeMembers();


private:
    qreal time10kmh;
    qreal time20kmh;
    qreal time30kmh;
    qreal time40kmh;
    qreal time50kmh;
    qreal time60kmh;
    qreal time70kmh;
    qreal time80kmh;
    qreal time90kmh;
    qreal time100kmh;
};

#endif // MEASURES_H
