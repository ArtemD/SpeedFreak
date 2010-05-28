/*
 * Calibrate dialog
 *
 * @author      Kai Rasilainen <kai.rasilainen@fudeco.com>
 * @author      Toni Jussila   <toni.jussila@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "calibratedialog.h"
#include "ui_calibratedialog.h"

/**
  * Default constructor for Calibrate dialog class.
  *
  */
CalibrateDialog::CalibrateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibrateDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Calibrating...");
}

/**
  * Default destructor for Calibrate dialog class.
  * Deletes all dynamic objects and sets them to NULL.
  */
CalibrateDialog::~CalibrateDialog()
{
    delete ui;
}

/**
  *
  */
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

/**
  * Set progressbar value.
  *
  * @param int progressbar value.
  */
void CalibrateDialog::setProgressValue(int value)
{
    ui->progressBar->setValue(value);
}

/**
  * Reset progressbar value.
  */
void CalibrateDialog::resetProgressValue()
{
    ui->progressBar->reset();
}

/**
  * Set max value.
  *
  * @param int max
  */
void CalibrateDialog::setMaxValue(int max)
{
    ui->progressBar->setMaximum( max );
}

/**
  * Set title.
  *
  * @param QString title
  */
void CalibrateDialog::setTitle(QString title)
{
    this->setWindowTitle(title);
}
