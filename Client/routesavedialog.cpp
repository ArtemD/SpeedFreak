/*
 * Route save dialog class
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "routesavedialog.h"
#include "ui_routesavedialog.h"
#include <QDebug>
#include <QPainter>
#include <QFileDialog>
#include <QDir>

const QPoint arrowStartEast(100, 100);
const QPoint arrowEndEast(140, 100);

const QPoint arrowStartNorth(120, 120);
const QPoint arrowEndNorth(120, 80);

const QPoint arrowStartNortheast(100, 120);
const QPoint arrowEndNortheast(140, 80);

const QPoint arrowStartNorthwest(140, 120);
const QPoint arrowEndNorthwest(100, 80);

/**
  * Constructor of this class.
  * @param QWidget pointer to parent object. By default the value is NULL.
  */
RouteSaveDialog::RouteSaveDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::RouteSaveDialog){

    qDebug() << "__RouteSaveDialog";
    ui->setupUi(this);
    this->setWindowTitle("Tracking");

    routeDialog = NULL;
    location = NULL;
    gpsData = NULL;
    helpRoutingDialog = NULL;
    calibrateDialog = NULL;

    //Clear variables
    averageSpeed = 0.0;
    speed = 0.0;
    allSpeeds = 0.0;
    speedCount = 0;
    direction = 0.0;

    //Button settings
    buttonStatus = true;
    pixmapRouteStop = new QPixmap("Graphics/route_stop.png");
    pixmapRouteStart = new QPixmap("Graphics/route_start.png");
    iconRouteStop = new QIcon(*pixmapRouteStop);
    iconRouteStart = new QIcon(*pixmapRouteStart);
    QSize iconSize(125, 125);
    ui->buttonRouteStartStop->setIconSize(iconSize);
    ui->buttonRouteStartStop->setIcon(*iconRouteStart);
    ui->buttonRouteStartStop->setAutoFillBackground(true);
    ui->buttonRouteStartStop->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");
    ui->pushButtonInfo->setAutoFillBackground(true);
    ui->pushButtonInfo->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");
    ui->buttonLoadRoute->setAutoFillBackground(true);
    ui->buttonLoadRoute->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");

    //Satellite picture and label
    ui->labelRouteSatelliteStatus->setVisible(0);
    ui->labelRouteSatellitePicture->setVisible(0);
    //ui->labelRouteSatellitePicture->setPixmap(QPixmap("Graphics/satellite_vista.png"));
    timerSatellitePicture = new QTimer();
    timerSatellitePicture->setInterval(400);
    connect(timerSatellitePicture, SIGNAL(timeout()),this, SLOT(timerSatellitePictureTimeout()));
    ui->labelUserInfo->setText("Push start button");  //User info label

    //Invisible or clear labels
    ui->labelRouteStatus->setVisible(0);
    ui->labelRoutePicture->setVisible(0);
    ui->labelGpsSpeed->setVisible(0); //GPS speed label
    ui->labelGpsAvgSpeed->setVisible(0); //GPS average speed label
    ui->labelDistance->setVisible(0); //GPS distance label
    ui->labelSignalStrength->setText(""); //GPS signal strength label

    // Timer
    timerRoutePicture = new QTimer();
    timerRoutePicture->setInterval(400);
    connect(timerRoutePicture, SIGNAL(timeout()),this, SLOT(timerRoutePictureTimeout()));

    //GPS
    location = new Maemo5Location(this);
    gpsData = new GPSData(location);
    connect(location,SIGNAL(agnss()),this,SLOT(gpsStatus()));

    // Route folder
    QString folder = "/home/user/MyDocs/speedfreak";
    if(!QDir(folder).exists())
    {
        QDir().mkdir(folder);
    }
    if(!QDir(folder + "/route").exists())
    {
        QDir().mkdir(folder + "/route");
    }
}

/**
  * Destructor of this class. Deletes all dynamic objects and sets them to NULL.
  */
