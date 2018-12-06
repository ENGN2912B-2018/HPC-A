#include "VTKReader.h"

#include <string>
#include <chrono>
#include <thread>

VTKReader::VTKReader(){
    int           colorScheme = 0;
    int           resolution = 0;
    int           timeStep = 0;
    int           timeMax = 0;
}

VTKReader::VTKReader(int colorScheme, int resolution, std::string filePath,
  std::string parameterCode, int timeStep, int timeMax){
    colorScheme(colorScheme);
    resolution(resolution);
    filePath(filePath);
    parameter(parameterCode);
    timeStep(timeStep);
    timeMax(timeMax);
}

int getColorScheme() const{
    return colorScheme;
}

int getResolution() const{
    return resolution;
}

int getTimeStep() const{
    return timeStep;
}

int getTimeMax() const{
    return timeMax;
}

double getParameterMax() const{
    return parameterMax;
}

double getParameterMin() const{
    return parameterMin;
}

void setColorScheme(int colors){
    colorScheme = colors;
}

void setResolution(int reso){
    resolution = reso;
}

void setParameterMin(double min){
    parameterMin = min;
}

void setParameterMax(double max){
    parameterMax = max;
}

void readParameterMinMax(){
    vtkSmartPointer<vtkUnstructuredGridReader> reader =
      vtkSmartPointer<vtkUnstructuredGridReader>::New();
    std::string fileName = filePath + "RBConvection_" +
      std::to_string(timeMax) + ".vtk";
    reader->SetFileName(filename.c_str());
    reader->SetFieldDataName("attributes");
    reader->Update();
    vtkSmartPointer<vtkCellData> cellData =
      vtkSmartPointer<vtkCellData>::New();
    cellData = reader->GetOutput()->GetCellData();
    vtkSmartPointer<vtkFloatArray> arrayParameters =
      vtkSmartPointer<vtkFloatArray>::New();
    arrayParameters =
      vtkFloatArray::SafeDownCast(cellData->GetAbstractArray(parameterCode));
    double parameterMinMax[2];
    arrayParameters->GetRange(parameterMinMax);
    //parameterMin = parameterMinMax[0];
    parameterMax = parameterMinMax[1];
}
