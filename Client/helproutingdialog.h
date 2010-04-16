#ifndef HELPROUTINGDIALOG_H
#define HELPROUTINGDIALOG_H

#include <QDialog>

namespace Ui {
    class HelpRoutingDialog;
}

class HelpRoutingDialog : public QDialog {
    Q_OBJECT
public:
    HelpRoutingDialog(QWidget *parent = 0);
    ~HelpRoutingDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::HelpRoutingDialog *ui;
    int pageCounter;

private slots:
    void on_pushButtonLast_clicked();
    void on_pushButtonNext_clicked();
};

#endif // HELPROUTINGDIALOG_H
