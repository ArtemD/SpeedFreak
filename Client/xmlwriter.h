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
    int tmpvalue;
    typedef struct {
            double time;
            double latitude;
            double longitude;
            double altitude;
            double speed;
            double track;
        } gpsPoint;
    gpsPoint trackTable[100];
    gpsPoint analyzeTable[100];
    int trackInd;

private:
    QXmlStreamWriter xmlwriter;

public slots:
    void writeRegistering(QBuffer *netbuf, QString usr, QString psswd, QString email);
    void writeResult(QBuffer *netbuf);
    bool writeXmlFile(QIODevice *device);
    //void writeXml(QString usr, QString psswd, QString email);
    void writeXml();
    void writeItems();
    void serverWritesXml();
    void writeGpsTrack(int startInd, int stopInd);
    void initPointTable(gpsPoint *table, int count, double add1, int add2, int add3);
    void analyzeGpsData();
};

#endif // XMLWRITER_H

