#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "creditsdialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    CreditsDialog *creditsDialog;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

private slots:
    void on_pushButtonCredits_clicked();
    void on_pushButtonWWW_clicked();
};

#endif // MAINWINDOW_H
