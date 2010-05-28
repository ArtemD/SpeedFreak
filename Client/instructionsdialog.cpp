/*
 * Instructions dialog for speedFreak project
 *
 * @author      Rikhard Kuutti 	<rikhard.kuutti@fudeco.com>
 * @author      Toni Jussila    <toni.jussila@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "instructionsdialog.h"
#include "ui_instructionsdialog.h"

/**
  * Default constructor of this class.
  */
InstructionsDialog::InstructionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InstructionsDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Help");
}

/**
  * Default destructor of this class.
  */
InstructionsDialog::~InstructionsDialog()
{
    delete ui;
}

/**
  *
  */
void InstructionsDialog::changeEvent(QEvent *e)
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
