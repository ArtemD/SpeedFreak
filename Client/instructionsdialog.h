/*
 * Instructions dialog for speedFreak project
 *
 * @author      Rikhard Kuutti 	<rikhard.kuutti@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef INSTRUCTIONSDIALOG_H
#define INSTRUCTIONSDIALOG_H

#include <QDialog>

namespace Ui {
    class InstructionsDialog;
}

class InstructionsDialog : public QDialog {
    Q_OBJECT
public:
    InstructionsDialog(QWidget *parent = 0);
    ~InstructionsDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::InstructionsDialog *ui;
};

#endif // INSTRUCTIONSDIALOG_H
