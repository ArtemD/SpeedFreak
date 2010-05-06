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

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    helpSettingsDialog = NULL;
    profileDialog = NULL;

    this->setWindowTitle("Settings");
    this->ui->regEMailLineEdit->setText("@");

    ui->pushButtonProfile->setDisabled(true);

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
        ui->pushButtonInfo->setAutoFillBackground(true);
        ui->pushButtonInfo->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");
        ui->pushButtonProfile->setDisabled(false);
    }

    ui->pushButtonInfo->setAutoFillBackground(true);
    ui->pushButtonInfo->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255)");
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

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

//
// Registrate
//
void SettingsDialog::on_registratePushButton_clicked()
{
    // Send username, password and email to SpeedFreak server
    this->regUsername = ui->regUserNameLineEdit->text();
    this->regPassword = ui->regPasswordLineEdit->text();
    this->regEmail = ui->regEMailLineEdit->text();

    if (this->regUsername.compare("") && this->regPassword.compare("") && this->regEmail.compare("") && this->regEmail.compare("@"))
    {
        emit sendregistration();

    }
    else
    {
        QMessageBox::about(this, "One or more of the fields is empty", "Set username (3-12 characters), password (at least 6 characters) and valid email address");
    }

    //close();      //using close() hides popup-window which reports error from server
}

// Next 6 functions can be removed if Settingsdialog is implemented without
// own copy of username, password & email
void SettingsDialog::setRegUserName(QString username)
{
    this->regUsername = username;
}

void SettingsDialog::setRegPassword(QString password)
{
    this->regPassword = password;
}

void SettingsDialog::setRegEmail(QString email)
{
    this->regEmail = email;
}

QString SettingsDialog::getRegUserName()
{
    return this->regUsername;
}

QString SettingsDialog::getRegPassword()
{
    return this->regPassword;
}

QString SettingsDialog::getRegEmail()
{
    return this->regEmail;
}

//
// Set / Change user
//
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
void SettingsDialog::setUserName(QString username)
{
    this->username = username;
}

void SettingsDialog::setPassword(QString password)
{
    this->password = password;
}

QString SettingsDialog::getUserName()
{
    return this->username;
}

QString SettingsDialog::getPassword()
{
    return this->password;
}

void SettingsDialog::setLabelInfoToUser(QString infoText)
{
    this->ui->labelInfoToUser->setText(infoText);
}

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
        ui->setUserUsernameLineEdit->clear();
        ui->setUserPasswordLineEdit->clear();
        this->username = ui->setUserUsernameLineEdit->text();
        this->password = ui->setUserPasswordLineEdit->text();
        saveLogin( this->username, this->password);
        ui->pushButtonProfile->setDisabled(true);
    }
}

void SettingsDialog::clearRegisterLineEdits()
{
    ui->regEMailLineEdit->setText("@");
    ui->regPasswordLineEdit->setText("");
    ui->regUserNameLineEdit->setText("");
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
    if(profileDialog)
    {
        qDebug() << "__Settings kill: profileDialog";
        delete profileDialog;
        profileDialog = NULL;
    }
}

/**
  * This slot function called when ever profile button clicked.
  * Open profile dialog.
  */
void SettingsDialog::on_pushButtonProfile_clicked()
{
    if(!profileDialog)
    {
        profileDialog = new ProfileDialog(this);
    }
    connect(profileDialog, SIGNAL(saveprofile()), this, SLOT(saveProfile()));
    connect(profileDialog, SIGNAL(rejected()), this, SLOT(killDialog()));
    profileDialog->show();
}

void SettingsDialog::saveProfile()
{
    emit saveprofile();
}
