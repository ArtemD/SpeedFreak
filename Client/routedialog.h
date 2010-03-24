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

protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *);

private:
    Ui::RouteDialog *ui;
    int left, top, right, bottom;       // Limits in screen coordinates in route dialog

private slots:
    void on_closePushButton_clicked();
};

#endif // ROUTEDIALOG_H
