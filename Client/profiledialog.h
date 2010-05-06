#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include <QDialog>

namespace Ui {
    class ProfileDialog;
}

class ProfileDialog : public QDialog {
    Q_OBJECT
public:
    ProfileDialog(QWidget *parent = 0);
    ~ProfileDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ProfileDialog *ui;
};

#endif // PROFILEDIALOG_H
