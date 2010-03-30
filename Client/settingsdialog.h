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

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SettingsDialog *ui;
    InstructionsDialog *instructionsDialog;

private slots:
    void on_pushButtonHelp_clicked();
};

#endif // SETTINGSDIALOG_H
