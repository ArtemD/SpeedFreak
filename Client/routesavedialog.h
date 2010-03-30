#ifndef ROUTESAVEDIALOG_H
#define ROUTESAVEDIALOG_H

#include <QDialog>

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
};

#endif // ROUTESAVEDIALOG_H
