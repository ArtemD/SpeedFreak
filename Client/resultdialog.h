/*
 * Result dialog
 *
 * @author     Janne Änäkkälä   <janne.anakkala@fudeco.com>
 * @author      Toni Jussila 	<toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include <helpaccelerationdialog.h>


namespace Ui {
    class ResultDialog;
}

class ResultDialog : public QDialog {
    Q_OBJECT
public:
    ResultDialog(QWidget *parent = 0);
    ~ResultDialog();
    HelpAccelerationDialog *helpAccelerationDialog;

    void setEnd(int pValue);
    void setValue(int pSpeed, double pTime);
    void setLabelInfoToUser(QString infoText);
    double getResult();
    void setSendServerButtonEnabled();

signals:
    void sendresult(double);

protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *);

private:
    QPoint changeMeasuresToDiagramPoint(int aSpeed, qreal aTime);
    void setTimesIntoLabels();
    void setTimeAxelLength(int pChoice);
    void setHeaders();
    void showOrHideLabels();
    int getTargetChoice();

private:
    Ui::ResultDialog *ui;
    qreal timeArray[11];
    double diagramGapStem;
    double diagramGapHorizontal;
    QStringList speedList;
    QStringList timeList;
    int timeAxelLength;
    QString resultString;

private slots:
    void on_pushButtonEMail_clicked();
    void on_pushButtonInfo_clicked();
    void on_pushButtonNew_clicked();
    void on_pushButtonSend_clicked();
    void killHelpDialog();
};

#endif // RESULTDIALOG_H
