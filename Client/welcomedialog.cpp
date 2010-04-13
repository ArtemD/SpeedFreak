/*
 * Welcome dialog
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @author     Rikhard Kuutti <rikhard.kuutti@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include "welcomedialog.h"
#include "ui_welcomedialog.h"
#include "instructionsdialog.h"

#include <QSettings>

WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(" ");
    movie = new QMovie("Graphics/start.gif");
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

        // Show instructionsDialog if this is
        // the first time the application is run
        QSettings settings;
        bool firstRunGone = settings.value("firstRunGone").toBool();
        if (!firstRunGone) {
            // show instructions
            InstructionsDialog *instructionsDialog = new InstructionsDialog;
            instructionsDialog->show();
            settings.setValue("firstRunGone", true);
        }
    }
}
