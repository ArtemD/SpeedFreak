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
//#include <QVector3D>
//#include <QDebug>
//#include <stdio.h>
#include <QMessageBox>

typedef struct
{
    qreal x, y, z;
} VECTOR;

int left, top, right, bottom;  // Limits in screen coordinates
qreal xmax, xmin, ymin, ymax;                        // Limits in world coordinates

//QList<QVector3D> vertexList;    // Vertecies of route
QList<VECTOR> vertexList;

//QVector3D atPoint, fromPoint, up;
//QVector3D a1, a2, a3;
VECTOR atPoint, fromPoint, up, a1, a2, a3;
// QVector3D dist;
qreal offsx, offsy, offsz;

qreal objxmin, objxmax, objymin, objymax, objzmin, objzmax;
qreal t_from;
qreal angle;
qreal a, b,c,d, dval;

#define maxof(val1,val2)  ((val1>val2)?val1:val2)
#define toradians( degrees) (degrees*0.017453293)

#define WIDTH 1.8

int length = 24;
int connection[24] = { 1, 5, 8, -4,
                    5, 6, 7, -8,
                    6, 2, 3, -7,
                    1, 4, 3, -2,
                    8, 7, 3, -4,
                    6, 5, 1, -2 };
/*QVector3D pa[8] = { {1.,1.,1.},{1.,1.,0.},
                    {1.,0.,0.},{1.,0.,1.},
                                {0.,1.,1.},{0.,1.,0.},
                    {0.,0.,0.},{0.,0.,1.}};*/
//QVector3D pa[8];
VECTOR pa[8];

void setAtPoint();
void setFromPoint();
void setEye();

