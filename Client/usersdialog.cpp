#include "usersdialog.h"
#include "ui_usersdialog.h"
#include <QPushButton>
#include <QDebug>

UsersDialog::UsersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsersDialog)
{
    ui->setupUi(this);
    //usersList = new QStringList();
    //ui->listWidgetUsers->addItems(usersList);
    //emit getUsers();
}

UsersDialog::~UsersDialog()
{
    delete ui;
}

void UsersDialog::changeEvent(QEvent *e)
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
  *This slot function will execute when user clicks listWidget item.
  *Emits signal for getting user info from server.
  *@param QListWidgetItem* item includes users name which need to send server.
  */
void UsersDialog::on_listWidgetUsers_itemClicked(QListWidgetItem* item)
{
    QString name;
    name = item->text();

    ui->labelManufacter->clear();
    ui->labelType->clear();
    ui->labelModel->clear();
    ui->plainTextEditDescription->clear();
    emit getUserInfo(item->text());
}

/**
  *Sets users to listWidget.
  */
void UsersDialog::appendUserToList(QString usrname)
{
    //usersList->append(usrname);
    ui->listWidgetUsers->addItem(usrname);
}

/**
  *Sets data to user's information labels.
  */
void UsersDialog::setUserInfo(QStringList *usersInfo)
{
   QStringList splitted;
   //QString temp;
   QString allInfo;
   //QString manufacter;
   //QString description;
   allInfo = usersInfo->at(1);
   splitted = allInfo.split(";");
   ui->labelUsersDetails->setText(usersInfo->at(0) + ":");

   //temp = splitted.at(0);
   //manufacter = temp.remove("![CDATA[", Qt::CaseSensitive);

   //temp = splitted.at(3);
   //description = temp.remove("]]>", Qt::CaseSensitive);

   if (splitted.count() == 4)
   {
       ui->labelManufacter->setText(splitted.at(0));
       ui->labelType->setText(splitted.at(1));
       ui->labelModel->setText(splitted.at(2));
       ui->plainTextEditDescription->setPlainText(splitted.at(3));
    }

   else
   {
       ui->plainTextEditDescription->setPlainText(splitted.at(0));
   }
   //ui->labelDescriptionHeader->setText("Description: " + usersInfo->at(4));
}

void UsersDialog::setLabelInfoToUser(QString infoText)
{
    this->ui->labelInfoToUser->setText(infoText);
}
