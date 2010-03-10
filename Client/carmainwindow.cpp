/*
 * CarMainWindow main class
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @author     Janne Änäkkälä <janne.anakkala@fudeco.com>
 * @author     Tiina Kivilinna-Korhola <tiina.kivilinna-korhola@fudeco.com>
 * @author     Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "carmainwindow.h"
#include "math.h"

/**
  *Constructor of this class.
  *@param QWidget pointer to parent object. By default the value is NULL.
  */
CarMainWindow::CarMainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::CarMainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentWidget(this->ui->StartTab);
    //result = new ResultDialog();
    //measure = new MeasureDialog();
    xmlreader = new XmlReader();

    initComboBoxStartTabUnits();
    initListViewStartTabAccelerationCategories();

    myLogin = new LoginWindow(this);
    myRegistration = new Registration(this);
    xmlwriter = new XmlWriter();
    manager = new QNetworkAccessManager(this);
    connect(myRegistration,SIGNAL(sendregistration()),this,SLOT(registrate()));

    time = 0;
    speed = 0;
    timer = new QTimer();

    accelerometer = new Accelerometer();
    accelerometer->setSampleRate(100);

    measures = new Measures();
    this->initializeMeasures();

    timer->setInterval(300);

    connect(this->timer, SIGNAL(timeout()), this, SLOT(after_timeout()));
    connect(myLogin, SIGNAL( userNameChanged()), this, SLOT(updateUserName()));

    ui->labelMeasureTabResult->hide();

    this->setWindowTitle("Speed freak");

}

/**
  *Destructor of this class. Should be used to release all allocated resources.
  */
CarMainWindow::~CarMainWindow()
{
    delete ui;
    //delete result;
    //delete measure;
    delete xmlreader;
    delete xmlwriter;
    delete manager;
}

/**
  *This function is used to .
  *@param
  */
void CarMainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/**
  *This slot function is called when ever list view is update. Start-tab view.
  */
void CarMainWindow::on_listViewStartTabAccelerationCategories_clicked(QModelIndex index)
{
    QString str = index.data().toString();
    QStringList list = str.split("-");
    QStringList list2 = list[1].split(" ");

    ui->lineEditStartTabMin->setText(list[0]);
    ui->lineEditStartTabMax->setText(list2[0]);
    updateComboBoxStartTabUnits(list2[1]);
}

/**
  *This slot function is called when ever auto start button clicked. Start-tab view.
  */
void CarMainWindow::on_autoStartButton_clicked()
{

    //delete measure;
    //measure = NULL;
    //measure = new MeasureDialog();
   // connect(measure, SIGNAL(speedAchieved()), this, SLOT(openResultView()));
    accelerometer->start();
    timer->start();
    // Show measure dialog.
    //measure->show();
    ui->tabWidget->setCurrentWidget(this->ui->tabMeasureResult);
}

/**
  *This slot function is called when ever list view is update. Start-tab view.
  *@param QString unit.
  */
void CarMainWindow::updateComboBoxStartTabUnits(QString unit)
{
    ui->comboBoxStartTabUnits->setCurrentIndex(ui->comboBoxStartTabUnits->findText(unit, Qt::MatchExactly));
}

/**
  *This function is used to init unit combobox. Start-tab view.
  */
void CarMainWindow::initComboBoxStartTabUnits()
{
    units << "km/h" << "km" << "h" << "m" << "min" << "Mile" << "Mph" << "in" << "ft" << "yrd";
    ui->comboBoxStartTabUnits->addItems(units);
}

/**
  *This function is used to set items to unit combobox. Start-tab view.
  *@param QStringlist units
  */
void CarMainWindow::setComboBoxStartTabUnits(QStringList units)
{
    ui->comboBoxStartTabUnits->addItems(units);
}

/**
  *This function is used to init listViewStartTabAccelerationCategories. Start-tab view.
  */
void CarMainWindow::initListViewStartTabAccelerationCategories()
{
    accelerationCategoriesStartTab << "0-40 km/h" << "0-100 km/h"; //<< "0-1/4 Mile" << "0-1/8 Mile" << "0-50 km" << "50-100 Mile" << "0-60 Mph" << "0-100 m" << "0-50 ft" << "0-50 yrd" << "0-500 in";
    QAbstractItemModel *model = new StringListModel(accelerationCategoriesStartTab);
    ui->listViewStartTabAccelerationCategories->setModel(model);
}

