/*
 * CarMainWindow main class
 *
 * @author     Janne Änäkkälä <janne.anakkala@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "resultdialog.h"
#include "ui_resultdialog.h"
#include <QPainter>

const int DIAGRAM_WIDTH = 400;
const int DIAGRAM_HEIGHT = 300;

const int DIAGRAMGAP100KMH = 30;
const int DIAGRAMGAP40KMH = 75;
const int DIAGRAMGAP60KMH = 50;
const int DIAGRAMGAP50KMH = 60;
const double DIAGRAMGAP80KMH = 37.5;

const QPoint diagramStemStart(70, 330);
const QPoint diagramStemEnd(70, 30);

const QPoint diagramHorizontalStart(70, 330);
const QPoint diagramHorizontalEnd(470, 330);

const int diagramGap = 30;

// Test arrays for changing speeds and times to the points in diagram
static const int speedArray[11] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
//static const int timeArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 12};

// Test point array for the diagram.
QPoint points[11];

/**
  * Constructor of this class.
  * @param QWidget pointer to parent object. By default the value is NULL.
  */
ResultDialog::ResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);
    speedList << "0" << "10" << "20" << "30" << "40" << "50" << "60" << "70" << "80" << "90" << "100" ;
    timeList << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10" << "11"
            << "12" << "13" << "14" << "15" << "16" << "17" << "18" << "19" << "20";
}

/**
  * Destructor of this class.  Should be used to release all allocated resources.
  */
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
  * @param QPaintEvent
 */
void ResultDialog::paintEvent(QPaintEvent *)
{
        QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen((Qt::red),2));
    QFont font;
    font.setPixelSize(12);
    painter.setFont(font);
    painter.setBrush(QBrush((Qt::yellow), Qt::SolidPattern));
    painter.drawLine(diagramStemStart, diagramStemEnd);
    painter.drawLine(diagramHorizontalStart, diagramHorizontalEnd);

    int currentX = 0;
    int currentY = diagramStemStart.y();

    painter.setPen(QPen((Qt::blue),1));
    // Draws diagram's X-axel
    int i = 0;
    while (currentX <= DIAGRAM_WIDTH)
    {
        painter.drawLine(currentX + diagramStemStart.x(), currentY, currentX + diagramStemStart.x(), currentY - 300);
        painter.drawText(currentX + diagramStemStart.x(), currentY + 20, timeList[i]);
        currentX += this->diagramGapHorizontal;
        i++;
    }

    currentX = diagramStemStart.x();
    currentY = 0;

    i = 0;
    // Draws diagram's Y-axel
    while (currentY >= -(DIAGRAM_HEIGHT))
    {
        painter.drawLine(currentX, diagramStemStart.y() + currentY, currentX+400, diagramStemStart.y() + currentY);
        painter.drawText(currentX - 25, diagramStemStart.y() + currentY, speedList[i]);
        currentY -= this->diagramGapStem;
        i++;
    }

    painter.setPen(QPen((Qt::white),2));

    // Draws result line to the diagram
    if (this->diagramGapStem == DIAGRAMGAP100KMH)
    {
        painter.drawPolyline(points, 11);
    }

    else if (this->diagramGapStem == DIAGRAMGAP80KMH)
    {
        painter.drawPolyline(points, 9);
    }

    else if (this->diagramGapStem == DIAGRAMGAP60KMH)
    {
        painter.drawPolyline(points, 7);
    }

    else if (this->diagramGapStem == DIAGRAMGAP50KMH)
    {
        painter.drawPolyline(points, 6);
    }

    else
    {
        painter.drawPolyline(points, 5);
    }
}

/**
  * Change the given speed and time to the point for the diagram.
  * @param aSpeed is speed which need to change, aTime is time in seconds which need to change.
  * @return point is calculated from aSpeed and aTime.
  */
QPoint ResultDialog::changeMeasuresToDiagramPoint(int aSpeed, qreal aTime)
{
    QPoint point;

    int speedAsPixels;
    int timeAsPixels;

    // Calculate speed and time to the point which can be drawn to the diagram
    if (this->diagramGapStem == DIAGRAMGAP100KMH)
    {
        speedAsPixels = DIAGRAM_HEIGHT*aSpeed/100;
        timeAsPixels = DIAGRAM_WIDTH*aTime/10;
    }

    else if (this->diagramGapStem == DIAGRAMGAP80KMH)
    {
        speedAsPixels = DIAGRAM_HEIGHT*aSpeed/80;
        timeAsPixels = DIAGRAM_WIDTH*aTime/10;
    }

    else if (this->diagramGapStem == DIAGRAMGAP60KMH)
    {
        speedAsPixels = DIAGRAM_HEIGHT*aSpeed/60;
        timeAsPixels = DIAGRAM_WIDTH*aTime/10;
    }

    else if (this->diagramGapStem == DIAGRAMGAP50KMH)
    {
        speedAsPixels = DIAGRAM_HEIGHT*aSpeed/50;
        timeAsPixels = DIAGRAM_WIDTH*aTime/10;
    }

    else
    {
        speedAsPixels = DIAGRAM_HEIGHT*aSpeed/40;
        timeAsPixels = DIAGRAM_WIDTH*aTime/10;
    }
    point.setY(diagramStemStart.y()-speedAsPixels);
    point.setX(diagramStemStart.x()+timeAsPixels);

    return point;
}

