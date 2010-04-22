/*
 * Custom button class for customized button.
 *
 * @author      Jukka Kurttila <jktla@suomi24.fi>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QPixmap>
#include <QMouseEvent>

class CustomButton : public QWidget
{
    Q_OBJECT
public:
    CustomButton(QWidget *parent = 0, QIcon* iconParam = 0);
    ~CustomButton();

signals:
    void OpenDialog();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent* me);
    void mouseReleaseEvent(QMouseEvent* me);
    void mouseMoveEvent(QMouseEvent* me);

private:
    QPixmap* pict1;
    QPixmap* pict2;
    bool bPressed;
    int mX,mY;
};

#endif // CUSTOMBUTTON_H
