#ifndef PARAMETER_SETTING_H
#define PARAMETER_SETTING_H

#include <QWidget>
#include <QDir>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QLabel;
class QErrorMessage;
class QComboBox;
QT_END_NAMESPACE

class Parameter_setting : public QWidget
{
    Q_OBJECT
public:
    explicit Parameter_setting(QWidget *parent = nullptr);

private slots:
    //simulation setters
    void setPr();
    void setRa();
    //visiualization setters
    void setColorScheme();
    void setParameterCode();
    void setTimeStep();
    //void browse();
    //apply changes
    void applySimulationChanges();
    void applyVisualizationChanges();
    //QComboBox *createComboBox(const QString &text = QString());
    //void animateFindClick();
signals:
public slots:

private:
    //simulation parameters
    QLabel *PrLabel;
    QLabel *RaLabel;
    //visualization parameters
    QLabel *colorSchemeLabel;
    QLabel *parameterCodeLabel;
    QLabel *timeStepLabel;

};

#endif // PARAMETER_SETTING_H
