/*
 * RouteDialog class
 *
 * @author     Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "routedialog.h"
#include "ui_routedialog.h"
#include <cmath>
#include <QPainter>
#include <QList>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

/*
  * Vector class
  */
class Vector
{
    qreal x, y, z;
public:
    Vector() { x=0.; y=0. ; z=0.; };
    Vector( qreal initX, qreal initY, qreal initZ) { x = initX, y = initY; z = initZ; };
    void setX( qreal newX) { x = newX; };
    void setY( qreal newY) { y = newY; };
    void setZ( qreal newZ) { z = newZ; };
    qreal getX() { return x; };
    qreal getY() { return y; };
    qreal getZ() { return z; };
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


class Viewing
{
    Vector atPoint, fromPoint, up, a1, a2, a3;
    qreal offsx, offsy, offsz;
    qreal dval;
    qreal angle;
public:
    qreal getOffsx() { return offsx; };
    qreal getOffsy() { return offsx; };
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
        Vector temp, dist;

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
        QString jono2 = QString("offsx %1 offsy %2 offsz %3").arg(offsx).arg(offsy).arg(offsz);
        QMessageBox::about(0,"offs x y z", jono2);
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

//Vector atPoint, fromPoint, up, a1, a2, a3;
//qreal offsx, offsy, offsz;

qreal objxmin, objxmax, objymin, objymax, objzmin, objzmax;
//qreal angle;
qreal a, b,c,d; //, dval;

#define maxof(val1,val2)  ((val1>val2)?val1:val2)
#define toradians( degrees) (degrees*0.017453293)

#define WIDTH 1.8

int length = 34; // 24;
int connection[50];

void setAtPoint( Viewing *v);
void setFromPoint( Viewing *v);
//void setEye();

Viewing view3d;

void dataMinMax( void);



RouteDialog::RouteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RouteDialog)
{
    ui->setupUi(this);
    left = 5; top = 5; right = 395; bottom = 195; // Limits in screen coordinates
}

RouteDialog::~RouteDialog()
{
    delete ui;
}

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
  * Draws route to the route dialog
  * @param QPaintEvent
 */
/* */
void RouteDialog::paintEvent(QPaintEvent *)
{
    // 2d draw
    int startx, starty; // Starting point of the route
    int i, maxi;
    qreal x1, y1, x2, y2;
    int scx1, scy1, scx2, scy2;
    Vector v1, v2;
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen((Qt::white),2));
    painter.setBrush(QBrush((Qt::yellow), Qt::SolidPattern));

    // Draw route window frame
    /*painter.drawLine(left,top,right,top);
    painter.drawLine(right,top,right,bottom);
    painter.drawLine(left,top,left,bottom);
    painter.drawLine(left,bottom,right,bottom);
    */

    maxi = vertexList.size()-1; // -1 to remove wrong last point !!!
    for (i=0; i<maxi-1; i++)
    {
        v1 = vertexList.at(i);
        v2 = vertexList.at(i+1);
        x1 = v1.getX(); y1 = v1.getY();
        x2 = v2.getX(); y2 = v2.getY();
        //QString jono = QString("x: %1 y: %2").arg(x1).arg(y1);
        //QMessageBox::about(0,"Tark",jono);

        scx1 = left + (x1-xmin)/(xmax-xmin)*(right-left);
        scy1 = top + (ymax-y1)/(ymax-ymin)*(bottom-top);
        scx2 = left + (x2-xmin)/(xmax-xmin)*(right-left);
        scy2 = top + (ymax-y2)/(ymax-ymin)*(bottom-top);

        // Show with circle if starting point
        if (i==0)
        {
            // Starting point
            startx = scx1; starty = scy1;
            painter.drawEllipse( scx1-5, scy1-5, 10, 10);
        }
        painter.drawLine( scx1, scy1, scx2, scy2);
    }
    // Show the endig point if different than the starting point
    if (scx2 != startx || scy2 != starty)
    {
        painter.drawEllipse( scx2-5, scy2-5, 10, 10);
    }
}
/* */

void RouteDialog::on_closePushButton_clicked()
{
    close();
}

