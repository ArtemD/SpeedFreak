#include "measuredialog.h"
#include "ui_measuredialog.h"

MeasureDialog::MeasureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeasureDialog)
{
    ui->setupUi(this);
}

MeasureDialog::~MeasureDialog()
{
    delete ui;
}

void MeasureDialog::changeEvent(QEvent *e)
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
