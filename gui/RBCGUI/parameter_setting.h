#ifndef PARAMETER_SETTING_H
#define PARAMETER_SETTING_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QLabel;
class QErrorMessage;
QT_END_NAMESPACE

class Parameter_setting : public QWidget
{
    Q_OBJECT
public:
    explicit Parameter_setting(QWidget *parent = nullptr);

private slots:
    //initial condition
    void set_Nu();
    void set_Beta();
    void set_TFloor();
    void set_Pr();
    /*void set_alphat();
    //physical constants
    void set_g();
    void set_transportProperties();
    void set_turbulenceProperties();
    //system directory
    void set_blockMeshDict();
    void set_controlDict();
    void set_fvSolution();
    void set_fvSchemes();
    //warning and error*/
    void warningMessage();
    void errorMessage();
    void invokeSet();
signals:

public slots:

private:
    //initial condition
    QLabel *Nu_label;
    QLabel *Beta_label;
    QLabel *TFloor_label;
    QLabel *Pr_label;
    int setFlag=0;
    double setValue=0;
    /*QLabel *alphat_label;
    //physical constants
    QLabel *g_label;
    QLabel *transportProperties_label;
    QLabel *turbulenceProperties_label;
    //system directory
    QLabel *blockMeshDict_label;
    QLabel *controlDict_label;
    QLabel *fvSolution_label;
    QLabel *fvSchemes_label;*/

    //warning and error
    QLabel *warning_label;
    QLabel *error_label;
    QErrorMessage *errorMessageDialog;

};

#endif // PARAMETER_SETTING_H
