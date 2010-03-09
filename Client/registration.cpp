/*
 * Registration class to registrate username for user
 *
 * @author      Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
 * @author
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "registration.h"
#include "ui_registration.h"
#include <QMessageBox>

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    this->setWindowTitle("Registration for Speed Freak server");

    //Let`s not type it again
    ui->newUsernameLineEdit->setText("user123");
    ui->newPasswordLineEdit->setText("salainen");
    ui->eMailLineEdit->setText("user123@emaili.fi");
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
