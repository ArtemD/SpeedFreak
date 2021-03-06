/*
 * RouteDialog class
 *
 * @author      Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
 * @author      Toni Jussila 	<toni.jussila@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "routesavedialog.h"
#include "routedialog.h"
#include "ui_routedialog.h"
#include "usersettings.h"
#include <cmath>
#include <QPainter>
#include <QList>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QPolygon>
#include <QDebug>

/**
  * Vector class.
  * In starting Qt 4.6 there is QVector3D.
  * Later (updating Qt version) this class can be removed.
  */
class Vector
{
    qreal x, y, z;      // Location
    qreal v;            // Velocity
public:
    Vector() { x=0.; y=0. ; z=0.; };
    Vector( qreal initX, qreal initY, qreal initZ) { x = initX, y = initY; z = initZ; };
    void setX( qreal newX) { x = newX; };
    void setY( qreal newY) { y = newY; };
    void setZ( qreal newZ) { z = newZ; };
    void setV( qreal newV) { v = newV; };
    qreal getX() { return x; };
    qreal getY() { return y; };
    qreal getZ() { return z; };
    qreal getV() { return v; };
    qreal length() { return sqrt(x*x+y*y+z*z); };
    Vector operator+(Vector v)
    {
        x = x + v.x; y = y + v.y; z = z + v.z;
        return *this;
    };
    Vector operator-(Vector v)
    {
        x = x - v.x; y = y - v.y; z = z - v.z;
        return *this;
    };
    Vector operator/(qreal c)
    {
        x = x/c; y = y/c; z = z/c;
        return *this;
    };
    Vector crossProduct( Vector a, Vector b)
    {
        x = a.y*b.z - a.z*b.y;
        y = a.z*b.x - a.x*b.z;
        z = a.x*b.y - a.y*b.x;
        return *this;
    };
};

/**
  * Viewing class.
  */
class Viewing
{
    Vector atPoint, fromPoint, up, a1, a2, a3;
    qreal offsx, offsy, offsz;
    qreal dval;
    qreal angle;
public:
    qreal getOffsx() { return offsx; };
    qreal getOffsy() { return offsy; };
    qreal getOffsz() { return offsz; };
    qreal getDval() { return dval; };
    void setAngle( qreal newA) { angle = newA; };
    void setUp( qreal newUpX, qreal newUpY, qreal newUpZ)
    {
        up.setX(newUpX); up.setY(newUpY); up.setZ(newUpZ);
    };
    void setAtPoint( qreal newX, qreal newY, qreal newZ)
    {
        atPoint.setX(newX); atPoint.setY(newY); atPoint.setZ(newZ);
    };
    void setFromPoint(qreal newX, qreal newY, qreal newZ)
    {
        fromPoint.setX(newX); fromPoint.setY(newY); fromPoint.setZ(newZ);
    }
    void setEye()
    {
        double amarkmag, tempmag;
        Vector temp;
        Vector dist;

        dval = cos(angle/2.0)/sin(angle/2.0);
        dist = atPoint-fromPoint;
        amarkmag = dist.length();
        a3 = dist/amarkmag;

        temp.crossProduct( dist, up);
        tempmag = temp.length();
        a1 = temp/tempmag;

        temp.crossProduct( a1, a3);
        tempmag = temp.length();
        a2 = temp/tempmag;

        offsx = -a1.getX()*fromPoint.getX() - a1.getY()*fromPoint.getY() - a1.getZ()*fromPoint.getZ();
        offsy = -a2.getX()*fromPoint.getX() - a2.getY()*fromPoint.getY() - a2.getZ()*fromPoint.getZ();
        offsz = -a3.getX()*fromPoint.getX() - a3.getY()*fromPoint.getY() - a3.getZ()*fromPoint.getZ();
        //QString jono2 = QString("offsx %1 offsy %2 offsz %3").arg(offsx).arg(offsy).arg(offsz);
        //QMessageBox::about(0,"offs x y z", jono2);
    } ;
    Vector getAtPoint() { return atPoint; };
    Vector getFromPoint() { return fromPoint; };
    Vector getA1() { return a1; };
    Vector getA2() { return a2; };
    Vector getA3() { return a3; };
    Viewing () {};
};

