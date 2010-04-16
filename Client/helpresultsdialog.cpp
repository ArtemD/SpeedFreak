#include "helpresultsdialog.h"
#include "ui_helpresultsdialog.h"

HelpResultsDialog::HelpResultsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpResultsDialog)
{
    ui->setupUi(this);
}

HelpResultsDialog::~HelpResultsDialog()
{
    delete ui;
}

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
