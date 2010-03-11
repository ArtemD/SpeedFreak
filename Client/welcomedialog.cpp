/*
 * Welcome dialog
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "welcomedialog.h"
#include "ui_welcomedialog.h"

WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(" ");
    movie = new QMovie("start.gif");
    ui->labelWelcome->setMovie(movie);
    movie->start();
    connect(movie,SIGNAL(frameChanged(int)),this,SLOT(stop(int)));
}

WelcomeDialog::~WelcomeDialog()
{
    delete ui;
    movie->stop();
    delete movie;
}

void WelcomeDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void WelcomeDialog::stop(int currentFrame)
{
    if (currentFrame == 21)
    {
        movie->stop();
        this->close();
    }
}
