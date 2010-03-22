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
#include "categorylist.h"

class XmlReader : public QObject {
    Q_OBJECT
public:
    XmlReader();
    ~XmlReader();
    CategoryList *myCategoryList;

private:
    QXmlStreamReader xmlreader;

    QXmlStreamAttributes attr;
    QString category;
    QString unit;
    QString date;
    QString position;
    QString user;
    QString value;

signals:
    void receivedCategoryList();
    void receivedTop10List();

public slots:
    void xmlReadTop10Results(QNetworkReply *device);
    void xmlReadCategories(QNetworkReply *device);
    //void xmlReadCategories(QIODevice *device);
    void xmlShow();
};

#endif // XMLREADER_H
