#include <QString>
#include <QMessageBox>
#include "httpclient.h"
#include "carmainwindow.h"


/**
  *@brief Constructor, connects object to GUI
  *@param Pointer to carmainwindow, which is temporarily used during development
  */
HttpClient::HttpClient(CarMainWindow *myCarw)
{
    myMainw = myCarw;
    netManager = new QNetworkAccessManager();
    myXmlwriter = new XmlWriter();
    myXmlreader = new XmlReader();
}

/**
  *@brief Destructor
  */
HttpClient::~HttpClient()
{

}

/**
  *@brief Sends registration information to the server in xml format.
  *Reads user name, password and emaol address from resuldialogs internal variables.
  *@todo Replace msg box with better reaction to server`s responce.
  */
void HttpClient::requestRegistration()
{
    qDebug() << "_requestRegistration" ;
    qDebug() <<  myMainw->myRegistration->getUserName() << "+" <<  myMainw->myRegistration->getPassword() << "+" <<  myMainw->myRegistration->getEmail();

    QBuffer *regbuffer = new QBuffer();
    QUrl qurl("http://api.speedfreak-app.com/api/register");
    QNetworkRequest request(qurl);
    qDebug() << qurl.toString();
    QNetworkReply *currentDownload;

    regbuffer->open(QBuffer::ReadWrite);
    myXmlwriter->writeRegistering(regbuffer,
                       myMainw->myRegistration->getUserName(),
                       myMainw->myRegistration->getPassword(),
                       myMainw->myRegistration->getEmail());
    qDebug() << "carmainwindow: regbuffer->data(): " << regbuffer->data();

    currentDownload = netManager->post(request, ("xml=" + regbuffer->data()));
    connect(currentDownload,SIGNAL(finished()),this,SLOT(ackOfRegistration()));
    //connect(currentDownload,SIGNAL(error(QNetworkReply::NetworkError)),myMainw,SLOT(errorFromServer(QNetworkReply::NetworkError)));

    regbuffer->close();
}

/**
  *@brief Sends result(s) to the server in xml format.
  *Send authentication information in the header.
  */
void HttpClient::sendResultXml(QString category)
{
    qDebug() << "_sendResultXml";

    QBuffer *xmlbuffer = new QBuffer();

    QUrl qurl("http://api.speedfreak-app.com/api/update/" + category);
    qDebug() << qurl.toString();
    QNetworkRequest request(qurl);
    QNetworkReply *currentDownload;

    xmlbuffer->open(QBuffer::ReadWrite);
    myXmlwriter->writeResult(xmlbuffer);
    qDebug() << "carmainwindow: xmlbuffer->data(): " << xmlbuffer->data();

    QString credentials = myMainw->myLogin->getUserName() + ":" + myMainw->myLogin->getPassword();
    credentials = "Basic " + credentials.toAscii().toBase64();
    request.setRawHeader(QByteArray("Authorization"),credentials.toAscii());

    currentDownload = netManager->post(request, ("xml=" + xmlbuffer->data()));
    connect(currentDownload,SIGNAL(finished()),this,SLOT(ackOfResult()));
    //connect(currentDownload,SIGNAL(error(QNetworkReply::NetworkError)),myMainw,SLOT(errorFromServer(QNetworkReply::NetworkError)));

    xmlbuffer->close();
}

/**
  *@brief Sends route to the server in xml format.
  *Send authentication information in the header.
  *@todo Check destination URL.
  */
void HttpClient::sendRouteXml()
{
    qDebug() << "_sendResultXml";

    QBuffer *xmlbuffer = new QBuffer();

    QUrl qurl("http://api.speedfreak-app.com/api/update/route");
    qDebug() << qurl.toString();
    QNetworkRequest request(qurl);
    QNetworkReply *currentDownload;

    xmlbuffer->open(QBuffer::ReadWrite);
    myXmlwriter->writeGpsTrack(xmlbuffer, myMainw->gpsData->getGpsDataArray(), myMainw->gpsData->getRoundCounter());
    qDebug() << "carmainwindow: xmlbuffer->data(): " << xmlbuffer->data();

    QString credentials = myMainw->myLogin->getUserName() + ":" + myMainw->myLogin->getPassword();
    credentials = "Basic " + credentials.toAscii().toBase64();
    request.setRawHeader(QByteArray("Authorization"),credentials.toAscii());

    currentDownload = netManager->post(request, ("xml=" + xmlbuffer->data()));
    connect(currentDownload,SIGNAL(finished()),this,SLOT(ackOfRoute()));
    //connect(currentDownload,SIGNAL(error(QNetworkReply::NetworkError)),myMainw,SLOT(errorFromServer(QNetworkReply::NetworkError)));

    xmlbuffer->close();
}

