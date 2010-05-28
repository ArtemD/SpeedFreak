/*
 * Profile dialog class
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include <QString>
#include <QFileDialog>
#include <QImage>
#include <QMessageBox>
#include <QPixmap>
#include <QSize>
#include <QDebug>
#include "profiledialog.h"
#include "ui_profiledialog.h"
#include "usersettings.h"
#include "settingsdialog.h"
#include "xmlreader.h"

/**
  * Constructor of this class.
  *
  * @param QWidget pointer to parent object. By default the value is NULL.
  */
ProfileDialog::ProfileDialog(SettingsDialog *parent) : QDialog(parent), ui(new Ui::ProfileDialog)
{
    qDebug() << "__ProfileDialog";
    ui->setupUi(this);

    if (loginSaved())
    {
        this->setWindowTitle("Profile - " + parent->getUserName());
    }
    else
    {
        this->setWindowTitle("Profile");
    }

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

    // Read user profile xml
    QString filename = "/home/user/MyDocs/speedfreak/profile/" + parent->getUserName() + "_profile.xml";
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
    file.close();
}

/**
  * Destructor of this class. Deletes all dynamic objects and sets them to NULL.
  */
ProfileDialog::~ProfileDialog()
{
    qDebug() << "__~ProfileDialog";

    if(ui)
        delete ui;

    if(xmlReader)
        delete xmlReader;
}

/**
  *
  */
void ProfileDialog::changeEvent(QEvent *e)
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
  * This slot function called when image button clicked.
  *
  */
void ProfileDialog::on_buttonImage_clicked()
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
  *
  * @param QString file name
  */
void ProfileDialog::loadPicture(QString fileName)
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

/**
  * This slot function called when save button clicked.
  *
  * @todo server connection
  */
void ProfileDialog::on_buttonSave_clicked()
{
    // Save labels data
    setManufacturer(ui->lineEditManufacturer->text());
    setType(ui->lineEditType->text());
    setModel(ui->lineEditModel->text());
    setDescription(ui->textEditDescription->toPlainText());

    this->close();
    // emit settingsdialog --> mainwindow --> httpclient
    //emit saveprofile();
}

/**
  * Get function return manufacturer.
  *
  * @return QString manufacturer
  */
QString ProfileDialog::getManufacturer()
{
    return manufacturer;
}

/**
  * Get function return type.
  *
  * @return QString type
  */
QString ProfileDialog::getType()
{
    return type;
}

/**
  * Get function return model.
  *
  * @return QString model
  */
QString ProfileDialog::getModel()
{
    return model;
}

/**
  * Get function return description.
  *
  * @return QString description
  */
QString ProfileDialog::getDescription()
{
    return description;
}

/**
  * Get function return picture.
  *
  * @return QString picture
  */
QString ProfileDialog::getPicture()
{
    return picture;
}

/**
  * This function set manufacturer.
  *
  * @param QString manufacturer
  */
void ProfileDialog::setManufacturer(QString m)
{
    manufacturer = m;
    ui->lineEditManufacturer->setText(m);
}

/**
  * This function set type.
  *
  * @param QString type
  */
void ProfileDialog::setType(QString t)
{
    type = t;
    ui->lineEditType->setText(t);
}

/**
  * This function set model.
  *
  * @param QString model
  */
void ProfileDialog::setModel(QString m)
{
    model = m;
    ui->lineEditModel->setText(m);
}

/**
  * This function set description.
  *
  * @param QString description
  */
void ProfileDialog::setDescription(QString d)
{
    description = d;
    ui->textEditDescription->setText(d);
}

/**
  * This function set description.
  *
  * @param QString picture
  */
void ProfileDialog::setPicture(QString p)
{
    picture = p;
    loadPicture(p);
}

/**
  * This function set label info text to user.
  *
  * @param QString info text
  */
void ProfileDialog::setLabelInfoToUser(QString infoText)
{
    ui->labelInfoToUser->setVisible(1);
    this->ui->labelInfoToUser->setText(infoText);
}
