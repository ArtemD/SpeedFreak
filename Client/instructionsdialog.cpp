/*
 * Instructions dialog for speedFreak project
 *
 * @author      Rikhard Kuutti 	<rikhard.kuutti@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "instructionsdialog.h"
#include "ui_instructionsdialog.h"

InstructionsDialog::InstructionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InstructionsDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Help");
}

InstructionsDialog::~InstructionsDialog()
{
    delete ui;
}

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
