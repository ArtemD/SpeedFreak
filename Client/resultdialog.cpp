/*
 * CarMainWindow main class
 *
 * @author     Janne Änäkkälä <janne.anakkala@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "resultdialog.h"
#include "ui_resultdialog.h"
#include "math.h"
#include <QPainter>
#include <QPicture>

const int DIAGRAM_WIDTH = 400;
const int DIAGRAM_HEIGHT = 300;

const int DIAGRAMGAP10KMH = 300;
const int DIAGRAMGAP20KMH = 150;
const int DIAGRAMGAP30KMH = 100;
const int DIAGRAMGAP40KMH = 75;
const int DIAGRAMGAP50KMH = 60;
const int DIAGRAMGAP60KMH = 50;
const double DIAGRAMGAP70KMH = 42.86;
const double DIAGRAMGAP80KMH = 37.5;
const double DIAGRAMGAP90KMH = 33.33;
const int DIAGRAMGAP100KMH = 30;

const int DIAGRAMGAP5S = 80;
const int DIAGRAMGAP10S = 40;
const int DIAGRAMGAP20S = 20;

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
    timeAxelLength = 10;
    speedList << "0" << "10" << "20" << "30" << "40" << "50" << "60" << "70" << "80" << "90" << "100" ;
    timeList << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10" << "11"
            << "12" << "13" << "14" << "15" << "16" << "17" << "18" << "19" << "20";
    for (int i = 0; i < 11; i++)
    {
        timeArray[i] = 0;
    }
    /*
    // TODO check that logging is ok.
    if (isloggingNotOk)
    {
        ui->pushButtonSend->setEnabled(false);
    }
    else
    {
        ui->pushButtonSend->setEnabled(true);
    }
    */
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
    QString resultString;
    resultString.append("Time was ");

    if (this->diagramGapStem == DIAGRAMGAP100KMH)
    {
        resultString.append(QString::number(timeArray[10]));
        this->setWindowTitle("Result for accelerating 100 km/h");
    }

    else if (this->diagramGapStem == DIAGRAMGAP80KMH)
    {
        resultString.append(QString::number(timeArray[8]));
        this->setWindowTitle("Result for accelerating 80 km/h");
    }

    else
    {
        resultString.append(QString::number(timeArray[4]));
        this->setWindowTitle("Result for accelerating 40 km/h");
    }

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen((Qt::gray),2));
    QFont font;
    QFont fontForResult;
    font.setPixelSize(12);
    painter.setFont(font);
    painter.setBrush(QBrush((Qt::yellow), Qt::SolidPattern));

    fontForResult.setPixelSize(50);
    painter.setFont(fontForResult);
    painter.drawText(diagramStemStart.x() + 50, diagramStemStart.y() - 150, resultString);
    painter.setFont(font);

    painter.setPen(QPen((Qt::darkCyan),2));
    painter.drawLine(diagramStemStart, diagramStemEnd);
    painter.drawLine(diagramHorizontalStart, diagramHorizontalEnd);

    int currentX = 0;
    int currentY = diagramStemStart.y();

    painter.setPen(QPen((Qt::darkCyan),1));

    int i = 0;
    // Draws diagram's X-axel
    while (currentX <= DIAGRAM_WIDTH)
    {
        painter.drawLine(currentX + diagramStemStart.x(), currentY, currentX + diagramStemStart.x(), currentY - 300);
        painter.drawText(currentX + diagramStemStart.x() - 3, currentY + 20, timeList[i]);
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
        painter.drawText(currentX - 25, diagramStemStart.y() + currentY + 3, speedList[i]);
        currentY -= this->diagramGapStem;
        i++;
    }

    painter.setPen(QPen((Qt::red),2));

    int pointsToShow = 0;
    bool pointsUnderDiagramWidth = true;

    for (i = 0; i < 11 ; i++)
    {
        if (points[i].x() > diagramHorizontalEnd.x())
        {
            pointsToShow = i;
            pointsUnderDiagramWidth = false;
            i = 10;
        }
    }

    // Draws result line to the diagram
    if (this->diagramGapStem == DIAGRAMGAP100KMH)
    {
        if (pointsUnderDiagramWidth)
        {
            painter.drawPolyline(points, 11);
        }

        else
        {
            painter.drawPolyline(points, pointsToShow);
        }
    }

    else if (this->diagramGapStem == DIAGRAMGAP80KMH)
    {
        if (pointsUnderDiagramWidth)
        {
            painter.drawPolyline(points, 9);
        }

        else
        {
            painter.drawPolyline(points, pointsToShow);
        }
    }

    else if (this->diagramGapStem == DIAGRAMGAP60KMH)
    {
        if (pointsUnderDiagramWidth)
        {
            painter.drawPolyline(points, 7);
        }

        else
        {
            painter.drawPolyline(points, pointsToShow);
        }
    }

    else if (this->diagramGapStem == DIAGRAMGAP50KMH)
    {
        if (pointsUnderDiagramWidth)
        {
            painter.drawPolyline(points, 6);
        }

        else
        {
            painter.drawPolyline(points, pointsToShow);
        }
    }

    else
    {
        if (pointsUnderDiagramWidth)
        {
            painter.drawPolyline(points, 5);
        }

        else
        {
            painter.drawPolyline(points, pointsToShow);
        }
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
        timeAsPixels = DIAGRAM_WIDTH*aTime/timeAxelLength;
    }

    else if (this->diagramGapStem == DIAGRAMGAP80KMH)
    {
        speedAsPixels = DIAGRAM_HEIGHT*aSpeed/80;
        timeAsPixels = DIAGRAM_WIDTH*aTime/timeAxelLength;
    }

    else if (this->diagramGapStem == DIAGRAMGAP60KMH)
    {
        speedAsPixels = DIAGRAM_HEIGHT*aSpeed/60;
        timeAsPixels = DIAGRAM_WIDTH*aTime/timeAxelLength;
    }

    else if (this->diagramGapStem == DIAGRAMGAP50KMH)
    {
        speedAsPixels = DIAGRAM_HEIGHT*aSpeed/50;
        timeAsPixels = DIAGRAM_WIDTH*aTime/timeAxelLength;
    }

    else
    {
        speedAsPixels = DIAGRAM_HEIGHT*aSpeed/40;
        timeAsPixels = DIAGRAM_WIDTH*aTime/timeAxelLength;
    }
    point.setY(diagramStemStart.y()-speedAsPixels);
    point.setX(diagramStemStart.x()+timeAsPixels);

    return point;
}

