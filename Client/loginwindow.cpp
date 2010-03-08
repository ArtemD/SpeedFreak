/*
 * Loginwindow class to maintain username for user
 *
 * @author      Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
 * @author
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Login to Speed Freak server");
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::changeEvent(QEvent *e)
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

void LoginWindow::on_cancelPushButton_clicked()
{
    close();
}

void setUser(QString uN, QString pW);

void LoginWindow::on_loginPushButton_clicked()
{
    this->username = ui->userNameLineEdit->text();
    this->password = ui->passwordLineEdit->text();
    close();
}

void LoginWindow::setUserName(QString username)
{
    this->username = username;
}

void LoginWindow::setPassword(QString password)
{
    this->password = password;
}

QString LoginWindow::getUserName()
{
    return this->username;
}

QString LoginWindow::getPassword()
{
    return this->password;
}





