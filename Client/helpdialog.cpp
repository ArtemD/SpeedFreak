#include "helpdialog.h"
#include "ui_helpdialog.h"

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

HelpDialog::~HelpDialog()
{
    delete ui;
}

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


void HelpDialog::on_pushButtonHelpResults_clicked()
{
    if(!helpResultsDialog)
    {
        helpResultsDialog = new HelpResultsDialog;
    }
    helpResultsDialog->show();
}

void HelpDialog::on_pushButtonHelpAccelerate_clicked()
{
    if(!helpAccelerationDialog)
    {
        helpAccelerationDialog = new HelpAccelerationDialog;
    }
    helpAccelerationDialog->show();
}

void HelpDialog::on_pushButtonHelpRoute_clicked()
{
    if(!helpRoutingDialog)
    {
        helpRoutingDialog = new HelpRoutingDialog;
    }
    helpRoutingDialog->show();
}

void HelpDialog::on_pushButtonCredits_clicked()
{
    if(!creditsDialog)
    {
        creditsDialog = new CreditsDialog;
    }
    creditsDialog->show();
}

void HelpDialog::on_pushButtonHelpSettings_clicked()
{
    if(!helpSettingsDialog)
    {
        helpSettingsDialog = new HelpSettingsDialog;
    }
    helpSettingsDialog->show();
}
