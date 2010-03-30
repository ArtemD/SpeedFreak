/*
 * Route save dialog class
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef ROUTESAVEDIALOG_H
#define ROUTESAVEDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QTimer>

namespace Ui {
    class RouteSaveDialog;
}

class RouteSaveDialog : public QDialog {
    Q_OBJECT
public:
    RouteSaveDialog(QWidget *parent = 0);
    ~RouteSaveDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RouteSaveDialog *ui;
    QTimer *timerSatellitePicture;

private slots:
    void on_buttonRouteStartStop_clicked();
    void timerSatellitePictureTimeout();
};

#endif // ROUTESAVEDIALOG_H