bool RouteDialog::readRouteFromFile( QString &filename)
{
/* 2d */
    Vector temp;
    int i;
    QString rivi;
    QFile file;
    //file.setFileName("route.txt");
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Read Route"), "./", tr("Route Files (*.txt)"));

    file.setFileName( fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::about(0, "Error", "File not found");
        return false;
    }

    vertexList.clear();
    i = 0;
    //while( file.canReadLine())
    while(!file.atEnd())
    {
        QString str1, str2, str3;
        rivi = file.readLine();

        str1 = rivi.section(" ", 0, 0);
        if (str1.compare("Start:") == 0 || str1.compare("Stop:") == 0)
        {

        }
        else
        {
            //QMessageBox::about(0, "LUKEE", file.readLine());
            str1 = rivi.section(" ",  2, 2); // latitude y-value
            str2 = rivi.section(" ",  4, 4); // longitude x-value
            str3 = rivi.section(" ",  6, 6); // altitude z-value
            QString str = QString("la: %1 lo: %2 al: %3").arg(str1).arg(str2).arg(str3);
            //QMessageBox::about(0, "LUKEE", str);

            double x, y, z;
            x = str2.toDouble();
            y = str1.toDouble();
            z = str3.toDouble();
            temp.setX( x); // Longitude
            temp.setY( y);// Latitude
            temp.setZ( z);// altitude

           vertexList.append(temp);
        }
        i++;
    }

   // la: lo: al:
    file.close();

   /* */
     /* for 3D test */
     /*vertexList.append(Vector(0.0, 0.0, 0.0));
     vertexList.append(Vector(1.0, 1.0, 1.0));
     vertexList.append(Vector(1.0, 1.0, 0.0));

     vertexList.append(Vector(1.0, 0.0, 0.0));
     vertexList.append(Vector(1.0, 0.0, 1.0));
     vertexList.append(Vector(0.0, 1.0, 1.0));

     vertexList.append(Vector(0.0, 1.0, 0.0));
     vertexList.append(Vector(0.0, 0.0, 0.0));
     vertexList.append(Vector(0.0, 0.0, 1.0));
*/
     /* For 3d */
     //int i;
     for(i= 0; i<35; i++)
     {
         connection[i] = i;
     }
 /* connection[0] = 0;
 connection[1] = 1; connection[2] = 5; connection[3] = 8; connection[4] = -4;
 connection[5] =  5; connection[6] = 6; connection[7] = 7; connection[8] = -8;
 connection[9] =  6; connection[10] = 2; connection[11] = 3; connection[12] = -7;
 connection[13] = 1; connection[14] = 4; connection[15] = 3; connection[16] = -2;
 connection[17] = 8; connection[18] = 7; connection[19] = 3; connection[20] = -4;
 connection[21] = 6;  connection[22] = 5; connection[23] = 1;  connection[24] = -2;*/

     /********  in 3d use only */
     a = 400/2.;
     b = 1 - a*(-1);
     c = -300/2.;
     d = 300 - c*(-1);
     //angle = toradians(60);

     view3d.setUp( 0.0, 0.0, 1.0);
     view3d.setAngle(toradians(60));
     setAtPoint( &view3d);
     xmin = objxmin; xmax = objxmax; ymin = objymin; ymax = objymax;
     setFromPoint( &view3d);
     view3d.setEye();
     /****** end of 3d *****/
     return true;
}

/*
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

    maxi = vertexList.size()-1; // Wrong last data
    //maxi = 9;
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


void setAtPoint( Viewing *v)
{
    qreal x, y, z;
    dataMinMax();
    Vector test;
    //atPoint.setX((
            x = (objxmax+objxmin)/2.0;
    //atPoint.setY(
            y= (objymax+objymin)/2.0;
    //atPoint.setZ(
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

void setFromPoint( Viewing *v)
{
    qreal x, y, z;
    Vector point;
    point = v->getAtPoint();
    Vector test;
    //fromPoint.setX( atPoint.getX() + (objxmax-objxmin)/2.0 + WIDTH*maxof((objzmax-objzmin)/2.0,(objymax-objymin)/2.0));
    //fromPoint.setX(
            //x = 3.0;
            x = point.getX() + 300; //25;
    //fromPoint.setY(
            y = point.getY();
    //fromPoint.setZ(
            z = point.getZ(); // + 150;
            v->setFromPoint(x,y,z);
    //QString jono = QString("FromX %1 FromY %2 FromZ %3").arg(fromPoint.x()).arg(fromPoint.y()).arg(fromPoint.z());
    //QString jono = QString("FromX %1 FromY %2 FromZ %3").arg(fromPoint.x).arg(fromPoint.y).arg(fromPoint.z);
    /* *
    test = v->getFromPoint();
    QString jono = QString("FromX %1 FromY %2 FromZ %3").arg(test.getX()).arg(test.getY()).arg(test.getZ());
    QMessageBox::about(0,"From point", jono); // (1.9, 0.5, 0.5)
    * */
}

/*void setEye()
{
    double amarkmag, tempmag;
    Vector temp, dist;

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
}*/

#define NOEDGE     0x00
#define LEFTEDGE   0x01
#define RIGHTEDGE  0x02
#define BOTTOMEDGE 0x04
#define TOPEDGE    0x08
/*
  * Returns a code specifying which edge in the viewing pyramid was crossed.
  * There may be more than one.
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
/*
  * Converts clipped world coordinates to screen coordinates.
  */
void WORLDtoSCREEN( qreal xWorld, qreal yWorld, int *xScreen, int *yScreen)
{
   *xScreen = (int) (a*xWorld+b);
   *yScreen = (int) (c*yWorld+d);
}

