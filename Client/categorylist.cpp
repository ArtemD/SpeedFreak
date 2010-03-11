/*
 * Categorylist
 *
 * @author     Olavi Pulkkinen <olavi.pulkkinena@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "categorylist.h"

/**
  *Constructor of this class.
  */
CategoryList::CategoryList()
{
    categoryList << "Speed" << "acceleration-0-40" << "acceleration-0-100" << "G-force"; // OLPU
    //top10AccelerationList << "acc-tulos1\nacc-tulos2\nacc-tulos3\nacc-tulos4\nacc-tulos5\nacc-tulos6\nacc-tulos7\nacc-tulos8\nacc-tulos9\nacc-tulos10";
}

/**
  *Destructor of this class. Should be used to release all allocated resources.
  */
CategoryList::~CategoryList()
{
}

/**
  *This is return function.
  *@todo Read real top 10 category list
  *@return QStringList categoryList
  */
QStringList CategoryList::getCategoryList()
{
    return categoryList;
}

/**
  *This function is used to get items to top list of current category.
  *@param QString category
  *@param int size
  */
QString CategoryList::getTopList( QString category, int size)
{
    if (category == "acceleration-0-100")
    {
        //topList.append(xmlreader->getTop10AccelerationList());
        //return top10AccelerationList;
        return "acc-tulos1\nacc-tulos2\nacc-tulos3\nacc-tulos4\nacc-tulos5\nacc-tulos6\nacc-tulos7\nacc-tulos8\nacc-tulos9\nacc-tulos10";

    }
    else if (category == "acceleration-0-40")
    {
                //topList.append(xmlreader->getTop10AccelerationList());
                //return top10AccelerationList;
                return "acc-40-tulos1\nacc-40-tulos2\nacc-40-tulos3\nacc-40-tulos4\nacc-40-tulos5\nacc-40-tulos6\nacc-40-tulos7\nacc-40-tulos8\nacc-40-tulos9\nacc-40-tulos10";

    }
    else if (category == "Speed")
    {
        //topList.append(xmlreader->getTop10SpeedList());
        //return top10SpeedList;
        return "speed-tulos1\nspeed-tulos2\nspeed-tulos3\nspeed-tulos4\nspeed-tulos5\nspeed-tulos6\nspeed-tulos7\nspeed-tulos8\nspeed-tulos9\nspeed-tulos10";
    }
    else if (category == "G-force")
    {
        //topList.append(xmlreader->getTop10GforceList());
        //return top10GforceList;
        return "g-tulos1\ng-tulos2\ng-tulos3\ng-tulos4\ng-tulos5\ng-tulos6\ng-tulos7\ng-tulos8\ng-tulos9\ng-tulos10";

    }
}

