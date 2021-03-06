/*
 * Xml writer
 *
 * @author     Tiina Kivilinna-Korhola
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "xmlwriter.h"

/**
  *@brief Constructor, connects object to GUI
  *@param Pointer to carmainwindow, which is temporarily used during development
  */
XmlWriter::XmlWriter()
{

}

/**
  *@brief Destructor
  */
XmlWriter::~XmlWriter()
{

}

/**
  * @brief Writes registration items into tags.
  * @param netbuf a buffer where xmlstreamwriter writes to.
  * @param usr for user name.
  * @param psswd for password.
  * @param email.
  * @param .
  * @param .
  * @param .
  * @param .
  * @param .
  */
//void XmlWriter::writeRegistering(QBuffer *netbuf, QString usr, QString psswd, QString email)
//void XmlWriter::writeRegistering(QBuffer *netbuf, QString usr, QString psswd, QString email, QString manufacturer, QString type, QString model, QString description, QString picture)
void XmlWriter::writeRegistering(QBuffer *netbuf, QString usr, QString psswd, QString email, QString description)
{
    qDebug() << "_writeRegistering";

    xmlwriter.setDevice(netbuf);

    xmlwriter.writeStartDocument();
    xmlwriter.writeStartElement("user");

    //<login>test827</login>
    xmlwriter.writeStartElement("login");
    xmlwriter.writeCharacters(usr);
    xmlwriter.writeEndElement();

    //<password>thisisaveryinsecurepassword</password>
    xmlwriter.writeStartElement("password");
    xmlwriter.writeCharacters(psswd);
    xmlwriter.writeEndElement();

    //<email>test@example.com</email>
    xmlwriter.writeStartElement("email");
    xmlwriter.writeCharacters(email);
    xmlwriter.writeEndElement();

    //<description>manufacturer;type;model;description</description>
    xmlwriter.writeStartElement("description");
    xmlwriter.writeCharacters(description);
    xmlwriter.writeEndElement();

    xmlwriter.writeEndElement();
    xmlwriter.writeEndDocument();
}

/**
  *@brief Writes Speed Freek results items as tags and contents into a buffer.
  *@todo Consider looping when writing many values.
  *@todo Replace test value to finally used variables.
  */
void XmlWriter::writeResult(QBuffer *netbuf, double result)
{
    qDebug() << "_writeResult";

    xmlwriter.setDevice(netbuf);

    xmlwriter.writeStartDocument();
    xmlwriter.writeStartElement("result");
    xmlwriter.writeAttribute("value", QString::number(result));
    xmlwriter.writeEndElement();
    xmlwriter.writeEndDocument();
}

/**
  *@brief Write track to server.
  *@param netbuf where to write.
  *@param counter is GPSData::roundCounter.
  *@todo Decide suitable attributes.
  */
void XmlWriter::writeGpsTrack(QBuffer *netbuf, int counter, int start, int stop, int lat, int lon, int alt, int speed, int time)
{
    qDebug() << "_writeGpsTrack";

    // Unused variables
    //double *ptrValue;
    //ptrValue = ptrTable;
    //double tmp = 0;
    int sTart = start;
    int sTop = stop;

    xmlwriter.setDevice(netbuf);
    xmlwriter.writeStartDocument();
    xmlwriter.writeStartElement("Route");
    xmlwriter.writeAttribute("starttime", QDateTime::currentDateTime().toString());
    xmlwriter.writeAttribute("endtime", QDateTime::currentDateTime().toString());
    xmlwriter.writeAttribute("points", QDateTime::currentDateTime().toString());
    for(int i = 0; i < counter; i++)
    {
        xmlwriter.writeStartElement("point");
        xmlwriter.writeAttribute("lat", QString::number(lat));
        xmlwriter.writeAttribute("lon", QString::number(lon));
        xmlwriter.writeAttribute("alt", QString::number(alt));
        xmlwriter.writeAttribute("speed", QString::number(speed));
        xmlwriter.writeAttribute("time", QString::number(time));
        xmlwriter.writeEndElement();
    }
    xmlwriter.writeEndElement();
    xmlwriter.writeEndDocument();
}

/**
  *@brief Opens and closes a file, when xml information is written into a file,
  *and passes file to writeXmlFile()
  *@param usr for user name.
  *@param psswd for password.
  *@param email.
  *@todo Replace hardcoced filename to finally GUI entry widget.
  */
//void XmlWriter::writeXml(QString usr, QString psswd, QString email)
void XmlWriter::writeXml()
{
    QString filename = "xmlcategoryfile.xml";
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "_xmlWrite fail";
        return;
    }

    writeXmlFile(&file);
    //writeRegistering(&file, usr, psswd, email);
    //writeResult(&file);
    file.close();
}