/**
  *This function is used to set items to listViewStartTabAccelerationCategories. Start-tab view.
  *@param QStringlist accelerationCategoriesStartTab
  */
void CarMainWindow::setListViewStartTabAccelerationCategories(QStringList accelerationCategoriesStartTab)
{
    QAbstractItemModel *model = new StringListModel(accelerationCategoriesStartTab);
    ui->listViewStartTabAccelerationCategories->setModel(model);
}

/**
  *This function is used to set items to category combobox. Top-tab view.
  *@param
  */
void CarMainWindow::setCategoryCompoBox()
{
    ui->comboBoxTopCategory->addItems(xmlreader->getTop10List());
}

/**
  *This function is used to set items to labelTopList. Top-tab view.
  *@param QString category
  */
void CarMainWindow::setListViewTopList(QString category)
{
    QString topList;

    if (category == "acceleration-0-100")
    {
        topList.append(xmlreader->getTop10AccelerationList());
    }

    else if (category == "Speed")
    {
        topList.append(xmlreader->getTop10SpeedList());
    }

    else if (category == "G-force")
    {
        topList.append(xmlreader->getTop10GforceList());
    }
    ui->labelTopList->setText(topList);
}

/**
  *This slot function is called when speed is achieved in measure dialog. Opens result dialog.
  */
void CarMainWindow::openResultView()
{
    //result->saveMeasuresToArray(measure->measures);
    // Show result dialog.
    //result->show();
    ui->pushButtonSendResult->setEnabled(true);
    QString timeInteger;
    timeInteger.setNum(this->measures->getTime40kmh());
    //time = "0 - 40 km/h: ";
    //time.append(timeInteger);
    //ui->labelResult40kmh->setText(time);
    ui->labelMeasureTabResult->show();
    ui->labelMeasureTabResult->setText(timeInteger);
    //ui->tabWidget->setCurrentWidget(this->ui->tabMeasureResult);
}


/**
  *This slot function is called when login/logout button is clicked.
  */
void CarMainWindow::on_loginLogoutButton_clicked()
{
    myLogin->show();
}

/**
  *This slot function is called when registrate button is clicked.
  */
void CarMainWindow::on_registratePushButton_clicked()
{
    myRegistration->show();
}

/**
  *This slot function is called when ever refresh button clicked. Top-tab view.
  */
void CarMainWindow::on_buttonTopRefresh_clicked()
{
    //setCategoryCompoBox();
    requestTopList();
}

/**
  *This slot function is called when ever category combobox current index changed. Top-tab view.
  *@param QString category
  */
void CarMainWindow::on_comboBoxTopCategory_currentIndexChanged(QString category)
{
    setListViewTopList(category);
}

/**
  *This slot function is called when ever category combobox activated. Top-tab view.
  *@param QString category
  */
void CarMainWindow::on_comboBoxTopCategory_activated(QString category)
{
    setListViewTopList(category);
}

/**
  *This slot function is called when set/change user button is clicked.
  */
void CarMainWindow::on_setUserPushButton_clicked()
{
    myLogin->show();

    ui->userNameLabel->setText( "User: " + myLogin->getUserName());
    ui->setUserPushButton->setText( "Change User");
}

/**
  *@brief Sends registration information to the server in xml format.
  *Reads user name, password and emaol address from resuldialogs internal variables.
  *@todo Replace msg box with better reaction to server`s responce.
  *@todo Write error handling.
  */
void CarMainWindow::registrate()
{
    qDebug() << "_registrate" ;
    qDebug() << this->myRegistration->getUserName() << "+" << this->myRegistration->getPassword() << "+" << this->myRegistration->getEmail();

    QBuffer *regbuffer = new QBuffer();
    QUrl qurl("http://api.speedfreak-app.com/api/register");
    QNetworkRequest request(qurl);
    qDebug() << qurl.toString();

    regbuffer->open(QBuffer::ReadWrite);
    xmlwriter->writeRegistering(regbuffer,
                      this->myRegistration->getUserName(),
                      this->myRegistration->getPassword(),
                      this->myRegistration->getEmail());
    //Tmp msgbox - later server responce
    QMessageBox::about(this,"Registrate",this->myRegistration->getUserName() + this->myRegistration->getPassword() + this->myRegistration->getEmail());

    manager->post(request, ("data=" + regbuffer->data()));
    qDebug() << "carmainwindow: regbuffer->data(): " << regbuffer->data();

    //ackOfRegistration function gets called when HTTP request is completed
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(ackOfRegistration(QNetworkReply*)));
    //connect(manager,SIGNAL(sslErrors(QNetworkReply*)),this,SLOT(errorFromServer(QNetworkReply*)));
    regbuffer->close();
}

