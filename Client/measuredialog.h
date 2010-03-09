/*
 * CarMainWindow main class
 *
 * @author     Janne Änäkkälä <janne.anakkala@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef MEASUREDIALOG_H
#define MEASUREDIALOG_H

#include "accelerometer.h"
#include "measures.h"
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
    Measures *measures;
    void initializeMeasures();
protected:
    void changeEvent(QEvent *e);

private:
    Ui::MeasureDialog *ui;

    QTimer *timer;
    Accelerometer *accelerometer;

    double time;
    double speed;

    signals:
    void speedAchieved();

private slots:
    void on_pushButtonAbort_clicked();
    void after_timeout();
};

#endif // MEASUREDIALOG_H
