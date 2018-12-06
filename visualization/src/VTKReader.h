#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>

#include <vtkGenericCell.h>

#include <vtkFieldData.h>
#include <vtkAbstractArray.h>
#include <vtkCellData.h>
#include <vtkColor.h>
#include <vtkFloatArray.h>
#include <vtkIntArray.h>
#include <vtkLookupTable.h>
#include <vtkPlaneSource.h>
#include <vtkScalarsToColors.h>
#include <vtkVariant.h>
#include <vtkVariantArray.h>

#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>
#include <vtkColorSeries.h>
#include <vtkDataSetMapper.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include <vtkCellIterator.h>
#include <vtkCellTypes.h>

#include <string>
#include <chrono>
#include <thread>


class RBVisualizer{
  public:
    // Constructors
    RBVisualizer();
    RBVisualizer(int colorScheme, int resolutionX, int resolutionY,
       std::string path, std::string parameter, int timeStep, int timeMax);

    // Destrcutors
    ~RBVisualizer();

    // Getters
    int getColorScheme() const;
    int getResolutionX() const;
    int getResolutionY() const;
    int getTimeStep() const;
    int getTimeMax() const;
    double getParameterMin() const;
    double getParameterMax() const;

    // Setters
    void setColorScheme(int colors);
    void setResolutionX(int resoX);
    void setResolutionY(int resoY);
    void setParameterMin(double min);
    void setParameterMax(double max);

    // Member methods
    void readParameterMinMax();
    void mainVisualizer();

    // Methods for debugging
    void coutDebugger(int debugMode);

  private:
    int           colorScheme = 0;
    int           resolutionX = 0;
    int           resolutionY = 0;
    int           timeStep = 0;
    int           timeMax = 0;
    std::string   filePath;
    //double        parameterMinMax[2] = {0};
    double        parameterMin;
    double        parameterMax;
    std::string   parameterCode;

};
