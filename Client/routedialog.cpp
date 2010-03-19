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
//#include <QMessageBox>

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

int left, top, right, bottom;       // Limits in screen coordinates
qreal xmax, xmin, ymin, ymax;       // Limits in world coordinates

QList<Vector> vertexList;           // Vertecies of route

Vector atPoint, fromPoint, up, a1, a2, a3;
qreal offsx, offsy, offsz;

qreal objxmin, objxmax, objymin, objymax, objzmin, objzmax;
qreal angle;
qreal a, b,c,d, dval;

#define maxof(val1,val2)  ((val1>val2)?val1:val2)
#define toradians( degrees) (degrees*0.017453293)

#define WIDTH 1.8

int length = 24;
int connection[30];

void setAtPoint();
void setFromPoint();
void setEye();

RouteDialog::RouteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RouteDialog)
{
    ui->setupUi(this);
    //left = 50; top = 50; right = 350; bottom = 200;
    left = 5; top = 5; right = 395; bottom = 295;
    xmin =0.0; xmax=100.0; ymin = 0.0; ymax = 20.0;
    // Ruudun koko 400 x 300

    /*vertexList.append(QVector3D(40.02, 10.02, 10.02));
   vertexList.append(QVector3D(50.01,  5.01, 10));
   vertexList.append(QVector3D(69.98,  4.98, 10));
   vertexList.append(QVector3D(80.02,  9.98, 10));
   vertexList.append(QVector3D(70.01, 15.01, 10));
   vertexList.append(QVector3D(49.99, 14.97, 10));
   vertexList.append(QVector3D(40.01, 10.01, 10.02));
*/
       vertexList.append(Vector(0.0, 0.0, 0.0));
       vertexList.append(Vector(1.0, 1.0, 1.0));
       vertexList.append(Vector(1.0, 1.0, 0.0));

       vertexList.append(Vector(1.0, 0.0, 0.0));
       vertexList.append(Vector(1.0, 0.0, 1.0));
       vertexList.append(Vector(0.0, 1.0, 1.0));

       vertexList.append(Vector(0.0, 1.0, 0.0));
       vertexList.append(Vector(0.0, 0.0, 0.0));
       vertexList.append(Vector(0.0, 0.0, 1.0));

   connection[0] = 0;
   connection[1] = 1; connection[2] = 5; connection[3] = 8; connection[4] = -4;
   connection[5] =  5; connection[6] = 6; connection[7] = 7; connection[8] = -8;
   connection[9] =  6; connection[10] = 2; connection[11] = 3; connection[12] = -7;
   connection[13] = 1; connection[14] = 4; connection[15] = 3; connection[16] = -2;
   connection[17] = 8; connection[18] = 7; connection[19] = 3; connection[20] = -4;
   connection[21] = 6;  connection[22] = 5; connection[23] = 1;  connection[24] = -2;

   fromPoint.setX( 1.0); fromPoint.setY( 0.0); fromPoint.setZ( 0.0);
   atPoint.setX( 0.0); atPoint.setY( 0.0); atPoint.setZ( 0.0);
   up.setX( 0.0); up.setY( 0.0); up.setZ(1.0);

   a = 400/2.;
   b = 1 - a*(-1);
   c = -300/2.;
   d = 300 - c*(-1);
   angle = toradians(60);

   setAtPoint();
   setFromPoint();
   setEye();
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
 *
void RouteDialog::paintEvent(QPaintEvent *)
{
    // 2d draw
    int i, maxi;
    qreal x1, y1, x2, y2;
    int scx1, scy1, scx2, scy2;

        QPainter painter(this);

        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen((Qt::black),2));
        painter.setBrush(QBrush((Qt::yellow), Qt::SolidPattern));

        // Draw route window frsme
        painter.drawLine(left,top,right,top);
        painter.drawLine(right,top,right,bottom);
        painter.drawLine(left,top,left,bottom);
        painter.drawLine(left,bottom,right,bottom);

        //maxi = vertexList.size();
        for (i=0; i<maxi-1; i++)
        {
            x1 = vertexList.at(i).x();
            y1 = vertexList.at(i).y();
            x2 = vertexList.at(i+1).x();
            y2 = vertexList.at(i+1).y();

            scx1 = left + (x1-xmin)/(xmax-xmin)*(right-left);
            scy1 = top + (ymax-y1)/(ymax-ymin)*(bottom-top);
            scx2 = left + (x2-xmin)/(xmax-xmin)*(right-left);
            scy2 = top + (ymax-y2)/(ymax-ymin)*(bottom-top);

            painter.drawLine( scx1, scy1, scx2, scy2);
        }
}
*/

