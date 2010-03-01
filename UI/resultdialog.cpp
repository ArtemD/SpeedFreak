#include "resultdialog.h"
#include "ui_resultdialog.h"
#include <QPainter>

const QPoint diagramStemStart(50, 350);
const QPoint diagramStemEnd(50, 30);

const QPoint diagramHorizontalStart(50, 350);
const QPoint diagramHorizontalEnd(450, 350);

const int diagramGap = 30;


// Test arrays for changing speeds and times to the points in diagram
static const int speedArray[10] = {12, 34, 56, 78, 90, 100, 104, 100, 90, 80};
static const int timeArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 12};



// Test point array for the diagram.
QPoint points[10];

ResultDialog::ResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);

    QString time, timeInteger;
    timeInteger.setNum(timeArray[9]);
    time = "0 - 100 km/h: ";
    time.append(timeInteger);
    ui->labelResult->setText(time);

    timeInteger.setNum(timeArray[8]);
    time = "0 - 90 km/h: ";
    time.append(timeInteger);
    ui->labelResult_2->setText(time);

    timeInteger.setNum(timeArray[7]);
    time = "0 - 80 km/h: ";
    time.append(timeInteger);
    ui->labelResult_3->setText(time);

    timeInteger.setNum(timeArray[6]);
    time = "0 - 70 km/h: ";
    time.append(timeInteger);
    ui->labelResult_4->setText(time);

    timeInteger.setNum(timeArray[5]);
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
    ui->labelResult_7->setText(time);

    for(int i = 0; i < 10; i++)
    {
        points[i] = changeMeasuresToDiagramPoint(speedArray[i], timeArray[i]);
    }
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

        painter.drawPolyline(points, 10);

}

/**
  *Change the given speed and time to the point for the diagram.
  *@param aSpeed is speed which need to change, aTime is time in seconds which need to change.
  *@return point is calculated from aSpeed and aTime.
  **/
QPoint ResultDialog::changeMeasuresToDiagramPoint(int aSpeed, int aTime)
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
