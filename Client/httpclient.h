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


class HttpClient : public QObject
{
    Q_OBJECT
public:
    HttpClient();
    ~HttpClient();

private:
    QNetworkAccessManager *netManager;

public slots:

};

#endif // HTTPCLIENT_H