/**
  *@brief Request the Top10List of certain category from the server.
  *Send authentication information in the header.
  *@param Category of results.
  *@param Limit, the number of results.
  */
void HttpClient::requestTopList(QString category, QString limit)
{
    qDebug() << "_requestTopList" ;

    QString urlBase = "http://api.speedfreak-app.com/api/results/";
    QUrl qurl(urlBase + category + "/" + limit);
    qDebug() << qurl.toString();
    QNetworkRequest request(qurl);
    QNetworkReply *currentDownload;

    QString credentials = myMainw->myLogin->getUserName() + ":" + myMainw->myLogin->getPassword();
    credentials = "Basic " + credentials.toAscii().toBase64();
    request.setRawHeader(QByteArray("Authorization"),credentials.toAscii());

    currentDownload = netManager->post(request, ("data=" ));
    connect(currentDownload,SIGNAL(finished()),this,SLOT(ackOfToplist()));
    //connect(currentDownload,SIGNAL(error(QNetworkReply::NetworkError)),myMainw,SLOT(errorFromServer(QNetworkReply::NetworkError)));
}


/**
  *@brief Request categories list from the server.
  *Send authentication information in the header.
  */
void HttpClient::requestCategories()
{
    qDebug() << "_requestCategories" ;

    QUrl qurl("http://api.speedfreak-app.com/api/categories/");
    qDebug() << qurl.toString();
    QNetworkRequest request(qurl);
    QNetworkReply *currentDownload;

    QString credentials = myMainw->myLogin->getUserName() + ":" + myMainw->myLogin->getPassword();
    credentials = "Basic " + credentials.toAscii().toBase64();
    request.setRawHeader(QByteArray("Authorization"),credentials.toAscii());

    currentDownload = netManager->post(request, ("data=" ));
    connect(currentDownload,SIGNAL(finished()),this,SLOT(ackOfCategories()));
    //connect(currentDownload,SIGNAL(error(QNetworkReply::NetworkError)),myMainw,SLOT(errorFromServer(QNetworkReply::NetworkError)));
}


/**
  *@brief Check that username and password exist on the server.
  *Send authentication information in the header.
  */
void HttpClient::checkLogin()
{
    qDebug() << "_checkLogin";

    QUrl qurl("http://api.speedfreak-app.com/api/login/");
    qDebug() << qurl.toString();
    QNetworkRequest request(qurl);
    QNetworkReply *currentDownload;

    QString credentials = myMainw->myLogin->getUserName() + ":" + myMainw->myLogin->getPassword();
    credentials = "Basic " + credentials.toAscii().toBase64();
    request.setRawHeader(QByteArray("Authorization"),credentials.toAscii());

    currentDownload = netManager->post(request, ("data=" ));
    connect(currentDownload,SIGNAL(finished()),this,SLOT(ackOfLogin()));
    //connect(currentDownload,SIGNAL(error(QNetworkReply::NetworkError)),myMainw,SLOT(errorFromServer(QNetworkReply::NetworkError)));
}


/**
  *@brief React to servers responce after result has been sent.
  *@todo Implement consequencies of reply.
  */
void HttpClient::ackOfResult()
{
    qDebug() << "_ackOfResult";

    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QNetworkReply::NetworkError errorcode;
    errorcode = reply->error();
    if(errorcode != 0) {
        qDebug() <<  "errorcode:" << errorcode << reply->errorString();
        QMessageBox::about(myMainw, "Server reply to result sending ",reply->errorString());
    }
    else {
        qDebug() << "errorcode:" << errorcode << reply->errorString();
        QMessageBox::about(myMainw, "Server reply to result sending", "Result received " + reply->readAll());
    }
}