RouteDialog::RouteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RouteDialog)
{
    ui->setupUi(this);
    left = 50;
    top = 50;
    right = 350;
    bottom = 200;
    xmin =0.0; xmax=100.0; ymin = 0.0; ymax = 20.0;

    /*vertexList.append(QVector3D(40.02, 10.02, 10.02));
   vertexList.append(QVector3D(50.01,  5.01, 10));
   vertexList.append(QVector3D(69.98,  4.98, 10));
   vertexList.append(QVector3D(80.02,  9.98, 10));
   vertexList.append(QVector3D(70.01, 15.01, 10));
   vertexList.append(QVector3D(49.99, 14.97, 10));
   vertexList.append(QVector3D(40.01, 10.01, 10.02));
*/
    /*pa[0] = QVector3D(1.,1.,1.);
    pa[1] = QVector3D(1.,1.,0.);
        pa[2] = QVector3D(1.,0.,0.);
        pa[3] = QVector3D(1.,0.,1.);
        pa[4] = QVector3D(0.,1.,1.);
        pa[5] = QVector3D(0.,1.,0.);
        pa[6] = QVector3D(0.,0.,0.);
        pa[7] = QVector3D(0.,0.,1.);
        */

   pa[0].x = 1.; pa[0].y = 1.; pa[0].z =1.;
   pa[1].x = 1.; pa[1].y = 1.; pa[1].z = 0.;
   pa[2].x = 1.; pa[2].y = 0.; pa[2].z = 0.;
   pa[3].x = 1.; pa[3].y = 0.; pa[3].z = 1.;
   pa[4].x = 0.; pa[4].y = 1.; pa[4].z = 1.;
   pa[5].x = 0.; pa[5].y = 1.; pa[5].y = 0.;
   pa[6].x = 0.; pa[6].y = 0.; pa[6].z = 0.;
   pa[7].x = 0.; pa[7].y = 0.; pa[7].z = 1.;

   fromPoint.x = 1.0; fromPoint.y = 0.0; fromPoint.z = 0.0;
   atPoint.x = 0.0; atPoint.y = 0.0; atPoint.z = 0.0;
   up.x = 0.0; up.y = 0.0; up.z = 1.0;

   a = 350/2;
   b = 1 - a*(-1);
   c = 200/2;
   d = 200 - c*(-1);
   angle = toradians(60);
   t_from = 1.0;

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

    objxmax = objxmin = pa[0].x; //vertexList.at(0).x();
    objymax = objymin = pa[0].y; //vertexList.at(0).y();
    objzmax = objzmin = pa[0].z; //vertexList.at(0).z();

    //maxi = vertexList.size();
    maxi = 8;
    for (i=1; i<maxi; i++)
    {
        x = pa[i].x; // vertexList.at(i).x();
        y = pa[i].y; //vertexList.at(i).y();
        z = pa[i].z; //vertexList.at(i).z();

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
    //qDebug() << "ojbxmin";
    //fprintf(stdout,"objxmin");
    //QString jono = QString("ojxmin %1 objxmax %2").arg(objxmin).arg(objxmax);
    //QString jono = QString("ojymin %1 objymax %2").arg(objymin).arg(objymax);
    //QString jono = QString("ojzmin %1 objzmax %2").arg(objzmin).arg(objzmax);
    //QMessageBox::about(0,"Tark", jono);
}

void setAtPoint()
{
    dataMinMax();
    /*atPoint.setX((objxmax+objxmin)/2.0);
    atPoint.setY((objymax+objymin)/2.0);
    atPoint.setZ((objzmax+objzmin)/2.0);
    */
    atPoint.x = (objxmax+objxmin)/2.0;
    atPoint.y = (objymax+objymin)/2.0;
    atPoint.z = (objzmax+objzmin)/2.0;
    //QString jono = QString("AtX %1 Aty %2 AtZ %3").arg(atPoint.x()).arg(atPoint.y()).arg(atPoint.z());
    //QMessageBox::about(0,"At point", jono);
}

void setFromPoint()
{
    /*fromPoint.setX( atPoint.x() + (objxmax-objxmin)/2.0 + WIDTH*maxof((objzmax-objzmin)/2.0,(objymax-objymin)/2.0));
    fromPoint.setY( atPoint.y());
    fromPoint.setZ( atPoint.z());
    */
    fromPoint.x = ( atPoint.x + (objxmax-objxmin)/2.0 + WIDTH*maxof((objzmax-objzmin)/2.0,(objymax-objymin)/2.0));
    fromPoint.y = atPoint.y;
    fromPoint.z = atPoint.z;

    //QString jono = QString("FromX %1 FromY %2 FromZ %3").arg(fromPoint.x()).arg(fromPoint.y()).arg(fromPoint.z());
    //QMessageBox::about(0,"From point", jono); // (1.9,
}

VECTOR CrossProduct( VECTOR a, VECTOR b)
{
    VECTOR c;

    c.x = a.y*b.z - a.z*b.y;
    c.y = a.z*b.x - a.x*b.z;
    c.z = a.x*b.y - a.y*b.x;

    return c;
}

void setEye()
{
    double amarkmag, tempmag;
    //QVector3D temp;
    //QVector3D dist;
    VECTOR temp, dist;

    dval = cos(angle/2.0)/sin(angle/2.0);
    //dist = atPoint-fromPoint;
    dist.x = atPoint.x - fromPoint.x;
    dist.y = atPoint.y - fromPoint.y;
    dist.z = atPoint.z - fromPoint.z;
    //amarkmag = dist.length();
    amarkmag = sqrt( dist.x*dist.x + dist.y*dist.y + dist.z*dist.z);
    //QString jono = QString("amarkmag %1").arg(amarkmag);
    //QMessageBox::about(0,"amarkmag", jono); // 1.4
    //a3 = dist.operator /=(amarkmag);
    a3.x = dist.x/amarkmag;
    a3.y = dist.y/amarkmag;
    a3.z = dist.z/amarkmag;

    //temp.crossProduct( dist, up);
    temp = CrossProduct( dist, up);
    //tempmag = temp.length();
    tempmag = sqrt( temp.x*temp.x + temp.y*temp.y + temp.z*temp.z);
    //a1 = temp.operator /=(tempmag);
    a1.x = temp.x/tempmag;
    a1.y = temp.y/tempmag;
    a1.z = temp.z/tempmag;

    //temp.crossProduct( a1, a3);
    temp = CrossProduct( a1, a3);
    //tempmag = temp.length();
    tempmag = sqrt( temp.x*temp.x + temp.y*temp.y + temp.z*temp.z);
    //a2 = temp.operator /=(tempmag);
    a2.x = temp.x/tempmag;
    a2.y = temp.y/tempmag;
    a2.z = temp.z/tempmag;

    /*offsx = -a1.x()*fromPoint.x() - a1.y()*fromPoint.y() - a1.z()*fromPoint.z();
    offsy = -a2.x()*fromPoint.x() - a2.y()*fromPoint.y() - a2.z()*fromPoint.z();
    offsz = -a3.x()*fromPoint.x() - a3.y()*fromPoint.y() - a3.z()*fromPoint.z();
*/
    offsx = -a1.x*fromPoint.x - a1.y*fromPoint.y - a1.z*fromPoint.z;
    offsy = -a2.x*fromPoint.x - a2.y*fromPoint.y - a2.z*fromPoint.z;
    offsz = -a3.x*fromPoint.x - a3.y*fromPoint.y - a3.z*fromPoint.z;

    //QString jono2 = QString("offsx %1 offsy %2 offsz %3").arg(offsx).arg(offsy).arg(offsz);
    //QMessageBox::about(0,"offs x y z", jono2);
}

#define NOEDGE     0x00
#define LEFTEDGE   0x01
#define RIGHTEDGE  0x02
#define BOTTOMEDGE 0x04
#define TOPEDGE    0x08

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

void WORLDtoSCREEN( qreal xw, qreal yw, int *xpc, int *ypc)
{
    *xpc = (int) (a+xw+b);
    *ypc = (int) (c+yw+d);
}


void clip3d( qreal x1, qreal y1, qreal z1, qreal x2, qreal y2, qreal z2, int *xpc1, int *ypc1, int *xpc2, int *ypc2)
{
    int c,c1,c2; //, xpc1, ypc1, xpc2, ypc2;
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
                t = (z1-x1)/((x2-x2)-(z2-z1));
                z = t*(z2-z1)+z1;
                x = z;
                y = t*(y2-y1)+y1;
        }
        else if ((c&BOTTOMEDGE) == BOTTOMEDGE)
        {
                // Crosses left edge
                t = (z1+y1)/((y1-y2)-(z2-z1));
                z = t*(z2-z1)+z1;
                x = t*(x2-x1)+x1;
                y = -z;
        }
        else if ((c&TOPEDGE) == TOPEDGE)
        {
                // Crosses left edge
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
        WORLDtoSCREEN(x1/z1,y1/z1,xpc1, ypc1);
        WORLDtoSCREEN(x2/z2,y2/z2,xpc2, ypc2);
    }
    else
    {
        WORLDtoSCREEN(x1,y1,xpc1, ypc1);
        WORLDtoSCREEN(x2,y2,xpc2, ypc2);
    }
    //line( xpc1, ypc1, xpc2, ypc2);
    //painter.drawLine(xpc1, ypc1, xpc2, ypc2);
}

