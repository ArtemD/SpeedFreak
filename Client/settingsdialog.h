#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

#include "instructionsdialog.h"

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
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

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SettingsDialog *ui;
    InstructionsDialog *instructionsDialog;
    QString regUsername;
    QString regPassword;
    QString regEmail;
    QString username;
    QString password;

private slots:
    void on_setUserPushButton_clicked();
    void on_registratePushButton_clicked();
    void on_pushButtonHelp_clicked();
};

#endif // SETTINGSDIALOG_H