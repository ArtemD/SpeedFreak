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

    ui->labelRouteSatelliteStatus->setVisible(0);
    ui->labelRouteSatellitePicture->setVisible(0);
    ui->labelRouteSatellitePicture->setPixmap(QPixmap("satellite_vista.png"));
    timerSatellitePicture = new QTimer();
    timerSatellitePicture->setInterval(400);
    connect(timerSatellitePicture, SIGNAL(timeout()),this, SLOT(timerSatellitePictureTimeout()));
}

/**
  *Destructor of this class. Deletes all dynamic objects and sets them to NULL.
  */
RouteSaveDialog::~RouteSaveDialog()
{
    delete ui;
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
    if ( ui->buttonRouteStartStop->text() == "Start" )
    {
        ui->buttonRouteStartStop->setText("Stop");
        ui->labelRouteSatelliteStatus->setText("Searching satellite");
        ui->labelRouteSatelliteStatus->setVisible(1);
        ui->labelRouteSatellitePicture->setVisible(1);
        timerSatellitePicture->start();
    }
    else
    {
        ui->buttonRouteStartStop->setText("Start");
        ui->labelRouteSatelliteStatus->setVisible(0);
        ui->labelRouteSatellitePicture->setVisible(0);
        timerSatellitePicture->stop();
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
