/*
 * Help settings dialog
 *
 * @author     Janne Änäkkälä   <janne.anakkala@fudeco.com>
 * @author     Toni Jussila 	<toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "helpsettingsdialog.h"
#include "ui_helpsettingsdialog.h"

/**
  * Default constructor of this class.
  */
HelpSettingsDialog::HelpSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpSettingsDialog)
{
    ui->setupUi(this);
    pageCounter = 0;

    ui->labelInfo2->hide();
    ui->labelLast->hide();
    ui->pushButtonLast->hide();
}

/**
  * Default destructor of this class.
  */
HelpSettingsDialog::~HelpSettingsDialog()
{
    delete ui;
}

/**
  *
  */
void HelpSettingsDialog::changeEvent(QEvent *e)
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
void HelpSettingsDialog::on_pushButtonNext_clicked()
{
    pageCounter ++;

    if(pageCounter == 1)
    {
        ui->labelNext->hide();
        ui->pushButtonNext->hide();
        ui->labelInfo1->hide();

        ui->labelInfo2->show();
        ui->labelLast->show();
        ui->pushButtonLast->show();
    }
}

/**
  * This slot function called when ever last button clicked.
  */
void HelpSettingsDialog::on_pushButtonLast_clicked()
{
    pageCounter --;

    if(pageCounter == 0)
    {
        ui->labelInfo2->hide();
        ui->labelLast->hide();
        ui->pushButtonLast->hide();

        ui->labelNext->show();
        ui->pushButtonNext->show();
        ui->labelInfo1->show();
    }
}
