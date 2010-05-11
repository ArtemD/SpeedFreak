/*
 * Result dialog
 *
 * @author     Janne Änäkkälä <janne.anakkala@fudeco.com>
 * @author     Toni Jussila 	<toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "resultdialog.h"
#include "ui_resultdialog.h"
#include "usersettings.h"
#include "math.h"
#include <QPainter>
#include <QPicture>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

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
const int DIAGRAMGAP16S = 25;
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

    helpAccelerationDialog = NULL;

    timeAxelLength = 10;
    resultString = "";
    speedList << "0" << "10" << "20" << "30" << "40" << "50" << "60" << "70" << "80" << "90" << "100" ;
    timeList << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10" << "11"
            << "12" << "13" << "14" << "15" << "16" << "17" << "18" << "19" << "20";
    this->diagramGapStem = DIAGRAMGAP100KMH;
    this->diagramGapHorizontal = DIAGRAMGAP20S;
    for (int i = 0; i < 11; i++)
    {
        timeArray[i] = 0;
    }

    //Clear info label
    ui->labelInfoToUser->setText("");

    if (loginSaved())
    {
        ui->pushButtonSend->setEnabled(true);
    }
    else
    {
        ui->pushButtonSend->setEnabled(false);
        ui->labelInfoToUser->setText("You're not logged! Please register or log in and accelerate again.");
    }
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
    setHeaders();
    //Create Pixmap, where image will be draw
    QPixmap image(ui->scrollArea->width(), ui->scrollArea->height()/*DIAGRAM_WIDTH+100, DIAGRAM_HEIGHT+70*/);
	
    //Create painter and give paramemeter where image will be draw
    QPainter painter(&image);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawRect(QRect(0, 0, ui->scrollArea->width(), ui->scrollArea->height()/*DIAGRAM_WIDTH+100, DIAGRAM_HEIGHT+70*/));
    

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen((Qt::gray),2));
    QFont font;
    QFont fontForResult;
    font.setPixelSize(12);
    painter.setFont(font);
    painter.setBrush(QBrush((Qt::yellow), Qt::SolidPattern));

    fontForResult.setPixelSize(50);
    painter.setFont(fontForResult);
    painter.drawText(diagramStemStart.x() + 30, diagramStemStart.y() - 150, resultString);
    painter.setFont(font);

    painter.setPen(QPen((Qt::darkCyan),2));
    painter.drawLine(diagramStemStart, diagramStemEnd);
    painter.drawLine(diagramHorizontalStart, diagramHorizontalEnd);
    painter.drawText(diagramStemStart.x() - 50, diagramStemEnd.y() + 100, "S");
    painter.drawText(diagramStemStart.x() - 50, diagramStemEnd.y() + 115, "P");
    painter.drawText(diagramStemStart.x() - 50, diagramStemEnd.y() + 130, "E");
    painter.drawText(diagramStemStart.x() - 50, diagramStemEnd.y() + 145, "E");
    painter.drawText(diagramStemStart.x() - 50, diagramStemEnd.y() + 160, "D");
    painter.drawText(diagramStemStart.x() - 65, diagramStemEnd.y() + 180, "(km/h)");

    painter.drawText(diagramStemStart.x() + 140, diagramStemStart.y() + 40, "T");
    painter.drawText(diagramStemStart.x() + 150, diagramStemStart.y() + 40, "I");
    painter.drawText(diagramStemStart.x() + 155, diagramStemStart.y() + 40, "M");
    painter.drawText(diagramStemStart.x() + 165, diagramStemStart.y() + 40, "E");
    painter.drawText(diagramStemStart.x() + 180, diagramStemStart.y() + 40, "(s)");

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
    if (pointsUnderDiagramWidth)
    {
        painter.drawPolyline(points, this->getTargetChoice() + 1);
    }

    else
    {
        painter.drawPolyline(points, pointsToShow);
    }
    //Save image in file acceleration.png
    image.save("acceleration.png", 0, -1);

    //Create label
    QLabel *imageLabel = new QLabel(this);
    
    //Set image pixmap to label
    imageLabel->setPixmap(image);
    
    //Set image label to scrollArea
    ui->scrollArea->setWidget(imageLabel);

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
    speedAsPixels = (DIAGRAM_HEIGHT*aSpeed) / (this->getTargetChoice() * 10);
    timeAsPixels = DIAGRAM_WIDTH*aTime/timeAxelLength;

    point.setY(diagramStemStart.y()-speedAsPixels);
    point.setX(diagramStemStart.x()+timeAsPixels);

    return point;
}