RouteSaveDialog::~RouteSaveDialog()
{
    qDebug() << "__~RouteSaveDialog";
    if(ui)
        delete ui;
    if(gpsData)
        delete gpsData;
    if(location)
        delete location;
    if(routeDialog)
        delete routeDialog;
    if(calibrateDialog)
    {
        delete calibrateDialog;
        calibrateDialog = NULL;
    }

    delete timerSatellitePicture;
    delete timerRoutePicture;
    delete pixmapRouteStop;
    delete pixmapRouteStart;
    delete iconRouteStop;
    delete iconRouteStart;
}

/**
  *
  */
void RouteSaveDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/**
  * Draws compass to the UI
  * @param QPaintEvent
 */
void RouteSaveDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen((Qt::gray),2));

    painter.drawEllipse(arrowStartEast.x() - 30, arrowStartEast.y() - 50, 100, 100);

    QFont font;
    font.setPixelSize(26);
    painter.setFont(font);
    painter.drawText(arrowStartNorth.x() - 10, arrowEndNorth.y() - 45, "N");
    painter.drawText(arrowStartEast.x() - 65, arrowStartEast.y() + 5, "W");
    painter.drawText(arrowStartNorth.x()-10, arrowStartNorth.y()+55, "S");
    painter.drawText(arrowEndEast.x() + 40, arrowEndEast.y() + 5, "E");

    font.setPixelSize(12);
    painter.setFont(font);
    painter.drawText(arrowStartNorth.x() + 40, arrowEndNorth.y() - 25, "NE");
    painter.drawText(arrowStartNorth.x() + 40, arrowStartEast.y() + 45, "SE");
    painter.drawText(arrowStartEast.x() - 45, arrowStartEast.y() + 45, "SW");
    painter.drawText(arrowStartEast.x() - 45, arrowEndNorth.y() - 25, "NW");

    if (direction >= 67.5 && direction <= 112.5)
    {
        // East arrow
        painter.drawLine(arrowStartEast, arrowEndEast);
        painter.drawLine(arrowEndEast.x(), arrowEndEast.y(), arrowEndEast.x()-10, arrowEndEast.y()-5);
        painter.drawLine(arrowEndEast.x(), arrowEndEast.y(), arrowEndEast.x()-10, arrowEndEast.y()+5);
    }

    else if (direction <= 292.5 && direction >= 247.5)
    {
        // West arrow
        painter.drawLine(arrowStartEast, arrowEndEast);
        painter.drawLine(arrowStartEast.x(), arrowStartEast.y(), arrowStartEast.x()+10, arrowEndEast.y()-5);
        painter.drawLine(arrowStartEast.x(), arrowStartEast.y(), arrowStartEast.x()+10, arrowStartEast.y()+5);
    }

    else if (direction <= 202.5 && direction >= 157.5)
    {
        // South arrow
        painter.drawLine(arrowStartNorth, arrowEndNorth);
        painter.drawLine(arrowStartNorth.x(), arrowStartNorth.y(), arrowStartNorth.x()-5, arrowStartNorth.y()-10);
        painter.drawLine(arrowStartNorth.x(), arrowStartNorth.y(), arrowStartNorth.x()+5, arrowStartNorth.y()-10);
    }

    else if (direction > 22.5 && direction < 67.5)
    {
        // Northeast arrow
        painter.drawLine(arrowStartNortheast, arrowEndNortheast);
        painter.drawLine(arrowEndNortheast.x(), arrowEndNortheast.y(), arrowEndNortheast.x()-10, arrowEndNortheast.y());
        painter.drawLine(arrowEndNortheast.x(), arrowEndNortheast.y(), arrowEndNortheast.x(), arrowEndNortheast.y()+10);
    }

    else if (direction > 202.5 && direction < 247.5)
    {
        // Southwest arrow
        painter.drawLine(arrowStartNortheast, arrowEndNortheast);
        painter.drawLine(arrowStartNortheast.x(), arrowStartNortheast.y(), arrowStartNortheast.x(), arrowStartNortheast.y() - 10);
        painter.drawLine(arrowStartNortheast.x(), arrowStartNortheast.y(), arrowStartNortheast.x() + 10, arrowStartNortheast.y());
    }

    else if (direction > 292.5 && direction < 336.5)
    {
        // Northwest arrow
        painter.drawLine(arrowStartNorthwest, arrowEndNorthwest);
        painter.drawLine(arrowEndNorthwest.x(), arrowEndNorthwest.y(), arrowEndNorthwest.x(), arrowEndNorthwest.y()+10);
        painter.drawLine(arrowEndNorthwest.x(), arrowEndNorthwest.y(), arrowEndNorthwest.x()+10, arrowEndNorthwest.y());
    }

    else if (direction > 112.5 && direction < 157.5)
    {
        // Southeast arrow
        painter.drawLine(arrowStartNorthwest, arrowEndNorthwest);
        painter.drawLine(arrowStartNorthwest.x(), arrowStartNorthwest.y(), arrowStartNorthwest.x(), arrowStartNorthwest.y()-10);
        painter.drawLine(arrowStartNorthwest.x(), arrowStartNorthwest.y(), arrowStartNorthwest.x()-10, arrowStartNorthwest.y());
    }

    else
    {
        // North arrow
        painter.drawLine(arrowStartNorth, arrowEndNorth);
        painter.drawLine(arrowEndNorth.x(), arrowEndNorth.y(), arrowEndNorth.x()-5, arrowEndNorth.y()+10);
        painter.drawLine(arrowEndNorth.x(), arrowEndNorth.y(), arrowEndNorth.x()+5, arrowEndNorth.y()+10);
    }
}

