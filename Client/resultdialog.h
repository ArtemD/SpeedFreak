/*
 * CarMainWindow main class
 *
 * @author     Janne Änäkkälä <janne.anakkala@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
//#include "measures.h"

namespace Ui {
    class ResultDialog;
}

class ResultDialog : public QDialog {
    Q_OBJECT
public:
    ResultDialog(QWidget *parent = 0);
    ~ResultDialog();
    //void saveMeasuresToArray(Measures *pMeasures);
    void setDiagramGapStem(double pDiagramGapStem);
    void setDiagramGapHorizontal(double pDiagramGapHorizontal);

    void setEnd(int pValue);
    void setValue(int pSpeed, double pTime);

signals:
    void sendresult(double result);

protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *);

private:
    QPoint changeMeasuresToDiagramPoint(int aSpeed, qreal aTime);
    void setTimesIntoLabels();
    void setTimeAxelLength();

private:
    Ui::ResultDialog *ui;
    qreal timeArray[11];
    double diagramGapStem;
    double diagramGapHorizontal;
    QStringList speedList;
    QStringList timeList;
    int timeAxelLength;

private slots:
    void on_pushButtonNew_clicked();
    void on_pushButtonSend_clicked();
};

#endif // RESULTDIALOG_H