/**
  *@brief React to servers responce after result has been sent.
  *@todo Implement consequencies of reply.
  */
void HttpClient::ackOfRoute()
{
    qDebug() << "_ackOfRoute";

    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QNetworkReply::NetworkError errorcode;
    errorcode = reply->error();
    if(errorcode != 0) {
        qDebug() <<  "errorcode:" << errorcode << reply->errorString();
        QMessageBox::about(myMainw, "Server reply to route sending ",reply->errorString());
    }
    else {
        qDebug() << "errorcode:" << errorcode << reply->errorString();
        QMessageBox::about(myMainw, "Server reply to route sending", "Route received " + reply->readAll());
    }
}

/**
  *@brief React to servers responce after registration has been sent.
  *@todo Implement consequencies of reply.
  */
void HttpClient::ackOfRegistration()
{
    qDebug() << "_ackOfRegistration";

    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QNetworkReply::NetworkError errorcode;
    errorcode = reply->error();
    if(errorcode != 0) {
        qDebug() <<  "errorcode:" << errorcode << reply->errorString();
        QMessageBox::about(myMainw, "Server reply to registration",reply->readAll());
    }
    else {
        qDebug() << "errorcode=0" << errorcode << reply->errorString();
        QMessageBox::about(myMainw, "Server reply to registration", "User registration " + reply->readAll());
    }

}


/**
  *@brief React to servers responce after request for categories has been sent.
  */
void HttpClient::ackOfCategories()
{
    qDebug() << "_ackOfCategories";

    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    myXmlreader->xmlReadCategories(reply);

    QNetworkReply::NetworkError errorcode;
    errorcode = reply->error();
    if(errorcode != 0) {
        qDebug() <<  "errorcode:" << errorcode << reply->errorString();
        QMessageBox::about(myMainw, "Server reply to requesting categories",reply->errorString());
    }
    else {
        qDebug() <<  "errorcode:" << errorcode << reply->errorString();
        QMessageBox::about(myMainw, "Server reply to requesting categories ", "OK");
    }

}


/**
  *@brief React to servers responce after request of TopList in certain category has been sent.
  *@todo Implement routing reply`s contents to UI.
  */
void HttpClient::ackOfLogin()
{
    qDebug() << "_ackOffLogin";

    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QNetworkReply::NetworkError errorcode;
    errorcode = reply->error();
    if(errorcode != 0) {
        qDebug() <<  "errorcode:" << errorcode << reply->errorString();
        QMessageBox::about(myMainw, "Server does not recognize your username. Please registrate.",reply->errorString());
    }
    else {
        qDebug() <<  "errorcode:" << errorcode << reply->errorString();
        QMessageBox::about(myMainw, "Server reply to login", "User login " + reply->readAll());
    }
}


/**
  *@brief Reports errors, when server has sent error signal.
  */
void HttpClient::errorFromServer(QNetworkReply::NetworkError errorcode)
{
    qDebug() << "_errorFromServer";

    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if(errorcode != 0) {
        qDebug() <<  "errorcode:" << errorcode;
        //Note that errors are already reported on other ach-functions for server communication
        //QMessageBox::about(myMainw, "Server reported an error", reply->errorString());
    }
    else {
        qDebug() <<  "errorcode:" << errorcode << reply->errorString();
        qDebug() << reply->readAll();
    }

}


/**
  *@brief React to servers responce after request of TopList in certain category has been sent.
  *@todo Implement routing reply`s contents to UI.
  */
void HttpClient::ackOfToplist()
{
    qDebug() << "_ackOfToplist";

    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    myXmlreader->xmlReadTop10Results(reply);

    QNetworkReply::NetworkError errorcode;
    errorcode = reply->error();
    if(errorcode != 0) {
        qDebug() <<  "errorcode:" << errorcode << reply->errorString();
        QMessageBox::about(myMainw, "Server reply to requesting top 10 list",reply->errorString());
    }
    else {
        qDebug() <<  "errorcode:" << errorcode << reply->errorString();
        QMessageBox::about(myMainw, "Server reply to requesting top 10 list", "OK " + reply->readAll());
    }

}