/**
  * Sets result times in to the labels.
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

    showOrHideLabels();
}

/**
  * Sets right timeAxelLength value depending the time which
  * has spent to reach target speed.
  */
void ResultDialog::setTimeAxelLength(int pChoice)
{
    if (timeArray[pChoice] <= 5.0)
    {
        timeAxelLength = 5;
    }

    else if (timeArray[pChoice] <= 10.0 && timeArray[pChoice] > 5.0)
    {
        timeAxelLength = 10;
    }

    else if (timeArray[pChoice] <= 16.0 && timeArray[pChoice] > 10.0)
    {
        timeAxelLength = 16;
    }

    else
    {
        timeAxelLength = 20;
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
    resultString = "";
    this->close();
    emit rejected();
}

/**
  * This slot function emits sendresult signal for sending results to server when
  * send results -button has been clicked.
  * Emit accrealtimedialog sendresult.
  */
void ResultDialog::on_pushButtonSend_clicked()
{
    ui->pushButtonSend->setEnabled(false);
    emit sendresult(timeArray[this->getTargetChoice()]);
}

double ResultDialog::getResult()
{
    return timeArray[this->getTargetChoice()];
}

/**
  * This public function sets diagram's stem gap
  * @param pValue is the speed value which determines diagram gap's value
  */
void ResultDialog::setEnd(int pValue)
{
    for (int i = 0; i < 11; i++)
    {
        timeArray[i] = 0;
    }
    resultString = "";

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
  * This public function stores time in timeArray
  * @param pSpeed is the speed value at the time so we know where store time
  * @param pTime is the result which needs to be store in timeArray
  */
void ResultDialog::setValue(int pSpeed, double pTime)
{
    //timeArray[0] = 0;
    if (pTime <= 5.0)
    {
        this->diagramGapHorizontal = DIAGRAMGAP5S;
    }

    else if (pTime <= 10.0 && pTime > 5.0)
    {
       this->diagramGapHorizontal = DIAGRAMGAP10S;
    }

    else if (pTime <= 16.0 && pTime > 10.0)
    {
        this->diagramGapHorizontal = DIAGRAMGAP16S;
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

    setTimeAxelLength(getTargetChoice());

    for (int i = 0; i < 11; i++)
    {
        points[i] = changeMeasuresToDiagramPoint(speedArray[i], timeArray[i]);
    }

    setTimesIntoLabels();
    this->repaint();
}

/**
  * Sets dialog's heading and result text
  */
void ResultDialog::setHeaders()
{
    //QString resultString;
    resultString.append("Time was ");

    QString time;

    if (this->diagramGapStem == DIAGRAMGAP100KMH)
    {
        time.sprintf("%.2f", timeArray[10]);
        resultString.append(time);
        this->setWindowTitle("Result for accelerating 100 km/h");
    }

    else if (this->diagramGapStem == DIAGRAMGAP90KMH)
    {
        time.sprintf("%.2f", timeArray[9]);
        resultString.append(time);
        this->setWindowTitle("Result for accelerating 90 km/h");
    }

    else if (this->diagramGapStem == DIAGRAMGAP80KMH)
    {
        time.sprintf("%.2f", timeArray[8]);
        resultString.append(time);
        this->setWindowTitle("Result for accelerating 80 km/h");
    }

    else if (this->diagramGapStem == DIAGRAMGAP70KMH)
    {
        time.sprintf("%.2f", timeArray[7]);
        resultString.append(time);
        this->setWindowTitle("Result for accelerating 70 km/h");
    }

    else if (this->diagramGapStem == DIAGRAMGAP60KMH)
    {
        time.sprintf("%.2f", timeArray[6]);
        resultString.append(time);
        this->setWindowTitle("Result for accelerating 60 km/h");
    }

    else if (this->diagramGapStem == DIAGRAMGAP50KMH)
    {
        time.sprintf("%.2f", timeArray[5]);
        resultString.append(time);
        this->setWindowTitle("Result for accelerating 50 km/h");
    }

    else if (this->diagramGapStem == DIAGRAMGAP40KMH)
    {
        time.sprintf("%.2f", timeArray[4]);
        resultString.append(time);
        this->setWindowTitle("Result for accelerating 40 km/h");
    }

    else if (this->diagramGapStem == DIAGRAMGAP30KMH)
    {
        time.sprintf("%.2f", timeArray[3]);
        resultString.append(time);
        this->setWindowTitle("Result for accelerating 30 km/h");
    }

    else if (this->diagramGapStem == DIAGRAMGAP20KMH)
    {
        time.sprintf("%.2f", timeArray[2]);
        resultString.append(time);
        this->setWindowTitle("Result for accelerating 20 km/h");
    }

    else
    {
        time.sprintf("%.2f", timeArray[1]);
        resultString.append(time);
        this->setWindowTitle("Result for accelerating 10 km/h");
    }
}

/**
  * Shows only wanted results and hides
  * unwanted
  */
void ResultDialog::showOrHideLabels()
{
    if (this->diagramGapStem == DIAGRAMGAP10KMH)
    {
        ui->labelResult20kmh->hide();
        ui->labelResult30kmh->hide();
        ui->labelResult40kmh->hide();
        ui->labelResult50kmh->hide();
        ui->labelResult60kmh->hide();
        ui->labelResult70kmh->hide();
        ui->labelResult80kmh->hide();
        ui->labelResult90kmh->hide();
        ui->labelResult100kmh->hide();
    }

    else if (this->diagramGapStem == DIAGRAMGAP20KMH)
    {
        ui->labelResult10kmh->show();
        ui->labelResult20kmh->show();
        ui->labelResult30kmh->hide();
        ui->labelResult40kmh->hide();
        ui->labelResult50kmh->hide();
        ui->labelResult60kmh->hide();
        ui->labelResult70kmh->hide();
        ui->labelResult80kmh->hide();
        ui->labelResult90kmh->hide();
        ui->labelResult100kmh->hide();
    }

    else if (this->diagramGapStem == DIAGRAMGAP30KMH)
    {
        ui->labelResult10kmh->show();
        ui->labelResult20kmh->show();
        ui->labelResult30kmh->show();
        ui->labelResult40kmh->hide();
        ui->labelResult50kmh->hide();
        ui->labelResult60kmh->hide();
        ui->labelResult70kmh->hide();
        ui->labelResult80kmh->hide();
        ui->labelResult90kmh->hide();
        ui->labelResult100kmh->hide();
    }

    else if (this->diagramGapStem == DIAGRAMGAP40KMH)
    {
        ui->labelResult10kmh->show();
        ui->labelResult20kmh->show();
        ui->labelResult30kmh->show();
        ui->labelResult40kmh->show();
        ui->labelResult50kmh->hide();
        ui->labelResult60kmh->hide();
        ui->labelResult70kmh->hide();
        ui->labelResult80kmh->hide();
        ui->labelResult90kmh->hide();
        ui->labelResult100kmh->hide();
    }

    else if (this->diagramGapStem == DIAGRAMGAP50KMH)
    {
        ui->labelResult10kmh->show();
        ui->labelResult20kmh->show();
        ui->labelResult30kmh->show();
        ui->labelResult40kmh->show();
        ui->labelResult50kmh->show();
        ui->labelResult60kmh->hide();
        ui->labelResult70kmh->hide();
        ui->labelResult80kmh->hide();
        ui->labelResult90kmh->hide();
        ui->labelResult100kmh->hide();
    }

    else if (this->diagramGapStem == DIAGRAMGAP60KMH)
    {
        ui->labelResult10kmh->show();
        ui->labelResult20kmh->show();
        ui->labelResult30kmh->show();
        ui->labelResult40kmh->show();
        ui->labelResult50kmh->show();
        ui->labelResult60kmh->show();
        ui->labelResult70kmh->hide();
        ui->labelResult80kmh->hide();
        ui->labelResult90kmh->hide();
        ui->labelResult100kmh->hide();
    }

    else if (this->diagramGapStem == DIAGRAMGAP70KMH)
    {
        ui->labelResult10kmh->show();
        ui->labelResult20kmh->show();
        ui->labelResult30kmh->show();
        ui->labelResult40kmh->show();
        ui->labelResult50kmh->show();
        ui->labelResult60kmh->show();
        ui->labelResult70kmh->show();
        ui->labelResult80kmh->hide();
        ui->labelResult90kmh->hide();
        ui->labelResult100kmh->hide();
    }

    else if (this->diagramGapStem == DIAGRAMGAP80KMH)
    {
        ui->labelResult10kmh->show();
        ui->labelResult20kmh->show();
        ui->labelResult30kmh->show();
        ui->labelResult40kmh->show();
        ui->labelResult50kmh->show();
        ui->labelResult60kmh->show();
        ui->labelResult70kmh->show();
        ui->labelResult80kmh->show();
        ui->labelResult90kmh->hide();
        ui->labelResult100kmh->hide();
    }

    else if (this->diagramGapStem == DIAGRAMGAP90KMH)
    {
        ui->labelResult10kmh->show();
        ui->labelResult20kmh->show();
        ui->labelResult30kmh->show();
        ui->labelResult40kmh->show();
        ui->labelResult50kmh->show();
        ui->labelResult60kmh->show();
        ui->labelResult70kmh->show();
        ui->labelResult80kmh->show();
        ui->labelResult90kmh->show();
        ui->labelResult100kmh->hide();
    }

    else
    {
        ui->labelResult10kmh->show();
        ui->labelResult20kmh->show();
        ui->labelResult30kmh->show();
        ui->labelResult40kmh->show();
        ui->labelResult50kmh->show();
        ui->labelResult60kmh->show();
        ui->labelResult70kmh->show();
        ui->labelResult80kmh->show();
        ui->labelResult90kmh->show();
        ui->labelResult100kmh->show();
    }
}

/**
  * Checks which target speed has been choosed
  * @return targetChoice which tells to caller integer value about the target speed
  * e.g. 20 km/h is value 2 and 60 km/h is value 6
  */
int ResultDialog::getTargetChoice()
{

    int targetChoice = 0;

    if (this->diagramGapStem == DIAGRAMGAP10KMH)
    {
       targetChoice = 1;
    }

    else if (this->diagramGapStem == DIAGRAMGAP20KMH)
    {
        targetChoice = 2;
    }

    else if (this->diagramGapStem == DIAGRAMGAP30KMH)
    {
        targetChoice = 3;
    }

    else if (this->diagramGapStem == DIAGRAMGAP40KMH)
    {
        targetChoice = 4;
    }

    else if (this->diagramGapStem == DIAGRAMGAP50KMH)
    {
        targetChoice = 5;
    }

    else if (this->diagramGapStem == DIAGRAMGAP60KMH)
    {
        targetChoice = 6;
    }

    else if (this->diagramGapStem == DIAGRAMGAP70KMH)
    {
        targetChoice = 7;
    }

    else if (this->diagramGapStem == DIAGRAMGAP80KMH)
    {
        targetChoice = 8;
    }

    else if (this->diagramGapStem == DIAGRAMGAP90KMH)
    {
        targetChoice = 9;
    }

    else
    {
        targetChoice = 10;
    }
    return targetChoice;
}

void ResultDialog::setLabelInfoToUser(QString infoText)
{
    this->ui->labelInfoToUser->setText(infoText);
}

/**
  * This function enable send server button.
  */
void ResultDialog::setSendServerButtonEnabled()
{
    ui->pushButtonSend->setEnabled(true);
}

/**
  * This slot function called when ever info button clicked.
  */
void ResultDialog::on_pushButtonInfo_clicked()
{
    if(!helpAccelerationDialog)
    {
        helpAccelerationDialog = new HelpAccelerationDialog;
    }
    connect(helpAccelerationDialog, SIGNAL(rejected()), this, SLOT(killHelpDialog()));
    helpAccelerationDialog->show();
}

/**
  * This slot function called when ever dialog rejected.
  */
void ResultDialog::killHelpDialog()
{
    if(helpAccelerationDialog)
    {
        qDebug() << "__Result kill: helpAccelerationDialog";
        delete helpAccelerationDialog;
        helpAccelerationDialog = NULL;
    }
}
/**
  * This slot function opens E-mail application with attachment file
  * (acceleration.png). Image of resultdialog
  */

void ResultDialog::on_pushButtonEMail_clicked()
{
    QDesktopServices::openUrl(QUrl("mailto:name@domain.com?Subject=Acceleration Result&Body=Hi, Here are my acceleration result!&Attachment=acceleration.png"));
}
