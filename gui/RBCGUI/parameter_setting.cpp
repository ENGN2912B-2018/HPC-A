#include <QtWidgets>
#include "parameter_setting.h"
#include<iostream>
using namespace std;

QString global_nu="0.000001";
QString global_beta="0.000214";
QString global_TFloor="340.000000";
QString global_Pr="7.560000";

Parameter_setting::Parameter_setting(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *verticalLayout;
    verticalLayout = new QVBoxLayout(this);
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

    warning_label = new QLabel;
    warning_label->setFrameStyle(frameStyle);
    QPushButton *warning_Button = new QPushButton(tr("warning: "));

    error_label = new QLabel;
    error_label->setFrameStyle(frameStyle);
    QPushButton *error_Button = new QPushButton(tr("error: "));

    QPushButton *applyButton=new QPushButton(tr("Apply Changes"));

    connect(Nu_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_Nu);
    connect(Beta_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_Beta);
    connect(TFloor_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_TFloor);
    connect(Pr_Button, &QAbstractButton::clicked, this, &Parameter_setting::set_Pr);
    connect(applyButton,&QAbstractButton::clicked, this,&Parameter_setting::applyChanges);
    connect(warning_Button, &QAbstractButton::clicked, this, &Parameter_setting::warningMessage);
    connect(error_Button, &QAbstractButton::clicked, this, &Parameter_setting::errorMessage);

    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    layout->setColumnStretch(1, 1);//2 cols
    layout->setColumnMinimumWidth(1, 250);//2 cols, each col 250 pixels wide
    layout->addWidget(Nu_Button, 0, 0);
    layout->addWidget(Nu_label, 0, 1);
    layout->addWidget(Beta_Button, 1, 0);
    layout->addWidget(Beta_label, 1, 1);
    layout->addWidget(TFloor_Button, 2, 0);
    layout->addWidget(TFloor_label, 2, 1);
    layout->addWidget(Pr_Button, 3, 0);
    layout->addWidget(Pr_label, 3, 1);
    layout->addWidget(applyButton,4,0);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);
    toolbox->addItem(page, tr("modifiable parameters"));

    //trasmit data
    //QString global_nu, global_beta,global_TFloor, global_Pr;

}


void Parameter_setting::set_Nu()
{
    bool ok=0;
    QString i = QInputDialog::getText(this, tr("modifiy Nu: "),
                                       tr("modifiy Nu: "), QLineEdit::Normal, "0.000001", &ok);
    if (ok)
    {
        this->setNuValue=i;
        invokeNuSet();
        //Nu_label->setText(tr("%1").arg(i));
        Nu_label->setText(setNuValue);
    }


}

void Parameter_setting::set_Beta()
{
    bool ok=0;
    QString i = QInputDialog::getText(this, tr("modifiy Beta: "),
                                       tr("modifiy Beta: "), QLineEdit::Normal,"0.000214",  &ok);
    if (ok)
    {
        this->setBetaValue=i;
        invokeBetaSet();
        Beta_label->setText(setBetaValue);
    }

}
void Parameter_setting::set_TFloor()
{
    bool ok=0;
    QString i = QInputDialog::getText(this, tr("modifiy TFloor: "),
                                       tr("modifiy TFloor: "), QLineEdit::Normal,"340.000000", &ok);
    if (ok)
    {
        this->setTFloorValue=i;
        invokeTFloorSet();
        TFloor_label->setText(setTFloorValue);
    }

}
void Parameter_setting::set_Pr()
{
    bool ok=0;
    QString i = QInputDialog::getText(this, tr("modifiy Pr: "),
                                       tr("modifiy Pr: "), QLineEdit::Normal,"7.56", &ok);
    if (ok)
    {
        this->setPrValue=i;
        invokePrSet();
        Pr_label->setText(setPrValue);
    }

}

void Parameter_setting::warningMessage()
{

}

void Parameter_setting::errorMessage()
{

}

void Parameter_setting::invokeNuSet()
{
    QFile fileIn("D:/Qt_projects/RBCGUI/files/transportProperties");
    QFile fileOut("D:/Qt_projects/RBCGUI/tmp/transportProperties");
    QString strAll="";
    QStringList strList=QStringList();
    //read all contexts
    if(!fileIn.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    else
    {

        QTextStream nu_streamIn(&fileIn);
        strAll=nu_streamIn.readAll();
        //qDebug()<<strAll;
        qDebug()<<"read successful "<<endl;
    }
    fileIn.close();

    //modify nu
    qDebug()<<"setting nu: "<<endl;

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
            QString cmp=Line.mid(0,3);
            if(cmp=="nu "&&cmp!="num")
            {
                nu_streamOut<<"nu [0 2 -1 0 0 0 0] " << setNuValue << ";" << endl;
            }
            else
            {
                nu_streamOut<<Line<<endl;
            }
        }
        fileOut.close();
        strAll="";
        strList=QStringList();
        qDebug()<<"set successful "<<endl;

        bool rm = QFile::remove("D:/Qt_projects/RBCGUI/files/transportProperties");
        QFile FileIn("D:/Qt_projects/RBCGUI/tmp/transportProperties");
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
            //qDebug()<<StrAll;

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
                //qDebug()<<LINE;

            }
            FileOut.close();
            StrAll="";
            StrList=QStringList();

            qDebug()<<"replace read(build file)"<<endl;
        }


    }

}

