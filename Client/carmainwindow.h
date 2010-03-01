#ifndef CARMAINWINDOW_H
#define CARMAINWINDOW_H

/**
  *This class
  *@author Toni Jussila
  *@version 0.0.1
  */

#include <QMainWindow>
#include "resultdialog.h"
#include "measuredialog.h"
#include <QModelIndex>

namespace Ui {
    class CarMainWindow;
}

class CarMainWindow : public QMainWindow {
    Q_OBJECT
public:
    CarMainWindow(QWidget *parent = 0);
    ~CarMainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CarMainWindow *ui;
    ResultDialog *result;
    void initUnitCompoBox();
    void initSpeedListView();
    MeasureDialog *measure;


private:
    QStringList numbers;
    QStringList units;

private slots:
    void on_autoStartButton_clicked();
    void on_listView_clicked(QModelIndex index);
    void updateUnitCompoBox(QString unit);
};

#endif // CARMAINWINDOW_H
