#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
    class RegisterDialog;
}

class RegisterDialog : public QDialog {
    Q_OBJECT
public:
    RegisterDialog(QWidget *parent = 0);
    ~RegisterDialog();
    void clearRegisterLineEdits();
    QString getRegUserName();
    QString getRegPassword();
    QString getRegEmail();
    void setRegUserName(QString username);
    void setRegPassword(QString password);
    void setRegEmail(QString email);
    QString getManufacturer();
    QString getType();
    QString getModel();
    QString getDescription();
    QString getPicture();
    void setManufacturer(QString m);
    void setType(QString t);
    void setModel(QString m);
    void setDescription(QString d);
    void setPicture(QString p);
    void setLabelInfoToUser(QString infoText);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RegisterDialog *ui;
    bool imageButtonState;
    void loadPicture(QString);
    QString regUsername;
    QString regPassword;
    QString regEmail;
    QString manufacturer;
    QString type;
    QString model;
    QString description;
    QString picture;

private slots:
    void on_buttonImage_clicked();
    void on_registratePushButton_clicked();

signals:
    void registrate();
};

#endif // REGISTERDIALOG_H
