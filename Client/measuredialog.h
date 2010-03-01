#ifndef MEASUREDIALOG_H
#define MEASUREDIALOG_H

#include <QDialog>

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
};

#endif // MEASUREDIALOG_H
