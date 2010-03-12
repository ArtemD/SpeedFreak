/*
 * Parse xml file
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @author     Tiina Kivilinna-Korhola <tiina.kivilinna-korhola@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef XMLREADER_H
#define XMLREADER_H

#include <QXmlStreamReader>
#include <QStringList>
#include <QNetworkReply>

class XmlReader : public QObject
{
public:
    XmlReader();
    ~XmlReader();

private:
    QXmlStreamReader xmlreader;
    QStringList top10List;              // Next 4 to be removed. Categorylist now in own class.
    QStringList categoryList;
    QString top10AccelerationList;
    QString top10SpeedList;
    QString top10GforceList;

    QXmlStreamAttributes attr;
    QString category;
    QString unit;
    QString description;
    QString position;
    QString user;
    QString value;

public slots:
    void xmlReadTop10Results(QNetworkReply *device);
    void xmlReadCategories(QNetworkReply *device);
    //void xmlReadCategories(QIODevice *device);
    void xmlShow();
};

#endif // XMLREADER_H
