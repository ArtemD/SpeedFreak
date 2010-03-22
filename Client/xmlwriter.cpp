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
    trackInd = 0;
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
  *@param Starting index of gps results table.
  *@param Ending index of gps results table.
  *@todo Connect to real values.
  *@todo Decide suitable parameters.
  */
void XmlWriter::writeGpsTrack(int startInd, int stopInd)
{
    qDebug() << "_writeGpsTrack";
    analyzeGpsData();

    int i = 0;

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
    for(i = startInd; i < (stopInd - startInd); i++) {
        xmlwriter.writeStartElement("trkpt");
        xmlwriter.writeAttribute("lat", QString::number(trackTable[i].latitude));
        xmlwriter.writeAttribute("lon", QString::number(trackTable[i].longitude));
        xmlwriter.writeStartElement("ele");
        xmlwriter.writeCharacters(QString::number(trackTable[i].altitude));
        xmlwriter.writeEndElement();
        xmlwriter.writeStartElement("time");
        xmlwriter.writeCharacters(QString::number(trackTable[i].time));
        xmlwriter.writeEndElement();
        xmlwriter.writeStartElement("speed");
        xmlwriter.writeCharacters(QString::number(trackTable[i].speed));
        xmlwriter.writeEndElement();
        xmlwriter.writeStartElement("track");
        xmlwriter.writeCharacters(QString::number(trackTable[i].track));
        xmlwriter.writeEndElement();
        xmlwriter.writeEndElement();    //trkpt
    }
    xmlwriter.writeEndElement();    //trkseg
    xmlwriter.writeEndElement();    //trk
    xmlwriter.writeEndElement();    //gpx
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
    //serverWritesXml();
    writeGpsTrack(0, 16);
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
    /* Server sends to client */
    /*
    int i = 0;
    int n = 5;

    //Write top 10 Results
    xmlwriter.writeStartElement("results");
    xmlwriter.writeAttribute("category", "acceleration-0-40");
    xmlwriter.writeAttribute("unit", "seconds");
    xmlwriter.writeAttribute("description", "Acceleration from 0 to 100 km/h");

    for (i = 0; i < n; i++) {
        xmlwriter.writeStartElement("result");
        xmlwriter.writeAttribute("position", QString::number(i));
        xmlwriter.writeAttribute("user", "test123");
        xmlwriter.writeAttribute("date", QDateTime::currentDateTime().toString());
        xmlwriter.writeAttribute("value", QString::number(i+i+1));
        xmlwriter.writeEndElement();
    }
    */
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


/**
  *@brief A temp function during development, used to create data for drawing route and for server.
  */
void XmlWriter::analyzeGpsData()
{
    qDebug() << "_analyzeGpsData";

    double startTime;
    int tableSize = 0;

    qDebug() << "sizeof(analyzeTable)" << sizeof(analyzeTable);
    tableSize = 16;

    for(int i = 1; i < tableSize; i++)
    {
        //example of one feature whose consequent values are compared and saved if they differentiate too much
        if(analyzeTable[i].speed < (analyzeTable[i-1].speed - 1) ||
           analyzeTable[i].speed > (analyzeTable[i-1].speed + 1) )
        {
           trackTable[trackInd] = analyzeTable[i];
           trackInd++;
           qDebug() << "trackTable[trackInd].speed" << trackTable[trackInd].speed;
        }
    }
}

void XmlWriter::initPointTable(gpsPoint *table, int count, double add1, int add2, int add3)
{
    qDebug() << "_initPointTable";

    int i = 1;
    int j = 0;

    table[0].latitude = 67.00;
    table[0].longitude = 27.50;
    table[0].altitude = 7.00;
    table[0].speed = 0;
    table[0].time = 0;

    for(j = 0; j < count; j++)
    {
        table[i].latitude = table[i-1].latitude + add1;
        //table[i].longitude = table[i-1].longitude + add1;
        table[i].altitude = table[i-1].altitude + add1;
        table[i].speed = table[i-1].speed + add2;
        table[i].track = table[i-1].track + 1;
        table[i].time = table[i-1].time + add3;
        i++;
    }
    for(j = 0; j < count; j++)
    {
        //table[i].latitude = table[i-1].latitude + add1;
        table[i].longitude = table[i-1].longitude + add1;
        table[i].altitude = table[i-1].altitude -add1;
        table[i].speed = table[i-1].speed + add2;
        table[i].track = table[i-1].track + 1;
        table[i].time = table[i-1].time + add3;
        i++;
    }
    for(j = 0; j < count; j++)
    {
        table[i].latitude = table[i-1].latitude - add1;
        //table[i].longitude = table[i-1].longitude + add1;
        table[i].altitude = table[i-1].altitude + add1;
        table[i].speed = table[i-1].speed - add2;
        table[i].track = table[i-1].track - 1;
        table[i].time = table[i-1].time + add3;
        i++;
    }
    for(j = 0; j < count; j++)
    {
        //table[i].latitude = table[i-1].latitude + add1;
        table[i].longitude = table[i-1].longitude - add1;
        table[i].altitude = table[i-1].altitude - add1;
        table[i].speed = table[i-1].speed - add2;
        table[i].track = table[i-1].track - 1;
        table[i].time = table[i-1].time + add3;
        i++;
    }
}


