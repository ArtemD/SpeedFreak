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
#include "profiledialog.h"

/**
  *Constructor of this class.
  */
XmlReader::XmlReader()
{
    qDebug() << "__XmlReader";
    myCategoryList = new CategoryList();
}

/**
  *Destructor of this class. Should be used to release all allocated resources.
  */
XmlReader::~XmlReader()
{
    qDebug() << "__~XmlReader";
    category = "";
    unit = "";
    position = "";
    user = "";
    value = "";

    if(myCategoryList)
        delete myCategoryList;
}

/**
  *This function is used to parse top 10 results of a certain category.
  */
void XmlReader::xmlReadTop10Results(QNetworkReply *device,  QString userName)
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
                qDebug() << xmlreader.name();
                attr = xmlreader.attributes();

                user = attr.value("username").toString();
                position = attr.value("position").toString();
                date = attr.value("date").toString();
                //unit = attr.value("unit").toString();
                unit = "s";
                value = attr.value("value").toString();

                if (userName.toUpper() == user.toUpper())//If user name match highlight result
                {
                    myCategoryList->top10List.append("<tr><td><b>" + position + "</b></td><td><b>" +
                                                    user + "</b></td><td><b>" +
                                                    value + " " +
                                                    unit + "</b></td><td><b>" +
                                                    date + "</b></td></tr>");
                }
                else//If user name not match
                {
                    myCategoryList->top10List.append("<tr><td>" + position + "</td><td>" +
                                                    user + "</td><td>" +
                                                    value + "&nbsp;" +
                                                    unit + "</td><td>" +
                                                    date + "</td></tr>");
                }
                /* Old way, no highlight
                myCategoryList->top10List.append(position + "\t" +
                                                user + "\t" +
                                                value + " " +
                                                unit + "\t" +
                                                date + "\n");*/

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

/**
  *
  *
  */
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

    myCategoryList->clearCats();

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
                attr = xmlreader.attributes();
                description = attr.value("description").toString();
                unit = attr.value("unit").toString();
                category = xmlreader.readElementText();
                myCategoryList->appendCats(i, description, unit, category);
                qDebug() << "description: " << description << "unit: " << unit << "category: " << category;
                i++;
                receivedFlag = 1;
            }
        }
    }
    //Only change comboBoxTopCategory if a new list has been received
    if(receivedFlag)
    {
        qDebug() << "receivedCategoryList() emitted";
        myCategoryList->realSizeOfCats = i;
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
    //xmlReadProfile(&file);
    file.close();
}

/**
  * This function is used to read profile xml.
  * @param QIODevice device: target of reading, here filename.
  * @param ProfileDialog *profileDialog
  */
void XmlReader::xmlReadProfile(QIODevice *device, ProfileDialog *profileDialog)
{
    qDebug() << "_xmlReadProfile";

    profile = profileDialog;

    xmlreader.clear();
    QByteArray array = device->readAll();

    xmlreader.addData(array);

    QString login;
    QString picture;

    // Go trough the xml document
    while(!xmlreader.atEnd())
    {
        // Read next node
        xmlreader.readNext();

        // Check if this element is starting element
        if(xmlreader.isStartElement())
        {
            if(xmlreader.name() == "profile")
            {
                qDebug() << xmlreader.name();
                attr = xmlreader.attributes();
                login = attr.value("login").toString();
                picture = attr.value("picture").toString();
            }
            if(xmlreader.name() == "manufacturer")
            {
                qDebug() << xmlreader.name();
                profile->setManufacturer(xmlreader.readElementText());
            }
            if(xmlreader.name() == "type")
            {
                qDebug() << xmlreader.name();
                profile->setType(xmlreader.readElementText());

            }
            if(xmlreader.name() == "model")
            {
                qDebug() << xmlreader.name();
                profile->setModel(xmlreader.readElementText());

            }
            if(xmlreader.name() == "description")
            {
                qDebug() << xmlreader.name();
                profile->setDescription(xmlreader.readElementText());
            }
            if(xmlreader.name() == "picture" && picture == "yes")
            {
                qDebug() << xmlreader.name();
                profile->setPicture(xmlreader.readElementText());
            }
        }
    }
    profile = NULL;
}