/**
  *@brief Sends result(s) to the server in xml format with authentication information in the header.
  *@todo Write error handling.
  */
void CarMainWindow::sendXml()
{
    qDebug() << "_sendXml";

    QBuffer *xmlbuffer = new QBuffer();
    QString category_name = "acceleration-0-100";    //replace with real value from category list

    QString credentials = this->myRegistration->getUserName() + ":" + this->myRegistration->getPassword();
    credentials = "Basic " + credentials.toAscii().toBase64();

    QUrl qurl("http://api.speedfreak-app.com/api/update/" + category_name);
    qDebug() << qurl.toString();
    QNetworkRequest request(qurl);
    request.setRawHeader(QByteArray("Authorization"),credentials.toAscii());

    xmlbuffer->open(QBuffer::ReadWrite);
    xmlwriter->writeResult(xmlbuffer);
    qDebug() << "carmainwindow: xmlbuffer->data(): " << xmlbuffer->data();

    manager->post(request, ("data=" + xmlbuffer->data()));
    //connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(ackOfResult(QNetworkReply*)));
    //connect(manager,SIGNAL(sslErrors(QNetworkReply*)),this,SLOT(errorFromServer(QNetworkReply*)));

    //QNetworkReply *currentDownload;
    //QString data("abcdefg");
    //currentDownload = manager->post(request,"data=" + QUrl::toPercentEncoding(data));   //testing
    //currentDownload = manager->post(request, ("data=" + xmlbuffer->data()));
    //ackOfResult function gets called when HTTP request is completed
    //connect(currentDownload, SIGNAL(finished()), SLOT(ackOfResult()));

    xmlbuffer->close();
}

/**
  *@brief Sends request to the server for a top list with authentication information in the header.
  *@todo Write error handling.
  *@todo Replace with real value from category list and limitNr
  */
void CarMainWindow::requestTopList()
{
    qDebug() << "_requestTopList" ;

    QString urlBase = "http://api.speedfreak-app.com/api/results/";
    QString category_name = "acceleration-0-100";    //replace with real value from category list/top window
    int limitNr = 5;
    QString limit = QString::number(limitNr);

    QString credentials = this->myRegistration->getUserName() + ":" + this->myRegistration->getPassword();
    credentials = "Basic " + credentials.toAscii().toBase64();

    QUrl qurl(urlBase + category_name + "/" + limit);
    qDebug() << qurl.toString();
    QNetworkRequest request(qurl);

    request.setRawHeader(QByteArray("Authorization"),credentials.toAscii());
    manager->post(request, ("data=" ));
    //connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(networkResponse(QNetworkReply*)));
    //connect(manager,SIGNAL(sslErrors(QNetworkReply*)),this,SLOT(errorFromServer(QNetworkReply*)));

    //QNetworkReply *currentDownload;
    //currentDownload = manager->post(request, ("data=" ));
    //ackOfResult function gets called when HTTP request is completed
    //connect(currentDownload, SIGNAL(error()),SLOT(errorFromServer()));
}

/**
  *@brief React to servers responce after result has been sent.
  *@todo Implement function and write error handling.
  */
void CarMainWindow::ackOfResult(QNetworkReply* reply)
{
    qDebug() << "_ackOfResult";
    qDebug() << reply->readAll();
    QNetworkReply::NetworkError errorcode;
    errorcode = reply->error();
    if(errorcode != 0) {
        qDebug() << errorcode << reply->errorString();
    }
    else {
        qDebug() << "errorcode=0";
    }
}

/**
  *@brief React to servers responce after registration has been sent.
  *@todo Implement function and write error handling.
  */
void CarMainWindow::ackOfRegistration(QNetworkReply* reply)
{
    qDebug() << "_ackOfRegistration";
    qDebug() << reply->readAll();
    QNetworkReply::NetworkError errorcode;
    errorcode = reply->error();
    if(errorcode != 0) {
        qDebug() <<  "errorcode:" << errorcode << reply->errorString();
    }
    else {
        qDebug() << "errorcode=0";
    }
}

void CarMainWindow::errorFromServer(QNetworkReply* reply)
{
    qDebug() << "_errorFromServer";
    QNetworkReply::NetworkError errorcode;

    errorcode = reply->error();
    if(errorcode != 0) {
        qDebug() << errorcode;
    }
    else {
        qDebug() << errorcode;
    }
}

