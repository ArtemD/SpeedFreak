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
  *@brief Writes registration items into tags.
  *@param netbuf a buffer where xmlstreamwriter writes to.
  *@param usr for user name.
  *@param psswd for password.
  *@param email.
  */
void XmlWriter::writeRegistering(QBuffer *netbuf, QString usr, QString psswd, QString email)
{
    qDebug() << "_writeRegistering";

    xmlwriter.setDevice(netbuf);

    xmlwriter.writeStartDocument();
    xmlwriter.writeStartElement("user");

    xmlwriter.writeStartElement("login");
    xmlwriter.writeCharacters(usr);
    xmlwriter.writeEndElement();

    xmlwriter.writeStartElement("password");
    xmlwriter.writeCharacters(psswd);
    xmlwriter.writeEndElement();

    xmlwriter.writeStartElement("email");
    xmlwriter.writeCharacters(email);
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

    double *ptrValue;
    //ptrValue = ptrTable;
    double tmp = 0;

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
