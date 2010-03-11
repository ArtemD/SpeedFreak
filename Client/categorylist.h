/*
 * Categorylist
 *
 * @author     Olavi Pulkkinen <olavi.pulkkinena@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef CATEGORYLIST_H
#define CATEGORYLIST_H

#include <QStringList>

class CategoryList : public QObject
{
public:
    CategoryList();
    ~CategoryList();
    QStringList getCategoryList();
    QString getTopList( QString category, int size);

private:
    QStringList categoryList;
    QString top10AccelerationList;
    QString top10SpeedList;
    QString top10GforceList;
};

#endif // CATEGORYLIST_H
