/*
 * RouteDialog class
 *
 * @author      Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
 * @author      Toni Jussila 	<toni.jussila@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef ROUTEDIALOG_H
#define ROUTEDIALOG_H

#include <QDialog>
#include <helproutingdialog.h>
class RouteSaveDialog;

namespace Ui {
    class RouteDialog;
}

class RouteDialog : public QDialog {
    Q_OBJECT

public:
    RouteDialog(RouteSaveDialog *parent = 0);
    ~RouteDialog();
    bool readRouteFromFile( QString &routeFile);
    int getLeft();
    int getTop();
    int getRight();
    int getBottom();
    void setLabelInfoToUser(QString infoText);
    void setSendServerButtonEnabled();
    HelpRoutingDialog *helpRoutingDialog;

signals:
    void sendroute(QString,int);
    void progressbar(int);

protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *);

private:
    Ui::RouteDialog *ui;
    int left, top, right, bottom;       // Limits in screen coordinates in route dialog
    void checkLogin();
    QString fileName;

private slots:
    void on_pushButtonInfo_clicked();
    void on_sendPushButton_clicked();
    void killHelpDialog();
};

#endif // ROUTEDIALOG_H