qreal xmax, xmin, ymin, ymax;       // Limits in world coordinates

QList<Vector> vertexList;           // Vertecies of route

qreal objxmin, objxmax, objymin, objymax, objzmin, objzmax; // data ranges

#define maxof(val1,val2)  ((val1>val2)?val1:val2)
#define toradians( degrees) (degrees*0.017453293)

#define WIDTH 1.8   // For 3d viewing only
qreal a, b,c,d; // Used for 3d viewing to calculate screen coordinates

Viewing view3d;   // Viewing settings for 3d

// Function prototypes
void dataMinMax( void);
void setAtPoint( Viewing *v);
void setFromPoint( Viewing *v);
void transformseg( Viewing *v, Vector *v1, Vector *v2, int *xscreen1, int *yscreen1, int *xscreen2, int *yscreen2 );

#define R 6378.140 // The radius of the earth by kilometers

/**
  * count distance of two points (defined by longitude & latitude)
  * on the surface of the earth.
  */
qreal countDistance(Vector *p1, Vector *p2)
{
    qreal dLon, dLat;   // delta of longitude & latitude
    qreal a, c;

    dLon = p2->getX() - p1->getX();     // longitude difference
    dLat = p2->getY() - p1->getY();     // latitude difference
    if (dLon <0) dLon = -dLon;
    if (dLat <0) dLat = -dLat;

    dLon = dLon*3.14/180;
    dLat = dLat*3.14/180;
    a = (sin(dLat/2.))*(sin(dLat/2.)) +
        (cos(p1->getY())*3.14/180)*(cos(p2->getY())*3.14/180)*(sin(dLon/2.))*(sin(dLon/2.));
    c = 2.*atan(sqrt(a)/sqrt(1-a));     // c is angle between points p1 & p2 with circel by radius 1.

    return R*c;   // Return distance in kilometers
}

/**
  * Constructor of this class.
  */
RouteDialog::RouteDialog(RouteSaveDialog *parent) :
    QDialog(parent), ui(new Ui::RouteDialog)
{
    qDebug() << "__RouteDialog";
    ui->setupUi(this);

    this->setWindowTitle("Route");
    left = 5; top = 5; right = 495; bottom = 295; // Limits in screen coordinates

    helpRoutingDialog = NULL;

    // Button settings
    ui->sendPushButton->setAutoFillBackground(true);
    ui->sendPushButton->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");

    // Clear labels
    ui->labelInfoToUser->setText("");
    ui->speedValueLabel->setText("");
    ui->avgSpeedValueLabel->setText("");

    // Check login
    checkLogin();

    // Set average speed
    QString average;
    ui->avgSpeedValueLabel->setText(average.sprintf("%.1f", parent->getAverageSpeed()) + " km/h");
    ui->distanceValueLabel->setText(parent->getDistanceTraveled() + " km");
}

/**
  * Destructor of this class.
  */
RouteDialog::~RouteDialog()
{
    qDebug() << "__~RouteDialog";
    if(ui)
        delete ui;
}

/**
  *
  */
void RouteDialog::changeEvent(QEvent *e)
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
  * Get left.
  *
  * @return int left
  */
int RouteDialog::getLeft()
{
    return left;
}

/**
  * Get right.
  *
  * @return int right
  */
int RouteDialog::getRight()
{
    return right;
}

/**
  * Get top.
  *
  * @return int top
  */
int RouteDialog::getTop()
{
    return top;
}

/**
  * Get bottom.
  *
  * @return int bottom
  */
int RouteDialog::getBottom()
{
    return bottom;
}

/**
  * draw flag
  *
  * @param RouteDialog*
  * @param QPainter*
  * @param int x
  * @param int y
  * @param QString startFinish
  */
