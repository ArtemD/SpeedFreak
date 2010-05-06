/*
 * SettingsDialog class
 *
 * @author     Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "instructionsdialog.h"
#include <helpsettingsdialog.h>
#include <profiledialog.h>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    HelpSettingsDialog *helpSettingsDialog;
    ProfileDialog *profileDialog;
    void setRegUserName(QString username);
    void setRegPassword(QString password);
    void setRegEmail(QString email);
    QString getRegUserName();
    QString getRegPassword();
    QString getRegEmail();
    void setUserName(QString username);
    void setPassword(QString password);
    QString getUserName();
    QString getPassword();
    void setLabelInfoToUser(QString infoText);
    void usernameOk(bool isOk);
    void clearRegisterLineEdits();

signals:
    void sendregistration();
    void userNameChanged();
    void logout();
    void saveprofile();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SettingsDialog *ui;
    QString regUsername;
    QString regPassword;
    QString regEmail;
    QString username;
    QString password;

private slots:
    void on_pushButtonProfile_clicked();
    void on_pushButtonInfo_clicked();
    void on_setUserPushButton_clicked();
    void on_registratePushButton_clicked();
    void killDialog();
    void saveProfile();
};

#endif // SETTINGSDIALOG_H
