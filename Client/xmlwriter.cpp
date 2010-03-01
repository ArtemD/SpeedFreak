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


/*! @brief Constructor, connects object to GUI
 */
XmlWriter::XmlWriter(Ui_MainWindow* myMainWindow)
{
    ui = myMainWindow;
}


/*! @brief Destructor
  */
XmlWriter::~XmlWriter()
{

}

/*! @brief Opens and closes a file, when xml information is written into a file,
  * and passes file to writeXmlFile()
  * @note Partly harcoded and commented for git.
  * @todo Replace hardcoced filename and GUI elements to finally used widgets.
  */
void XmlWriter::xmlWrite()
{
    //QString filename = ui->lineEditFile->text();
    QString filename = "xmlfile.xml";
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        /*QMessageBox::warning(this->ui->centralWidget, tr("QXmlStream Bookmarks"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(filename)
                             .arg(file.errorString()));
                             */
        qDebug() << "_xmlWrite fail";
        return;
    }

    writeXmlFile(&file);
    file.close();
}

/*! @brief Writes general xml information.
  * @todo Check API connection to QBuffer, when Speed Freek network client has been written.
  */
bool XmlWriter::writeXmlFile(QIODevice *device)
//bool XmlWriter::writeXmlFile(QBuffer *device)
{
    xmlwriter.setDevice(device);
    xmlwriter.writeStartDocument();
    xmlwriter.writeDTD("<!DOCTYPE xml>");
    xmlwriter.writeStartElement("xml");
    xmlwriter.writeAttribute("version", "1.0");
    writeItems();
    xmlwriter.writeEndDocument();

    return true;
}

/*! @brief Writes Speed Freek application specific items as tags and contents.
  * @brief Results of speed/ direction/ acceleration into QMap are calculated elsewhere
  * @todo Consider looping of writing QMap values.
  * @todo Replace hardcoced names to finally used GUI elements.
  */
void XmlWriter::writeItems()
{
    //xmlwriter.writeCharacters(ui->lineEditPlace->text());
    //Temporarily:
    xmlwriter.writeStartElement("place");
    xmlwriter.writeCharacters("rallirata");
    xmlwriter.writeEndElement();

    xmlwriter.writeStartElement("date");
    xmlwriter.writeCharacters(QDate::currentDate().toString());
    xmlwriter.writeEndElement();

    xmlwriter.writeStartElement("time");
    xmlwriter.writeCharacters(QTime::currentTime().toString());
    xmlwriter.writeEndElement();

    /* Or combined:
    xmlwriter.writeStartElement("datetime");
    xmlwriter.writeCharacters(QDateTime::currentDateTime().toString());
    xmlwriter.writeEndElement(); */

    xmlwriter.writeStartElement("result");
    xmlwriter.writeStartElement("speed");
    xmlwriter.writeAttribute("value", QString::number(resultmap.value("speed")));
    xmlwriter.writeAttribute("unit", "m/s");
    xmlwriter.writeEndElement();
    xmlwriter.writeStartElement("distance");
    xmlwriter.writeAttribute("value", QString::number(resultmap.value("distance")));
    xmlwriter.writeAttribute("unit", "m");
    xmlwriter.writeEndElement();
    xmlwriter.writeStartElement("acceleration");
    xmlwriter.writeAttribute("value", QString::number(resultmap.value("acceleration")));
    xmlwriter.writeAttribute("unit", "m/s2");
    xmlwriter.writeEndElement();
    xmlwriter.writeEndElement();    //result
    //or:
    //xmlwriter.writeTextElement("speed", QString::number(resultmap.value("speed")) + " m/s");
    //xmlwriter.writeTextElement("distance", QString::number(resultmap.value("distance")) + " m");
    //xmlwriter.writeTextElement("acceleration", QString::number(resultmap.value("acceleration")) + " m/s2");
}

/*! @brief Initializes QMap by zeroing values for a new measurement.
  */
void XmlWriter::initResultmap()
{
    resultmap["acceleration"] = 0;
    resultmap["speed"] = 0;
    resultmap["distance"] = 0;
}

/*! @brief A temp function during development, used until real QMap available.
  */
void XmlWriter::fillResultmap()
{
    resultmap["acceleration"] = 9;
    resultmap["speed"] = 48;
    resultmap["distance"] = 600;
}
