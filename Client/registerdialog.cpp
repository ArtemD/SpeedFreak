#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QSize>
#include "usersettings.h"
#include "settingsdialog.h"
#include "xmlreader.h"

/**
  * Constructor of this class.
  */
RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Register new user");
    this->ui->regEMailLineEdit->setText("@");
    // User info label
    ui->labelInfoToUser->setVisible(0);
    ui->labelInfoToUser->setText("");
    // Button
    imageButtonState = false;
    manufacturer="";
    type="";
    model="";
    description="";
    picture="";

    ui->buttonImage->setVisible(false);
    ui->labelImage->setVisible(false);
    // Read user profile xml
    /*QString filename = "/home/user/MyDocs/speedfreak/profile/" + parent->getUserName() + "_profile.xml";
    QFile file(filename);

    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "_xmlRead fail";
        return;
    }
    else
    {
        xmlReader = new XmlReader();
        xmlReader->xmlReadProfile(&file,this);
    }
    file.close();*/
}

/**
  * Destructor of this class.
  */
RegisterDialog::~RegisterDialog()
{
    delete ui;
}

/**
  *
  */
void RegisterDialog::changeEvent(QEvent *e)
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
  * This function is used to clear lineEdits and close this dialog.
  */
void RegisterDialog::clearRegisterLineEdits()
{
    ui->regEMailLineEdit->setText("@");
    ui->regPasswordLineEdit->setText("");
    ui->regUserNameLineEdit->setText("");
    ui->lineEditManufacturer->setText("");
    ui->lineEditModel->setText("");
    ui->lineEditType->setText("");
    ui->textEditDescription->setText("");

    this->close();
}

// Next 6 functions can be removed if Settingsdialog is implemented without
// own copy of username, password & email
/**
  *
  */
void RegisterDialog::setRegUserName(QString username)
{
    this->regUsername = username;
}

/**
  *
  */
void RegisterDialog::setRegPassword(QString password)
{
    this->regPassword = password;
}

/**
  *
  */
void RegisterDialog::setRegEmail(QString email)
{
    this->regEmail = email;
}

/**
  *
  */
QString RegisterDialog::getRegUserName()
{
    return this->regUsername;
}

/**
  *
  */
QString RegisterDialog::getRegPassword()
{
    return this->regPassword;
}

/**
  *
  */
QString RegisterDialog::getRegEmail()
{
    return this->regEmail;
}

void RegisterDialog::on_registratePushButton_clicked()
{
    // Save labels data
    setManufacturer(ui->lineEditManufacturer->text());
    setType(ui->lineEditType->text());
    setModel(ui->lineEditModel->text());
    setDescription(ui->textEditDescription->toPlainText());

    // emit settingsdialog --> mainwindow --> httpclient
    //emit saveprofile();



    // Send username, password and email to SpeedFreak server
    this->regUsername = ui->regUserNameLineEdit->text();
    this->regPassword = ui->regPasswordLineEdit->text();
    this->regEmail = ui->regEMailLineEdit->text();

    if (this->regUsername.compare("") && this->regPassword.compare("") && this->regEmail.compare("") && this->regEmail.compare("@"))
    {
        emit registrate();
    }
    else
    {
        QMessageBox::about(this, "One or more of the fields is empty", "Set username (3-12 characters), password (at least 6 characters) and valid email address");
    }

    //close();      //using close() hides popup-window which reports error from server
}

/**
  * This get function return manufacturer
  * @return QString
  */
QString RegisterDialog::getManufacturer()
{
    return manufacturer;
}

/**
  * This get function return type
  * @return QString
  */
QString RegisterDialog::getType()
{
    return type;
}

/**
  * This get function return model
  * @return QString
  */
QString RegisterDialog::getModel()
{
    return model;
}

/**
  * This get function return description
  * @return QString
  */
QString RegisterDialog::getDescription()
{
    QString all = manufacturer + ";" + type + ";" + model + ";" + description;
    return all;
}

/**
  * This get function return description
  * @return QString
  */
QString RegisterDialog::getPicture()
{
    return picture;
}

/**
  * This set function set manufacturer
  * @param QString
  */
void RegisterDialog::setManufacturer(QString m)
{
    manufacturer = m;
    ui->lineEditManufacturer->setText(m);
}

/**
  * This set function set type
  * @param QString
  */
void RegisterDialog::setType(QString t)
{
    type = t;
    ui->lineEditType->setText(t);
}

/**
  * This set function set model
  * @param QString
  */
void RegisterDialog::setModel(QString m)
{
    model = m;
    ui->lineEditModel->setText(m);
}

/**
  * This set function set description
  * @param QString
  */
void RegisterDialog::setDescription(QString d)
{
    description = d;
    ui->textEditDescription->setText(d);
}

/**
  * This set function set description
  * @param QString
  */
void RegisterDialog::setPicture(QString p)
{
    picture = p;
    loadPicture(p);
}

/**
  * This function set label info text to user
  * @param QString
  */
void RegisterDialog::setLabelInfoToUser(QString infoText)
{
    ui->labelInfoToUser->setVisible(1);
    this->ui->labelInfoToUser->setText(infoText);
}

/**
  * This slot function called when image button clicked.
  */
void RegisterDialog::on_buttonImage_clicked()
{
    if (imageButtonState == false)
    {
        ui->buttonImage->setText("Load image");
    }
    else
    {
        ui->buttonImage->setText("Change image");
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    loadPicture(fileName);
}

/**
  * This function load picture.
  * @param QString
  */
void RegisterDialog::loadPicture(QString fileName)
{
    if (!fileName.isEmpty())
    {
        QImage image(fileName);
        if (image.isNull())
        {
            QMessageBox::information(this, tr("Profile"),tr("Cannot load %1.").arg(fileName));
            return;
        }
        ui->labelImage->setPixmap(QPixmap::fromImage(image.scaled(QSize(120,120), Qt::KeepAspectRatio)));
        picture = fileName;
    }
}
