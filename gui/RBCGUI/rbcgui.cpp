//#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
//#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include "rbcgui.h"
#include "ui_rbcgui.h"

#include "parameter_setting.h"

#include<QtWidgets>
#include<QApplication>
//#include "qvtkopenglwidget.h"
#include<QVTKOpenGLWidget.h>
#include <QDialog>
#include<QImage>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include "vtkGenericOpenGLRenderWindow.h"
#include <vtkRenderWindowInteractor.h>

#include <vtkNew.h>
#include <vtkSmartPointer.h>
#include<vtkSmartPointerBase.h>
#include <vtkImageViewer2.h>
#include <vtkImageData.h>
#include <vtkPNGReader.h>
#include <vtkImageAlgorithm.h>
#include <vtkEventQtSlotConnect.h>
#include <vtkInteractorStyleTrackballActor.h>

#include <vtkPolyDataMapper.h>
#include <vtkSphereSource.h>

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle);

RBCGUI::RBCGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RBCGUI)
{
    ui->setupUi(this);
    //QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());
       //file menu
       QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
       QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
       QToolBar *mainToolBar = addToolBar(tr("Main"));

       //[0] open:fileMenu
       const QIcon openIcon = QIcon(":/files/open.png");
       QAction *openAct = new QAction(openIcon, tr("&Open"), this);
       openAct->setShortcuts(QKeySequence::Open);
       openAct->setStatusTip(tr("Open a file"));
       //connect(saveAct, &QAction::triggered, this, &MainWindow::newFile);
       fileMenu->addAction(openAct);
       mainToolBar->addAction(openAct);

       //[1]save:fileMenu
       const QIcon saveIcon = QIcon(":/files/save.png");
       QAction *saveAct = new QAction(saveIcon, tr("&Save"), this);
       saveAct->setShortcuts(QKeySequence::Save);
       saveAct->setStatusTip(tr("Save a file"));
       //connect(saveAct, &QAction::triggered, this, &MainWindow::newFile);
       fileMenu->addAction(saveAct);
       mainToolBar->addAction(saveAct);

       //[2] zoom-in:editMenu
       const QIcon zoominIcon = QIcon(":/files/zoom-in.png");
       QAction *zoominAct = new QAction(zoominIcon, tr("&Zoom-in"), this);
       //zoominAct->setShortcuts(QKeySequence::Zoomin);
       zoominAct->setStatusTip(tr("Zoom in the graph"));
       //connect(saveAct, &QAction::triggered, this, &MainWindow::newFile);
       editMenu->addAction(zoominAct);
       mainToolBar->addAction(zoominAct);

       //[3] zoom-out:editMenu
       const QIcon zoomoutIcon = QIcon(":/files/zoom-out.png");
       QAction *zoomoutAct = new QAction(zoomoutIcon, tr("&Zoom-out"), this);
       //zoominAct->setShortcuts(QKeySequence::Zoomin);
       zoomoutAct->setStatusTip(tr("Zoom out the graph"));
       //connect(saveAct, &QAction::triggered, this, &MainWindow::newFile);
       editMenu->addAction(zoomoutAct);
       mainToolBar->addAction(zoomoutAct);

       //[4] move:editMenu
       const QIcon moveIcon = QIcon(":/files/move.png");
       QAction *moveAct = new QAction(moveIcon, tr("&Move"), this);
       //zoominAct->setShortcuts(QKeySequence::Zoomin);
       moveAct->setStatusTip(tr("Move the graph"));
       //connect(saveAct, &QAction::triggered, this, &MainWindow::newFile);
       editMenu->addAction(moveAct);
       mainToolBar->addAction(moveAct);


       //widget window

       vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;//Allocate and hold a VTK object
       ui->qvtkWidget->SetRenderWindow(renderWindow);

       vtkNew<vtkEventQtSlotConnect> slotConnector;
       this->Connections = slotConnector;

         // Sphere
         vtkNew<vtkSphereSource> sphereSource;
         sphereSource->Update();
         vtkNew<vtkPolyDataMapper> sphereMapper;
         sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

         vtkNew<vtkActor> sphereActor;
         sphereActor->SetMapper(sphereMapper);

         // VTK Renderer
         vtkNew<vtkRenderer> renderer;
         renderer->AddActor(sphereActor);

         ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

         this->Connections->Connect(ui->qvtkWidget->GetRenderWindow()->GetInteractor(),
         vtkCommand::LeftButtonPressEvent,
         this,
         SLOT(slot_clicked(vtkObject*, unsigned long, void*, void*)));


}



RBCGUI::~RBCGUI()
{
    delete ui;
}


void RBCGUI::slot_clicked(vtkObject*, unsigned long, void*, void*)
{
  std::cout << "Clicked." << std::endl;
}


void RBCGUI::on_para_setting_clicked()
{ 
    bool REMOVE=QFile::remove("D:/Qt_projects/RBCGUI/files/transportProperties");
    if(REMOVE==true)
        cout<<"remove successful"<<endl;
    else
    {
        cout<<"error"<<endl;
    }
    //initialize the parameter file
    QFile FileIn("D:/Qt_projects/RBCGUI/transportProperties");
    QFile FileOut("D:/Qt_projects/RBCGUI/files/transportProperties");
    QString StrAll="";
    QStringList StrList=QStringList();

    //read all contexts
    if(!FileIn.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    else
    {

        QTextStream StreamIn(&FileIn);
        StrAll=StreamIn.readAll();
        qDebug()<<StrAll;

    }
    FileIn.close();

    if(!FileOut.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"Can't write the file!"<<endl;
    }
    else
    {
        QTextStream StreamOut(&FileOut);
        StrList=StrAll.split("\n");
        for(int i=0;i<StrList.count();i++)
        {
            QString LINE=StrList.at(i);
            StreamOut<<LINE<<endl;
        }
        FileOut.close();
        StrAll="";
        StrList=QStringList();
        cout<<"load successful "<<endl;

        paraWin=new Parameter_setting;
        paraWin->show();
    }
}




