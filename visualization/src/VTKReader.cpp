#include "VTKReader.h"

#include <string>
#include <chrono>
#include <thread>
#include <iostream>

#define DEBUG

namespace
{
//! Create a lookup table.
/*!
@param lut - An indexed lookup table.
*/
void MakeLUT(int const& colorScheme, vtkLookupTable* lut);


}

RBVisualizer::RBVisualizer(){
    int           colorScheme = 0;
    int           resolutionX = 0;
    int           resolutionY = 0;
    int           timeStep = 0;
    int           timeMax = 0;
}

RBVisualizer::RBVisualizer(int colorScheme, int resolutionX, int resolutionY,
   std::string filePath, std::string parameterCode, int timeStep, int timeMax){
    this->colorScheme = colorScheme;
    this->resolutionX = resolutionX;
    this->resolutionY = resolutionY;
    this->filePath    = filePath;
    if(this->filePath.back() != '/'){
      this->filePath.push_back('/');
    }
    this->parameterCode = parameterCode;
    this->timeStep = timeStep;
    this->timeMax = timeMax;
}

RBVisualizer::~RBVisualizer(){}

int RBVisualizer::getColorScheme() const{
    return colorScheme;
}

int RBVisualizer::getResolutionX() const{
    return resolutionX;
}

int RBVisualizer::getResolutionY() const{
    return resolutionY;
}

int RBVisualizer::getTimeStep() const{
    return timeStep;
}

int RBVisualizer::getTimeMax() const{
    return timeMax;
}

double RBVisualizer::getParameterMax() const{
    return parameterMax;
}

double RBVisualizer::getParameterMin() const{
    return parameterMin;
}

void RBVisualizer::setColorScheme(int colors){
    colorScheme = colors;
}

void RBVisualizer::setResolutionX(int resoX){
    resolutionX = resoX;
}

void RBVisualizer::setResolutionY(int resoY){
    resolutionY = resoY;
}

void RBVisualizer::setParameterMin(double min){
    parameterMin = min;
}

void RBVisualizer::setParameterMax(double max){
    parameterMax = max;
}

void RBVisualizer::readParameterMinMax(){
    vtkSmartPointer<vtkUnstructuredGridReader> reader =
      vtkSmartPointer<vtkUnstructuredGridReader>::New();
    std::string fileName = filePath + "RBConvection_" +
      std::to_string(timeMax) + ".vtk";
    reader->SetFileName(fileName.c_str());
    reader->SetFieldDataName("attributes");
    reader->Update();
    vtkSmartPointer<vtkCellData> cellData =
      vtkSmartPointer<vtkCellData>::New();
    cellData = reader->GetOutput()->GetCellData();
    vtkSmartPointer<vtkFloatArray> arrayParameters =
      vtkSmartPointer<vtkFloatArray>::New();
    arrayParameters =
      vtkFloatArray::SafeDownCast(cellData->GetAbstractArray(parameterCode.c_str()));
    double parameterMinMax[2];
    arrayParameters->GetRange(parameterMinMax);
    //parameterMin = parameterMinMax[0];
    parameterMax = parameterMinMax[1];
}