/**
  * Saves the given measures to array.
  * @param pMeasures has information about acceleration.
  */
void ResultDialog::saveMeasuresToArray(Measures *pMeasures)
{
    timeArray[0] = 0;
    timeArray[1] = pMeasures->getTime10kmh();
    timeArray[2] = pMeasures->getTime20kmh();
    timeArray[3] = pMeasures->getTime30kmh();
    timeArray[4] = pMeasures->getTime40kmh();
    timeArray[5] = pMeasures->getTime50kmh();
    timeArray[6] = pMeasures->getTime60kmh();
    timeArray[7] = pMeasures->getTime70kmh();
    timeArray[8] = pMeasures->getTime80kmh();
    timeArray[9] = pMeasures->getTime90kmh();
    timeArray[10] = pMeasures->getTime100kmh();

    for (int i = 0; i < 11; i++)
    {
        points[i] = changeMeasuresToDiagramPoint(speedArray[i], timeArray[i]);
    }

    setTimesIntoLabels();
    this->repaint();

    for (int i = 0; i < 11; i++)
    {
        timeArray[i] = 0;
    }
}

void ResultDialog::on_pushButtonSend_clicked()
{
    emit sendresult();
}

/**
  * Saves the given diagram gap to the member variable.
  * @param pDiagramGapStem has information about the right gap for diagram stem axel.
  */
void ResultDialog::setDiagramGapStem(double pDiagramGapStem)
{
    this->diagramGapStem = pDiagramGapStem;
}

/**
  * Saves the given diagram gap to the member variable.
  * @param pDiagramGapHorizontal has information about the right gap for diagram horizontal axel.
  */
void ResultDialog::setDiagramGapHorizontal(double pDiagramGapHorizontal)
{
    this->diagramGapHorizontal = pDiagramGapHorizontal;
}

/**
  * Sets result times in to the labels and shows only wanted results and hides
  * unwanted.
  */
void ResultDialog::setTimesIntoLabels()
{
    QString time, timeInteger;
    timeInteger.setNum(timeArray[4]);
    time = "0 - 40 km/h: ";
    time.append(timeInteger);
    ui->labelResult40kmh->setText(time);

    timeInteger.setNum(timeArray[3]);
    time = "0 - 30 km/h: ";
    time.append(timeInteger);
    ui->labelResult30kmh->setText(time);

    timeInteger.setNum(timeArray[2]);
    time = "0 - 20 km/h: ";
    time.append(timeInteger);
    ui->labelResult20kmh->setText(time);

    timeInteger.setNum(timeArray[1]);
    time = "0 - 10 km/h: ";
    time.append(timeInteger);
    ui->labelResult10kmh->setText(time);

    timeInteger.setNum(timeArray[6]);
    time = "0 - 60 km/h: ";
    time.append(timeInteger);
    ui->labelResult60kmh->setText(time);

    timeInteger.setNum(timeArray[5]);
    time = "0 - 50 km/h: ";
    time.append(timeInteger);
    ui->labelResult50kmh->setText(time);

    timeInteger.setNum(timeArray[7]);
    time = "0 - 70 km/h: ";
    time.append(timeInteger);
    ui->labelResult70kmh->setText(time);

    timeInteger.setNum(timeArray[8]);
    time = "0 - 80 km/h: ";
    time.append(timeInteger);
    ui->labelResult80kmh->setText(time);

    timeInteger.setNum(timeArray[9]);
    time = "0 - 90 km/h: ";
    time.append(timeInteger);
    ui->labelResult90kmh->setText(time);

    timeInteger.setNum(timeArray[10]);
    time = "0 - 100 km/h: ";
    time.append(timeInteger);
    ui->labelResult100kmh->setText(time);

    if (this->diagramGapStem == DIAGRAMGAP40KMH)
    {
        ui->labelResult50kmh->hide();
        ui->labelResult60kmh->hide();
        ui->labelResult70kmh->hide();
        ui->labelResult80kmh->hide();
        ui->labelResult90kmh->hide();
        ui->labelResult100kmh->hide();
    }

    else
    {
        ui->labelResult50kmh->show();
        ui->labelResult60kmh->show();
        ui->labelResult70kmh->show();
        ui->labelResult80kmh->show();
        ui->labelResult90kmh->show();
        ui->labelResult100kmh->show();
    }
}
