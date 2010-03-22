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
    QString top10List;

    QStringList getCategoryList();
    void fillCategoryList(int index, QString item);
    void appendCategoryList(QString item);
    QString itemOfCategoryList(int index);
    QString getTopList( QString category, int size);
    void clearCategoryList();
    int sizeOfCategoryList();

private:
    QStringList categoryList;

};

#endif // CATEGORYLIST_H
