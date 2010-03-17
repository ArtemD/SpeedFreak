/*
 * RouteDialog class
 *
 * @author     Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "routedialog.h"
#include "ui_routedialog.h"
#include <QPainter>
#include <QList>
#include <QVector3D>

int left = 50, top = 50, right = 350, bottom = 200;  // Limits in screen coordinates
qreal xmax, xmin, ymin, ymax;                        // Limits in world coordinates

QList<QVector3D> vertexList;    // Vertecies of route

RouteDialog::RouteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RouteDialog)
{
    ui->setupUi(this);
    xmin =0.0; xmax=100.0; ymin = 0.0; ymax = 20.0;

   vertexList.append(QVector3D(40.02, 10.02, 10.02));
   vertexList.append(QVector3D(50.01,  5.01, 10));
   vertexList.append(QVector3D(69.98,  4.98, 10));
   vertexList.append(QVector3D(80.02,  9.98, 10));
   vertexList.append(QVector3D(70.01, 15.01, 10));
   vertexList.append(QVector3D(49.99, 14.97, 10));
   vertexList.append(QVector3D(40.01, 10.01, 10.02));
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
void RouteDialog::paintEvent(QPaintEvent *)
{
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

        maxi = vertexList.size();
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

void RouteDialog::on_closePushButton_clicked()
{
    close();
}
