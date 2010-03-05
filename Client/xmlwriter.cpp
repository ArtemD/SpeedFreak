#include <QtGui>
#include <QNetworkRequest>
//#include <QNetworkReply>
#include <QIODevice>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QApplication>
#include "xmlwriter.h"


/**
  *@brief Constructor, connects object to GUI
  *@param Pointer to carmainwindow, which is temporarily used during development
  */
XmlWriter::XmlWriter(Ui_CarMainWindow* myMainWindow)
{
    ui = myMainWindow;
}


/**
  *@brief Destructor
  */
XmlWriter::~XmlWriter()
{

}

/**
  *@brief Opens and closes a file, when xml information is written into a file,
  *and passes file to writeXmlFile()
  *@note Partly harcoded and commented for git.
  *@todo Replace hardcoced filename and GUI elements to finally used widgets.
  */
void XmlWriter::writeXml()
{
    QString filename = "xmlfile.xml";
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "_xmlWrite fail";
        return;
    }

    writeXmlFile(&file);
    file.close();
}

/**
  *@brief Writes general xml information.
  *Calls other functions to insert login and result information.
  *@todo Check API connection to QBuffer, when Speed Freek network client has been written.
  */
bool XmlWriter::writeXmlFile(QIODevice *device)
//bool XmlWriter::writeXmlFile(QBuffer *device)
{
    xmlwriter.setDevice(device);
    xmlwriter.writeStartDocument();
    xmlwriter.writeStartElement("xml");
    xmlwriter.writeAttribute("version", "1.0");
    writeRegister();
    writeItems();
    xmlwriter.writeEndDocument();

    return true;
}

/**
  *@brief Writes Speed Freek application specific items as tags and contents.
  *@brief Results of speed/ direction/ acceleration into QMap are calculated elsewhere
  *@todo Replace hardcoced user, password and email to finally used GUI elements.
  */
void XmlWriter::writeRegister()
{
    xmlwriter.writeStartElement("user");

    xmlwriter.writeStartElement("login");
    xmlwriter.writeCharacters("test123");
    xmlwriter.writeEndElement();

    xmlwriter.writeStartElement("password");
    xmlwriter.writeCharacters("thisisaveryinsecurepassword");
    xmlwriter.writeEndElement();

    //Is this neacessary when sending results
    xmlwriter.writeStartElement("email");
    xmlwriter.writeCharacters("test@example.com");
    xmlwriter.writeEndElement();

    xmlwriter.writeEndElement();
}

/**
  *@brief Writes Speed Freek results items as tags and contents.
  *@brief Results of speed/ direction/ acceleration into QMap are calculated elsewhere
  *@todo Consider looping of writing QMap values.
  *@todo Replace hardcoced names to finally used values.
  */
void XmlWriter::writeItems()
{
    //During development
    this->fillResultmap();

    xmlwriter.writeStartElement("result");
    xmlwriter.writeAttribute("value", QString::number(resultmap.value("speed")));
    xmlwriter.writeAttribute("unit", "seconds");
    xmlwriter.writeAttribute("date", QDateTime::currentDateTime().toString());
    xmlwriter.writeEndElement();
}


/**
  *@brief A temp function during development, used until real QMap available.
  */
void XmlWriter::fillResultmap()
{
    resultmap["acceleration"] = 9;
    resultmap["speed"] = 48;
    resultmap["distance"] = 600;
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
    xmlwriter.writeAttribute("category", "acceleration-0-100");
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
