/*
 * Mainwindow for speedFreak project
 *
 * @author      Rikhard Kuutti <rikhard.kuutti@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "creditsdialog.h"
#include "routesavedialog.h"
#include "welcomedialog.h"
#include "settingsdialog.h"
#include "accelerationstart.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    CreditsDialog *creditsDialog;
    RouteSaveDialog *routeSaveDialog;
    WelcomeDialog *welcomeDialog;
    SettingsDialog *settingsDialog;
    accelerationstart* accstart;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

private slots:
    void on_pushButtonAccelerate_clicked();
    void on_pushButtonSettings_clicked();
    void on_pushButtonRoute_clicked();
    void on_pushButtonCredits_clicked();
    void on_pushButtonWWW_clicked();
};

#endif // MAINWINDOW_H