/*
 * Xml writer
 *
 * @author     Tiina Kivilinna-Korhola
 * @copyright  (c) 2010 Speed Freak team
 * license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QXmlStreamWriter>
#include <QBuffer>
#include <QtGui>
#include <QNetworkRequest>
#include <QIODevice>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QByteArray>
#include <QApplication>


class XmlWriter : public QObject {
    Q_OBJECT
public:
    XmlWriter();
    ~XmlWriter();

private:
    QXmlStreamWriter xmlwriter;

public slots:
    void writeRegistering(QBuffer *netbuf, QString usr, QString psswd, QString email);
    void writeResult(QBuffer *netbuf, double result);
    void writeGpsTrack(QBuffer *netbuf, int counter, int start, int stop, int lat, int lon, int alt, int speed, int time);
    bool writeXmlFile(QIODevice *device);
    //void writeXml(QString usr, QString psswd, QString email);
    void writeXml();
    void writeItems();
};

#endif // XMLWRITER_H

