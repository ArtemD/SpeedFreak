#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
    class LoginWindow;
}

class LoginWindow : public QDialog {
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    void setUserName(QString username);
    void setPassword(QString password);
    QString getUserName();
    QString getPassword();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::LoginWindow *ui;
    QString username;
    QString password;

private slots:
    void on_loginPushButton_clicked();
    void on_cancelPushButton_clicked();
};

#endif // LOGINWINDOW_H
