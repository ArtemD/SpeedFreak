#include "measuredialog.h"
#include "ui_measuredialog.h"


/**
  *Constructor of this class.
  *@param QWidget pointer to parent object. By default the value is NULL.
  */
MeasureDialog::MeasureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeasureDialog)
{
    ui->setupUi(this);
    ui->labelInfo->setText("Accelerate to 100 km/h");
    time = 0;
    speed = 0;
    timer = new QTimer();

    accelerometer = new Accelerometer();
    accelerometer->start();

    timer->setInterval(100);
    timer->start();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(after_timeout()));
}

/**
  *Destructor of this class.  Should be used to release all allocated resources.
  */
MeasureDialog::~MeasureDialog()
{
    delete ui;
}

void MeasureDialog::changeEvent(QEvent *e)
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
  *This slot function is called when timer gives timeout signal.
  */
void MeasureDialog::after_timeout()
{
    QString timeString, speedString;
    //time++;
    time = accelerometer->getIntervalTime();
    speed = accelerometer->getCurrentSpeed();

    // If speed is over 100 km/h emits speedAchieved() signal and close this dialog.
    if(speed>=100.0)
    {
        timer->stop();
        accelerometer->stop();
        time = 0;
        speed = 0;
        emit this->speedAchieved();
        this->close();

    }

    // Updates speed and time.
    else
    {
        timeString.setNum(time);
        speedString.setNum(speed);
        ui->labelSpeed->setText(speedString);
        ui->labelTime->setText(timeString);
        timer->start();
    }
}

/**
  *This slot function is called when Abort button is clicked.
  */
void MeasureDialog::on_pushButtonAbort_clicked()
{
    timer->stop();
    accelerometer->stop();
    time = 0;
    speed = 0;
    this->close();
}
