/*
 * Categorylist
 *
 * @author     Olavi Pulkkinen <olavi.pulkkinena@fudeco.com>
 * @author     Tiina Kivilinna-Korhola <tiina.kivilinna-korhola@fudeco.com>
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
    void appendCats(int ind, QString des, QString uni, QString cat);
    void clearCats();
    QString desOfCats(int i);

private:
    QStringList categoryList;   //Stores categories. categoryList is routed to UI.
    typedef struct {
        QString category;       //name of category variable
        QString description;    //verbal description of category
        QString unit;           //km/h, miles/h
    } categoryElements;
    categoryElements cats[10];

};

#endif // CATEGORYLIST_H
