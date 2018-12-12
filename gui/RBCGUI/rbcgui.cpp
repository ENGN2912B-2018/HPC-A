//#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
//#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include "rbcgui.h"
#include "ui_rbcgui.h"
#include "parameter_setting.h"
#include "VTKReader.h"

#include<QtWidgets>
#include<QApplication>
#include<QVTKOpenGLWidget.h>
#include <QDialog>
#include<QImage>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include "vtkGenericOpenGLRenderWindow.h"
#include <vtkRenderWindowInteractor.h>

#include <vtkNew.h>
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
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

    //display the changed parameters
    /*Parameter_setting *para=new Parameter_setting;
    connect(para,SIGNAL(sendData(QString D1,QString D2,QString D3,QString D4)),this, SLOT(receiveData(QString data1, QString data2,QString data3,QString data4)));*/


    /*vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;//Allocate and hold a VTK object
    ui->qvtkWidget->SetRenderWindow(renderWindow);
    //vtkNew<vtkEventQtSlotConnect> slotConnector;
    //this->Connections = slotConnector;
    // Sphere
    vtkNew<vtkSphereSource> sphereSource;
   // sphereSource->Update();
    vtkNew<vtkPolyDataMapper> sphereMapper;
    sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
    vtkNew<vtkActor> sphereActor;
    sphereActor->SetMapper(sphereMapper);
    // VTK Renderer
    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(sphereActor);
    ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);*/
    /*this->Connections->Connect(ui->qvtkWidget->GetRenderWindow()->GetInteractor(),
                               vtkCommand::LeftButtonPressEvent,
                               this,
                               SLOT(slot_clicked(vtkObject*, unsigned long, void*, void*)));*/


    /*initialize all the files*/


    bool REMOVE1=QFile::remove("D:/Qt_projects/RBCGUI/files/transportProperties");
    //bool REMOVE2=QFile::remove("D:/Qt_projects/tmp_-RBCGUI-Desktop_Qt_5_10_1_MSVC2017_64bit-Release/transportProperties");
    //bool CP=QFile::copy("D:/Qt_projects/RBCGUI/transportProperties","D:/Qt_projects/RBCGUI/files/transportProperties");
    if(REMOVE1==true)
        qDebug()<<"remove files successful"<<endl;
    else
    {
        qDebug()<<"error"<<endl;
    }


    //initialize the parameter file
    QFile FileIn_tran("D:/Qt_projects/RBCGUI/transportProperties");
    QFile FileOut_tran("D:/Qt_projects/RBCGUI/files/transportProperties");
    QString StrAll_tran="";
    QStringList StrList_tran=QStringList();
    //read all contexts
    if(!FileIn_tran.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    else
    {
        QTextStream StreamIn_tran(&FileIn_tran);
        StrAll_tran=StreamIn_tran.readAll();
        //qDebug()<<StrAll_tran;
    }
    FileIn_tran.close();

    if(!FileOut_tran.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"Can't write the file!"<<endl;
    }
    else
    {
        QTextStream StreamOut_tran(&FileOut_tran);
        StrList_tran=StrAll_tran.split("\n");
        for(int i=0;i<StrList_tran.count();i++)
        {
            QString LINE=StrList_tran.at(i);
            StreamOut_tran<<LINE<<endl;
        }
        FileOut_tran.close();
        StrAll_tran="";
        StrList_tran=QStringList();
        qDebug()<<"initialize files successful "<<endl;
    }


    //initialize the tmp transportProperties
    QFile tmp_FileIn_tran("D:/Qt_projects/RBCGUI/transportProperties");
    QFile tmp_FileOut_tran("D:/Qt_projects/RBCGUI/tmp/transportProperties");
    QString tmp_StrAll_tran="";
    QStringList tmp_StrList_tran=QStringList();

    //read all contexts
    if(!tmp_FileIn_tran.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    else
    {

        QTextStream tmp_StreamIn_tran(&tmp_FileIn_tran);
        tmp_StrAll_tran=tmp_StreamIn_tran.readAll();
        //qDebug()<<tmp_StrAll_tran;

    }
    tmp_FileIn_tran.close();

    if(!tmp_FileOut_tran.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"Can't write the file!"<<endl;
    }
    else
    {
        QTextStream tmp_StreamOut_tran(&tmp_FileOut_tran);
        tmp_StrList_tran=tmp_StrAll_tran.split("\n");
        for(int i=0;i<tmp_StrList_tran.count();i++)
        {
            QString tmp_LINE=tmp_StrList_tran.at(i);
            tmp_StreamOut_tran<<tmp_LINE<<endl;
        }
        tmp_FileOut_tran.close();
        tmp_StrAll_tran="";
        tmp_StrList_tran=QStringList();
        qDebug()<<"initialize tmp_ successful "<<endl;
    }

    //
    //initialize the T
    QFile FileIn_T("D:/Qt_projects/RBCGUI/T");
    QFile FileOut_T("D:/Qt_projects/RBCGUI/files/T");
    QString StrAll_T="";
    QStringList StrList_T=QStringList();

    //read all contexts
    if(!FileIn_T.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    else
    {

        QTextStream StreamIn_T(&FileIn_T);
        StrAll_T=StreamIn_T.readAll();
        //qDebug()<<StrAll_T;

    }
    FileIn_T.close();

    if(!FileOut_T.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"Can't write the file!"<<endl;
    }
    else
    {
        QTextStream StreamOut_T(&FileOut_T);
        StrList_T=StrAll_T.split("\n");
        for(int i=0;i<StrList_T.count();i++)
        {
            QString tmp_LINE=StrList_T.at(i);
            StreamOut_T<<tmp_LINE<<endl;
        }
        FileOut_T.close();
        StrAll_T="";
        StrList_T=QStringList();
        qDebug()<<"initialize tmp_ successful "<<endl;
    }

    //initialize the tmp T
    QFile tmp_FileIn_T("D:/Qt_projects/RBCGUI/T");
    QFile tmp_FileOut_T("D:/Qt_projects/RBCGUI/tmp/T");
    QString tmp_StrAll_T="";
    QStringList tmp_StrList_T=QStringList();

    //read all contexts
    if(!tmp_FileIn_T.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    else
    {

        QTextStream tmp_StreamIn_T(&tmp_FileIn_T);
        tmp_StrAll_T=tmp_StreamIn_T.readAll();
        //qDebug()<<tmp_StrAll_T;

    }
    tmp_FileIn_T.close();

    if(!tmp_FileOut_T.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"Can't write the file!"<<endl;
    }
    else
    {
        QTextStream tmp_StreamOut_T(&tmp_FileOut_T);
        tmp_StrList_T=tmp_StrAll_T.split("\n");
        for(int i=0;i<tmp_StrList_T.count();i++)
        {
            QString tmp_LINE=tmp_StrList_T.at(i);
            tmp_StreamOut_T<<tmp_LINE<<endl;
        }
        tmp_FileOut_T.close();
        tmp_StrAll_T="";
        tmp_StrList_T=QStringList();
        qDebug()<<"initialize tmp_ successful "<<endl;
    }
}



RBCGUI::~RBCGUI()
{
    delete ui;

}


/*void RBCGUI::slot_clicked(vtkObject*, unsigned long, void*, void*)
{
    std::cout << "Clicked." << std::endl;
}*/


void RBCGUI::on_para_setting_clicked()
{ 


    paraWin=new Parameter_setting;
    paraWin->show();


}

/*void RBCGUI::receiveData(QString data1,QString data2,QString data3,QString data4)
{
    ui->nu_display->setText(data1);
    ui->beta_display->setText(data2);
    ui->TFloor_display->setText(data3);
    ui->Pr_display->setText(data4);
}*/



void RBCGUI::on_apply_changes_clicked()
{
    extern QString global_nu, global_beta,global_TFloor, global_Pr;
    ui->nu_display->setText(global_nu);
    ui->beta_display->setText(global_beta);
    ui->TFloor_display->setText(global_TFloor);
    ui->Pr_display->setText(global_Pr);
}

void RBCGUI::on_visualization_clicked()
{
    int colorScheme = 1;
    int resolutionX = 100;
    int resolutionY = 50;
    std::string filePath = "D:/Qt_projects/RBCGUI/RBConvection/";
    std::string parameterCode = "T";
    int timeStep = 20;
    int timeMax = 2000;
    RBVisualizer visual(colorScheme, resolutionX, resolutionY, filePath, parameterCode,
                         timeStep, timeMax);
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;//Allocate and hold a VTK object
    ui->qvtkWidget->SetRenderWindow(renderWindow);
    visual.readParameterMinMax();
    visual.setParameterMin(280);
    visual.mainVisualizer();
    vtkSmartPointer<vtkRenderer> renderer=visual.Get_Render();
    ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
}
