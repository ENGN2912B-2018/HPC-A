#include "rbcgui.h"
#include <QApplication>
#include"parameter_setting.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RBCGUI w;
    w.show();

    return a.exec();
}
