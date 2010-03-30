#include "routesavedialog.h"
#include "ui_routesavedialog.h"

RouteSaveDialog::RouteSaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RouteSaveDialog)
{
    ui->setupUi(this);
}

RouteSaveDialog::~RouteSaveDialog()
{
    delete ui;
}

void RouteSaveDialog::changeEvent(QEvent *e)
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
