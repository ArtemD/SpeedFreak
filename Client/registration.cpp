#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    this->setWindowTitle("Registration for Speed Freak server");
}

Registration::~Registration()
{
    delete ui;
}

void Registration::changeEvent(QEvent *e)
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

void Registration::on_registratePushButton_clicked()
{
    // Send username, password and email to SpeedFreak server
    close();  // Needs some new signal/slot to go forward or ???
    //registrateToServer(ui->newUsernameLineEdit->text(),
    //                   ui->newPasswordLineEdit->text(),
    //                   ui->eMailLineEdit->text());
}

void Registration::on_cancelPushButton_clicked()
{
    close();
}

