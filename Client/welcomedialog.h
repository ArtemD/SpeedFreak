/*
 * Welcome dialog
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>
#include <QMovie>

namespace Ui {
    class WelcomeDialog;
}

class WelcomeDialog : public QDialog {
    Q_OBJECT
public:
    WelcomeDialog(QWidget *parent = 0);
    ~WelcomeDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::WelcomeDialog *ui;
    QMovie *movie;

private slots:
    void stop(int currentFrame);
};

#endif // WELCOMEDIALOG_H
