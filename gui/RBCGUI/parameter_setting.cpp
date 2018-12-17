#include <QtWidgets>
#include "parameter_setting.h"
#include<iostream>
#include"VTKReader.h"
#include <string>


using namespace std;

QString global_Pr="0.100000";
QString global_Ra="10000000.000000";
int scheme=1,step=2;
std::string code="T";
RBVisualizer visualizer;
std::string folder="RBC_Pr0.100000_Ra10000000.000000/";
bool prFlag=false, raFlag=false, colorFlag=false,codeFlag=false,stepFlag=false;

Parameter_setting::Parameter_setting(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *verticalLayout;
    verticalLayout = new QVBoxLayout(this);

    QToolBox *toolbox = new QToolBox;
    verticalLayout->addWidget(toolbox);

    int frameStyle = QFrame::Sunken | QFrame::Panel;

    //simulation parameters
    PrLabel = new QLabel;
    PrLabel->setFrameStyle(frameStyle);
    PrLabel->setText(global_Pr);
    QPushButton *PrButton = new QPushButton(tr("Pr: "));

    RaLabel = new QLabel;
    RaLabel->setFrameStyle(frameStyle);
    RaLabel->setText(global_Ra);
    QPushButton *RaButton = new QPushButton(tr("Ra: "));

    QPushButton *applySimulationButton=new QPushButton(tr("Apply Simulation Changes"));

    connect(PrButton, &QAbstractButton::clicked, this, &Parameter_setting::setPr);
    connect(RaButton, &QAbstractButton::clicked, this, &Parameter_setting::setRa);
    connect(applySimulationButton,&QAbstractButton::clicked, this,&Parameter_setting::applySimulationChanges);

    QWidget *page = new QWidget;
    //page->setMaximumSize(500,500);
    //page->setFixedSize(200,200);
    QGridLayout *layout = new QGridLayout(page);
    layout->setColumnStretch(1, 1);//2 cols

    layout->setColumnMinimumWidth(1, 100);//2 cols, each col 250 pixels wide
    layout->addWidget(PrButton, 0, 0);
    layout->addWidget(PrLabel, 0, 1);
    layout->addWidget(RaButton, 1, 0);
    layout->addWidget(RaLabel, 1, 1);
    layout->addWidget(applySimulationButton,2,0);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 3, 0);
    toolbox->addItem(page, tr("simulation parameters"));


    //visualization parameters
    RBVisualizer visualizer;

    colorSchemeLabel = new QLabel;
    colorSchemeLabel->setFrameStyle(frameStyle);
    colorSchemeLabel->setText(QString::number(scheme));
    QPushButton *colorSchemeButton = new QPushButton(tr("color scheme: "));

    //QPushButton *browseButton=new QPushButton(tr("&Browse..."));
    //directoryComboBox = createComboBox(QDir::toNativeSeparators(QDir::currentPath()));
    //connect(directoryComboBox->lineEdit(), &QLineEdit::returnPressed,
            //this, &Parameter_setting::animateFindClick);

    parameterCodeLabel=new QLabel;
    parameterCodeLabel->setFrameStyle(frameStyle);
    parameterCodeLabel->setText(QString::fromStdString(code));
    QPushButton *parameterCodeButton=new QPushButton(tr("parameter code: "));

    timeStepLabel=new QLabel;
    timeStepLabel->setFrameStyle(frameStyle);
    timeStepLabel->setText(QString::number(step));
    QPushButton *timeStepButton=new QPushButton(tr("time step: "));

    QPushButton *applyVisualizationButton=new QPushButton(tr("Apply Visualization Changes"));

    connect(colorSchemeButton, &QAbstractButton::clicked, this, &Parameter_setting::setColorScheme);
    connect(parameterCodeButton, &QAbstractButton::clicked, this, &Parameter_setting::setParameterCode);
    //connect(browseButton, &QAbstractButton::clicked, this, &Parameter_setting::browse);
    connect(timeStepButton, &QAbstractButton::clicked, this, &Parameter_setting::setTimeStep);
    connect(applyVisualizationButton,&QAbstractButton::clicked, this,&Parameter_setting::applyVisualizationChanges);

    page = new QWidget;
    //page->setMaximumSize(500,500);
    //page->setFixedSize(200,200);
    layout = new QGridLayout(page);
    layout->setColumnStretch(1, 1);//2 cols
    layout->setColumnMinimumWidth(1, 250);//2 cols, each col 250 pixels wide
    layout->addWidget(colorSchemeButton, 0, 0);
    layout->addWidget(colorSchemeLabel, 0, 1);
    layout->addWidget(parameterCodeButton, 1, 0);
    layout->addWidget(parameterCodeLabel, 1, 1);
    layout->addWidget(timeStepButton,2,0);
    layout->addWidget(timeStepLabel,2,1);
    //layout->addWidget(new QLabel(tr("load file: ")),3,0);
    //layout->addWidget(directoryComboBox,3,1);
    //layout->addWidget(browseButton,3,2);
    layout->addWidget(applyVisualizationButton,3,0);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 4, 0);
    toolbox->addItem(page, tr("visualization parameters"));

}

