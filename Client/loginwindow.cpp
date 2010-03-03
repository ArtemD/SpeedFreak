#include "loginwindow.h"
#include "ui_loginwindow.h"

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

void LoginWindow::on_loginPushButton_clicked()
{
    // To do
    //loginToServer(ui->userNameLineEdit->text(),
    //              ui->passwordLineEdit->text());
}



