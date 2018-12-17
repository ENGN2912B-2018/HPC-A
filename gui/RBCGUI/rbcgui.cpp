

#include "rbcgui.h"
#include "ui_rbcgui.h"
#include "parameter_setting.h"
#include "VTKReader.h"
#include <vtkWindowToImageFilter.h>
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
#include "vtkOpenGLRenderer.h"

#include <vtkPolyDataMapper.h>
#include <vtkSphereSource.h>

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
#define DEBUG
extern QString global_Pr, global_Ra;
extern int scheme,step;
extern std::string code;
extern bool prFlag, raFlag,colorFlag,codeFlag,stepFlag;

RBCGUI::RBCGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RBCGUI)
{
    ui->setupUi(this);

    ui->Pr_display->setText(global_Pr);

    if(global_Ra.toDouble()==10000000.000000)
    {
        ui->Ra_display->setText("1e7");//the number is very large, so we display it in a scientific way
    }
    if(global_Ra.toDouble()==1000000000.000000)
    {
        ui->Ra_display->setText("1e9");
    }
    if(global_Ra.toDouble()==100000000000.000000)
    {
        ui->Ra_display->setText("1e11");
    }

    QString colorScheme=QString::number(scheme);//convert from int to QString
    ui->ColorScheme_display->setText(colorScheme);
    QString CODE=QString::fromStdString(code);//convert from std::string to QString
    ui->ParemeterCode_display->setText(CODE);
    QString timeStep=QString::number(step);//convert from std::string to QString
    ui->TimeStep_display->setText(timeStep);

}



RBCGUI::~RBCGUI()
{
    delete ui;

}

void RBCGUI::on_para_setting_clicked()
{


    paraWin=new Parameter_setting;
    paraWin->show();


}

