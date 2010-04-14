/*
 * Route save dialog class
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "routesavedialog.h"
#include "ui_routesavedialog.h"

/**
  *Constructor of this class.
  *@param QWidget pointer to parent object. By default the value is NULL.
  */
RouteSaveDialog::RouteSaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RouteSaveDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Tracking");

    routeDialog = new RouteDialog;

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

    //Satellite picture and label
    ui->labelRouteSatelliteStatus->setVisible(0);
    ui->labelRouteSatellitePicture->setVisible(0);
    //ui->labelRouteSatellitePicture->setPixmap(QPixmap("Graphics/satellite_vista.png"));
    timerSatellitePicture = new QTimer();
    timerSatellitePicture->setInterval(400);
    connect(timerSatellitePicture, SIGNAL(timeout()),this, SLOT(timerSatellitePictureTimeout()));

    //Route picture and label
    ui->labelRouteStatus->setVisible(0);
    ui->labelRoutePicture->setVisible(0);
    timerRoutePicture = new QTimer();
    timerRoutePicture->setInterval(400);
    connect(timerRoutePicture, SIGNAL(timeout()),this, SLOT(timerRoutePictureTimeout()));

    //GPS speed label
    ui->labelGpsSpeed->setVisible(0);

    //GPS
    location = new Maemo5Location(this);
    gpsData = new GPSData(location);
    connect(location,SIGNAL(agnss()),this,SLOT(gpsStatus()));
}

/**
  *Destructor of this class. Deletes all dynamic objects and sets them to NULL.
  */
RouteSaveDialog::~RouteSaveDialog()
{
    delete ui;
    delete timerSatellitePicture;
    delete timerRoutePicture;
    delete location;
    delete gpsData;
    delete routeDialog;
    delete pixmapRouteStop;
    delete pixmapRouteStart;
    delete iconRouteStop;
    delete iconRouteStart;
}

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
  *This slot function is called when route start/stop button clicked.
  */
void RouteSaveDialog::on_buttonRouteStartStop_clicked()
{
    //If start button clicked
    if ( buttonStatus == true )
    {
        buttonStatus = false;
        ui->buttonRouteStartStop->setIcon(*iconRouteStop);
        location->startPollingGPS();
        gpsStatus();
    }
    else
    {
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

        QString routeFile = QString("routetemp.xml");
        if (routeDialog->readRouteFromFile( routeFile) == true)
        {
            routeDialog->show();
        }

        //GPS speed label
        ui->labelGpsSpeed->setVisible(0);

        //Stop route recording
        gpsData->stopRouteRecording();
    }
}

/**
  *This slot function is called when satellite picture timer timeout(400ms).
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
  *This slot function is called when route picture timer timeout(400ms).
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

void RouteSaveDialog::gpsStatus()
{
    //IF GPS start button clicked
    if (buttonStatus == false)
    {
        //If GPS find 4 satellite.
        if (location->getSatellitesInUse() >= 4)
        {
            //Satellite picture and label
            ui->labelRouteSatelliteStatus->setText("GPS Ready");
            ui->labelRouteSatelliteStatus->setVisible(1);
            ui->labelRouteSatellitePicture->setVisible(1);
            timerSatellitePicture->stop();

            //Route picture and label
            ui->labelRouteStatus->setText("Recorded " + QString::number(gpsData->roundCounter) + " route point");
            ui->labelRouteStatus->setVisible(1);
            ui->labelRoutePicture->setVisible(1);
            timerRoutePicture->start();

            //Set GPS speed.
            gpsSpeed.sprintf("%.0f",location->getSpeed());
            ui->labelGpsSpeed->setText(gpsSpeed + " km/h");
            ui->labelGpsSpeed->setVisible(1);

            //Start route recording
            gpsData->startRouteRecording();
        }

        //If GPS find less than 4 satellite.
        else
        {
            //Satellite picture and label
            ui->labelRouteSatelliteStatus->setText("Searching satellite");
            ui->labelRouteSatelliteStatus->setVisible(1);
            ui->labelRouteSatellitePicture->setVisible(1);
            timerSatellitePicture->start();

            //Route picture and label
            ui->labelRouteStatus->setVisible(0);
            ui->labelRoutePicture->setVisible(0);
            timerRoutePicture->stop();

            //GPS speed label
            ui->labelGpsSpeed->setVisible(0);
        }
    }
    else
    {
        //Satellite picture and label
        ui->labelRouteSatelliteStatus->setText("Searching satellite");
        ui->labelRouteSatelliteStatus->setVisible(0);
        ui->labelRouteSatellitePicture->setVisible(0);
        timerSatellitePicture->stop();

        //Route picture and label
        ui->labelRouteStatus->setVisible(0);
        ui->labelRoutePicture->setVisible(0);
        timerRoutePicture->stop();

        //GPS speed label
        ui->labelGpsSpeed->setVisible(0);
    }
}
