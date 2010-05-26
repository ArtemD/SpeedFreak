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

class ProfileDialog;

class XmlReader : public QObject {
    Q_OBJECT
public:
    XmlReader();
    ~XmlReader();
    CategoryList *myCategoryList;
    void xmlReadProfile(QIODevice *device, ProfileDialog *profileDialog);
    QStringList *usersList;

private:
    QXmlStreamReader xmlreader;
    QXmlStreamAttributes attr;
    ProfileDialog *profile;
    QString category;
    QString unit;
    QString date;
    QString position;
    QString user;
    QString value;
    QString description;
    QStringList *usersInfo;

signals:
    void receivedCategoryList();
    void receivedTop10List();
    void userInfo(QStringList *userInfo);

public slots:
    void xmlReadTop10Results(QNetworkReply *device, QString userName);
    void xmlReadCategories(QNetworkReply *device);
    //void xmlReadCategories(QIODevice *device);
    void xmlShow();

    //void xmlReadUserInfo(QIODevice *device);
    void xmlReadUserInfo(QNetworkReply *device);
    void xmlReadUsers(QNetworkReply *device);
    //void xmlReadUsers(QIODevice *device);
};

#endif // XMLREADER_H
