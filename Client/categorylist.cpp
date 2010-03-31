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
    qDebug() << "_getCategoryList" << realSizeOfCats;

    if(sizeOfCategoryList() != 0) {
        clearCategoryList();
    }

    for(int i = 0; i < realSizeOfCats; i++)
    {
        categoryList.append(cats[i].description);
    }

    return categoryList;
}

/**
  *Append an item in the end of the categorylist.
  *@param Item.
  */
void CategoryList::appendCategoryList(QString item)
{
    categoryList.append(item);
}

/**
  *Input an item into the categorylist.
  *@param Index.
  *@param Item to be appended.
  */
void CategoryList::fillCategoryList(int index, QString item)
{
    categoryList.insert(index, item);
}

/**
  *Show an item of the categorylist.
  *@param Index.
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
}

/**
  *Read size of categorylist.
  */
int CategoryList::sizeOfCategoryList()
{
    return categoryList.size();
}

/**
  *Append an item in the end of the categoryelementable.
  *@param Index.
  *@param Description of category.
  *@param Unit.
  *@param Category.
  */
void CategoryList::appendCats(int ind, QString des, QString uni, QString cat)
{
    cats[ind].description = des;
    cats[ind].unit = uni;
    cats[ind].category = cat;
}

/**
  *Search description for an index af cats table.
  *@param Index.
  */
QString CategoryList::getRecentDescription(int ind)
{
    return cats[ind].description;
}

/**
  *Search category for an index af cats table.
  *@param Index.
  */
QString CategoryList::getRecentCategory(int ind)
{
    return cats[ind].category;
}

/**
  *Clear cats.
  */
void CategoryList::clearCats()
{
    for(int i = 0; i < 20; i++)
    {
        cats[i].description.clear();
        cats[i].unit.clear();
        cats[i].category.clear();
    }
}

/**
  *This function is used to get items to top list of the category that is chosen from combobox.
  *@param QString category
  *@param int size
  *@todo Now there is only one (the latest top10List). Later picking up the requested category.
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