/**
  *@brief Writes general xml information.
  *Calls other functions to insert login and result information.
  *@param device: target of writing, here filename.
  *@param usr for user name.
  *@param psswd for password.
  *@param email.
  */
bool XmlWriter::writeXmlFile(QIODevice *device)
{
    xmlwriter.setDevice(device);
    xmlwriter.writeStartDocument();
    writeItems();
    xmlwriter.writeEndDocument();

    return true;
}

/**
  *@brief Writes Speed Freek results items as tags and contents to earlier defined target.
  *@todo Consider looping when writing many values.
  *@todo Replace testing values to finally used variabls.
  */
void XmlWriter::writeItems()
{
    xmlwriter.writeStartElement("result");
    xmlwriter.writeAttribute("value", QString::number(14)); //tmp testing value
    xmlwriter.writeAttribute("unit", "seconds");
    xmlwriter.writeAttribute("date", QDateTime::currentDateTime().toString());
    xmlwriter.writeEndElement();
}

/**
  * Write profile xml
  * @param QIODevice device: target of writing, here filename.
  * @param QString user name
  * @param QString manufacturer
  * @param QString type
  * @param QString model
  * @param QString description
  * @param QString picture: filename.
  */
void XmlWriter::writeProfileXmlFile(QIODevice *device, QString userName, QString manufacturer,
                                    QString type, QString model, QString description, QString picture)
{
    QString pictureStatus;
    if(picture != "")
        pictureStatus = "yes";
    else
        pictureStatus = "no";

    /*example of XML:
    <?xml version="1.0" encoding="UTF-8"?>
    <profile login="test827" picture="yes">
            <manufacturer>toyota</manufacturer>
            <type>corolla</type>
            <model>1983</model>
            <description>Fuel efficient, GPS system, only one owner</description>
    </profile>*/

    xmlwriter.setDevice(device);
    xmlwriter.writeStartDocument();
        xmlwriter.writeStartElement("profile");
        xmlwriter.writeAttribute("login", userName);
        xmlwriter.writeAttribute("picture", pictureStatus);
            xmlwriter.writeStartElement("manufacturer");
                xmlwriter.writeCharacters(manufacturer);
            xmlwriter.writeEndElement();
            xmlwriter.writeStartElement("type");
                xmlwriter.writeCharacters(type);
            xmlwriter.writeEndElement();
            xmlwriter.writeStartElement("model");
                xmlwriter.writeCharacters(model);
            xmlwriter.writeEndElement();
            xmlwriter.writeStartElement("description");
                xmlwriter.writeCharacters(description);
            xmlwriter.writeEndElement();
            xmlwriter.writeStartElement("picture");
                xmlwriter.writeCharacters(picture);
            xmlwriter.writeEndElement();
        xmlwriter.writeEndElement();
    xmlwriter.writeEndDocument();
}

/**
  * Write profile xml
  * @param QIODevice device: target of writing, here netbuf.
  * @param QString user name
  * @param QString manufacturer
  * @param QString type
  * @param QString model
  * @param QString description
  * @param QString picture: filename.
  */
void XmlWriter::writeProfileXmlFile(QBuffer *netbuf, QString userName, QString manufacturer,
                                    QString type, QString model, QString description, QString picture)
{
    QString pictureStatus;
    if(picture != "")
        pictureStatus = "yes";
    else
        pictureStatus = "no";

    /*example of XML:
    <?xml version="1.0" encoding="UTF-8"?>
    <profile login="test827" picture="yes">
            <manufacturer>toyota</manufacturer>
            <type>corolla</type>
            <model>1983</model>
            <description>Fuel efficient, GPS system, only one owner</description>
    </profile>*/

    xmlwriter.setDevice(netbuf);
    xmlwriter.writeStartDocument();
        xmlwriter.writeStartElement("profile");
        xmlwriter.writeAttribute("login", userName);
        xmlwriter.writeAttribute("picture", pictureStatus);
            xmlwriter.writeStartElement("manufacturer");
                xmlwriter.writeCharacters(manufacturer);
            xmlwriter.writeEndElement();
            xmlwriter.writeStartElement("type");
                xmlwriter.writeCharacters(type);
            xmlwriter.writeEndElement();
            xmlwriter.writeStartElement("model");
                xmlwriter.writeCharacters(model);
            xmlwriter.writeEndElement();
            xmlwriter.writeStartElement("description");
                xmlwriter.writeCharacters(description);
            xmlwriter.writeEndElement();
            xmlwriter.writeStartElement("picture");
                xmlwriter.writeCharacters(picture);
            xmlwriter.writeEndElement();
        xmlwriter.writeEndElement();
    xmlwriter.writeEndDocument();
}