void Parameter_setting::invokeBetaSet()
{
    QFile fileIn("D:/Qt_projects/RBCGUI/files/transportProperties");
    QFile fileOut("D:/Qt_projects/RBCGUI/tmp/transportProperties");
    QString strAll="";
    QStringList strList=QStringList();
    //read all contexts
    if(!fileIn.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    else
    {
        QTextStream beta_streamIn(&fileIn);
        strAll=beta_streamIn.readAll();
        //qDebug()<<strAll;
    }
    fileIn.close();
    qDebug()<<"read successful"<<endl;

    //modify beta
    qDebug()<<"setting beta: "<<endl;
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
            if(Line.contains("beta "))
            {
                beta_streamOut<<"beta [0 0 0 -1 0 0 0] " << setBetaValue << ";" << endl;

            }
            else
            {
                beta_streamOut<<Line<<endl;
            }
        }
        fileOut.close();
        strAll="";
        strList=QStringList();
        qDebug()<<"set successful "<<endl;

        bool rm = QFile::remove("D:/Qt_projects/RBCGUI/files/transportProperties");
        QFile FileIn("D:/Qt_projects/RBCGUI/tmp/transportProperties");
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
            //qDebug()<<StrAll;

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
                //qDebug()<<LINE;

            }
            FileOut.close();
            StrAll="";
            StrList=QStringList();

            qDebug()<<"replace read(build file)"<<endl;
        }
    }
}

void Parameter_setting::invokeTFloorSet()
{
    QFile TFloorfileIn("D:/Qt_projects/RBCGUI/files/T");
    QFile TFloorfileOut("D:/Qt_projects/RBCGUI/tmp/T");
    QString strAll="";
    QStringList strList=QStringList();
    //read all contexts
    if(!TFloorfileIn.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    else
    {
        QTextStream TFloor_streamIn(&TFloorfileIn);
        strAll=TFloor_streamIn.readAll();
        //qDebug()<<strAll;
    }
    TFloorfileIn.close();

    //modify nu
    qDebug()<<"setting TFloor: "<<endl;
    if(!TFloorfileOut.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"Can't write the file!"<<endl;
    }
    else
    {
        QTextStream TFloor_streamOut(&TFloorfileOut);
        strList=strAll.split("\n");
        for(int i=0;i<strList.count();i++)
        {
            QString Line=strList.at(i);
            if(Line.contains("floor"))
            {
                TFloor_streamOut <<Line << endl; //floor
                Line=strList.at(i++);
                TFloor_streamOut<< Line << endl; // {
                Line=strList.at(i++);
                TFloor_streamOut<< Line<< endl; // type
                Line=strList.at(i++);
                TFloor_streamOut<< "        value           uniform "<<setTFloorValue<<endl;

            }
            else
            {
                TFloor_streamOut<<Line<<endl;
            }
        }
        TFloorfileOut.close();
        strAll="";
        strList=QStringList();
        qDebug()<<"set successful "<<endl;


        bool rm = QFile::remove("D:/Qt_projects/RBCGUI/files/T");
        QFile FileIn("D:/Qt_projects/RBCGUI/tmp/T");
        QFile FileOut("D:/Qt_projects/RBCGUI/files/T");
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
            //qDebug()<<StrAll;

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
                //qDebug()<<LINE;

            }
            FileOut.close();
            StrAll="";
            StrList=QStringList();

            qDebug()<<"replace read(build file)"<<endl;
        }
    }


}

void Parameter_setting::invokePrSet()
{
    QFile fileIn("D:/Qt_projects/RBCGUI/files/transportProperties");
    QFile fileOut("D:/Qt_projects/RBCGUI/tmp/transportProperties");
    QString strAll="";
    QStringList strList=QStringList();
    //read all contexts
    if(!fileIn.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    else
    {
        QTextStream Pr_streamIn(&fileIn);
        strAll=Pr_streamIn.readAll();
        //qDebug()<<strAll;
    }
    fileIn.close();

    //modify Pr
    qDebug()<<"setting Pr: "<<endl;
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
            QString cmp=Line.mid(0,3);
            if(cmp=="Pr "&&cmp!="Prt")

            {
                Pr_streamOut<<"Pr [0 0 0 0 0 0 0] " << setPrValue << ";" << endl;

            }
            else
            {
                Pr_streamOut<<Line<<endl;
            }
        }
        fileOut.close();
        strAll="";
        strList=QStringList();
        qDebug()<<"set successful "<<endl;
        bool rm = QFile::remove("D:/Qt_projects/RBCGUI/files/transportProperties");
        QFile FileIn("D:/Qt_projects/RBCGUI/tmp/transportProperties");
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
            //qDebug()<<StrAll;

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
                //qDebug()<<LINE;

            }
            FileOut.close();
            StrAll="";
            StrList=QStringList();

            qDebug()<<"replace read(build file)"<<endl;
        }

    }

}


void Parameter_setting::applyChanges()
{
    /*QString buf1=this->setNuValue;
    QString buf2=this->setBetaValue;
    QString buf3=this->setTFloorValue;
    QString buf4=this->setPrValue;
    emit sendData(buf1,buf2,buf3,buf4);
    this->close();*/

    global_nu=this->setNuValue;
    global_beta=this->setBetaValue;
    global_TFloor=this->setTFloorValue;
    global_Pr=this->setPrValue;
    this->close();
}
