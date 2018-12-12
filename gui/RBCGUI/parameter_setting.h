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
    void warningMessage();
    void errorMessage();
    void invokeNuSet();
    void invokeBetaSet();
    void invokeTFloorSet();
    void invokePrSet();
    void applyChanges();
signals:
//void sendData(QString D1,QString D2,QString D3,QString D4);
public slots:

private:
    //initial condition
    QLabel *Nu_label;
    QLabel *Beta_label;
    QLabel *TFloor_label;
    QLabel *Pr_label;
    int setFlag=0;
    QString setNuValue="0.000001";
    QString setBetaValue="0.000214";
    QString setTFloorValue="340.000000";
    QString setPrValue="7.560000";
    //warning and error
    QLabel *warning_label;
    QLabel *error_label;
    QErrorMessage *errorMessageDialog;

};

#endif // PARAMETER_SETTING_H