void drawFlag( RouteDialog *rD, QPainter *p, int x, int y, QString startFinish)
{
    if (y> (rD->getTop() + 25))
    {
        // Upside
        p->drawLine(x,y,x,y-15);
        if (x <= (rD->getRight()-20))
        {
            // flag right
            p->drawLine( x,    y-25, x+10, y-20);
            p->drawLine( x+10, y-20, x,    y-15);
            p->drawLine( x,    y-15, x,    y-25);

            // Draw start or finish
            p->drawText(x+10, y, startFinish);
        }
        else
        {
            // Flag left
            p->drawLine( x,    y-25, x-10, y-20);
            p->drawLine( x-10, y-20, x,    y-15);
            p->drawLine( x,    y-15, x,    y-25);

            // Draw start or finish
            p->drawText(x+10, y, startFinish);
        }    
    }
    else if (y <= (rD->getTop() + 25))
    {
        // downside
        p->drawLine(x,y,x,y+15);
        if (x <= (rD->getRight()-20))
        {
            // flag right
            p->drawLine( x,    y+25, x+10, y+20);
            p->drawLine( x+10, y+20, x,    y+15);
            p->drawLine( x,    y+15, x,    y+25);

            // Draw start or finish
            p->drawText(x+10, y+15, startFinish);
        }
        else
        {
            // Flag left
            p->drawLine( x,    y+25, x-10, y+20);
            p->drawLine( x-10, y+20, x,    y+15);
            p->drawLine( x,    y+15, x,    y+25);

            // Draw start or finish
            p->drawText(x+10, y+15, startFinish);
        }
    }
}

/**
  * Draws route to the route dialog.
  * Type 0 is 2d viewing and type 1 is for 3d viewing
  *
  * @param QPaintEvent*
 */
/* */
void RouteDialog::paintEvent(QPaintEvent *)
{
    // Check login
    checkLogin();

    int type = 0; //  0 for 2d, 1 for 3d
    int startx = 0; // Starting x point of the route
    int starty = 0; // Starting y point of the route
    int i = 0;
    int maxi = 0;
    qreal x1, y1, x2, y2;
    int x1Screen = 0;
    int y1Screen = 0;
    int x2Screen = 0;
    int y2Screen = 0;
    Vector v1, v2;
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen((Qt::white),2));
    painter.setBrush(QBrush((Qt::yellow), Qt::SolidPattern));

    maxi = vertexList.size();

    for (i=0; i<maxi-1; i++)
    {
       v1 = vertexList.at(i);
       v2 = vertexList.at(i+1);

       if (type == 0)
       {    // 2d
            x1 = v1.getX(); y1 = v1.getY();
            x2 = v2.getX(); y2 = v2.getY();
            //QString jono = QString("x: %1 y: %2").arg(x1).arg(y1);
            //QMessageBox::about(0,"Tark",jono);

            x1Screen = left + (x1-xmin)/(xmax-xmin)*(right-left);
            y1Screen = top + (ymax-y1)/(ymax-ymin)*(bottom-top);
            x2Screen = left + (x2-xmin)/(xmax-xmin)*(right-left);
            y2Screen = top + (ymax-y2)/(ymax-ymin)*(bottom-top);
        }
        else if (type == 1)
        {   // 3d
            transformseg( &view3d, &v1,&v2, &x1Screen, &y1Screen, &x2Screen, &y2Screen);
        }

        // Show with circle if starting point
        if (i==0)
        {
            // Starting point
            startx = x1Screen; starty = y1Screen;
           // painter.drawEllipse( x1Screen-5, y1Screen-5, 10, 10);
           drawFlag( this, &painter,  x1Screen,  y1Screen, "Start" );
        }
        painter.drawLine( x1Screen, y1Screen, x2Screen, y2Screen);
    }
    // Show the endig point if different than the starting point
    if (x2Screen != startx || y2Screen != starty)
    {
        //painter.drawEllipse( x2Screen-5, y2Screen-5, 10, 10);
        drawFlag( this, &painter, x2Screen, y2Screen, "Finish" );
    }

    {
        qreal maxvx = 0; // max speed x point
        qreal maxvy = 0; // max speed y point
        qreal maxv = 0;  // max speed
        Vector v;

        maxv = 0.0;
        for (i=0; i<maxi-1; i++)
        {
            v = vertexList.at(i);
            if (v.getV() > maxv)
            {
                maxv = v.getV();
                maxvx = v.getX();
                maxvy = v.getY();
            }
        }
        // Translate world coordinates to screen coordinates
        x1Screen = left + (maxvx-xmin)/(xmax-xmin)*(right-left);
        y1Screen = top + (ymax-maxvy)/(ymax-ymin)*(bottom-top);

        // Show max velocity point by yellow circle
        painter.drawEllipse( x1Screen-5, y1Screen-5, 10, 10);
        painter.drawEllipse( ui->maxSpeedLabel->geometry().x()-15, ui->maxSpeedLabel->geometry().y()+15, 10, 10);

        QString jono;
        //jono = QString("%1 km/h").arg(maxv);
        jono.sprintf("%.1f km/h", maxv); // Show only 1 decimal
        ui->speedValueLabel->setText(jono);
    }
}

