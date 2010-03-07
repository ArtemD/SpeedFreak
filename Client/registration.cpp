#include "registration.h"
#include "ui_registration.h"
#include <QMessageBox>

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
    //Let`s not type it again
    ui->newUsernameLineEdit->setText("user123");
    ui->newPasswordLineEdit->setText("salainen");
    ui->eMailLineEdit->setText("user123@emaili.fi");

    for(int i = 0; i < 3000; i++);

    // Send username, password and email to SpeedFreak server
    this->username = ui->newUsernameLineEdit->text();
    this->password = ui->newPasswordLineEdit->text();
    this->email = ui->eMailLineEdit->text();

    emit sendregistration();

    close();
}

void Registration::on_cancelPushButton_clicked()
{
    close();
}

void Registration::setUserName(QString username)
{
    this->username = username;
}

void Registration::setPassword(QString password)
{
    this->password = password;
}

void Registration::setEmail(QString email)
{
    this->email = email;
}

QString Registration::getUserName()
{
    return this->username;
}

QString Registration::getPassword()
{
    return this->password;
}

QString Registration::getEmail()
{
    return this->email;
}
