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
    int trackInd;

private:
    QXmlStreamWriter xmlwriter;

public slots:
    void writeRegistering(QBuffer *netbuf, QString usr, QString psswd, QString email);
    void writeResult(QBuffer *netbuf);
    void writeGpsTrack(QBuffer *netbuf, double *ptrTable, int counter);
    bool writeXmlFile(QIODevice *device);
    //void writeXml(QString usr, QString psswd, QString email);
    void writeXml();
    void writeItems();
    void serverWritesXml();
};

#endif // XMLWRITER_H

