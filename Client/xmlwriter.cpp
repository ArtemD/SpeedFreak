/*
 * Xml writer
 *
 * @author     Tiina Kivilinna-Korhola
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
    tmpvalue = 110;
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
void XmlWriter::writeResult(QBuffer *netbuf)
{
    qDebug() << "_writeResult";

    xmlwriter.setDevice(netbuf);

    xmlwriter.writeStartDocument();
    xmlwriter.writeStartElement("result");
    tmpvalue++;
    qDebug() << tmpvalue;
    xmlwriter.writeAttribute("value", QString::number(tmpvalue));
    xmlwriter.writeEndElement();
    xmlwriter.writeEndDocument();
}


/**
  *@brief Write track to server.
  *@param ptrTable points to GPSData::gpsDataArray[100][4].
  *@param counter is GPSData::roundCounter.
  *@todo Decide suitable attributes.
  */
void XmlWriter::writeGpsTrack(QBuffer *netbuf, double *ptrTable, int counter)
{
    qDebug() << "_writeGpsTrack";

    double *ptrValue;
    ptrValue = ptrTable;
    double tmp = 0;

    xmlwriter.setDevice(netbuf);

    xmlwriter.writeStartDocument();

    xmlwriter.writeStartElement("gpx");
    xmlwriter.writeAttribute("someattribute", "abc");
    xmlwriter.writeAttribute("otherattribute", "cde");

    xmlwriter.writeStartElement("metadata");
    xmlwriter.writeStartElement("link");
    xmlwriter.writeAttribute("href", "http://api.speedfreak-app.com/api/track");
    xmlwriter.writeCharacters("Speed Freak");
    xmlwriter.writeEndElement();
    xmlwriter.writeStartElement("time");
    xmlwriter.writeCharacters(QDateTime::currentDateTime().toString());
    xmlwriter.writeEndElement();
    xmlwriter.writeEndElement();    //metadata

    xmlwriter.writeStartElement("trk");
    xmlwriter.writeStartElement("name");
    xmlwriter.writeCharacters("Example Track");
    xmlwriter.writeEndElement();
    xmlwriter.writeStartElement("trkseg");
    for(int i = 0; i < counter; i++)
    {
        xmlwriter.writeStartElement("trkpt");
        tmp = *ptrValue;
        ptrValue++;
        xmlwriter.writeAttribute("lat", QString::number(tmp));    //gpspoints[i][0]
        tmp = *ptrValue;
        ptrValue++;
        xmlwriter.writeAttribute("lon", QString::number(tmp));    //gpspoints[i][1]
        xmlwriter.writeStartElement("ele");
        tmp = *ptrValue;
        ptrValue++;
        xmlwriter.writeCharacters(QString::number(tmp));          //gpspoints[i][2]
        xmlwriter.writeEndElement();
        xmlwriter.writeStartElement("speed");
        tmp = *ptrValue;
        ptrValue++;
        xmlwriter.writeCharacters(QString::number(tmp));          //gpspoints[i][3]
        xmlwriter.writeEndElement();
        xmlwriter.writeEndElement();    //trkpt
    }
    xmlwriter.writeEndElement();        //trkseg
    xmlwriter.writeEndElement();        //trk
    xmlwriter.writeEndElement();        //gpx
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
    //writeItems();
    serverWritesXml();
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
  *@brief A temp function during development, used to create a "serverfile".
  */
void XmlWriter::serverWritesXml()
{
    //Write categories
    xmlwriter.writeStartElement("categories");

    xmlwriter.writeStartElement("category");
    xmlwriter.writeCharacters("acceleration-0-10");
    xmlwriter.writeEndElement();

    xmlwriter.writeStartElement("category");
    xmlwriter.writeCharacters("acceleration-0-40");
    xmlwriter.writeEndElement();

    xmlwriter.writeStartElement("category");
    xmlwriter.writeCharacters("acceleration-0-100");
    xmlwriter.writeEndElement();

    xmlwriter.writeEndElement();
}
