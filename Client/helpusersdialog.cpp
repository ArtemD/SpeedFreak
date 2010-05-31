#include "helpusersdialog.h"
#include "ui_helpusersdialog.h"

HelpUsersDialog::HelpUsersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpUsersDialog)
{
    ui->setupUi(this);
}

HelpUsersDialog::~HelpUsersDialog()
{
    delete ui;
}

void HelpUsersDialog::changeEvent(QEvent *e)
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
