/*
 * Parse xml file
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @author     Tiina Kivilinna-Korhola <tiina.kivilinna-korhola@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include <QFile>
#include <QDebug>
#include "xmlreader.h"

/**
  *Constructor of this class.
  */
XmlReader::XmlReader()
{
    myCategoryList = new CategoryList();
}

/**
  *Destructor of this class. Should be used to release all allocated resources.
  */
XmlReader::~XmlReader()
{
    category = "";
    unit = "";
    position = "";
    user = "";
    value = "";
    delete myCategoryList;
}

/**
  *This function is used to parse top 10 results of a certain category.
  */
void XmlReader::xmlReadTop10Results(QNetworkReply *device)
{
    qDebug() << "_xmlReadTop10Results";

    int i = 0;
    int receivedFlag = 0;

    xmlreader.clear();
    QByteArray array = device->readAll();
    qDebug() << "array: " << array;
    xmlreader.addData(array);
    //xmlreader.addData(device->readAll());

    if(!(myCategoryList->top10List.isEmpty())) {
        myCategoryList->top10List.clear();
    }

    //Go trough the xml document
    while(!xmlreader.atEnd())
    {
        //Read next node
        xmlreader.readNext();
        //Check if this element is starting element
        if(xmlreader.isStartElement())
        {
            if(xmlreader.name() == "results")
            {
                qDebug() << xmlreader.name();
            }
            if(xmlreader.name() == "result")
            {
                qDebug() << "result";
                attr = xmlreader.attributes();

                user = attr.value("username").toString();
                position = attr.value("position").toString();
                date = attr.value("date").toString();
                unit = attr.value("unit").toString();
                value = attr.value("value").toString();

                myCategoryList->top10List.append(position + "\t" +
                                                user + "\t" +
                                                value + " " +
                                                unit + "\t" +
                                                date + "\n");

                qDebug() << position << user << value << unit << date;
                i++;
                receivedFlag = 1;
            }
        }
    }
    //Only change labelTopList if a new top10List has been received
    if(receivedFlag)
    {
        qDebug() << "receivedTop10List() emitted";
        emit receivedTop10List();
    }
}

void XmlReader::xmlReadCategories(QNetworkReply *device)
//void XmlReader::xmlReadCategories(QIODevice *device)
{
    qDebug() << "_xmlReadCategories";

    int i = 0;
    int receivedFlag = 0;

    xmlreader.clear();
    QByteArray array = device->readAll();
    qDebug() << "array: " << array;
    xmlreader.addData(array);
    //xmlreader.addData(device->readAll());

    if(myCategoryList->sizeOfCategoryList() != 0) {
        myCategoryList->clearCategoryList();
    }
    //qDebug() << "sizeOfCategoryList(): " << myCategoryList->sizeOfCategoryList();

    //Go trough the xml document
    while(!xmlreader.atEnd())
    {
        //Read next node
        xmlreader.readNext();

        //Check if this element is starting element
        if(xmlreader.isStartElement())
        {
            if(xmlreader.name() == "categories")
            {
                qDebug() << xmlreader.name();
            }
            if(xmlreader.name() == "category")
            {
                qDebug() << xmlreader.name();
                myCategoryList->appendCategoryList(xmlreader.readElementText());
                qDebug() << "i=" << i << myCategoryList->itemOfCategoryList(i);
                i++;
                receivedFlag = 1;
            }
        }
    }
    //Only change comboBoxTopCategory if a new list has been received
    if(receivedFlag)
    {
        qDebug() << "receivedCategoryList() emitted";
        emit receivedCategoryList();
    }
}

/**
  *This function is used to read example xml file (results.xml).
  *@todo Read real xml.
  */
void XmlReader::xmlShow()
{
    //QString filename = "results.xml";
    QString filename = "xmlcategoryfile.xml";
    QFile file(filename);

    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "_xmlShow fail";
        return;
    }

    //xmlReadTop10Results(&file);
    //xmlReadCategories(&file);
    file.close();
}

