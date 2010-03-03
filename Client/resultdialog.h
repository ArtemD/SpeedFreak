#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include "measures.h"

namespace Ui {
    class ResultDialog;
}

class ResultDialog : public QDialog {
    Q_OBJECT
public:
    ResultDialog(QWidget *parent = 0);
    ~ResultDialog();
    void saveMeasuresToArray(Measures *pMeasures);

protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *);

private:
    QPoint changeMeasuresToDiagramPoint(int aSpeed, qreal aTime);
    qreal timeArray[10];

private:
    Ui::ResultDialog *ui;
};

#endif // RESULTDIALOG_H
