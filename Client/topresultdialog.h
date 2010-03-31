#ifndef TOPRESULTDIALOG_H
#define TOPRESULTDIALOG_H

#include <QDialog>

namespace Ui {
    class TopResultDialog;
}

class TopResultDialog : public QDialog {
    Q_OBJECT
public:
    TopResultDialog(QWidget *parent = 0);
    ~TopResultDialog();
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
    void on_comboBoxTopCategory_currentIndexChanged(int index);
    void on_buttonTopRefresh_clicked();

};

#endif // TOPRESULTDIALOG_H