void RBCGUI::on_apply_changes_clicked()
{

    ui->Pr_display->setText(global_Pr);

    if(global_Ra.toDouble()==10000000.000000)
    {
        ui->Ra_display->setText("1e7");//the number is very large, so we display it in a scientific way
    }
    if(global_Ra.toDouble()==1000000000.000000)
    {
        ui->Ra_display->setText("1e9");
    }
    if(global_Ra.toDouble()==100000000000.000000)
    {
        ui->Ra_display->setText("1e11");
    }

    QString colorScheme=QString::number(scheme);//convert from int to QString
    ui->ColorScheme_display->setText(colorScheme);
    QString CODE=QString::fromStdString(code);//convert from std::string to QString
    ui->ParemeterCode_display->setText(CODE);
    QString timeStep=QString::number(step);//convert from std::string to QString
    ui->TimeStep_display->setText(timeStep);
}
void visualizerScript(RBVisualizer& testReader, bool isVideoSave);
void RBCGUI::on_visualization_clicked()
{
    extern QString global_Pr, global_Ra;
    extern int scheme,step;
    extern std::string code;
    extern bool prFlag, raFlag,colorFlag,codeFlag,stepFlag;

    if(prFlag==false||raFlag==false||colorFlag==false||codeFlag==false||stepFlag==false)
    {
        QMessageBox msgBox(QMessageBox::Warning, tr("QMessageBox::warning()"),
                               tr("Parameter setting reminder: You haven't made any change to parameters. "
                                  "Do you want to start your program with default parameters?"), 0, this);
        msgBox.setWindowTitle("Reminder");
        msgBox.addButton(tr("&No, I want to go back."), QMessageBox::AcceptRole);
        msgBox.addButton(tr("&Yes, I want to continue"), QMessageBox::RejectRole);
        if(msgBox.exec() ==  QMessageBox::AcceptRole)
        {
            return;
        }

    }
    extern int scheme;
    extern std::string code;
    int colorScheme = scheme;//0,1,2
    int resolutionX = 100;
    int resolutionY = 50;
    std::string filePath = "D:/Qt_projects/RBCGUI/RBConvection/";
    std::string parameterCode =code;//mag(U)
    int timeStep = step;
    int timeMax = 2000;
    cout<<"done"<<endl;
    RBVisualizer visual(colorScheme, resolutionX, resolutionY, filePath, parameterCode,
                         timeStep, timeMax);
    visual.readParameterMinMax();
extern int loadFlag;

    vtkSmartPointer<vtkRenderWindow> renWin =
            vtkSmartPointer<vtkRenderWindow>::New();
   RendererVector rendererOutput=visual.mainVisualizer();

   int index = 1;
    for (auto it= rendererOutput.cbegin(); it != rendererOutput.cend(); it++)
    {
       renWin->AddRenderer(*it);
        renWin->SetSize(resolutionX*8, resolutionY*8);
        renWin->Render();
        cout<<"2: "<<*it<<endl;
        cout<<"Rendering the " << index << "th window..." << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    bool isVideoSave = true;

      try {
          RBVisualizer testReader(colorScheme, resolutionX, resolutionY, filePath, parameterCode,
              timeStep, timeMax);
          testReader.readParameterMinMax();
          visualizerScript(testReader, isVideoSave);
      }
      catch(const fileNotExistError &eFNE){
        cout << "Hey!" << endl;
        //QString msg="The file we tried to access does not exist.This may happen when you entered a wrong timeStep. "
                    //"The timeStep could be the multiple of the actual time step.";
        QMessageBox msgBox1(QMessageBox::Warning, tr("QMessageBox::warning()"),
                           tr("The file we tried to access does not exist.This may happen when you entered a wrong timeStep. "
                              "The timeStep could be the multiple of the actual time step."), 0, this);
        msgBox1.setWindowTitle("warning");
        msgBox1.addButton(tr("&Ok"), QMessageBox::AcceptRole);
        msgBox1.addButton(tr("&cancel"), QMessageBox::RejectRole);
            //return;
          std::cerr << "fileNotExistError caught in " << filePath << " : "
              << eFNE.what() << std::endl;
          std::cerr << "The file we tried to access does not exist. "
              "This may happen when you entered a wrong timeStep. " << std::endl;
          std::cerr << "The timeStep could be the multiple of the actual time step." << std::endl;
          return ;
      }
      catch (const pathNotExistError &ePNE) {
        QString msg="The path you entered does not exist. "
                    "Make sure you have downloaded and unzipped the results." ;
        QMessageBox msgBox(QMessageBox::Warning, tr("QMessageBox::warning()"),
                           msg, 0, this);
        msgBox.setWindowTitle("warning");
        msgBox.addButton(tr("&Ok"), QMessageBox::AcceptRole);
        //return;


        std::cerr << "pathNotExistError caught in " << filePath << " : "
              << ePNE.what() << std::endl;
          std::cerr << "The path you entered does not exist. "
              "Make sure you have downloaded and unzipped the results." << std::endl;
          return ;
      }
      catch (...) {
        QString msg="This may happen when your computation resources are "
                    "exhausted, or system platform is incompatible.\n"
                    "Try it again later, or contact us at our Github Issues page:\n"
                "https://github.com/ENGN2912B-2018/HPC-A/issues";
        QMessageBox msgBox(QMessageBox::Warning, tr("QMessageBox::warning()"),
                           msg, 0, this);
        msgBox.setWindowTitle("warning");
        msgBox.addButton(tr("&Ok"), QMessageBox::AcceptRole);
        return;


          /*std::cerr << "Execption thrown while visualizing the results." << std::endl;
          std::cerr << "This may happen when your computation resources are "
              "exhausted, or system platform is incompatible." << std::endl;
          std::cerr << "Try it again later, or contact us at our Github Issues page: "
              << std::endl;
          std::cerr << "https://github.com/ENGN2912B-2018/HPC-A/issues" << std::endl;
          return ;*/
      }

      return ;
    }

    void visualizerScript(RBVisualizer& testReader, bool isViedoSave) {
        if (isViedoSave ==  true) {
            RendererVector rendererOutput = testReader.mainVisualizer();
            vtkSmartPointer<vtkRenderWindow> renWin =
                vtkSmartPointer<vtkRenderWindow>::New();
            vtkSmartPointer<vtkWindowToImageFilter> w2i =
                vtkSmartPointer<vtkWindowToImageFilter>::New();
            vtkSmartPointer<vtkAVIWriter> writer =
                vtkSmartPointer<vtkAVIWriter>::New();
            renWin->AddRenderer(*rendererOutput.cbegin());
            renWin->SetSize(testReader.getResolutionX() * 8,
                testReader.getResolutionY() * 8);
            renWin->Render();
            w2i->SetInput(renWin);
            w2i->Update();
            std::string saveName = testReader.getSavePath() + testReader.getSaveName();
            writer->SetFileName(saveName.c_str());
            writer->SetInputConnection(w2i->GetOutputPort());
            writer->SetRate(50);
            writer->SetQuality(2);
            writer->SetCompressorFourCC("MSVC");
            writer->Start();
            int frameCounter = 2;
            for (auto it = rendererOutput.cbegin() + 1; it != rendererOutput.cend(); it++) {
                renWin->AddRenderer(*it);
                renWin->SetSize(testReader.getResolutionX() * 8,
                    testReader.getResolutionY() * 8);
    #ifdef DEBUG
                std::cout << "Attempting to write the video frame: "
                    << frameCounter << std::endl;
    #endif
                renWin->Render();
                w2i->Modified();
                writer->Write();


                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                frameCounter++;
            }
        }
        else {
            RendererVector rendererOutput = testReader.mainVisualizer();
            vtkSmartPointer<vtkRenderWindow> renWin =
                vtkSmartPointer<vtkRenderWindow>::New();
            int frameCounter = 1;
            for (auto it = rendererOutput.cbegin() + 1; it != rendererOutput.cend(); it++) {
                renWin->AddRenderer(*it);
                renWin->SetSize(testReader.getResolutionX() * 8,
                    testReader.getResolutionY() * 8);
    #ifdef DEBUG
                std::cout << "Rendering the frame: "
                    << frameCounter << std::endl;
    #endif
                renWin->Render();

                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                frameCounter++;
            }
        }

}

void RBCGUI::setStatusText(QString status)
{
    ui->statusLabel->setText(status);
}

