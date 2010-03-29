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

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RouteDialog *ui;
};

#endif // ROUTEDIALOG_H