/*
  * Clips the line segment in three-dimensional coordinates to the
  * viewing pyramid.
  */
void clip3d( qreal x1, qreal y1, qreal z1, qreal x2, qreal y2, qreal z2, int *xscreen1, int *yscreen1, int *xscreen2, int *yscreen2)
{
    int c,c1,c2;
    qreal x,y,z,t;

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
    //line( xscreen1, yscreen1, xscreen2, yscreen2);
}

/*
  * Transform the segment connecting the two vectors into the viewing plane.
  * clip3d() clips the line if needed.
  */
void transformseg( Viewing *v, Vector *v1, Vector *v2, int *xscreen1, int *yscreen1, int *xscreen2, int *yscreen2 )

{
    qreal x1, y1, z1, x2, y2, z2;
    qreal offsx, offsy, offsz;
    qreal dval;
    Vector a1, a2, a3;
    a1 = v->getA1();
    a2 = v->getA2();
    a3 = v->getA3();
    offsx = v->getOffsx();
    offsy = v->getOffsy();
    offsz = v->getOffsz();
    dval = v->getDval();

    x1 = (a1.getX()*v1->getX() + a1.getY()*v1->getY() + a1.getZ()*v1->getZ() + offsx)*dval;
    y1 = (a2.getX()*v1->getX() + a2.getY()*v1->getY() + a2.getZ()*v1->getZ() + offsy)*dval;
    z1 = a3.getX()*v1->getX() + a3.getY()*v1->getY() + a3.getZ()*v1->getZ() + offsz;

    x2 = (a1.getX()*v2->getX() + a1.getY()*v2->getY() + a1.getZ()*v2->getZ() + offsx)*dval;
    y2 = (a2.getX()*v2->getX() + a2.getY()*v2->getY() + a2.getZ()*v2->getZ() + offsy)*dval;
    z2 = a3.getX()*v2->getX() + a3.getY()*v2->getY() + a3.getZ()*v2->getZ() + offsz;

    clip3d(x1,y1,z1,x2,y2,z2, xscreen1, yscreen1, xscreen2, yscreen2 );
}

/*
  *
  * 3D route viewing
*
void RouteDialog::paintEvent(QPaintEvent *)
{
    int i, startofside;
    int xscreen1, yscreen1, xscreen2, yscreen2;
    Vector temp1, temp2;

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen((Qt::black),2));
    painter.setBrush(QBrush((Qt::yellow), Qt::SolidPattern));

    // Draw route window frsme
    //painter.drawLine(left,top,right,top);
    //painter.drawLine(right,top,right,bottom);
    //painter.drawLine(left,top,left,bottom);
    //painter.drawLine(left,bottom,right,bottom);

    i = 1;
    while (i<length)
    {
        temp1 = vertexList.at(connection[i-1]);
        temp2 = vertexList.at(connection[i]);
        transformseg( &view3d, &temp1,&temp2, &xscreen1, &yscreen1, &xscreen2, &yscreen2);

        painter.drawLine(xscreen1, yscreen1, xscreen2, yscreen2);
        if (i==1)
        {
            painter.drawEllipse( xscreen1-5, yscreen1-5, 10, 10);
        }
        i++;
    }
    /*
    i=1;
    while(i<length)
    {
        startofside = i;
        i++;
        while (connection[i] > 0)
        {
            //transformseg( &pa[connection[i-1]],&pa[connection[i]], &xpc1, &ypc1, &xpc2, &ypc2);
            temp1 = vertexList.at(connection[i-1]);
            temp2 = vertexList.at(connection[i]);
            transformseg( &view3d, &temp1,&temp2, &xscreen1, &yscreen1, &xscreen2, &yscreen2);

            painter.drawLine(xscreen1, yscreen1, xscreen2, yscreen2);
            if (i==2)
            {
                painter.drawEllipse( xscreen1-5, yscreen1-5, 10, 10);
            }
            i++;
        }
        // to last segment
        //transformseg( &pa[connection[i-1]],&pa[-connection[i]],&xpc1, &ypc1, &xpc2, &ypc2);
        temp1 = vertexList.at(connection[i-1]);
        temp2 = vertexList.at(-connection[i]);
        transformseg( &view3d, &temp1,&temp2, &xscreen1, &yscreen1, &xscreen2, &yscreen2);
        painter.drawLine(xscreen1, yscreen1, xscreen2, yscreen2);
        // from last segemt to start
        //transformseg( &pa[-connection[i]],&pa[connection[startofside]],&xpc1, &ypc1, &xpc2, &ypc2);
        temp1 = vertexList.at(-connection[i]);
        temp2 = vertexList.at(connection[startofside]);
        transformseg( &view3d, &temp1,&temp2, &xscreen1, &yscreen1, &xscreen2, &yscreen2);
        painter.drawLine(xscreen1, yscreen1, xscreen2, yscreen2);
        i++;
    }
    *
}
** */
