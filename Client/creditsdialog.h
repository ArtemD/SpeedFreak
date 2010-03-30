/*
 * Credits Dialog
 *
 * @author      Rikhard Kuutti <rikhard.kuutti@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef CREDITSDIALOG_H
#define CREDITSDIALOG_H

#include <QDialog>

namespace Ui {
    class CreditsDialog;
}

class CreditsDialog : public QDialog {
    Q_OBJECT
public:
    CreditsDialog(QWidget *parent = 0);
    ~CreditsDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CreditsDialog *ui;

private slots:
};

#endif // CREDITSDIALOG_H
