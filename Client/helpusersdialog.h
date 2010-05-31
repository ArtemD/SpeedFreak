#ifndef HELPUSERSDIALOG_H
#define HELPUSERSDIALOG_H

#include <QDialog>

namespace Ui {
    class HelpUsersDialog;
}

class HelpUsersDialog : public QDialog {
    Q_OBJECT
public:
    HelpUsersDialog(QWidget *parent = 0);
    ~HelpUsersDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::HelpUsersDialog *ui;
};

#endif // HELPUSERSDIALOG_H
