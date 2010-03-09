/*
 * Registration class
 *
 * @author     Olavi Pulkkinen <olavi.pulkkinen@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

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

signals:
    void sendregistration();

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

