#include <QtGui>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QIODevice>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QApplication>
#include "xmlreader.h"


/*! @brief Constructor, connects object to GUI
 */
XmlReader::XmlReader(Ui_MainWindow* myMainWindow)
{
    ui = myMainWindow;
}

/*! @brief Destructor
  */
XmlReader::~XmlReader()
{

}

QString XmlReader::errorString() const
{
    return QObject::tr("%1\nLine %2, column %3")
            .arg(xmlreader.errorString())
            .arg(xmlreader.lineNumber())
            .arg(xmlreader.columnNumber());
}


/*! @brief parsing xml file that is sent by server over network.
  * Shows received information on screen and parsed information on command line.
  * @note Partly commented for git.
  * @todo (Development: Seems to omit element tags and some values when reading from QFile. Why? This used
  * earlier with QNetworkReply printed all xml contents.)
  * @todo Remove command line output and use final GUI widget names.
  * @todo Replace using of QFile to QNetworkReply.
  */
void XmlReader::xmlRead(QIODevice *device)
//void XmlReader::xmlRead(QNetworkReply *device)
{
    qDebug() << "_xmlRead";

    xmlreader.addData(device->readAll());
    //Or: View webpage contents on textEdit by adding all data to xml stream reader,
    //since readAll() empties the buffer
    /*QByteArray readAllArr = device->readAll();
    ui->textEditXml->append(readAllArr);
    xmlreader.addData(readAllArr);*/

    //Go trough the xml document
    while(!xmlreader.atEnd())
    {
        //Read next node
        xmlreader.readNext();
        //Check if this element is starting element
        if(xmlreader.isStartElement())
        {
            if(xmlreader.name() == "place")
            {
                qDebug() << xmlreader.name();
            }
            if(xmlreader.name() == "date")
            {
                 qDebug() << xmlreader.name();
            }
            if(xmlreader.name() == "time")
            {
                 qDebug() << xmlreader.name();
            }
            if(xmlreader.name() == "result")
            {
                //Two consequent start elements
                if(xmlreader.readNextStartElement())
                {
                    if(xmlreader.name() == "speed")
                    {
                    QString speed;
                    QXmlStreamAttributes attr = xmlreader.attributes();
                    speed = (attr.value("value").toString() + " " + attr.value("unit").toString());
                    //ui->lineEditSpeed->setText(speed);
                    qDebug() << xmlreader.name() << speed;
                    }
                }
            }
            if(xmlreader.name() == "distance")
            {
                QString distance;
                QXmlStreamAttributes attr = xmlreader.attributes();
                distance = (attr.value("value").toString() + " " + attr.value("unit").toString());
                //ui->lineEditDist->setText(distance);
                qDebug() << xmlreader.name() << distance;
            }
            if(xmlreader.name() == "acceleration")
            {
                QString acceleration;
                QXmlStreamAttributes attr = xmlreader.attributes();
                acceleration = (attr.value("value").toString()+ " " + attr.value("unit").toString());
                //ui->lineEditAccel->setText(acceleration);
                qDebug() << xmlreader.name() << acceleration;
            }
        }
    }
}

/*! @brief A function used tmp in development.
  * @note Partly harcoded and commented for git.
  */
void XmlReader::xmlShow()
{
    //QString filename = ui->lineEditFile->text();
    QString filename = "xmlfile.xml";
    QFile file(filename);

    if (!file.open(QFile::ReadOnly))
    {
        /*QMessageBox::warning(this->ui->centralWidget,
                                tr("QXmlStream Bookmarks"),
                                tr("Cannot write file %1:\n%2.")
                                .arg(file.fileName())
                                .arg(file.errorString()));*/
        qDebug() << "_xmlShow fail";
        return;
    }

    xmlRead(&file);

    file.close();
}

