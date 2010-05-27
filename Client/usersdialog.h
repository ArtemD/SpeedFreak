#ifndef USERSDIALOG_H
#define USERSDIALOG_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
    class UsersDialog;
}

class UsersDialog : public QDialog {
    Q_OBJECT
public:
    UsersDialog(QWidget *parent = 0);
    ~UsersDialog();
    void appendUserToList(QString usrname);
    void setUserInfo(QStringList *usersInfo);
    void setLabelInfoToUser(QString infoText);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::UsersDialog *ui;
    //QStringList *usersList;

signals:
    void getUserInfo(QString name);

private slots:
    void on_listWidgetUsers_itemClicked(QListWidgetItem* item);
};

#endif // USERSDIALOG_H
