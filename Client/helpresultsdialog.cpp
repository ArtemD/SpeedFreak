/*
 * Help result dialog
 *
 * @author     Janne Änäkkälä   <janne.anakkala@fudeco.com>
 * @author     Toni Jussila 	<toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "helpresultsdialog.h"
#include "ui_helpresultsdialog.h"

/**
  * Default constructor of this class.
  */
HelpResultsDialog::HelpResultsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpResultsDialog)
{
    ui->setupUi(this);
}

/**
  * Default destructor of this class.
  */
HelpResultsDialog::~HelpResultsDialog()
{
    delete ui;
}

/**
  *
  */
void HelpResultsDialog::changeEvent(QEvent *e)
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