/**
  *This slot function is called when route start/stop button clicked.
  */
void RouteSaveDialog::on_buttonRouteStartStop_clicked()
{
    if ( buttonStatus == true )//If start button clicked
    {
        qDebug() << "__start button clicked";

        //Clear variables
        averageSpeed = 0.0;
        speed = 0.0;
        allSpeeds = 0.0;
        speedCount = 1;

        buttonStatus = false;
        ui->buttonRouteStartStop->setIcon(*iconRouteStop);
        location->startPollingGPS();
        gpsStatus();
    }
    else //If stop button clicked
    {
        qDebug() << "__stop button clicked";
        buttonStatus = true;
        ui->buttonRouteStartStop->setIcon(*iconRouteStart);

        //Satellite picture and label
        ui->labelRouteSatelliteStatus->setText("Searching satellite");
        ui->labelRouteSatelliteStatus->setVisible(0);
        ui->labelRouteSatellitePicture->setVisible(0);
        timerSatellitePicture->stop();

        //Route picture and label
        ui->labelRouteStatus->setVisible(0);
        ui->labelRoutePicture->setVisible(0);
        timerRoutePicture->stop();
        location->stopPollingGPS();

        //Set GPS speed labels in visible
        ui->labelGpsSpeed->setVisible(0);
        ui->labelGpsAvgSpeed->setVisible(0);

        //GPS distance label
        ui->labelDistance->setVisible(0);

        //Stop route recording
        gpsData->stopRouteRecording();

        //User info label
        ui->labelUserInfo->setText("Push start button");

        fileName = "/home/user/MyDocs/speedfreak/route/routetemp.xml";
        openRouteDialog();
    }
}

/**
  * This slot function is called when satellite picture timer timeout(400ms).
  */
void RouteSaveDialog::timerSatellitePictureTimeout()
{
    //If satellite picture visible.
    if (ui->labelRouteSatellitePicture->isVisible() == 1)
    {
        ui->labelRouteSatelliteStatus->setVisible(0);
        ui->labelRouteSatellitePicture->setVisible(0);
    }
    else
    {
        ui->labelRouteSatelliteStatus->setVisible(1);
        ui->labelRouteSatellitePicture->setVisible(1);
    }
    timerSatellitePicture->start();
}

