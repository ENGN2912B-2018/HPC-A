#ifndef RBCGUI_H
#define RBCGUI_H

#include <QMainWindow>
#include <vtkSmartPointer.h>
#include <vtkObject.h>
#include <vtkEventQtSlotConnect.h>
#include "QVTKOpenGLWidget.h"
#include "parameter_setting.h"


typedef std::vector<vtkSmartPointer<vtkRenderer>> RendererVector;
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

    //void slot_clicked(vtkObject*, unsigned long, void*, void*);
private slots:
    void on_para_setting_clicked();
    //void receiveData(QString data1, QString data2,QString data3,QString data4);
    void on_apply_changes_clicked();

    void on_visualization_clicked();

private:
    Ui::RBCGUI *ui;
    //vtkSmartPointer<vtkEventQtSlotConnect> Connections;
    Parameter_setting *paraWin;

};

#endif // RBCGUI_H
