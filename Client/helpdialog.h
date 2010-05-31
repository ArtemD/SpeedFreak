/*
 * Help dialog
 *
 * @author     Janne Änäkkälä   <janne.anakkala@fudeco.com>
 * @author     Toni Jussila 	<toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <helpresultsdialog.h>
#include <helpaccelerationdialog.h>
#include <helproutingdialog.h>
#include <helpsettingsdialog.h>
#include "creditsdialog.h"
#include <helpusersdialog.h>

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
   HelpSettingsDialog *helpSettingsDialog;
   HelpUsersDialog *helpUsersDialog;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::HelpDialog *ui;


private slots:
    void on_pushButtonHelpUsers_clicked();
    void on_pushButtonHelpSettings_clicked();
    void on_pushButtonCredits_clicked();
    void on_pushButtonHelpRoute_clicked();
    void on_pushButtonHelpAccelerate_clicked();
    void on_pushButtonHelpResults_clicked();
    void killHelpDialogs();
};

#endif // HELPDIALOG_H
