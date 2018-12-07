#include "rbcgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RBCGUI w;
    w.show();

    return a.exec();
}
