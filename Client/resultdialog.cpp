#include "resultdialog.h"
#include "ui_resultdialog.h"
#include <QPainter>

const QPoint diagramStemStart(50, 350);
const QPoint diagramStemEnd(50, 30);

const QPoint diagramHorizontalStart(50, 350);
const QPoint diagramHorizontalEnd(450, 350);

const int diagramGap = 30;

// Test arrays for changing speeds and times to the points in diagram
static const int speedArray[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
//static const int timeArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 12};

// Test point array for the diagram.
QPoint points[10];

ResultDialog::ResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);



   // ui->labelXLine->setText(ui->labelXLine->text().append(": time/ s"));
   // ui->labelYLine->setText(ui->labelYLine->text().append(": speed/ km/h"));
}

ResultDialog::~ResultDialog()
{
    delete ui;
}

void ResultDialog::changeEvent(QEvent *e)
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
  * Draws speed diagram to the UI
  *
 */
void ResultDialog::paintEvent(QPaintEvent *)
{
        QPainter painter(this);

        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen((Qt::white),2));
        painter.setBrush(QBrush((Qt::yellow), Qt::SolidPattern));
        painter.drawLine(diagramStemStart, diagramStemEnd);
        painter.drawLine(diagramHorizontalStart, diagramHorizontalEnd);

        int currentX = diagramStemStart.x();
        int currentY = diagramStemStart.y();

        // Draws diagram's X-axel
        for(int i = 0; i<13; i++)
        {
            currentX += diagramGap;
            painter.drawLine(currentX, currentY, currentX, currentY - 10);
        }

        currentX = diagramStemStart.x();
        currentY = diagramStemStart.y();

        // Draws diagram's Y-axel
        for(int i = 0; i<10; i++)
        {
            currentY -= diagramGap;
            painter.drawLine(currentX, currentY, currentX+10, currentY);
        }

        painter.drawPolyline(points, 4);

}

/**
  *Change the given speed and time to the point for the diagram.
  *@param aSpeed is speed which need to change, aTime is time in seconds which need to change.
  *@return point is calculated from aSpeed and aTime.
  **/
QPoint ResultDialog::changeMeasuresToDiagramPoint(int aSpeed, qreal aTime)
{
    QPoint point;

    int speedAsPixels;
    int timeAsPixels;
    speedAsPixels = 300*aSpeed/100;
    timeAsPixels = 300*aTime/10;
    point.setY(diagramStemStart.y()-speedAsPixels);
    point.setX(diagramStemStart.x()+timeAsPixels);

    return point;
}

/**
  *Saves the given measures to array.
  *@param pMeasures has information about acceleration.
  **/
void ResultDialog::saveMeasuresToArray(Measures *pMeasures)
{
    timeArray[0] = pMeasures->getTime10kmh();
    timeArray[1] = pMeasures->getTime20kmh();
    timeArray[2] = pMeasures->getTime30kmh();
    timeArray[3] = pMeasures->getTime40kmh();
    timeArray[4] = pMeasures->getTime50kmh();
    timeArray[5] = pMeasures->getTime60kmh();
    timeArray[6] = pMeasures->getTime70kmh();
    timeArray[7] = pMeasures->getTime80kmh();
    timeArray[8] = pMeasures->getTime90kmh();
    timeArray[9] = pMeasures->getTime100kmh();

    for(int i = 0; i < 4; i++)
    {
        points[i] = changeMeasuresToDiagramPoint(speedArray[i], timeArray[i]);
    }

    QString time, timeInteger;
    timeInteger.setNum(timeArray[3]);
    time = "0 - 40 km/h: ";
    time.append(timeInteger);
    ui->labelResult40kmh->setText(time);

    timeInteger.setNum(timeArray[2]);
    time = "0 - 30 km/h: ";
    time.append(timeInteger);
    ui->labelResult30kmh->setText(time);

    timeInteger.setNum(timeArray[1]);
    time = "0 - 20 km/h: ";
    time.append(timeInteger);
    ui->labelResult20kmh->setText(time);

    timeInteger.setNum(timeArray[0]);
    time = "0 - 10 km/h: ";
    time.append(timeInteger);
    ui->labelResult10kmh->setText(time);

   /* timeInteger.setNum(timeArray[5]);
    time = "0 - 60 km/h: ";
    time.append(timeInteger);
    ui->labelResult_5->setText(time);

    timeInteger.setNum(timeArray[4]);
    time = "0 - 50 km/h: ";
    time.append(timeInteger);
    ui->labelResult_6->setText(time);

    timeInteger.setNum(timeArray[3]);
    time = "0 - 40 km/h: ";
    time.append(timeInteger);
    ui->labelResult_7->setText(time);*/

    this->repaint();

    for(int i = 0; i < 10; i++)
    {
        timeArray[i] = 0;
    }
}
