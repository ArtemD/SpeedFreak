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
void XmlReader::xmlReadTop10Results(QNetworkReply *device)
{
    qDebug() << "_xmlReadTop10Results";

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

void XmlReader::xmlReadCategories(QNetworkReply *device)
//void XmlReader::xmlReadCategories(QIODevice *device)
{
    qDebug() << "_xmlReadCategories";

    int i = 0;

    QByteArray array = device->readAll();
    qDebug() << array;
    xmlreader.addData(array);

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
                categoryList.insert(i, xmlreader.readElementText());
                qDebug() << "i=" << i << categoryList.at(i);
                i++;
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

