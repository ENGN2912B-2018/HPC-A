//#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
//#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include "rbcgui.h"
#include "ui_rbcgui.h"
#include "RBConvSim.h"
#include "parameter_setting.h"

#include<QtWidgets>
#include<QApplication>
//#include "qvtkopenglwidget.h"
#include<QVTKOpenGLWidget.h>
#include <QDialog>
#include<QImage>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
//#include "vtkGenericOpenGLRenderWindow.h"
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
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());
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

      /* vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;//Allocate and hold a VTK object
       this->qvtkWidget->SetRenderWindow(renderWindow);

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

         this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

         this->Connections->Connect(this->qvtkWidget->GetRenderWindow()->GetInteractor(),
         vtkCommand::LeftButtonPressEvent,
         this,
         SLOT(slot_clicked(vtkObject*, unsigned long, void*, void*)));*/










       //[5]load vtk image
       /*char* filename="/home/Qt_projects/RGCGUI/RBCexample.png";
       vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
       reader->SetFileName(filename);
       //reader->Update();

       vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2>::New();
       viewer->SetInputConnection(reader->GetOutputPort());
       //和ui文件中的 my_widget 对应
       vtkSmartPointer<vtkRenderWindowInteractor>renderWindowInteractor = \
               vtkSmartPointer<vtkRenderWindowInteractor>::New();
       viewer->SetupInteractor(renderWindowInteractor);
       viewer->SetRenderWindow(ui->qvtkWidget->GetRenderWindow());
       viewer->Render();
       viewer->GetRenderer()->ResetCamera();
       viewer->Render();
       renderWindowInteractor->Start();*/


                                  //建立自己新建的类的对象xy1
           /*if(this->paraWin.exec()==QDialog::Accepted)    //利用Accepted信号判断enterBtn是否被按下
           {
               paraWin.show();                        //如果被按下，显示主窗口
                              //程序一直执行，直到主窗口关闭
           }*/

}



RBCGUI::~RBCGUI()
{
    delete ui;
}


void RBCGUI::slot_clicked(vtkObject*, unsigned long, void*, void*)
{
  std::cout << "Clicked." << std::endl;
}

/*void RBCGUI::on_parameter_clicked()
{

    QDialog *dlg = new QDialog(this);
    QWidget *paraSetting=new QWidget(this);
        dlg->show();
    //open a new window which contains all the parameters that can be modified.
}*/



/*void RBCGUI::loadFile(const QString &fileName)
//! [42] //! [43]
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    //setCurQVTKOpenGLWidgetrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}*/


void RBCGUI::on_para_setting_clicked()
{

    paraWin=new Parameter_setting;
    paraWin->show();
}

/*//VTK image data
       // Create a green 50x50 imageData for demonstration purposes
       vtkSmartPointer<vtkImageData> createDemoImageData()
       {
         vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
         image->SetDimensions( 50, 50, 1 );

         int width = image->GetDimensions()[0];
         int height = image->GetDimensions()[1];

         for ( int y = 0; y < height; y++ )
         {
           for ( int x = 0; x < width; x++ )
           {
             unsigned char *pixel =
               static_cast<unsigned char *>( image->GetScalarPointer( x, y, 0 ) );
             pixel[0] = 0;
             pixel[1] = 255;
             pixel[2] = 0;
           }
         }

         return image;
       }*/



//end


