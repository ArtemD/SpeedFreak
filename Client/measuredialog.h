#ifndef MEASUREDIALOG_H
#define MEASUREDIALOG_H

#include "accelerometer.h"
#include <QDialog>
#include <QTimer>

namespace Ui {
    class MeasureDialog;
}

class MeasureDialog : public QDialog {
    Q_OBJECT
public:
    MeasureDialog(QWidget *parent = 0);
    ~MeasureDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MeasureDialog *ui;

    QTimer *timer;
    Accelerometer *accelerometer;


    qreal time;
    qreal speed;

    signals:
    void speedAchieved();

private slots:
    void on_pushButtonAbort_clicked();
    void after_timeout();
};

#endif // MEASUREDIALOG_H
