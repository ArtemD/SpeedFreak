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


class XmlWriter : public QObject
{
public:
    XmlWriter();
    ~XmlWriter();
    int tmpvalue;

private:
    QXmlStreamWriter xmlwriter;

public slots:
    void writeRegistering(QBuffer *netbuf, QString usr, QString psswd, QString email);
    void writeResult(QBuffer *netbuf);
    bool writeXmlFile(QIODevice *device);
    void writeXml(QString usr, QString psswd, QString email);
    void writeItems();
    void serverWritesTop();

};

#endif // XMLWRITER_H
