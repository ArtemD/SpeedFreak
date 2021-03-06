/*
 * Help routing dialog
 *
 * @author     Janne Änäkkälä   <janne.anakkala@fudeco.com>
 * @author     Toni Jussila 	<toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "helproutingdialog.h"
#include "ui_helproutingdialog.h"

/**
  * Default constructor of this class.
  */
HelpRoutingDialog::HelpRoutingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpRoutingDialog)
{
    ui->setupUi(this);
    pageCounter = 0;

    ui->labelInfo2->hide();
    ui->labelLast->hide();
    ui->pushButtonLast->hide();
    ui->labelStopPic->hide();

    ui->labelInfo3->hide();
    ui->labelNewPic->hide();
    ui->labelSavePic->hide();
}

/**
  * Default destructor of this class.
  */
HelpRoutingDialog::~HelpRoutingDialog()
{
    delete ui;
}

/**
  *
  */
void HelpRoutingDialog::changeEvent(QEvent *e)
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
  * This slot function called when ever next button clicked.
  */
void HelpRoutingDialog::on_pushButtonNext_clicked()
{
    pageCounter ++;

    if(pageCounter == 1)
    {
        ui->labelStartPic->hide();
        ui->labelSatellitePic->hide();
        ui->labelInfo1->hide();

        ui->labelLast->show();
        ui->pushButtonLast->show();
        ui->labelInfo2->show();
        ui->labelStopPic->show();
    }

    if(pageCounter == 2)
    {
        ui->labelStartPic->hide();
        ui->labelSatellitePic->hide();
        ui->labelInfo1->hide();

        ui->labelInfo2->hide();
        ui->labelStopPic->hide();

        ui->labelNext->hide();
        ui->pushButtonNext->hide();

        ui->labelLast->show();
        ui->pushButtonLast->show();
        ui->labelInfo3->show();
        ui->labelSavePic->show();
        ui->labelNewPic->show();
    }
}

/**
  * This slot function called when ever last button clicked.
  */
void HelpRoutingDialog::on_pushButtonLast_clicked()
{
    pageCounter --;

    if(pageCounter == 0)
    {
        ui->labelInfo2->hide();
        ui->labelLast->hide();
        ui->pushButtonLast->hide();
        ui->labelStopPic->hide();

        ui->labelStartPic->show();
        ui->labelSatellitePic->show();
        ui->labelInfo1->show();

        ui->labelNext->show();
        ui->pushButtonNext->show();
    }

    if(pageCounter == 1)
    {
        ui->labelLast->hide();
        ui->pushButtonLast->hide();
        ui->labelInfo3->hide();
        ui->labelSavePic->hide();
        ui->labelNewPic->hide();

        ui->labelNext->show();
        ui->pushButtonNext->show();

        ui->labelInfo2->show();
        ui->labelLast->show();
        ui->pushButtonLast->show();
        ui->labelStopPic->show();
    }
}
