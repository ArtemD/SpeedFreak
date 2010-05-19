/*
 * Http client Connects application to server.
 *
 * @author      Tiina Kivilinna-Korhola
 * @author      Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
 * @author      Toni Jussila 	<toni.jussila@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * license      http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "xmlwriter.h"
#include "xmlreader.h"
class MainWindow;



class HttpClient : public QObject {
    Q_OBJECT
public:
    HttpClient(MainWindow *myCarw);
    ~HttpClient();
    XmlWriter *myXmlwriter;
    XmlReader *myXmlreader;

private:
    MainWindow *myMainw;
    QNetworkAccessManager *netManager;

signals:
    void loginOK();

public slots:
    void requestRegistration();
    void checkLogin();
    void sendResultXml(QString category, double result);
    void sendRouteXml(QString oldName, QString newName, int i);
    void requestTopList(QString category, QString limit);
    void requestCategories();
    void ackOfResult();
    void ackOfRoute();
    void ackOfRegistration();
    void ackOfCategories();
    void ackOfToplist();
    void ackOfLogin();
    bool ackOfProfile();
    void ackOfSendingPicture();
    void errorFromServer(QNetworkReply::NetworkError);
    void sendProfileXml();

};

#endif // HTTPCLIENT_H