/**
  * read route from file
  *
  * @param QString route file
  */
bool RouteDialog::readRouteFromFile( QString &routeFile )
{
    QString rFile = routeFile;
    fileName = routeFile;
    Vector temp;
    QString rivi;
    QFile file;
    int progressbarInt = 5;
    int count;

    file.setFileName( rFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::about(0, "Error", "Empty file");
        return false;
    }
    emit progressbar(progressbarInt);
    vertexList.clear();

    while(!file.atEnd())
    {
        bool allRead;
        QString astr1, astr2, astr3, astr4;
        QString str1, str2, str3, str4;
        rivi = file.readLine();
        allRead = false;
        count = 0;
        while( !allRead)
        {
            astr1 = rivi.section(" ", count*4+1, count*4+1); // latitude=""
            astr2 = rivi.section(" ", count*4+2, count*4+2); // longitude=""
            astr3 = rivi.section(" ", count*4+3, count*4+3); // altitude=""
            astr4 = rivi.section(" ", count*4+4, count*4+4); // speed=""

            {
                double x, y, z, v;
                str1 = astr1.section('"',1,1);
                str2 = astr2.section('"',1,1);
                str3 = astr3.section('"',1,1);
                str4 = astr4.section('"',1,1);

                if (str1.length() > 0)
                {
                    x = str2.toDouble();// latitude y-value
                    y = str1.toDouble();// longitude x-value
                    z = str3.toDouble();// altitude z-value
                    v = str4.toDouble();// speed km/h
                    temp.setX( x); // Longitude
                    temp.setY( y); // Latitude
                    temp.setZ( z); // altitude
                    temp.setV( v);

                    vertexList.append(temp);
                    count++;
                }
                else
                {
                    allRead = true;
                }
            }
            if(progressbarInt < 50)
                progressbarInt++;
            emit progressbar(progressbarInt);
        }
    }
    file.close();

    if(count == 1) // Check is file empty.
    {
        progressbarInt = 50;
        emit progressbar(progressbarInt);
        qDebug() << "count: " + QString::number(count);
         /********  in 3d use only */
         a = 400/2.;
         b = 1 - a*(-1);
         c = -300/2.;
         d = 300 - c*(-1);
         emit progressbar(60);
         //angle = toradians(60);
         view3d.setUp( 1.0, 0.0, 0.0);
         emit progressbar(70);
         view3d.setAngle(toradians(60));
         emit progressbar(80);
         setAtPoint( &view3d); // If file is empty software crash here.
         emit progressbar(90);
         xmin = objxmin; xmax = objxmax; ymin = objymin; ymax = objymax; // 2d viewing needs this !!!!
         emit progressbar(95);
         setFromPoint( &view3d);
         emit progressbar(98);
         view3d.setEye();
         emit progressbar(99);
         /****** end of 3d *****/
         /*
         //Testing distance counting
         Vector a1, a2;
         qreal dist;
         //a1.setX( xmin); a1.setY( ymin);
         //a2.setX( xmax); a2.setY( ymax);
         a1.setX( 25.483); a1.setY( 65.017); // Oulu
         a2.setX( 27.767); a2.setY( 64.283); // Kajaani
         dist = countDistance( &a1, &a2);
         QString str = QString("Min & Max datan välimatka %1").arg(dist);
         QMessageBox::about( 0, "Testi", str);
         */
        emit progressbar(100);
        return true;
    }
    else // Probably file is empty.
    {
        QMessageBox::about(0, "Error", "Empty file");
        return false;
    }
}

