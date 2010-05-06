/*
 * Custom button class for customized button.
 *
 * @author      Jukka Kurttila <jktla@suomi24.fi>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "custombutton.h"

#include <QPainter>
#include <QIcon>

/**
  *Constructor of this class.
  */
CustomButton::CustomButton(QWidget *parent, QIcon *icon) : QWidget(parent)
{
    bPressed = false;
    //Get size of the icon
    QList<QSize> list = icon->availableSizes(QIcon::Normal,QIcon::On);

    //If icon is empty, do not create pixmaps and leave
    if(list.isEmpty())
        return;
    QSize size = list.first();
    if( icon )
    {
        pict1 = new QPixmap(icon->pixmap(size.width(),size.height(),QIcon::Normal,QIcon::On));
        pict2 = new QPixmap(icon->pixmap(size.width(),size.height(),QIcon::Normal,QIcon::Off));
    }
}
/**
  *Destructor of this class.
  */
CustomButton::~CustomButton()
{
    if(!pict1)
        delete pict1;
    if(!pict2)
        delete pict2;
}

void CustomButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if(!bPressed)
        painter.drawPixmap(0,0,*pict2);
    else
        painter.drawPixmap(0,0,*pict1);

    //Debug print
    //painter.drawText(50,50,"y: "+QString::number(mY));
}
void CustomButton::mousePressEvent(QMouseEvent* me)
{
    bPressed = true;
    repaint();
}
void CustomButton::mouseReleaseEvent(QMouseEvent* me)
{
    mX = me->x();
    mY = me->y();
    //Emit open dialog signal if mouse is still over button
    if( mY < this->height() && mY > 0 && mX < this->width() && mX > 0 )
        emit OpenDialog();

    bPressed = false;
    repaint();
}
void CustomButton::mouseMoveEvent(QMouseEvent* me)
{
    mX = me->x();
    mY = me->y();
    //Is mouse moved outside button?
    if( mY > this->height() || mY < 0 || mX > this->width() || mX < 0 )
        bPressed = false;
    else
        bPressed = true;
    repaint();
}
