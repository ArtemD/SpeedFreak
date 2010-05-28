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

/**
  * Constructor of this class
  */
TopResultDialog::TopResultDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::TopResultDialog)
{
    ui->setupUi(this);

    helpResultsDialog = NULL;

    this->setWindowTitle("Top Results");

    //Set the amount of requested top results here, untill there is user input
    setLimitNr(10);

    //Button settings
    ui->buttonTopRefresh->setAutoFillBackground(true);
    ui->buttonTopRefresh->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");
    ui->pushButtonInfo->setAutoFillBackground(true);
    ui->pushButtonInfo->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");

    //Clear labels
    ui->labelInfoToUser->setText("");
    ui->labelTopList->setText("");
}

/**
  * Destructor of this class
  */
TopResultDialog::~TopResultDialog()
{
    qDebug() << "__~TopResultDialog";
    delete ui;
}

/**
  *
  */
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

/**
  * This slot function called when ever refresh button clicked.
  */
void TopResultDialog::on_buttonTopRefresh_clicked()
{
    ui->labelTopList->clear();
    ui->comboBoxTopCategory->clear();
    emit refreshCategoryList();
}

/**
  * Set categories compobox.
  *
  * @param QStringList list
  */
void TopResultDialog::setCompoBoxCategories(QStringList list)
{
    ui->comboBoxTopCategory->addItems(list);
}

/**
  * Show top list.
  *
  * @param QString str
  */
void TopResultDialog::showTopList(QString str)
{
    qDebug() << "__showTopList";
    ui->labelTopList->setText(str);
}

/**
  * Get recent category index.
  *
  * @return int category index
  */
int TopResultDialog::getRecentCategoryIndex()
{
    return recentCategoryIndex;
}

/**
  * Set limit nr.
  *
  * @param int number
  */
void TopResultDialog::setLimitNr(int number)
{
    limitNr = number;
}

/**
  * Get limit nr.
  *
  * @return int limit nr
  */
int TopResultDialog::getLimitNr()
{
    return limitNr;
}

/**
  * This slot function called when ever top category combobox current index changed.
  *
  * @param int index
  */
void TopResultDialog::on_comboBoxTopCategory_currentIndexChanged(int index)
{
    ui->labelTopList->clear();
    recentCategoryIndex = index;
    emit refreshTopList(index);
}

/**
  * Set label info to user.
  *
  * @param QString info text
  */
void TopResultDialog::setLabelInfoToUser(QString infoText)
{
    this->ui->labelInfoToUser->setText(infoText);
}

/**
  * This slot function called when ever info button clicked.
  */
void TopResultDialog::on_pushButtonInfo_clicked()
{
    if(!helpResultsDialog)
    {
        helpResultsDialog = new HelpResultsDialog;
    }
    connect(helpResultsDialog, SIGNAL(rejected()), this, SLOT(killHelpDialog()));
    helpResultsDialog->show();
}

/**
  * This slot function called when ever dialog rejected.
  */
void TopResultDialog::killHelpDialog()
{
    if(helpResultsDialog)
    {
        qDebug() << "__Top result kill: helpResultsDialog";
        delete helpResultsDialog;
        helpResultsDialog = NULL;
    }
}