/**
  *This slot function is called when the server has finished guery.
  */
void CarMainWindow::networkResponse(QNetworkReply *reply)
{
    qDebug() << "_networkResponse";
    xmlreader->xmlRead(reply);
    qDebug() << reply->readAll();
    QNetworkReply::NetworkError errorcode;
    errorcode = reply->error();
    if(errorcode != 0) {
        qDebug() << errorcode << reply->errorString();
    }
    else {
        qDebug() << "errorcode=0";
    }
}

/**
  *@brief Just for development, for the real button is not shown until
  *measurin started and there are results.
  *@todo Implement with real code and yet leave sendXml in the bottom in use.
  */
void CarMainWindow::on_manualStartButton_clicked()
{
    sendXml();
}

/**
  * This slot function is called when timer gives timeout signal. Checks current speed
  * and stores times in measure class.
  */
void CarMainWindow::after_timeout()
{
    QString timeString, speedString;
    //time++;
    time = accelerometer->getTotalTime();
    speed = accelerometer->getCurrentSpeed();
    //speed = speed +10;

    if (floor(speed) == 10)
    {
        measures->setTime10kmh(time);
    }

    else if (floor(speed) == 20)
    {
        measures->setTime20kmh(time);
    }

    else if (floor(speed) == 30)
    {
        measures->setTime30kmh(time);
    }

    else if (floor(speed) == 40)
    {
        measures->setTime40kmh(time);
    }

    else if (floor(speed) == 50)
    {
        measures->setTime50kmh(time);
    }

    else if (floor(speed) == 60)
    {
        measures->setTime60kmh(time);
    }

    else if (floor(speed) == 70)
    {
        measures->setTime70kmh(time);
    }

    else if (floor(speed) == 80)
    {
        measures->setTime80kmh(time);
    }

    else if (floor(speed) == 90)
    {
        measures->setTime90kmh(time);
    }

    else if (floor(speed) == 100)
    {
        measures->setTime100kmh(time);
    }

    else
    {

    }

    // If speed is over 40 km/h emits speedAchieved() signal and close this dialog.
    if (speed >= 40.0)
    {
        timer->stop();
        accelerometer->stop();
        time = 0;
        speed = 0;
        //emit this->speedAchieved();
        this->openResultView();
        //this->close();

    }

    // Updates speed and time.
    else
    {
        timeString.setNum(time);
        speedString.setNum(speed);
        ui->labelMeasureTabTime->setText(timeString);
        ui->labelMeasureTabSpeed->setText(speedString);

        timer->start();
    }

}

/**
  * Initializes measures class's member variables.
  */
void CarMainWindow::initializeMeasures()
{
    measures->setTime10kmh(0);
    measures->setTime20kmh(0);
    measures->setTime30kmh(0);
    measures->setTime40kmh(0);
    measures->setTime50kmh(0);
    measures->setTime60kmh(0);
    measures->setTime70kmh(0);
    measures->setTime80kmh(0);
    measures->setTime90kmh(0);
    measures->setTime100kmh(0);
}

/**
  * This slot function is called when Abort button is clicked.
  */
void CarMainWindow::on_pushButtonMeasureTabAbort_clicked()
{
    measures->setTime10kmh(0);
    measures->setTime20kmh(0);
    measures->setTime30kmh(0);
    measures->setTime40kmh(0);
    measures->setTime50kmh(0);
    measures->setTime60kmh(0);
    measures->setTime70kmh(0);
    measures->setTime80kmh(0);
    measures->setTime90kmh(0);
    measures->setTime100kmh(0);
    timer->stop();
    accelerometer->stop();
    time = 0;
    speed = 0;
    ui->tabWidget->setCurrentWidget(this->ui->StartTab);
    //this->close();
}

void CarMainWindow::on_pushButtonSendResult_clicked()
{
    sendXml();
    ui->pushButtonSendResult->setEnabled(false);
}

void CarMainWindow::updateUserName()
{
    QString newUserName;

    newUserName = myLogin->getUserName();
    ui->userNameLabel->setText( "User: " + newUserName);

    if (newUserName.length())
    {
       ui->setUserPushButton->setText( "Change User");
       this->setWindowTitle("Speed freak - " + newUserName);
    }
    else
    {
        ui->setUserPushButton->setText( "Set User");
        this->setWindowTitle("Speed freak");
    }
}
