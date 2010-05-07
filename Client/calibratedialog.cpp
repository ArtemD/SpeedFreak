/*
 * Calibrate dialog
 *
 * @author     Kai Rasilainen <kai.rasilainen@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "calibratedialog.h"
#include "ui_calibratedialog.h"

CalibrateDialog::CalibrateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibrateDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Calibrating...");
}

CalibrateDialog::~CalibrateDialog()
{
    delete ui;
}

void CalibrateDialog::changeEvent(QEvent *e)
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

void CalibrateDialog::setProgressValue(int value)
{
    ui->progressBar->setValue(value);
}

void CalibrateDialog::resetProgressValue()
{
    ui->progressBar->reset();
}

void CalibrateDialog::setMaxValue(int max)
{
    ui->progressBar->setMaximum( max );
}

void CalibrateDialog::setTitle(QString title)
{
    this->setWindowTitle(title);
}