void Parameter_setting::setPr()
{
    QStringList items;
    items<<tr("0.100000")<<tr("1.000000")<<tr("10.000000");
    bool ok=0;
    QString item = QInputDialog::getItem(this, tr("set Pr: "),
                                       tr("set Pr: "), items,0,false, &ok);
    if(ok&&!item.isEmpty())
    {
        PrLabel->setText(item);
        global_Pr=item;
        prFlag=true;
    }
}

void Parameter_setting::setRa()
{
    QStringList items;
    items<<tr("10000000.000000")<<tr("1000000000.000000")<<tr("100000000000.000000");
    bool ok=0;

    QString item = QInputDialog::getItem(this, tr("set Ra: "),
                                       tr("set Ra: "), items,0,false, &ok);
    if(ok&&!item.isEmpty())
    {
        RaLabel->setText(item);
        global_Ra=item;
        raFlag=true;
    }
}



void Parameter_setting::applySimulationChanges()
{
    extern std::string folder;
    QString DIR="RBC_Pr"+global_Pr+"_Ra"+global_Ra+"/";
    folder=DIR.toStdString();
    this->close();

}

void Parameter_setting::setColorScheme()
{
    QStringList items;
    items<<tr("0")<<tr("1");
    bool ok=0;
    QString item = QInputDialog::getItem(this, tr("set color scheme: "),
                                       tr("set color scheme: "), items,0,false, &ok);
    if(ok&&!item.isEmpty())
    {
        colorSchemeLabel->setText(item);
        visualizer.setColorScheme(item.toInt());//convert from QString to int
        scheme=visualizer.getColorScheme();
        colorFlag=true;
    }
}

void Parameter_setting::setParameterCode()
{
    QStringList items;
    items<<tr("T")<<tr("mag(U)");
    bool ok=0;
    QString item = QInputDialog::getItem(this, tr("set parameter code: "),
                                       tr("set parameter code: "), items,0,false, &ok);
    if(ok&&!item.isEmpty())
    {
        parameterCodeLabel->setText(item);
        std::string ITEM=item.toStdString();//convert from QSring to std::string
        visualizer.setParameterCode(ITEM);
        code=visualizer.getParameterCode();
        codeFlag=true;
    }
}

void Parameter_setting::setTimeStep()
{
    QStringList items;
    items<<tr("2")<<tr("4")<<tr("10")<<tr("20");
    bool ok=0;
    QString item = QInputDialog::getItem(this, tr("set time step: "),
                                       tr("set time step: "), items,0,false, &ok);
    if(ok&&!item.isEmpty())
    {
        timeStepLabel->setText(item);
        visualizer.setTimeStep(item.toInt());//convert from QString to int
        step=visualizer.getTimeStep();
        stepFlag=true;
    }
}

 void Parameter_setting::applyVisualizationChanges()
 {
     this->close();
 }


