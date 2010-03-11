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

/**
  *This is return function.
  *@return QString top10AccelerationList
  */
QString XmlReader::getTop10AccelerationList()
{
    return top10AccelerationList;
}

/**
  *This is return function.
  *@return QString top10SpeedList
  */
QString XmlReader::getTop10SpeedList()
{
    return top10SpeedList;
}

/**
  *This is return function.
  *@return QString top10GforceList
  */
QString XmlReader::getTop10GforceList()
{
    return top10GforceList;
}
