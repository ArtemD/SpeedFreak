#include <QtGui/QApplication>
#include "carmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CarMainWindow w;
    w.show();
    return a.exec();
}
