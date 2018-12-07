#include <QtWidgets>
#include "parameter_setting.h"

#include <iostream>
#include <string>
#include <ios>
#include <stdlib.h>
#include <vector>
#include <regex>
#include <cmath>
#include <cctype>
#include <fstream>

using namespace std;

Parameter_setting::Parameter_setting(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *verticalLayout;
    if (QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized())
    {
        QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
        QGroupBox *groupBox = new QGroupBox(QGuiApplication::applicationDisplayName(), this);
        horizontalLayout->addWidget(groupBox);
        verticalLayout = new QVBoxLayout(groupBox);
    }
    else
    {
        verticalLayout = new QVBoxLayout(this);
    }
    QToolBox *toolbox = new QToolBox;
    verticalLayout->addWidget(toolbox);

    errorMessageDialog = new QErrorMessage(this);
    int frameStyle = QFrame::Sunken | QFrame::Panel;

    //initial condition
    Nu_label = new QLabel;
    Nu_label->setFrameStyle(frameStyle);
    QPushButton *Nu_Button = new QPushButton(tr("modifiy Nu: "));

    Beta_label = new QLabel;
    Beta_label->setFrameStyle(frameStyle);
    QPushButton *Beta_Button = new QPushButton(tr("modifiy Beta: "));

    TFloor_label = new QLabel;
    TFloor_label->setFrameStyle(frameStyle);
    QPushButton *TFloor_Button = new QPushButton(tr("modifiy TFloor: "));

    Pr_label = new QLabel;
    Pr_label->setFrameStyle(frameStyle);
    QPushButton *Pr_Button = new QPushButton(tr("modifiy Pr: "));

    /*alphat_label = new QLabel;
    alphat_label->setFrameStyle(frameStyle);
    QPushButton *alphat_Button = new QPushButton(tr("modifiy alphat: "));

    //physical constants
    g_label = new QLabel;
    g_label->setFrameStyle(frameStyle);
    QPushButton *g_Button = new QPushButton(tr("modifiy g: "));

    transportProperties_label = new QLabel;
    transportProperties_label->setFrameStyle(frameStyle);
    QPushButton *transportProperties_Button = new QPushButton(tr("modifiy transportProperties: "));

    turbulenceProperties_label = new QLabel;
    turbulenceProperties_label->setFrameStyle(frameStyle);
    QPushButton *turbulenceProperties_Button = new QPushButton(tr("modifiy turbulenceProperties: "));

    //system directory
    blockMeshDict_label = new QLabel;
    blockMeshDict_label->setFrameStyle(frameStyle);
    QPushButton *blockMeshDict_Button = new QPushButton(tr("modifiy blockMeshDict: "));

    controlDict_label = new QLabel;
    controlDict_label->setFrameStyle(frameStyle);
    QPushButton *controlDict_Button = new QPushButton(tr("modifiy controlDict: "));

    fvSolution_label = new QLabel;
    fvSolution_label->setFrameStyle(frameStyle);
    QPushButton *fvSolution_Button = new QPushButton(tr("modifiy fvSolution: "));

    fvSchemes_label = new QLabel;
    fvSchemes_label->setFrameStyle(frameStyle);
    QPushButton *fvSchemes_Button = new QPushButton(tr("modifiy fvSchemes: "));*/

    warning_label = new QLabel;
    warning_label->setFrameStyle(frameStyle);
    QPushButton *warning_Button = new QPushButton(tr("warning: "));

    error_label = new QLabel;
    error_label->setFrameStyle(frameStyle);
    QPushButton *error_Button = new QPushButton(tr("error: "));

    connect(Nu_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_Nu);
    connect(Beta_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_Beta);
    connect(TFloor_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_TFloor);
    connect(Pr_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_Pr);
    /*connect(alphat_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_alphat);
    connect(g_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_g);
    connect(transportProperties_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_transportProperties);
    connect(turbulenceProperties_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_turbulenceProperties);
    connect(blockMeshDict_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_blockMeshDict);
    connect(controlDict_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_controlDict);
    connect(fvSolution_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_fvSolution);
    connect(fvSchemes_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_fvSchemes);*/
    connect(warning_Button, &QAbstractButton::clicked, this, &Parameter_setting::warningMessage);
    connect(error_Button, &QAbstractButton::clicked, this, &Parameter_setting::errorMessage);

    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(1, 250);
    layout->addWidget(Nu_Button, 0, 0);
    layout->addWidget(Nu_label, 0, 1);
    layout->addWidget(Beta_Button, 1, 0);
    layout->addWidget(Beta_label, 1, 1);
    layout->addWidget(TFloor_Button, 2, 0);
    layout->addWidget(TFloor_label, 2, 1);
    layout->addWidget(Pr_Button, 3, 0);
    layout->addWidget(Pr_label, 3, 1);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 4, 0);
    toolbox->addItem(page, tr("modifiable parameters"));

}
void Parameter_setting::set_Nu()
{
    bool ok;
    double i = QInputDialog::getDouble(this, tr("modifiy Nu: "),
                                 tr("modifiy Nu: "), 0.000001, 0, 100, 6, &ok);
    if (ok)
    {
        Nu_label->setText(tr("%1").arg(i));
        this->setFlag=1;
        this->setValue=i;
        invokeSet();
    }

}

