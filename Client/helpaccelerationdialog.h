#ifndef HELPACCELERATIONDIALOG_H
#define HELPACCELERATIONDIALOG_H

#include <QDialog>

namespace Ui {
    class HelpAccelerationDialog;
}

class HelpAccelerationDialog : public QDialog {
    Q_OBJECT
public:
    HelpAccelerationDialog(QWidget *parent = 0);
    ~HelpAccelerationDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::HelpAccelerationDialog *ui;
    int pageCounter;

private slots:
    void on_pushButtonLast_clicked();
    void on_pushButtonNext_clicked();
};

#endif // HELPACCELERATIONDIALOG_H
