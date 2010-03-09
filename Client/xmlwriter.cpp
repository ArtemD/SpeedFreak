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
    tmpvalue = 10;
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
    xmlwriter.writeAttribute("unit", "seconds");
    xmlwriter.writeAttribute("date", QDateTime::currentDateTime().toString());
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
void XmlWriter::writeXml(QString usr, QString psswd, QString email)
{
    QString filename = "xmlfile.xml";
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
  *@brief A temp function during development, used to create a "serverfile".
  */
void XmlWriter::serverWritesTop()
{
    int i = 0;
    int n = 5;

    /* Server sends to client */
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
}