/**
  * Find out data range for x-, y- and z-coordinates
  */
void dataMinMax( void)
{
    int i, maxi;
    qreal x,y,z;
    Vector temp;

    temp = vertexList.at(0);
    objxmax = objxmin = temp.getX();
    objymax = objymin = temp.getY();
    objzmax = objzmin = temp.getZ();

    maxi = vertexList.size();
    for (i=1; i<maxi; i++)
    {
        temp = vertexList.at(i);
        x = temp.getX();
        y = temp.getY();
        z = temp.getZ();

        if (x < objxmin)
        {
                objxmin = x;
        }
        else if (x > objxmax)
        {
               objxmax = x;
        }

        if (y < objymin)
        {
                objymin = y;
        }
        else if (y > objymax)
        {
               objymax = y;
        }

        if (z < objzmin)
        {
                objzmin = z;
        }
        else if (z > objzmax)
        {
               objzmax = z;
        }
    }
    //QString jono = QString("ojxmin %1 objxmax %2").arg(objxmin).arg(objxmax);
    //QString jono = QString("ojymin %1 objymax %2").arg(objymin).arg(objymax);
    //QString jono = QString("ojzmin %1 objzmax %2").arg(objzmin).arg(objzmax);
    //QMessageBox::about(0,"Tark", jono);
}

/**
  * Setting the point where the viewed object is. In the middle of datapoints.
  */
void setAtPoint( Viewing *v)
{
    qreal x, y, z;
    dataMinMax();
    //Vector test;

    x = (objxmax+objxmin)/2.0;
    y= (objymax+objymin)/2.0;
    z= (objzmax+objzmin)/2.0;

    v->setAtPoint( x, y, z);
    //QString jono = QString("AtX %1 Aty %2 AtZ %3").arg(atPoint.x()).arg(atPoint.y()).arg(atPoint.z());
    //QString jono = QString("AtX %1 Aty %2 AtZ %3").arg(atPoint.x).arg(atPoint.y).arg(atPoint.z);

    /* *
    test = v->getAtPoint();
    QString jono = QString("AtX %1 Aty %2 AtZ %3").arg(test.getX()).arg(test.getY()).arg(test.getZ());
    QMessageBox::about(0,"At point", jono);
    * */
}

/**
  * Setting the point where the object is viewed by eye.
  */
void setFromPoint( Viewing *v)
{
    qreal x, y, z;
    Vector point;
    point = v->getAtPoint();
    //Vector test;
    //fromPoint.setX( atPoint.getX() + (objxmax-objxmin)/2.0 + WIDTH*maxof((objzmax-objzmin)/2.0,(objymax-objymin)/2.0));
    //x = 3.0;
    //x = point.getX() + (objxmax-objxmin)/2.0 + WIDTH*maxof((objzmax-objzmin)/2.0,(objymax-objymin)/2.0);
    x = point.getX();
    //y = point.getY();
    y = point.getY() + 40; // + (objymax-objymin)/2.0 + WIDTH*maxof((objzmax-objzmin)/2.0,(objxmax-objxmin)/2.0);
    z = point.getZ();

    v->setFromPoint(x,y,z);
    //QString jono = QString("FromX %1 FromY %2 FromZ %3").arg(fromPoint.x()).arg(fromPoint.y()).arg(fromPoint.z());
    //QString jono = QString("FromX %1 FromY %2 FromZ %3").arg(fromPoint.x).arg(fromPoint.y).arg(fromPoint.z);
    /* *
    test = v->getFromPoint();
    QString jono = QString("FromX %1 FromY %2 FromZ %3").arg(test.getX()).arg(test.getY()).arg(test.getZ());
    QMessageBox::about(0,"From point", jono); // (1.9, 0.5, 0.5)
    * */
}

#define NOEDGE     0x00
#define LEFTEDGE   0x01
#define RIGHTEDGE  0x02
#define BOTTOMEDGE 0x04
#define TOPEDGE    0x08

