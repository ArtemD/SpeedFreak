/*
 * Profile dialog class
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include <QDialog>

class SettingsDialog;
class XmlReader;

namespace Ui
{
    class ProfileDialog;
}

class ProfileDialog : public QDialog
{
    Q_OBJECT
public:
    ProfileDialog(SettingsDialog *parent = 0);
    ~ProfileDialog();
    XmlReader *xmlReader;
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
    Ui::ProfileDialog *ui;
    bool imageButtonState;
    void loadPicture(QString);
    QString manufacturer;
    QString type;
    QString model;
    QString description;
    QString picture;

private slots:
    void on_buttonSave_clicked();
    void on_buttonImage_clicked();

signals:
    void saveprofile();
};

#endif // PROFILEDIALOG_H
