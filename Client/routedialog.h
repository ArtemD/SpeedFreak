/*
 * RouteDialog class
 *
 * @author     Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef ROUTEDIALOG_H
#define ROUTEDIALOG_H

#include <QDialog>

namespace Ui {
    class RouteDialog;
}

class RouteDialog : public QDialog {
    Q_OBJECT
public:
    RouteDialog(QWidget *parent = 0);
    ~RouteDialog();
    bool readRouteFromFile( QString &routeFile);
    int getLeft();
    int getTop();
    int getRight();
    int getBottom();
    void setLabelInfoToUser(QString infoText);

signals:
    void sendroute();

protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *);

private:
    Ui::RouteDialog *ui;
    int left, top, right, bottom;       // Limits in screen coordinates in route dialog

private slots:
    void on_sendPushButton_clicked();
    void on_newPushButton_clicked();
};

#endif // ROUTEDIALOG_H