/**
  * Returns a code specifying which edge in the viewing pyramid was crossed.
  * There may be more than one.
  *
  * @param qreal x
  * @param qreal y
  * @param qreal z
  * @return int
  */
int code( qreal x, qreal y, qreal z)
{
    int c;
    c = NOEDGE;
    if (x<-z) c |= LEFTEDGE;
    if (x>z) c |= RIGHTEDGE;
    if (y<-z) c |= BOTTOMEDGE;
    if (y>z) c |= TOPEDGE;
    return c;
}

/**
  * Converts clipped world coordinates to screen coordinates.
  *
  * @param qreal xWorld
  * @param qreal yWorld
  * @param int *xScreen
  * @param int *yScreen
  */
void WORLDtoSCREEN( qreal xWorld, qreal yWorld, int *xScreen, int *yScreen)
{
   *xScreen = (int) (a*xWorld+b);
   *yScreen = (int) (c*yWorld+d);
}

/**
  * Clips the line segment in three-dimensional coordinates to the
  * viewing pyramid.
  *
  * @param qreal x1
  * @param qreal y1
  * @param qreal z1
  * @param qreal x2
  * @param qreal y2
  * @param qreal z2
  * @param int *xscreen1
  * @param int *yscreen1
  * @param int *xscreen2
  * @param int *yscreen2
  */
void clip3d( qreal x1, qreal y1, qreal z1, qreal x2, qreal y2, qreal z2, int *xscreen1, int *yscreen1, int *xscreen2, int *yscreen2)
{
    int c = 0;
    int c1 = 0;
    int c2 = 0;
    qreal x = 0;
    qreal y = 0;
    qreal z = 0;
    qreal t = 0;

    c1 = code(x1,y1,z1);
    c2 = code(x2,y2,z2);

    while (c1!= NOEDGE || c2 != NOEDGE)
    {
        if ((c1 & c2 ) != NOEDGE) return;
        c = c1;
        if (c == NOEDGE) c = c2;
        if ((c&LEFTEDGE) == LEFTEDGE)
        {
                // Crosses left edge
                t = (z1+x1)/((x1-x2)-(z2-z1));
                z = t*(z2-z1)+z1;
                x = -z;
                y = t*(y2-y1)+y1;
        }
        else if ((c&RIGHTEDGE) == RIGHTEDGE)
        {
                // Crosses right edge
                t = (z1-x1)/((x2-x1)-(z2-z1));
                z = t*(z2-z1)+z1;
                x = z;
                y = t*(y2-y1)+y1;
        }
        else if ((c&BOTTOMEDGE) == BOTTOMEDGE)
        {
                // Crosses bottom edge
                t = (z1+y1)/((y1-y2)-(z2-z1));
                z = t*(z2-z1)+z1;
                x = t*(x2-x1)+x1;
                y = -z;
        }
        else if ((c&TOPEDGE) == TOPEDGE)
        {
                // Crosses top edge
                t = (z1-y1)/((y2-y1)-(z2-z1));
                z = t*(z2-z1)+z1;
                x = t*(x2-x1)+x1;
                y = z;
        }

        if (c == c1)
        {
            x1=x; y1=y; z1=z;
            c1 = code(x,y,z);
        }
        else
        {
            x2=x; y2=y; z2=z;
            c2 = code(x,y,z);
        }
    }

    if (z1 != 0)
    {
        WORLDtoSCREEN(x1/z1,y1/z1,xscreen1, yscreen1);
        WORLDtoSCREEN(x2/z2,y2/z2,xscreen2, yscreen2);
    }
    else
    {
        WORLDtoSCREEN(x1,y1,xscreen1, yscreen1);
        WORLDtoSCREEN(x2,y2,xscreen2, yscreen2);
    }
    //Now ready to draw line( xscreen1, yscreen1, xscreen2, yscreen2);
}

/**
  * Transform the segment connecting the two vectors into the viewing plane.
  * clip3d() clips the line if needed.
  *
  * @param Viewing *v
  * @param Vector *v1
  * @param Vector *v2
  * @param int *xscreen1
  * @param int *yscreen1
  * @param int *xscreen2
  * @param int *yscreen2
  */