/**
  * This slot function is called when route picture timer timeout(400ms).
  */
void RouteSaveDialog::timerRoutePictureTimeout()
{
    //If route picture visible.
    if (ui->labelRoutePicture->isVisible() == 1)
    {
        ui->labelRouteStatus->setVisible(0);
        ui->labelRoutePicture->setVisible(0);
    }
    else
    {
        ui->labelRouteStatus->setVisible(1);
        ui->labelRoutePicture->setVisible(1);
    }
    timerRoutePicture->start();
}

/**
  * This slot function is called when GPS update location.
  */
void RouteSaveDialog::gpsStatus()
{
    //IF GPS start button clicked
    if (buttonStatus == false)
    {
        //ui->labelSignalStrength->setText(QString::number(location->getSignalStrength()));    //Returns average signal strength of satellites which are in use.

        //If GPS find 4 or more satellite and signal stregth is 30 or more.
        if (location->getSatellitesInUse() >= 4 && location->getSignalStrength() >= 30)
        {
            //Satellite picture and label
            ui->labelRouteSatelliteStatus->setText("GPS Ready");
            ui->labelRouteSatelliteStatus->setVisible(1);
            ui->labelRouteSatellitePicture->setVisible(1);
            timerSatellitePicture->stop();

            //Route picture and label
            ui->labelRouteStatus->setText("Recorded " + QString::number(gpsData->roundCounter) + " route point");
            ui->labelUserInfo->setText("Recorded " + QString::number(gpsData->roundCounter) + " route point");
            ui->labelRouteStatus->setVisible(1);
            ui->labelRoutePicture->setVisible(1);
            timerRoutePicture->start();

            //Get GPS speed
            speed = location->getSpeed();

            //Get GPS track means direction
            direction = gpsData->getDirection();
            repaint();

            //Set GPS speed
            gpsSpeed.sprintf("%.0f", speed);
            ui->labelGpsSpeed->setText(gpsSpeed + " km/h");
            ui->labelGpsSpeed->setVisible(1);

            //Set GPS average speed
            allSpeeds += speed;
            averageSpeed = allSpeeds/speedCount;
            gpsSpeed.sprintf("%.0f",averageSpeed);
            ui->labelGpsAvgSpeed->setText("Avg: " + gpsSpeed + " km/h");
            ui->labelGpsAvgSpeed->setVisible(1);
            speedCount++;

            //Set distance traveled.
            distanceString.sprintf("%.3f", gpsData->getDistanceTraveled());
            ui->labelDistance->setText(distanceString + " km");
            ui->labelDistance->setVisible(1);

            //Start route recording
            gpsData->startRouteRecording();
        }
        else //If GPS find less than 4 satellite or signal strength is poor.
        {
            //Satellite picture and label
            ui->labelRouteSatelliteStatus->setText("Searching satellite");
            ui->labelUserInfo->setText("Searching satellite");
            ui->labelRouteSatelliteStatus->setVisible(1);
            ui->labelRouteSatellitePicture->setVisible(1);
            timerSatellitePicture->start();

            //Route picture and label
            ui->labelRouteStatus->setVisible(0);
            ui->labelRoutePicture->setVisible(0);
            timerRoutePicture->stop();

            //Set GPS speed labels in visible
            ui->labelGpsSpeed->setVisible(0);
            ui->labelGpsAvgSpeed->setVisible(0);

            //GPS distance label
            ui->labelDistance->setVisible(0);
        }
    }
    else //If stop button clicked
    {
        //Satellite picture and label
        ui->labelRouteSatelliteStatus->setText("Searching satellite");
        ui->labelUserInfo->setText("Push start button");
        ui->labelRouteSatelliteStatus->setVisible(0);
        ui->labelRouteSatellitePicture->setVisible(0);
        timerSatellitePicture->stop();

        //Route picture and label
        ui->labelRouteStatus->setVisible(0);
        ui->labelRoutePicture->setVisible(0);
        timerRoutePicture->stop();

        //Set GPS speed labels in visible
        ui->labelGpsSpeed->setVisible(0);
        ui->labelGpsAvgSpeed->setVisible(0);

        //GPS distance label
        ui->labelDistance->setVisible(0);
    }
}

