/*
 * Categorylist
 *
 * @author     Olavi Pulkkinen <olavi.pulkkinena@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include <QDebug>
#include "categorylist.h"

/**
  *Constructor of this class.
  */
CategoryList::CategoryList()
{

}

/**
  *Destructor of this class. Should be used to release all allocated resources.
  */
CategoryList::~CategoryList()
{
}

/**
  *This is return function.
  *@return QStringList categoryList
  */
QStringList CategoryList::getCategoryList()
{
    qDebug() << "_getCategoryList" ;
    return categoryList;
}

/**
  *Append an item in the end of the categorylist.
  */
void CategoryList::appendCategoryList(QString item)
{
    categoryList.append(item);
}

/**
  *Input an item into the categorylist.
  */
void CategoryList::fillCategoryList(int index, QString item)
{
    categoryList.insert(index, item);
}

/**
  *Show an item of the categorylist.
  */
QString CategoryList::itemOfCategoryList(int index)
{
    return categoryList.at(index);
}

/**
  *Clear categorylist.
  */
void CategoryList::clearCategoryList()
{
    categoryList.clear();
    qDebug() << "_clearCategoryList" ;
}

/**
  *Read size of categorylist.
  */
int CategoryList::sizeOfCategoryList()
{
    return categoryList.size();
}

/**
  *This function is used to get items to top list of current category.
  *@param QString category
  *@param int size
  */
QString CategoryList::getTopList( QString category, int size)
{
    qDebug() << "_getTopList";

    if(!(top10List.isEmpty()))
    {
        return top10List;
    }
    else
    {
        QString emptyStr("");
        qDebug() << "_getTopList: Category not found";
        return emptyStr;
    }
}