void transformseg( Viewing *v, Vector *v1, Vector *v2, int *xscreen1, int *yscreen1, int *xscreen2, int *yscreen2)

{
    qreal x1, y1, z1, x2, y2, z2;
    Vector a1, a2, a3;

    a1 = v->getA1();
    a2 = v->getA2();
    a3 = v->getA3();

    x1 = (a1.getX()*v1->getX() + a1.getY()*v1->getY() + a1.getZ()*v1->getZ() + v->getOffsx())*v->getDval();
    y1 = (a2.getX()*v1->getX() + a2.getY()*v1->getY() + a2.getZ()*v1->getZ() + v->getOffsy())*v->getDval();
    z1 = a3.getX()*v1->getX() + a3.getY()*v1->getY() + a3.getZ()*v1->getZ() + v->getOffsz();

    x2 = (a1.getX()*v2->getX() + a1.getY()*v2->getY() + a1.getZ()*v2->getZ() + v->getOffsx())*v->getDval();
    y2 = (a2.getX()*v2->getX() + a2.getY()*v2->getY() + a2.getZ()*v2->getZ() + v->getOffsy())*v->getDval();
    z2 = a3.getX()*v2->getX() + a3.getY()*v2->getY() + a3.getZ()*v2->getZ() + v->getOffsz();

    clip3d(x1,y1,z1,x2,y2,z2, xscreen1, yscreen1, xscreen2, yscreen2 );
}

/**
  * This slot function is called when ever send push button clicked.
  */
void RouteDialog::on_sendPushButton_clicked()
{
    ui->sendPushButton->setEnabled(false);

    // Check default file dir.
    if(!QDir("/home/user/MyDocs/speedfreak/route").exists())
    {
        QDir().mkdir("/home/user/MyDocs/speedfreak/route");
    }

    // If file name is empty set it to default.
    if(fileName == "")
        fileName = "/home/user/MyDocs/speedfreak/route/";

    if(fileName == "/home/user/MyDocs/speedfreak/route/routetemp.xml")
        fileName = "/home/user/MyDocs/speedfreak/route/route.xml";

    qDebug() << "__FileName: " + fileName;
    QString newFileName = QFileDialog::getSaveFileName(this, tr("Save Route"), fileName);
    int server = QMessageBox::question(this, "Save route to server?", "", 4,3);

    if(server == 3) // Yes button
    {
        qDebug() << "__Save to server: yes";
        emit sendroute(newFileName,1); // Save route to server and phone.
    }
    else if(server == 4) // No button
    {
        qDebug() << "__Save to server: no";

        if(fileName != "")
            emit sendroute(newFileName,0); // Save route to phone.
    }
}

/**
  * This function is set info text to user.
  *
  * @param QString info text
  */
void RouteDialog::setLabelInfoToUser(QString infoText)
{
    this->ui->labelInfoToUser->setText(infoText);
}

/**
  * This function enable send server button.
  */
void RouteDialog::setSendServerButtonEnabled()
{
    ui->sendPushButton->setEnabled(true);
}

/**
  * This function check login and set send route to server button disabled/enabled.
  */
void RouteDialog::checkLogin()
{
    if (loginSaved())
    {
        ui->sendPushButton->setEnabled(true);
        ui->labelInfoToUser->setText("");
    }
    else
    {
        ui->sendPushButton->setEnabled(false);
        ui->labelInfoToUser->setText("You're not logged! Please register or log in.");
    }
}

/**
  * This slot function called when ever info button clicked.
  */
void RouteDialog::on_pushButtonInfo_clicked()
{    
    if(!helpRoutingDialog)
    {
        helpRoutingDialog = new HelpRoutingDialog;
    }
    connect(helpRoutingDialog, SIGNAL(rejected()), this, SLOT(killHelpDialog()));
    helpRoutingDialog->show();
}

/**
  * This slot function called when ever dialog rejected.
  */
void RouteDialog::killHelpDialog()
{
    if(helpRoutingDialog)
    {
        qDebug() << "__Route kill: helpRoutingDialog";
        delete helpRoutingDialog;
        helpRoutingDialog = NULL;
    }
}