//void transformseg( QVector3D *v1, QVector3D *v2, int *xpc1, int *ypc1, int *xpc2, int *ypc2 )
void transformseg( VECTOR *v1, VECTOR *v2, int *xpc1, int *ypc1, int *xpc2, int *ypc2 )
{
    qreal x1, y1, z1, x2, y2, z2;

    /*x1 = (a1.x()*v1->x() + a1.y()*v1->y() + a1.z()*v1->z() + offsx)*dval;
    y1 = (a2.x()*v1->x() + a2.y()*v1->y() + a2.z()*v1->z() + offsy)*dval;
    z1 = a3.x()*v1->x() + a3.y()*v1->y() + a3.z()*v1->z() + offsz;*/
    x1 = (a1.x*v1->x + a1.y*v1->y + a1.z*v1->z + offsx)*dval;
    y1 = (a2.x*v1->x + a2.y*v1->y + a2.z*v1->z + offsy)*dval;
    z1 = a3.x*v1->x + a3.y*v1->y + a3.z*v1->z + offsz;

    /*x2 = (a1.x()*v2->x() + a1.y()*v2->y() + a1.z()*v2->z() + offsx)*dval;
    y2 = (a2.x()*v2->x() + a2.y()*v2->y() + a2.z()*v2->z() + offsy)*dval;
    z2 = a3.x()*v2->x() + a3.y()*v2->y() + a3.z()*v2->z() + offsz;*/
    x2 = (a1.x*v2->x + a1.y*v2->y + a1.z*v2->z + offsx)*dval;
    y2 = (a2.x*v2->x + a2.y*v2->y + a2.z*v2->z + offsy)*dval;
    z2 = a3.x*v2->x + a3.y*v2->y + a3.z*v2->z + offsz;

    clip3d(x1,y1,z1,x2,y2,z2, xpc1, ypc1, xpc2, ypc2 );
}

void RouteDialog::paintEvent(QPaintEvent *)
{
    //int i, maxi;
    int i, startofside;
    qreal x1, y1, x2, y2;
    int scx1, scy1, scx2, scy2;
    int xpc1, ypc1, xpc2, ypc2;

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen((Qt::black),2));
    painter.setBrush(QBrush((Qt::yellow), Qt::SolidPattern));

    // Draw route window frsme
    painter.drawLine(left,top,right,top);
    painter.drawLine(right,top,right,bottom);
    painter.drawLine(left,top,left,bottom);
    painter.drawLine(left,bottom,right,bottom);

//void view( void)
//{
    //int i, startofside;
    i=1;
    while(i<length)
    {
        startofside = i;
        i++;
        while (connection[i] > 0)
        {
            transformseg( &pa[connection[i-1]],&pa[connection[i]], &xpc1, &ypc1, &xpc2, &ypc2);
            painter.drawLine(xpc1, ypc1, xpc2, ypc2);
            i++;
        }
        transformseg( &pa[connection[i-1]],&pa[-connection[i]],&xpc1, &ypc1, &xpc2, &ypc2);
        painter.drawLine(xpc1, ypc1, xpc2, ypc2);
        transformseg( &pa[-connection[i]],&pa[connection[startofside]],&xpc1, &ypc1, &xpc2, &ypc2);
        painter.drawLine(xpc1, ypc1, xpc2, ypc2);
        i++;
    }
}