void Parameter_setting::set_Beta()
{
    bool ok;
    double i = QInputDialog::getDouble(this, tr("modifiy Beta: "),
                                 tr("modifiy Beta: "), 0.000214, 0, 100, 6, &ok);
    if (ok)
        Beta_label->setText(tr("%1").arg(i));
    this->setFlag=2;
    this->setValue=i;
    invokeSet();
}
void Parameter_setting::set_TFloor()
{
    bool ok;
    double i = QInputDialog::getDouble(this, tr("modifiy TFloor: "),
                                 tr("modifiy TFloor: "), 340, 0, 10000, 1, &ok);
    if (ok)
        TFloor_label->setText(tr("%1").arg(i));
    this->setFlag=3;
    this->setValue=i;
    invokeSet();
}
void Parameter_setting::set_Pr()
{
    bool ok;
    double i = QInputDialog::getDouble(this, tr("modifiy Pr: "),
                                 tr("modifiy Pr: "), 7.56, 0, 100, 2, &ok);
    if (ok)
        Pr_label->setText(tr("%1").arg(i));
    this->setFlag=4;
    this->setValue=i;
    invokeSet();
}

void Parameter_setting::warningMessage()
{

}

void Parameter_setting::errorMessage()
{

}

void Parameter_setting::invokeSet()
{
    QFile fileIn(":/files/transportProperties");
    QFile fileOut("transportProperties0");
    QString strAll;
    QStringList strList;
    switch (setFlag)
    {
    case 1://nu
    {
        //read all contexts
        if(!fileIn.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            qDebug()<<"Can't open the file!"<<endl;
        }
        else
        {
            QTextStream nu_streamIn(&fileIn);
            strAll=nu_streamIn.readAll();
            qDebug()<<strAll;
        }
        fileIn.close();

        //modify nu
        cout<<"setting nu: "<<endl;
        if(!fileOut.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            qDebug()<<"Can't write the file!"<<endl;
        }
        else
        {
            QTextStream nu_streamOut(&fileOut);
            strList=strAll.split("\n");
            for(int i=0;i<strList.count();i++)
            {
                QString Line=strList.at(i);
                if(Line.contains("nu"))
                {
                    nu_streamOut<<"nu [0 2 -1 0 0 0 0] " << setValue << ";" << endl;

                }
                else
                {
                    nu_streamOut<<Line<<endl;
                }
            }
            fileOut.close();
            cout<<"set successful "<<endl;
        }
    }
        break;
    case 2://beta
    {
        //read all contexts
        if(!fileIn.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            qDebug()<<"Can't open the file!"<<endl;
        }
        else
        {
            QTextStream beta_streamIn(&fileIn);
            strAll=beta_streamIn.readAll();
            qDebug()<<strAll;
        }
        fileIn.close();

        //modify nu
        cout<<"setting beta: "<<endl;
        if(!fileOut.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            qDebug()<<"Can't write the file!"<<endl;
        }
        else
        {
            QTextStream beta_streamOut(&fileOut);
            strList=strAll.split("\n");
            for(int i=0;i<strList.count();i++)
            {
                QString Line=strList.at(i);
                if(Line.contains("beta"))
                {
                    beta_streamOut<<"beta [0 0 0 -1 0 0 0] " << setValue << ";" << endl;

                }
                else
                {
                    beta_streamOut<<Line<<endl;
                }
            }
            fileOut.close();
            cout<<"set successful "<<endl;
        }
    }
        break;
    case 3://TFloor
    {
        QFile TFloorfileIn(":/files/T");
        QFile TFloorfileOut("T0");
        //read all contexts
        if(!TFloorfileIn.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            qDebug()<<"Can't open the file!"<<endl;
        }
        else
        {
            QTextStream TFloor_streamIn(&fileIn);
            strAll=TFloor_streamIn.readAll();
            qDebug()<<strAll;
        }
        TFloorfileIn.close();

        //modify nu
        cout<<"setting TFloor: "<<endl;
        if(!TFloorfileOut.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            qDebug()<<"Can't write the file!"<<endl;
        }
        else
        {
            QTextStream TFloor_streamOut(&fileOut);
            strList=strAll.split("\n");
            for(int i=0;i<strList.count();i++)
            {
                QString Line=strList.at(i);
                if(Line.contains("beta"))
                {
                    TFloor_streamOut<<"beta [0 0 0 -1 0 0 0] " << setValue << ";" << endl;

                }
                else
                {
                    TFloor_streamOut<<Line<<endl;
                }
            }
            TFloorfileOut.close();
            cout<<"set successful "<<endl;
        }
    }
        break;
    case 4://Pr
    {
        //read all contexts
        if(!fileIn.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            qDebug()<<"Can't open the file!"<<endl;
        }
        else
        {
            QTextStream Pr_streamIn(&fileIn);
            strAll=Pr_streamIn.readAll();
            qDebug()<<strAll;
        }
        fileIn.close();

        //modify nu
        cout<<"setting beta: "<<endl;
        if(!fileOut.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            qDebug()<<"Can't write the file!"<<endl;
        }
        else
        {
            QTextStream Pr_streamOut(&fileOut);
            strList=strAll.split("\n");
            for(int i=0;i<strList.count();i++)
            {
                QString Line=strList.at(i);
                if(Line.contains("Pr "))
                {
                    Pr_streamOut<<"Pr [0 0 0 0 0 0 0] " << setValue << ";" << endl;

                }
                else
                {
                    Pr_streamOut<<Line<<endl;
                }
            }
            fileOut.close();
            cout<<"set successful "<<endl;
        }
    }
        break;

    }






}

