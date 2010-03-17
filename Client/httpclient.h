/*
 * Http client Connects application to server.
 *
 * @author     Tiina Kivilinna-Korhola
 * @copyright  (c) 2010 Speed Freak team
 * license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "xmlwriter.h"
#include "xmlreader.h"
class CarMainWindow;



class HttpClient : public QObject
{
    Q_OBJECT
public:
    HttpClient(CarMainWindow *myCarw);
    ~HttpClient();
    XmlWriter *myXmlwriter;
    XmlReader *myXmlreader;

private:
    CarMainWindow *myMainw;
    QNetworkAccessManager *netManager;
    //XmlWriter *myXmlwriter;
    //XmlReader *myXmlreader;

public slots:
    void requestRegistration();
    void checkLogin();
    void sendResultXml();
    void requestTopList(QString category, QString limit);
    void requestCategories();
    void ackOfResult();
    void ackOfRegistration();
    void ackOfCategories();
    void ackOfToplist();
    void ackOfLogin();
    void errorFromServer(QNetworkReply::NetworkError);

};

#endif // HTTPCLIENT_H
