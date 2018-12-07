#ifndef RBCGUI_H
#define RBCGUI_H

#include <QMainWindow>
#include <vtkImageData.h>
//#include "qvtkopenglwidget.h"
#include <vtkSmartPointer.h>
#include <vtkObject.h>
#include <vtkEventQtSlotConnect.h>
#include "QVTKOpenGLWidget.h"
#include "parameter_setting.h"

namespace Ui {
class RBCGUI;
}

class RBCGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit RBCGUI(QWidget *parent = 0);
    ~RBCGUI();
    void loadFile(const QString &fileName);
    void slot_clicked(vtkObject*, unsigned long, void*, void*);
private slots:
    //void on_parameter_clicked();

    void on_para_setting_clicked();



private:
    Ui::RBCGUI *ui;
    vtkSmartPointer<vtkEventQtSlotConnect> Connections;
    QVTKOpenGLWidget *qvtkWidget;
    Parameter_setting *paraWin;

};

#endif // RBCGUI_H
