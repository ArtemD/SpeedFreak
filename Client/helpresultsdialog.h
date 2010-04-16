#ifndef HELPRESULTSDIALOG_H
#define HELPRESULTSDIALOG_H

#include <QDialog>

namespace Ui {
    class HelpResultsDialog;
}

class HelpResultsDialog : public QDialog {
    Q_OBJECT
public:
    HelpResultsDialog(QWidget *parent = 0);
    ~HelpResultsDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::HelpResultsDialog *ui;
};

#endif // HELPRESULTSDIALOG_H
