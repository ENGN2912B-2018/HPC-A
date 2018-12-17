#include "rbcgui.h"
#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLWidget.h>
#include"parameter_setting.h"
#include <thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //vtkOpenGLRenderWindow::SetGlobalMaximumNumberOfMultiSamples();
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

    RBCGUI w;

    w.show();
    return a.exec();
}
