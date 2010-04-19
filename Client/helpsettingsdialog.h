#ifndef HELPSETTINGSDIALOG_H
#define HELPSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
    class HelpSettingsDialog;
}

class HelpSettingsDialog : public QDialog {
    Q_OBJECT
public:
    HelpSettingsDialog(QWidget *parent = 0);
    ~HelpSettingsDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::HelpSettingsDialog *ui;
    int pageCounter;

private slots:
    void on_pushButtonLast_clicked();
    void on_pushButtonNext_clicked();
};

#endif // HELPSETTINGSDIALOG_H
