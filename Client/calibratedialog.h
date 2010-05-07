/*
 * Calibrate dialog
 *
 * @author     Kai Rasilainen <kai.rasilainen@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef CALIBRATEDIALOG_H
#define CALIBRATEDIALOG_H

#include <QDialog>

namespace Ui {
    class CalibrateDialog;
}

class CalibrateDialog : public QDialog {
    Q_OBJECT
public:
    CalibrateDialog(QWidget *parent = 0);
    ~CalibrateDialog();

    void setProgressValue(int value);
    void resetProgressValue();
    void setMaxValue(int max);
    void setTitle(QString title);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CalibrateDialog *ui;
};

#endif // CALIBRATEDIALOG_H
