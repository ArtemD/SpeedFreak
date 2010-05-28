/*
 * Help acceleration dialog.
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "helpaccelerationdialog.h"
#include "ui_helpaccelerationdialog.h"

/**
  * Default constructor of this class.
  */
HelpAccelerationDialog::HelpAccelerationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpAccelerationDialog)
{
    ui->setupUi(this);
    pageCounter = 0;
    ui->labelLast->hide();
    ui->pushButtonLast->hide();

    ui->labelInfo2->hide();
    ui->labelStartPic->hide();

    ui->labelInfo3->hide();
    ui->labelMeasurePic->hide();

    ui->labelInfo4->hide();
}

/**
  * Default destructor of this class.
  */
HelpAccelerationDialog::~HelpAccelerationDialog()
{
    delete ui;
}

/**
  *
  */
void HelpAccelerationDialog::changeEvent(QEvent *e)
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
void HelpAccelerationDialog::on_pushButtonNext_clicked()
{
    pageCounter ++;

    if(pageCounter == 1)
    {
        ui->labelCalibratePic->hide();
        ui->labelInfo1->hide();

        ui->labelLast->show();
        ui->pushButtonLast->show();
        ui->labelInfo2->show();
        ui->labelStartPic->show();
    }

    if(pageCounter == 2)
    {
        ui->labelCalibratePic->hide();
        ui->labelInfo1->hide();
        ui->labelInfo2->hide();
        ui->labelStartPic->hide();

        ui->labelLast->show();
        ui->pushButtonLast->show();
        ui->labelInfo3->show();
        ui->labelMeasurePic->show();
    }

    if(pageCounter == 3)
    {
        ui->labelCalibratePic->hide();
        ui->labelInfo1->hide();
        ui->labelInfo2->hide();
        ui->labelStartPic->hide();

        //ui->labelLast->hide();
        //ui->pushButtonLast->hide();
        ui->labelInfo3->hide();
        ui->labelMeasurePic->hide();

        ui->pushButtonNext->hide();
        ui->labelNext->hide();

        ui->labelInfo4->show();
    }
}

/**
  * This slot function called when ever last button clicked.
  */
void HelpAccelerationDialog::on_pushButtonLast_clicked()
{
    pageCounter --;

    if(pageCounter == 0)
    {
        ui->labelCalibratePic->show();
        ui->labelInfo1->show();
        ui->labelStartPic->hide();
        ui->labelLast->hide();
        ui->pushButtonLast->hide();
        ui->labelInfo2->hide();
        ui->labelInfo3->hide();
        ui->labelMeasurePic->hide();
    }

    if(pageCounter == 1)
    {
        ui->labelCalibratePic->hide();
        ui->labelInfo1->hide();
        ui->labelInfo3->hide();
        ui->labelMeasurePic->hide();

        ui->labelLast->show();
        ui->pushButtonLast->show();
        ui->labelInfo2->show();
        ui->labelStartPic->show();
    }

    if(pageCounter == 2)
    {
        ui->labelCalibratePic->hide();
        ui->labelInfo1->hide();
        ui->labelInfo3->hide();
        ui->labelMeasurePic->hide();
        ui->labelInfo4->hide();

        ui->pushButtonNext->show();
        ui->labelNext->show();

        ui->labelLast->show();
        ui->pushButtonLast->show();
        ui->labelInfo2->hide();
        ui->labelStartPic->hide();

        ui->labelInfo3->show();
        ui->labelMeasurePic->show();
    }
}