/**
  * Saves the given measures to array.
  * @param pMeasures has information about acceleration.
  */
/*
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

    setTimeAxelLength();

    for (int i = 0; i < 11; i++)
    {
        points[i] = changeMeasuresToDiagramPoint(speedArray[i], timeArray[i]);
    }

    setTimesIntoLabels();
    this->repaint();
}*/

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

    else if (this->diagramGapStem == DIAGRAMGAP80KMH)
    {
        ui->labelResult50kmh->show();
        ui->labelResult60kmh->show();
        ui->labelResult70kmh->show();
        ui->labelResult80kmh->show();
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

/**
  * Sets right timeAxelLength value depending the time which
  * has spent to reach target speed.
  */
void ResultDialog::setTimeAxelLength()
{
    if (this->diagramGapStem == DIAGRAMGAP40KMH)
    {
        if (timeArray[4] <= 5)
        {
            timeAxelLength = 5;
        }

        else if (timeArray[4] <= 10)
        {
            timeAxelLength = 10;
        }

        else if (timeArray[4] <= 15)
        {
            timeAxelLength = 15;
        }

        else
        {
            timeAxelLength = 20;
        }
    }

    else if (this->diagramGapStem == DIAGRAMGAP80KMH)
    {
        if (timeArray[8] <= 5)
        {
            timeAxelLength = 5;
        }

        else if (timeArray[8] <= 10)
        {
            timeAxelLength = 10;
        }

        else if (timeArray[8] <= 15)
        {
            timeAxelLength = 15;
        }

        else
        {
            timeAxelLength = 20;
        }
    }

    else
    {
        if (timeArray[10] <= 5)
        {
            timeAxelLength = 5;
        }

        else if (timeArray[10] <= 10)
        {
            timeAxelLength = 10;
        }

        else if (timeArray[10] <= 15)
        {
            timeAxelLength = 15;
        }

        else
        {
            timeAxelLength = 20;
        }
    }
}

/**
  * This slot function close result dialog when new run -button has been clicked.
  */
void ResultDialog::on_pushButtonNew_clicked()
{
    for (int i = 0; i < 11; i++)
    {
        timeArray[i] = 0;
    }
    this->close();
}

/**
  * This slot function emits sendresult signal for sending results to server when
  * send results -button has been clicked.
  */
void ResultDialog::on_pushButtonSend_clicked()
{
    if (this->diagramGapStem == DIAGRAMGAP100KMH)
    {
        emit sendresult(timeArray[10]);
    }

    else if (this->diagramGapStem == DIAGRAMGAP80KMH)
    {
        emit sendresult(timeArray[8]);
    }

    else
    {
        emit sendresult(timeArray[4]);
    }
}

/**
  * This public function sets diagram's stem gap
  * @param pValue is the speed value which determines diagram gap's value
  */
void ResultDialog::setEnd(int pValue)
{
    switch (pValue)
    {
    case 10:
        this->diagramGapStem = DIAGRAMGAP10KMH;
        break;

    case 20:
        this->diagramGapStem = DIAGRAMGAP20KMH;
        break;

    case 30:
        this->diagramGapStem = DIAGRAMGAP30KMH;
        break;

    case 40:
        this->diagramGapStem = DIAGRAMGAP40KMH;
        break;

    case 50:
        this->diagramGapStem = DIAGRAMGAP50KMH;
        break;

    case 60:
        this->diagramGapStem = DIAGRAMGAP60KMH;
        break;

    case 70:
        this->diagramGapStem = DIAGRAMGAP70KMH;
        break;

    case 80:
        this->diagramGapStem = DIAGRAMGAP80KMH;
        break;

    case 90:
        this->diagramGapStem = DIAGRAMGAP90KMH;
        break;

    case 100:
        this->diagramGapStem = DIAGRAMGAP100KMH;
        break;

    default:
        this->diagramGapStem = DIAGRAMGAP100KMH;
        break;
    }

}

/**
  * This public function stores times in timeArray
  * @param pSpeed is the speed value at the time so we know where store time
  * @param pTime is the result which needs to be store in timeArray
  */
void ResultDialog::setValue(int pSpeed, double pTime)
{
    timeArray[0] = 0;
    if (floor(pTime) <= 5)
    {
        this->diagramGapHorizontal = DIAGRAMGAP5S;
    }

    else if (floor(pTime) <= 10)
    {
       this->diagramGapHorizontal = DIAGRAMGAP10S;
    }

    else
    {
        this->diagramGapHorizontal = DIAGRAMGAP20S;
    }

    switch (pSpeed)
    {
    case 10:
        timeArray[1] = pTime;
        break;
    case 20:
        timeArray[2] = pTime;
        break;
    case 30:
        timeArray[3] = pTime;
        break;
    case 40:
        timeArray[4] = pTime;
        break;
    case 50:
        timeArray[5] = pTime;
        break;
    case 60:
        timeArray[6] = pTime;
        break;
    case 70:
        timeArray[7] = pTime;
        break;
    case 80:
        timeArray[8] = pTime;
        break;
    case 90:
        timeArray[9] = pTime;
        break;
    case 100:
        timeArray[10] = pTime;
        break;
    }
    setTimeAxelLength();

    for (int i = 0; i < 11; i++)
    {
        points[i] = changeMeasuresToDiagramPoint(speedArray[i], timeArray[i]);
    }

    setTimesIntoLabels();
    this->repaint();
}
