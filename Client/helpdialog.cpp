/*
 * Help dialog
 *
 * @author     Janne Änäkkälä <janne.anakkala@fudeco.com>
 * @author     Toni Jussila 	<toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "helpdialog.h"
#include "ui_helpdialog.h"
#include <QDebug>

/**
  * Constructor
  */
HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
    helpResultsDialog = NULL;
    helpAccelerationDialog = NULL;
    helpRoutingDialog = NULL;
    creditsDialog = NULL;
    helpSettingsDialog = NULL;
}

/**
  * Destructor
  */
HelpDialog::~HelpDialog()
{
    delete ui;
}

/**
  *
  */
void HelpDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/**
  *
  */
void HelpDialog::on_pushButtonHelpResults_clicked()
{
    if(!helpResultsDialog)
    {
        helpResultsDialog = new HelpResultsDialog;
    }
    connect(helpResultsDialog, SIGNAL(rejected()), this, SLOT(killHelpDialogs()));
    helpResultsDialog->show();
}

/**
  *
  */
void HelpDialog::on_pushButtonHelpAccelerate_clicked()
{
    if(!helpAccelerationDialog)
    {
        helpAccelerationDialog = new HelpAccelerationDialog;
    }
    connect(helpAccelerationDialog, SIGNAL(rejected()), this, SLOT(killHelpDialogs()));
    helpAccelerationDialog->show();
}

/**
  *
  */
void HelpDialog::on_pushButtonHelpRoute_clicked()
{
    if(!helpRoutingDialog)
    {
        helpRoutingDialog = new HelpRoutingDialog;
    }
    connect(helpRoutingDialog, SIGNAL(rejected()), this, SLOT(killHelpDialogs()));
    helpRoutingDialog->show();
}

/**
  *
  */
void HelpDialog::on_pushButtonCredits_clicked()
{
    if(!creditsDialog)
    {
        creditsDialog = new CreditsDialog;
    }
    connect(creditsDialog, SIGNAL(rejected()), this, SLOT(killHelpDialogs()));
    creditsDialog->show();
}

/**
  *
  */
void HelpDialog::on_pushButtonHelpSettings_clicked()
{
    if(!helpSettingsDialog)
    {
        helpSettingsDialog = new HelpSettingsDialog;
    }
    connect(helpSettingsDialog, SIGNAL(rejected()), this, SLOT(killHelpDialogs()));
    helpSettingsDialog->show();
}

/**
  * This slot function called when ever dialog rejected.
  */
void HelpDialog::killHelpDialogs()
{
    if(helpResultsDialog)
    {
        qDebug() << "__Help kill: helpResultsDialog";
        delete helpResultsDialog;
        helpResultsDialog = NULL;
    }
    if(helpAccelerationDialog)
    {
        qDebug() << "__Help kill: helpAccelerationDialog";
        delete helpAccelerationDialog;
        helpAccelerationDialog = NULL;
    }
    if(helpRoutingDialog)
    {
        qDebug() << "__Help kill: helpRoutingDialog";
        delete helpRoutingDialog;
        helpRoutingDialog = NULL;
    }
    if(creditsDialog)
    {
        qDebug() << "__Help kill: creditsDialog";
        delete creditsDialog;
        creditsDialog = NULL;
    }

    if(helpSettingsDialog)
    {
        qDebug() << "__Help kill: helpSettingsDialog";
        delete helpSettingsDialog;
        helpSettingsDialog = NULL;
    }
}