/**
  * This slot function is called when routeDialog emit sendroute (sendPushButton).
  */
void RouteSaveDialog::sendRoute(QString newName, int i)
{
    emit sendroute(fileName, newName, i); //Emit mainwindow clientSendRoute
}

/**
  * This slot function called when ever info button clicked.
  */
void RouteSaveDialog::on_pushButtonInfo_clicked()
{
    if(!helpRoutingDialog)
    {
        helpRoutingDialog = new HelpRoutingDialog;
    }
    connect(helpRoutingDialog, SIGNAL(rejected()), this, SLOT(killHelpDialog()));
    helpRoutingDialog->show();
}

/**
  * This slot function called when ever dialog rejected.
  */
void RouteSaveDialog::killHelpDialog()
{
    if(helpRoutingDialog)
    {
        qDebug() << "__Route save kill: helpRoutingDialog";
        delete helpRoutingDialog;
        helpRoutingDialog = NULL;
    }
}

/**
  * This slot function called when ever route dialog rejected.
  */
void RouteSaveDialog::killRouteDialog()
{
    if(routeDialog)
    {
        qDebug() << "__Route save kill: routeDialog";
        delete routeDialog;
        routeDialog = NULL;
    }
    if(calibrateDialog)
    {
        qDebug() << "__Route save kill: calibrateDialog";
        delete calibrateDialog;
        calibrateDialog = NULL;
    }
}

/**
  * This function return speed average.
  * @return double average speed
  */
double RouteSaveDialog::getAverageSpeed()
{
    return averageSpeed;
}

/**
  * This function return distance traveled in QString.
  * @return QString distance traveled
  */
QString RouteSaveDialog::getDistanceTraveled()
{
    return distanceString;
}

/**
  * This function
  */
void RouteSaveDialog::setProgressbar(int i)
{
    qDebug() << "__setProgressbar: " + QString::number(i);
    //qDebug() << i;
    calibrateDialog->setProgressValue(i);
    progressbarIteration++;
}

/**
  * This slot function called when ever load route button clicked.
  */
void RouteSaveDialog::on_buttonLoadRoute_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open route"), "/home/user/MyDocs/speedfreak/route", "XML (*.xml)");
    qDebug() << "__Opening: " + fileName;
    openRouteDialog();//fileName);
}

/**
  * This function open and show route.
  * @param QString file name
  */
void RouteSaveDialog::openRouteDialog()
{
    if(fileName != "")
    {
        // Progress bar
        if(!calibrateDialog)
        {
            calibrateDialog = new CalibrateDialog();
        }

        progressbarPoints = 100;
        progressbarIteration = 0;
        calibrateDialog->resetProgressValue();
        calibrateDialog->setMaxValue( progressbarPoints );
        calibrateDialog->setTitle("Calculating route...");
        calibrateDialog->show();

        if(!routeDialog)
        {
            routeDialog = new RouteDialog(this);
        }

        connect(routeDialog, SIGNAL(sendroute(QString, int)), this, SLOT(sendRoute(QString, int)));
        connect(routeDialog, SIGNAL(progressbar(int)), this, SLOT(setProgressbar(int)));
        connect(routeDialog, SIGNAL(rejected()), this, SLOT(killRouteDialog()));

        if (routeDialog->readRouteFromFile( fileName ) == true)
        {
            calibrateDialog->close();
            routeDialog->show();
        }
        else
        {
            calibrateDialog->close();
        }
    }
}
