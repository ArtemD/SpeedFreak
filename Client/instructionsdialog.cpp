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
