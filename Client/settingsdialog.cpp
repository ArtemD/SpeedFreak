/*
 * SettingsDialog class
 *
 * @author      Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
 * @author      Toni Jussila    <toni.jussila@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "usersettings.h"
#include <QMessageBox>
#include <QDebug>

/**
  * Constructor of this class
  */
SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    helpSettingsDialog = NULL;
    registerDialog = NULL;
    this->setWindowTitle("Settings");

    if (loginSaved())
    {
        QString uName, pWord;

        getLoginInfo( &uName, &pWord);
        this->username = uName;
        this->password = pWord;

        // Set line edit
        ui->setUserPasswordLineEdit->setText(this->password);
        ui->setUserUsernameLineEdit->setText(this->username);
        ui->setUserPasswordLineEdit->setDisabled(1); // Disable because user logged
        ui->setUserUsernameLineEdit->setDisabled(1); // Disable because user logged

        // Already someone as user - change button text to "Change"
        ui->setUserPushButton->setText("Log out");

        // Button settings
        ui->pushButtonProfile->setAutoFillBackground(true);
        ui->pushButtonProfile->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");
        ui->pushButtonProfile->setDisabled(false);
        ui->pushButtonProfile->setVisible(false);
    }
    // Button settings
    ui->pushButtonInfo->setAutoFillBackground(true);
    ui->pushButtonInfo->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");
    ui->pushButtonProfile->setVisible(false);
}

/**
  * Destructor of this class
  */
SettingsDialog::~SettingsDialog()
{
    delete ui;
}

/**
  *
  */
void SettingsDialog::changeEvent(QEvent *e)
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

/**
  * This slot function called when ever "register new user" -button clicked.
  */
void SettingsDialog::on_registratePushButton_clicked()
{
    if(!registerDialog)
    {
        registerDialog = new RegisterDialog(this);
    }
    connect(registerDialog, SIGNAL(registrate()), this, SLOT(registrate()));
    connect(registerDialog, SIGNAL(rejected()), this, SLOT(killDialog()));
    registerDialog->show();
}

/**
  *  Set / Change user
  */
void SettingsDialog::on_setUserPushButton_clicked()
{
    if (!ui->setUserPushButton->text().compare("Log out"))
    {
        ui->setUserUsernameLineEdit->setDisabled(false);
        ui->setUserPasswordLineEdit->setDisabled(false);
        //ui->setUserUsernameLineEdit->setText("");
        //ui->setUserPasswordLineEdit->setText("");
        ui->setUserUsernameLineEdit->clear();
        ui->setUserPasswordLineEdit->clear();
        this->username = ui->setUserUsernameLineEdit->text();
        this->password = ui->setUserPasswordLineEdit->text();
        ui->setUserPushButton->setText("Log in");
        saveLogin( this->username, this->password);
        ui->pushButtonProfile->setDisabled(true);
        emit logout();
    }
    else
    {
        this->username = ui->setUserUsernameLineEdit->text();
        this->password = ui->setUserPasswordLineEdit->text();
        saveLogin( this->username, this->password);
        ui->setUserPushButton->setText("Log out");

        if(this->username.compare(""))
        {
            emit userNameChanged();
            //ui->setUserPushButton->setText("Log out");
        }

        else
        {
            QMessageBox::about(this, "Username field is empty", "Set username and log in again");
            ui->setUserPushButton->setText("Log in");
        }
    }
    // Save these also to usersettings
    //saveLogin( this->username, this->password);

    /*
    // Set "Set/Change User" button text
    if (this->username.length() > 0)
    {
        ui->setUserPushButton->setText("Log out");
    }
    else
    {   // Username "cleared"
        ui->setUserPushButton->setText("Log in");
    }

    emit userNameChanged();
    */
    //close();  //using close() hides popup-window which reports error from server
}

// Next 4 functions can be removed if Settingsdialog is implemented without
// own copy of username & password
/**
  *
  */
void SettingsDialog::setUserName(QString username)
{
    this->username = username;
}

/**
  *
  */
void SettingsDialog::setPassword(QString password)
{
    this->password = password;
}

/**
  *
  */
QString SettingsDialog::getUserName()
{
    return this->username;
}

/**
  *
  */
QString SettingsDialog::getPassword()
{
    return this->password;
}

/**
  *
  */
void SettingsDialog::setLabelInfoToUser(QString infoText)
{
    this->ui->labelInfoToUser->setText(infoText);
}

/**
  *
  */
void SettingsDialog::usernameOk(bool isOk)
{
    if (isOk)
    {
        ui->setUserPushButton->setText("Log out");
        ui->setUserUsernameLineEdit->setDisabled(true);
        ui->setUserPasswordLineEdit->setDisabled(true);
        ui->pushButtonProfile->setDisabled(false);
    }

    else
    {
        ui->setUserPushButton->setText("Log in");
        ui->setUserPasswordLineEdit->clear();
        this->username = "";
        this->password = "";
        saveLogin( this->username, this->password);
        ui->pushButtonProfile->setDisabled(true);
    }
}

/**
  * This slot function called when ever info button clicked.
  */
void SettingsDialog::on_pushButtonInfo_clicked()
{
    if(!helpSettingsDialog)
    {
        helpSettingsDialog = new HelpSettingsDialog;
    }
    connect(helpSettingsDialog, SIGNAL(rejected()), this, SLOT(killDialog()));
    helpSettingsDialog->show();
}

/**
  * This slot function called when ever dialog rejected.
  */
void SettingsDialog::killDialog()
{
    if(helpSettingsDialog)
    {
        qDebug() << "__Settings kill: helpSettingsDialog";
        delete helpSettingsDialog;
        helpSettingsDialog = NULL;
    }
    if(registerDialog)
    {
        qDebug() << "__Settings kill: registerDialog";
        delete registerDialog;
        registerDialog = NULL;
    }
}

/**
  * This slot function called when
  */
void SettingsDialog::registrate()
{
    emit sendregistration();
}
