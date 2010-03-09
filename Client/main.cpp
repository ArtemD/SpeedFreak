/*
 * CarMainWindow main class
 *
 * @author     Toni Jussila <toni.jussila@fudeco.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license    http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include <QtGui/QApplication>
#include "carmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CarMainWindow w;
    w.show();
    return a.exec();
}
