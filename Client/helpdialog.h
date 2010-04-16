#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <helpresultsdialog.h>
#include <helpaccelerationdialog.h>
#include <helproutingdialog.h>
#include "creditsdialog.h"

namespace Ui {
    class HelpDialog;
}

class HelpDialog : public QDialog {
    Q_OBJECT
public:
    HelpDialog(QWidget *parent = 0);
    ~HelpDialog();

   HelpResultsDialog *helpResultsDialog;
   HelpAccelerationDialog *helpAccelerationDialog;
   HelpRoutingDialog *helpRoutingDialog;
   CreditsDialog *creditsDialog;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::HelpDialog *ui;


private slots:
    void on_pushButtonCredits_clicked();
    void on_pushButtonHelpRoute_clicked();
    void on_pushButtonHelpAccelerate_clicked();
    void on_pushButtonHelpResults_clicked();
};

#endif // HELPDIALOG_H
