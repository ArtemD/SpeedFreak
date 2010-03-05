#include "measuredialog.h"
#include "ui_measuredialog.h"


/**
  * Constructor of this class.
  * @param QWidget pointer to parent object. By default the value is NULL.
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
    accelerometer->setSampleRate(100);
    accelerometer->start();

    measures = new Measures();
    this->initializeMeasures();

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
  * This slot function is called when timer gives timeout signal. Checks current speed
  * and stores times in measure class.
  */
void MeasureDialog::after_timeout()
{
    QString timeString, speedString;
    //time++;
    time = accelerometer->getTotalTime();
    speed = accelerometer->getCurrentSpeed();
    //speed = speed +10;

    if (speed > 9.7 && speed < 10.3)
    {
        measures->setTime10kmh(time);
    }

    else if (speed > 19.7 && speed < 20.3)
    {
        measures->setTime20kmh(time);
    }

    else if (speed > 29.7 && speed < 30.3)
    {
        measures->setTime30kmh(time);
    }

    else if (speed > 39.7 && speed < 40.3)
    {
        measures->setTime40kmh(time);
    }

    else if (speed > 49.7 && speed < 50.3)
    {
        measures->setTime50kmh(time);
    }

    else if (speed > 59.7 && speed < 60.3)
    {
        measures->setTime60kmh(time);
    }

    else if (speed > 69.7 && speed < 70.3)
    {
        measures->setTime70kmh(time);
    }

    else if (speed > 79.7 && speed < 80.3)
    {
        measures->setTime80kmh(time);
    }

    else if (speed > 89.7 && speed < 90.3)
    {
        measures->setTime90kmh(time);
    }

    else if (speed > 99.7 && speed < 100.3)
    {
        measures->setTime100kmh(time);
    }

    else
    {

    }

    // If speed is over 100 km/h emits speedAchieved() signal and close this dialog.
    if (speed >= 40.0)
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
  * This slot function is called when Abort button is clicked.
  */
void MeasureDialog::on_pushButtonAbort_clicked()
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
    this->close();
}

/**
  * Initializes measures class's member variables.
  */
void MeasureDialog::initializeMeasures()
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
