#ifndef ACCELERATIONSTART_H
#define ACCELERATIONSTART_H

#include <QDialog>
#include "accrealtimedialog.h"

namespace Ui {
    class accelerationstart;
}

class accelerationstart : public QDialog {
    Q_OBJECT
public:
    accelerationstart(QWidget *parent = 0);
    ~accelerationstart();
    QString getMeasureCategory();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::accelerationstart *ui;
    AccRealTimeDialog* accRealTimeDialog;
    double stopMeasureSpeed;
    QString measureCategory;

private slots:
    void on_categorComboBox_currentIndexChanged(int index);
    void on_buttonStart_clicked();
    void on_buttonCalib_clicked();
};

#endif // ACCELERATIONSTART_H
