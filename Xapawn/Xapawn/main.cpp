#include "Xapawn.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XapawnMainWindow w;
    w.show();
    return a.exec();
}