RendererVector RBVisualizer::mainVisualizer(){

 
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  for(int fileIndex = timeStep; fileIndex <= timeMax; fileIndex += timeStep){
	  ///   Data Structres   ///
	  vtkSmartPointer<vtkPlaneSource> parameterPlane =
		  vtkSmartPointer<vtkPlaneSource>::New();

	  vtkSmartPointer<vtkUnstructuredGridReader> reader =
		  vtkSmartPointer<vtkUnstructuredGridReader>::New();

	  vtkSmartPointer<vtkCellData> cellData =
		  vtkSmartPointer<vtkCellData>::New();

	  // vtkSmartPointer<vtkIntArray> arrayID =
	  //   vtkSmartPointer<vtkIntArray>::New();

	  vtkSmartPointer<vtkFloatArray> arrayParameters =
		  vtkSmartPointer<vtkFloatArray>::New();

	  // vtkSmartPointer<vtkLookupTable> lutID =
	  //   vtkSmartPointer<vtkLookupTable>::New();

	  vtkSmartPointer<vtkLookupTable> lutParameter =
		  vtkSmartPointer<vtkLookupTable>::New();

	  vtkSmartPointer<vtkNamedColors> colors =
		  vtkSmartPointer<vtkNamedColors>::New();

	  vtkSmartPointer<vtkPolyDataMapper> mapper =
		  vtkSmartPointer<vtkPolyDataMapper>::New();

	  vtkSmartPointer<vtkActor> dataActor =
		  vtkSmartPointer<vtkActor>::New();

	  vtkSmartPointer<vtkRenderer> ren =
		  vtkSmartPointer<vtkRenderer>::New();

      /////    Data manipulation    /////
      std::string fileName = filePath + "RBConvection_" +
        std::to_string(fileIndex) + ".vtk";
      std::cout << "Loading " << fileName.c_str() << std::endl;
      reader->SetFileName(fileName.c_str());
      reader->SetFieldDataName("attributes");
      reader->Update();

      // Achieve the Cell data
      cellData = reader->GetOutput()->GetCellData();

      // Ge the array using SafeDownCast()
      arrayParameters =
        vtkFloatArray::SafeDownCast(cellData->GetAbstractArray(parameterCode.c_str()));
      //arrayTemperature->SetName("Temperature");
      double arrayParameterRange[2];
      arrayParameters->GetRange(arrayParameterRange);

      // Set up lookupTables
      int tableSize = resolutionX*resolutionY + 1;
      lutParameter->SetNumberOfTableValues(tableSize);
      // Set up the color schemes
      MakeLUT(colorScheme, lutParameter);
      lutParameter->SetTableRange(parameterMin, parameterMax);
      lutParameter->Build();

      parameterPlane->SetXResolution(resolutionX);
      parameterPlane->SetYResolution(resolutionY);

      parameterPlane->Update();
      parameterPlane->GetOutput()->GetCellData()->SetScalars(arrayParameters);

      #ifdef DEBUG
        std::cout << "Hello!" << endl;
        // std::cout << "Range of arrayID: " << arrayIDRange[0]
        //   << " " << arrayIDRange[1] << endl;
        std::cout << "Range of current parameter: " << arrayParameterRange[0]
          << " " << arrayParameterRange[1] << endl;
        std::cout << "Range used in lut: " << parameterMin
          << " " << parameterMax << endl;
        // std::cout << "Values of the float array: " << endl;
        // for(int i = 0; i < resolution*resolution; i++){
        //   std::cout << arrayTemperature->GetVariantValue(i) << " ";
        //   if(i % resolution == (resolution-1)){
        //     std::cout << "\n";
        //   }
        // }
        // std::cout << "Values of the int array: " << endl;
        // for(int i = 0; i < resolution*resolution; i++){
        //   std::cout << arrayID->GetVariantValue(i) << " ";
        //   if(i % resolution == (resolution-1)){
        //     std::cout << "\n";
        //   }
        // }

        double tableColor[3];
        lutParameter->GetColor(arrayParameterRange[0], tableColor);
        std::cout << "The color of arrayParameterRange[0]: " <<
        tableColor[0] << " " << tableColor[1] << " " << tableColor[2] << std::endl;
        lutParameter->GetColor(arrayParameterRange[1], tableColor);
        std::cout << "The color of arrayParameterRange[1]: " <<
        tableColor[0] << " " << tableColor[1] << " " << tableColor[2] << std::endl;
      #endif

      /////   Visualization Pipeline    /////

      mapper->SetInputConnection(parameterPlane->GetOutputPort());
      mapper->SetScalarRange(parameterMin, parameterMax);
      mapper->SetLookupTable(lutParameter);

      dataActor->SetMapper(mapper);

      ren->AddActor(dataActor);
      ren->SetBackground(colors->GetColor3d("SlateGray").GetData());
	  rendererOutput.push_back(ren);

      //renWin->AddRenderer(ren);
      //renWin->SetSize(400, 400);

      //iren->SetRenderWindow(renWin);
      //renWin->Render();
      //std::this_thread::sleep_for(std::chrono::milliseconds(16));
      //iren->Start();

  }
  return rendererOutput;
}



// MakeLUT: Adopted from
// https://lorensen.github.io/VTKExamples/site/Cxx/Visualization/Hawaii/
namespace
{
void MakeLUT(int const& colorScheme, vtkLookupTable* lut)
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  // Select a color scheme.
  switch (colorScheme)
  {
    case 0:
    default:
    {
      // Make the lookup using a Brewer palette.
      vtkSmartPointer<vtkColorSeries> colorSeries =
        vtkSmartPointer<vtkColorSeries>::New();
      colorSeries->SetNumberOfColors(8);
      int colorSeriesEnum = colorSeries->BREWER_DIVERGING_BROWN_BLUE_GREEN_8;
      colorSeries->SetColorScheme(colorSeriesEnum);
      colorSeries->BuildLookupTable(lut, colorSeries->ORDINAL);
      lut->SetNanColor(1, 0, 0, 1);
      break;
    }
    case 1:
    {
      // A lookup table of 256 colours ranging from
      //  deep blue(water) to yellow - white(mountain top)
      //  is used to color map this figure.
      lut->SetHueRange(0.7, 0);
      lut->SetSaturationRange(1.0, 0);
      lut->SetValueRange(0.5, 1.0);
      break;
    }
    case 2:
      // Make the lookup table with a preset number of colours.
      vtkSmartPointer<vtkColorSeries> colorSeries =
        vtkSmartPointer<vtkColorSeries>::New();
      colorSeries->SetNumberOfColors(8);
      colorSeries->SetColorSchemeName("Hawaii");
      colorSeries->SetColor(0, colors->GetColor3ub("turquoise_blue"));
      colorSeries->SetColor(1, colors->GetColor3ub("sea_green_medium"));
      colorSeries->SetColor(2, colors->GetColor3ub("sap_green"));
      colorSeries->SetColor(3, colors->GetColor3ub("green_dark"));
      colorSeries->SetColor(4, colors->GetColor3ub("tan"));
      colorSeries->SetColor(5, colors->GetColor3ub("beige"));
      colorSeries->SetColor(6, colors->GetColor3ub("light_beige"));
      colorSeries->SetColor(7, colors->GetColor3ub("bisque"));
      colorSeries->BuildLookupTable(lut, colorSeries->ORDINAL);
      lut->SetNanColor(1, 0, 0, 1);
  };
}
}
