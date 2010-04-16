/*
 * Topresultdialog
 *
 * @author     Olavi Pulkkinen <olavi.pulkkinena@fudeco.com>
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include <QDebug>
#include "topresultdialog.h"
#include "ui_topresultdialog.h"

TopResultDialog::TopResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TopResultDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Top Results");

    //Set the amount of requested top results here, untill there is user input
    setLimitNr(10);

    //Button settings
    ui->buttonTopRefresh->setAutoFillBackground(true);
    ui->buttonTopRefresh->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");

    //Clear labels
    ui->labelInfoToUser->setText("");
    ui->labelTopList->setText("");
}

TopResultDialog::~TopResultDialog()
{
    delete ui;
}

void TopResultDialog::changeEvent(QEvent *e)
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


void TopResultDialog::on_buttonTopRefresh_clicked()
{
    ui->labelTopList->clear();
    ui->comboBoxTopCategory->clear();
    emit refreshCategoryList();
}

void TopResultDialog::setCompoBoxCategories(QStringList list)
{
    ui->comboBoxTopCategory->addItems(list);
}

void TopResultDialog::showTopList(QString str)
{
    ui->labelTopList->setText(str);
}

int TopResultDialog::getRecentCategoryIndex()
{
    return recentCategoryIndex;
}

void TopResultDialog::setLimitNr(int number)
{
    limitNr = number;
}

int TopResultDialog::getLimitNr()
{
    return limitNr;
}

void TopResultDialog::on_comboBoxTopCategory_currentIndexChanged(int index)
{
    ui->labelTopList->clear();
    recentCategoryIndex = index;
    emit refreshTopList(index);
}

void TopResultDialog::setLabelInfoToUser(QString infoText)
{
    this->ui->labelInfoToUser->setText(infoText);
}
