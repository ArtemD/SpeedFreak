/*
 * Credits Dialog
 *
 * @author     Rikhard Kuutti   <rikhard.kuutti@fudeco.com>
 * @author     Toni Jussila     <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "creditsdialog.h"
#include "ui_creditsdialog.h"
#include <QDesktopServices>
#include <QUrl>

/**
  * Constructor of this class.
  */
CreditsDialog::CreditsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditsDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Credits");
}

/**
  * Destructor of this class. Should be used to release all allocated resources.
  */
CreditsDialog::~CreditsDialog()
{
    delete ui;
}

/**
  *
  */
void CreditsDialog::changeEvent(QEvent *e)
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
