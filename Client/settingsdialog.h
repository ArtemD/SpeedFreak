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
#include <registerdialog.h>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    HelpSettingsDialog *helpSettingsDialog;
    RegisterDialog *registerDialog;
    void setUserName(QString username);
    void setPassword(QString password);
    QString getUserName();
    QString getPassword();
    void setLabelInfoToUser(QString infoText);
    void usernameOk(bool isOk);

signals:
    void sendregistration();
    void userNameChanged();
    void logout();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SettingsDialog *ui;
    QString username;
    QString password;

private slots:
    void on_pushButtonInfo_clicked();
    void on_setUserPushButton_clicked();
    void on_registratePushButton_clicked();
    void killDialog();
    void registrate();
};

#endif // SETTINGSDIALOG_H
