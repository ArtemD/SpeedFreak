/*
 * Acceleration start dialog
 *
 * @author      Jukka Kurttila <jukka.kurttila@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */
#include "accelerationstart.h"
#include "ui_accelerationstartdialog.h"
#include <QMessageBox>

accelerationstart::accelerationstart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accelerationstart)
{
    ui->setupUi(this);
    ui->buttonStart->setDisabled(true);

    accRealTimeDialog = NULL;

    stopMeasureSpeed = 0;

    ui->categorComboBox->addItem("Select category");
    //ui->categorComboBox->addItem("-");
    ui->categorComboBox->addItem("0 - 20 km/h",20);
    ui->categorComboBox->addItem("0 - 40 km/h");
    ui->categorComboBox->addItem("0 - 100 km/h");

    //Button settings
    ui->buttonCalib->setAutoFillBackground(true);
    ui->buttonCalib->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");
    ui->buttonStart->setAutoFillBackground(true);
    ui->buttonStart->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");
}

accelerationstart::~accelerationstart()
{
    delete ui;
    if(accRealTimeDialog)
        delete accRealTimeDialog;
}

void accelerationstart::changeEvent(QEvent *e)
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

void accelerationstart::on_buttonCalib_clicked()
{
    if(accRealTimeDialog == NULL)
        accRealTimeDialog = new AccRealTimeDialog(this);

    connect(accRealTimeDialog, SIGNAL(sendresult(double)), this, SLOT(sendResult(double)));

    accRealTimeDialog->Calibrate();

    ui->buttonStart->setEnabled(true);
}

void accelerationstart::on_buttonStart_clicked()
{
    if( stopMeasureSpeed == 0 )
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Can not start measure!");
        msgBox.setText("Select category first!");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    accRealTimeDialog->SetStopMeasureSpeed( stopMeasureSpeed );
    accRealTimeDialog->startAccelerationMeasure();
    accRealTimeDialog->show();
}

void accelerationstart::on_categorComboBox_currentIndexChanged( int index )
{
    stopMeasureSpeed = 0;
    if( index == 1 ) {
        stopMeasureSpeed = 20;
        measureCategory = "acceleration-0-20";
    }
    else if( index == 2 ) {
        stopMeasureSpeed = 40;
        measureCategory = "acceleration-0-40";
    }
    else if( index == 3 ) {
        stopMeasureSpeed = 100;
        measureCategory = "acceleration-0-100";
    }
}


QString accelerationstart::getMeasureCategory()
{
    return measureCategory;
}

/**
  *This slot function emit mainwindow sendresult.
  *
  **/
void accelerationstart::sendResult(double result)
{
    emit sendresult(measureCategory, result);
}
