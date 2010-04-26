/*
 * Topresultdialog
 *
 * @author     Olavi Pulkkinen <olavi.pulkkinena@fudeco.com>
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef TOPRESULTDIALOG_H
#define TOPRESULTDIALOG_H

#include <QDialog>
#include <helpresultsdialog.h>

namespace Ui {
    class TopResultDialog;
}

class TopResultDialog : public QDialog {
    Q_OBJECT
public:
    TopResultDialog(QWidget *parent = 0);
    ~TopResultDialog();
    HelpResultsDialog *helpResultsDialog;
    void setCompoBoxCategories(QStringList list);
    void showTopList(QString str);
    int getRecentCategoryIndex();
    int getLimitNr();
    void setLimitNr(int number);
    void setLabelInfoToUser(QString infoText);

protected:
    void changeEvent(QEvent *e);

signals:
    void refreshCategoryList();
    void refreshTopList(int index);

private:
    Ui::TopResultDialog *ui;
    int recentCategoryIndex;
    int limitNr;

private slots:
    void on_pushButtonInfo_clicked();
    void on_comboBoxTopCategory_currentIndexChanged(int index);
    void on_buttonTopRefresh_clicked();
    void killHelpDialog();
};

#endif // TOPRESULTDIALOG_H
