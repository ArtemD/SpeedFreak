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
    xmlShow();
    // Remove next line from final code
    categoryList << "Speed" << "acceleration-0-40" << "acceleration-0-100" << "G-force";
}

/**
  *Destructor of this class. Should be used to release all allocated resources.
  */
XmlReader::~XmlReader()
{
    category = "";
    unit = "";
    description = "";
    position = "";
    user = "";
    value = "";
}

/**
  *This function is used to parsing xml file.
  */
void XmlReader::xmlRead(QNetworkReply *device)
{
    qDebug() << "_xmlRead";

    xmlreader.addData(device->readAll());

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
                attr = xmlreader.attributes();

                category = attr.value("category").toString();
                unit = attr.value("unit").toString();
                description = attr.value("description").toString();

                top10List << category;
                qDebug() << top10List << unit << description;
            }

            if(xmlreader.name() == "result")
            {
                qDebug() << "result";
                attr = xmlreader.attributes();

                position = attr.value("position").toString();
                user = attr.value("user").toString();
                value = attr.value("value").toString();

                if (category == "acceleration-0-100")
                {
                    top10AccelerationList.append(position + "\t" +
                                                user + "\t" +
                                                value +
                                                unit + "\t" +
                                                description + "\n");
                }

                if(category == "top10speed")
                {
                    top10SpeedList.append(position + "\t" +
                                          user + "\t" +
                                          value +
                                          unit + "\t" +
                                          description + "\n");
                }

                if(category == "top10gforce")
                {
                    top10GforceList.append(position + "\t" +
                                           user + "\t" +
                                           value +
                                           unit + "\t" +
                                           description + "\n");
                }
                qDebug() << position << user << value << unit;
            }
        }
    }
}

/**
  *This function is used to read example xml file (results.xml).
  *@todo Read real xml.
  */
void XmlReader::xmlShow()
{
    QString filename = "results.xml";
    QFile file(filename);

    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "_xmlShow fail";
        return;
    }

    //xmlRead(&file);
    file.close();
}

/**
  *This is return function.
  *@todo Read real category list
  *@return QStringList categoryList
  */
QStringList XmlReader::getCategoryList()
{
    return categoryList;
}

/**
  *This is return function.
  *@todo Read real top 10 category list
  *@return QStringList top10List
  */
QStringList XmlReader::getTop10List()
{
    //During development is needed some values for categorylist
    top10List.clear();
    top10List << "acceleration-0-10" << "acceleration-0-60" << "acceleration-0-100";

    return top10List;
}

QString XmlReader::getTopList( QString category, int size)
{
    if (category == "acceleration-0-100")
    {
        //return top10AccelerationList;
        return "acc-tulos1\nacc-tulos2\nacc-tulos3\nacc-tulos4\nacc-tulos5\nacc-tulos6\nacc-tulos7\nacc-tulos8\nacc-tulos9\nacc-tulos10";
    }
    else if (category == "acceleration-0-40")
    {
         //return top10AccelerationList;
         return "acc-40-tulos1\nacc-40-tulos2\nacc-40-tulos3\nacc-40-tulos4\nacc-40-tulos5\nacc-40-tulos6\nacc-40-tulos7\nacc-40-tulos8\nacc-40-tulos9\nacc-40-tulos10";
    }
    else if (category == "Speed")
    {
        //return top10SpeedList;
        return "speed-tulos1\nspeed-tulos2\nspeed-tulos3\nspeed-tulos4\nspeed-tulos5\nspeed-tulos6\nspeed-tulos7\nspeed-tulos8\nspeed-tulos9\nspeed-tulos10";
    }
    else if (category == "G-force")
    {
        //return top10GforceList;
        return "g-tulos1\ng-tulos2\ng-tulos3\ng-tulos4\ng-tulos5\ng-tulos6\ng-tulos7\ng-tulos8\ng-tulos9\ng-tulos10";
    }
}