void RouteDialog::on_closePushButton_clicked()
{
    close();
}

// Next functions below for 3D
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

void setAtPoint()
{
    dataMinMax();
    atPoint.setX((objxmax+objxmin)/2.0);
    atPoint.setY((objymax+objymin)/2.0);
    atPoint.setZ((objzmax+objzmin)/2.0);
    //QString jono = QString("AtX %1 Aty %2 AtZ %3").arg(atPoint.x()).arg(atPoint.y()).arg(atPoint.z());
    //QString jono = QString("AtX %1 Aty %2 AtZ %3").arg(atPoint.x).arg(atPoint.y).arg(atPoint.z);
    //QMessageBox::about(0,"At point", jono);
}

void setFromPoint()
{
    //fromPoint.setX( atPoint.getX() + (objxmax-objxmin)/2.0 + WIDTH*maxof((objzmax-objzmin)/2.0,(objymax-objymin)/2.0));
    fromPoint.setX(3.0);
    fromPoint.setY( atPoint.getY());
    fromPoint.setZ( atPoint.getZ());
    //QString jono = QString("FromX %1 FromY %2 FromZ %3").arg(fromPoint.x()).arg(fromPoint.y()).arg(fromPoint.z());
    //QString jono = QString("FromX %1 FromY %2 FromZ %3").arg(fromPoint.x).arg(fromPoint.y).arg(fromPoint.z);
    //QMessageBox::about(0,"From point", jono); // (1.9, 0.5, 0.5)
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
    //QString jono2 = QString("offsx %1 offsy %2 offsz %3").arg(offsx).arg(offsy).arg(offsz);
    //QMessageBox::about(0,"offs x y z", jono2);
}

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
void transformseg( Vector *v1, Vector *v2, int *xscreen1, int *yscreen1, int *xscreen2, int *yscreen2 )

{
    qreal x1, y1, z1, x2, y2, z2;

    x1 = (a1.getX()*v1->getX() + a1.getY()*v1->getY() + a1.getZ()*v1->getZ() + offsx)*dval;
    y1 = (a2.getX()*v1->getX() + a2.getY()*v1->getY() + a2.getZ()*v1->getZ() + offsy)*dval;
    z1 = a3.getX()*v1->getX() + a3.getY()*v1->getY() + a3.getZ()*v1->getZ() + offsz;

    x2 = (a1.getX()*v2->getX() + a1.getY()*v2->getY() + a1.getZ()*v2->getZ() + offsx)*dval;
    y2 = (a2.getX()*v2->getX() + a2.getY()*v2->getY() + a2.getZ()*v2->getZ() + offsy)*dval;
    z2 = a3.getX()*v2->getX() + a3.getY()*v2->getY() + a3.getZ()*v2->getZ() + offsz;

    clip3d(x1,y1,z1,x2,y2,z2, xscreen1, yscreen1, xscreen2, yscreen2 );
}

void RouteDialog::paintEvent(QPaintEvent *)
{
    int i, startofside;
    qreal x1, y1, x2, y2;
    int scx1, scy1, scx2, scy2;
    int xpc1, ypc1, xpc2, ypc2;
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
            transformseg( &temp1,&temp2, &xpc1, &ypc1, &xpc2, &ypc2);

            painter.drawLine(xpc1, ypc1, xpc2, ypc2);
            i++;
        }
        // to last segment
        //transformseg( &pa[connection[i-1]],&pa[-connection[i]],&xpc1, &ypc1, &xpc2, &ypc2);
        temp1 = vertexList.at(connection[i-1]);
        temp2 = vertexList.at(-connection[i]);
        transformseg( &temp1,&temp2, &xpc1, &ypc1, &xpc2, &ypc2);
        painter.drawLine(xpc1, ypc1, xpc2, ypc2);
        // from last segemt to start
        //transformseg( &pa[-connection[i]],&pa[connection[startofside]],&xpc1, &ypc1, &xpc2, &ypc2);
        temp1 = vertexList.at(-connection[i]);
        temp2 = vertexList.at(connection[startofside]);
        transformseg( &temp1,&temp2, &xpc1, &ypc1, &xpc2, &ypc2);
        painter.drawLine(xpc1, ypc1, xpc2, ypc2);
        i++;
    }
}
