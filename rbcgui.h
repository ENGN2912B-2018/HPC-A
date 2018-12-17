#ifndef RBCGUI_H
#define RBCGUI_H

#include <QMainWindow>
#include <vtkSmartPointer.h>
#include <vtkObject.h>
#include <vtkEventQtSlotConnect.h>
#include "QVTKOpenGLWidget.h"
#include "parameter_setting.h"
//VTK_MODULE_INIT(vtkRenderingFreeType);

//typedef std::vector<vtkSmartPointer<vtkRenderer>> RendererVector;
//typedef std::vector<QOpenGLWidget> QVTKWidgetVector;

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
    void setStatusText(QString status);

private slots:
    void on_para_setting_clicked();
    void on_apply_changes_clicked();
    void on_visualization_clicked();

private:
    Ui::RBCGUI *ui;
    Parameter_setting *paraWin;

};

#endif // RBCGUI_H
