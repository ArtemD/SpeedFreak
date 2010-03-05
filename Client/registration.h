#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>

namespace Ui {
    class Registration;
}

class Registration : public QDialog {
    Q_OBJECT
public:
    Registration(QWidget *parent = 0);
    ~Registration();
    void setUserName(QString username);
    void setPassword(QString password);
    void setEmail(QString email);
    QString getUserName();
    QString getPassword();
    QString getEmail();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Registration *ui;
    QString username;
    QString password;
    QString email;

private slots:
    void on_cancelPushButton_clicked();
    void on_registratePushButton_clicked();
};

#endif // REGISTRATION_H

