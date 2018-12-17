#include "VTKReader.h"

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <omp.h>
#include <fstream>


//#define DEBUG
#define CHRONO
#define MULTI
#define ERROR
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
    this->_colorScheme = colorScheme;
    this->_resolutionX = resolutionX;
    this->_resolutionY = resolutionY;
    this->_filePath    = filePath;
	// The path of video saved is the same as the path of .vtk files at default
#ifdef ERROR
	std::cout << "Calling the constructor..." << std::endl;
#endif
	this->setSavePath(filePath);
    if(this->_filePath.back() != '/'){
      this->_filePath.push_back('/');
	  this->_savePath.push_back('/');
    }
	// The parameterCode should be initialized before the name of video
	this->_parameterCode = parameterCode;
	this->setSaveNameDefault();
    
    this->_timeStep = timeStep;
    this->_timeMax = timeMax;

	// Initialize the vector with a fixed size
	this->_vectorSize = (timeMax - timeStep) / timeStep + 1;
}

// No need to define a destrctor because all variables in VTK are smartpointers
RBVisualizer::~RBVisualizer(){}


/////	Getters		/////

int RBVisualizer::getColorScheme() const{
    return _colorScheme;
}

int RBVisualizer::getResolutionX() const{
    return _resolutionX;
}

int RBVisualizer::getResolutionY() const{
    return _resolutionY;
}

int RBVisualizer::getTimeStep() const{
    return _timeStep;
}

int RBVisualizer::getTimeMax() const{
    return _timeMax;
}

double RBVisualizer::getParameterMax() const{
    return _parameterMax;
}

double RBVisualizer::getParameterMin() const{
    return _parameterMin;
}

std::string RBVisualizer::getSavePath() const {
	return _savePath;
}

std::string RBVisualizer::getSaveName() const {
	return _saveName;
}

/////	 Setters	/////

void RBVisualizer::setColorScheme(int colors){
    _colorScheme = colors;
}

void RBVisualizer::setResolutionX(int resoX){
    _resolutionX = resoX;
}

void RBVisualizer::setResolutionY(int resoY){
    _resolutionY = resoY;
}

void RBVisualizer::setParameterMin(double min){
    _parameterMin = min;
}

void RBVisualizer::setParameterMax(double max){
    _parameterMax = max;
}

void RBVisualizer::setSavePath(std::string savePath){
#ifdef ERROR
	std::cout << "Calling the setSavePath()..." << std::endl;
#endif
	_savePath = savePath;
	// Create the path if it does not exist
	vtkSmartPointer<vtkDirectory> currentPath =
		vtkSmartPointer<vtkDirectory>::New();

	int openIndicator = currentPath->Open(_savePath.c_str());
	if (!openIndicator && _savePath == _filePath) {
		std::cout << "Hey! Exception!" << std::endl;
		throw pathNotExistError();
	}
	else {
		currentPath->MakeDirectory(_savePath.c_str());
	}
#ifdef ERROR
	std::cout << "Done calling the setSavePath()..." << std::endl;
#endif
}

void RBVisualizer::setSaveName(std::string saveName) {
	_saveName = saveName;
}

void RBVisualizer::setSaveNameDefault() {
	// Setting the name of video by default: 
	// "RBConvection_<attribute>(velocity/temperature)_localtime.avi"
	time_t rawTime;
	struct tm* timeInfo;
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	std::string year = std::to_string(1900 + timeInfo->tm_year);
	std::string month = std::to_string(1 + timeInfo->tm_mon);
	std::string day = std::to_string(timeInfo->tm_mday);
	std::string hour = std::to_string(1 + timeInfo->tm_hour);
	std::string minute = std::to_string(1 + timeInfo->tm_min);
	//std::string second = std::to_string(1 + timeInfo->tm_sec);
	std::string attributeName;
	if (_parameterCode == "mag(U)")
		attributeName = "Velocity_";
	else
		attributeName = "Temperature_";
	_saveName = "RBConvection_" + attributeName + year + month + day + hour + minute + ".avi";
}


void RBVisualizer::readParameterMinMax(){
#ifdef ERROR
	std::cout << "Calling the readParameterMinMax()..." << std::endl;
#endif

    vtkSmartPointer<vtkUnstructuredGridReader> reader =
      vtkSmartPointer<vtkUnstructuredGridReader>::New();
    std::string fileNameMax = _filePath + "RBConvection_" +
      std::to_string(_timeMax) + ".vtk";
	std::string fileNameMin = _filePath + "RBConvection_" +
		std::to_string(_timeStep) + ".vtk";

	vtkSmartPointer<vtkDirectory> currentPath =
		vtkSmartPointer<vtkDirectory>::New();
#ifdef ERROR
	std::cout << "Calling the vtkDirectory->Open()..." << std::endl;
#endif
	int openIndicator = currentPath->Open(_filePath.c_str());
#ifdef ERROR
	std::cout << "Done calling the vtkDirectory->Open()..." << std::endl;
#endif
	if (!openIndicator) {
		throw pathNotExistError();
	}
	ifstream currentFileMin(fileNameMin.c_str());
	if (!currentFileMin.good()) {
		throw fileNotExistError();
	}
	ifstream currentFileMax(fileNameMax.c_str());
	if (!currentFileMax.good()) {
		throw fileNotExistError();
	}
    reader->SetFileName(fileNameMax.c_str());
    reader->SetFieldDataName("attributes");
    reader->Update();
    vtkSmartPointer<vtkCellData> cellData =
      vtkSmartPointer<vtkCellData>::New();
    cellData = reader->GetOutput()->GetCellData();
    vtkSmartPointer<vtkFloatArray> arrayParameters =
      vtkSmartPointer<vtkFloatArray>::New();
    arrayParameters =
      vtkFloatArray::SafeDownCast(cellData->GetAbstractArray(_parameterCode.c_str()));
    double parameterMinMax[2];
    arrayParameters->GetRange(parameterMinMax);
	_parameterMax = parameterMinMax[1];


	if (_parameterCode == "mag(U)") {
		_parameterMin = 0;
	}
	else if(_parameterCode == "T"){

		reader->SetFileName(fileNameMin.c_str());
		reader->Update();
		cellData = reader->GetOutput()->GetCellData();
		arrayParameters =
			vtkFloatArray::SafeDownCast(cellData->GetAbstractArray(_parameterCode.c_str()));
		arrayParameters->GetRange(parameterMinMax);
		_parameterMin = parameterMinMax[0];
	}

#ifdef ERROR
	std::cout << "Done calling the readParameterMinMax()..." << std::endl;
#endif
}

template <typename T>
void RBVisualizer::vectorInitalizer(std::vector<vtkSmartPointer<T>>& pointerVector) {
	for (int initializerIndex = 0; initializerIndex < _vectorSize; initializerIndex ++){
		pointerVector.at(initializerIndex) = vtkSmartPointer<T>::New();
	}
}



RendererVector RBVisualizer::mainVisualizer(){
#ifdef CHRONO
	auto startTime = std::chrono::steady_clock::now();
	cout << "Hello!" << endl;
#endif
  
	///		Data Structures (Vector Version)	///
	PlaneSourceVector				parameterPlaneVec(_vectorSize);
	UnstructuredGridReaderVector	readerVec(_vectorSize);
	CellDataVector					cellDataVec(_vectorSize);
	FloatArrayVector				arrayParametersVec(_vectorSize);
	LookupTableVector				lutParameterVec(_vectorSize);
	NamedColorsVector				colorsVec(_vectorSize);
	PolyDataMapperVector			mapperVec(_vectorSize);
	ScalarBarActorVector			scalarBarVec(_vectorSize);
	ActorVector						dataActorVec(_vectorSize);
	RendererVector					rendererOutput(_vectorSize);

	vectorInitalizer<vtkPlaneSource>(parameterPlaneVec);
	vectorInitalizer<vtkUnstructuredGridReader>(readerVec);
	vectorInitalizer<vtkCellData>(cellDataVec);
	vectorInitalizer<vtkFloatArray>(arrayParametersVec);
	vectorInitalizer<vtkLookupTable>(lutParameterVec);
	vectorInitalizer<vtkNamedColors>(colorsVec);
	vectorInitalizer<vtkPolyDataMapper>(mapperVec);
	vectorInitalizer<vtkScalarBarActor>(scalarBarVec);
	vectorInitalizer<vtkActor>(dataActorVec);
	vectorInitalizer<vtkRenderer>(rendererOutput);

 // vtkSmartPointer<vtkRenderWindow> renWin =
 //   vtkSmartPointer<vtkRenderWindow>::New();

//  vtkSmartPointer<vtkRenderWindowInteractor> iren =
 //   vtkSmartPointer<vtkRenderWindowInteractor>::New();
	


 #pragma omp parallel for ordered schedule(guided) num_threads(2)
  for(int fileIndex = _timeStep; fileIndex <= _timeMax; fileIndex += _timeStep){
	#ifdef CHRONO
	  auto tic = std::chrono::steady_clock::now();
	#endif
	  int currentVectorIndex = fileIndex / _timeStep - 1;

	  

      /////    Data manipulation    /////
      std::string fileName = _filePath + "RBConvection_" +
        std::to_string(fileIndex) + ".vtk";
      readerVec.at(currentVectorIndex)->SetFileName(fileName.c_str());
      readerVec.at(currentVectorIndex)->SetFieldDataName("attributes");
      readerVec.at(currentVectorIndex)->Update();
#ifdef MULTI
	  int tid = omp_get_thread_num();
	  std::cout << "Current thread: " << tid << endl;
#endif
      // Achieve the Cell data
      cellDataVec.at(currentVectorIndex) = readerVec.at(currentVectorIndex)->GetOutput()->GetCellData();

      // Ge the array using SafeDownCast()
      arrayParametersVec.at(currentVectorIndex) =
        vtkFloatArray::SafeDownCast(cellDataVec.at(currentVectorIndex)->GetAbstractArray(_parameterCode.c_str()));
      //arrayTemperature->SetName("Temperature");
      double arrayParameterRange[2];
      arrayParametersVec.at(currentVectorIndex)->GetRange(arrayParameterRange);

      // Set up lookupTables
      int tableSize = _resolutionX*_resolutionY + 1;
      lutParameterVec.at(currentVectorIndex)->SetNumberOfTableValues(tableSize);
      // Set up the color schemes
      MakeLUT(_colorScheme, lutParameterVec.at(currentVectorIndex));
      lutParameterVec.at(currentVectorIndex)->SetTableRange(_parameterMin, _parameterMax);
      lutParameterVec.at(currentVectorIndex)->Build();

      parameterPlaneVec.at(currentVectorIndex)->SetXResolution(_resolutionX);
      parameterPlaneVec.at(currentVectorIndex)->SetYResolution(_resolutionY);
	  parameterPlaneVec.at(currentVectorIndex)->SetOrigin(0, 0, 0);
	  parameterPlaneVec.at(currentVectorIndex)->SetPoint1(_resolutionX * 8, 0, 0);
	  parameterPlaneVec.at(currentVectorIndex)->SetPoint2(0, _resolutionY * 8, 0);
      parameterPlaneVec.at(currentVectorIndex)->Update();
      parameterPlaneVec.at(currentVectorIndex)->GetOutput()
		  ->GetCellData()->SetScalars(arrayParametersVec.at(currentVectorIndex));

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
        lutParameterVec.at(currentVectorIndex)->GetColor(arrayParameterRange[0], tableColor);
        std::cout << "The color of arrayParameterRange[0]: " <<
        tableColor[0] << " " << tableColor[1] << " " << tableColor[2] << std::endl;
        lutParameterVec.at(currentVectorIndex)->GetColor(arrayParameterRange[1], tableColor);
        std::cout << "The color of arrayParameterRange[1]: " <<
        tableColor[0] << " " << tableColor[1] << " " << tableColor[2] << std::endl;
      #endif  

      /////   Visualization Pipeline    /////

      mapperVec.at(currentVectorIndex)->SetInputConnection(parameterPlaneVec.at(currentVectorIndex)->GetOutputPort());
      mapperVec.at(currentVectorIndex)->SetScalarRange(_parameterMin, _parameterMax);
      mapperVec.at(currentVectorIndex)->SetLookupTable(lutParameterVec.at(currentVectorIndex));


	  // Set up a scalar bar(legend) on the render window
	  scalarBarVec.at(currentVectorIndex)->SetLookupTable(mapperVec.at(currentVectorIndex)->GetLookupTable());
	  if (_parameterCode == "T")
		  scalarBarVec.at(currentVectorIndex)->SetTitle("Temperature(K)");
	  else if (_parameterCode == "mag(U)")
		  scalarBarVec.at(currentVectorIndex)->SetTitle("Velocity(m/s)");

	  scalarBarVec.at(currentVectorIndex)->SetNumberOfLabels(4);
	  scalarBarVec.at(currentVectorIndex)->SetWidth(0.1);
	  scalarBarVec.at(currentVectorIndex)->SetHeight(0.6);
	  //scalarBarVec.at(currentVectorIndex)->GetPositionCoordinate()->SetValue(resolutionX * 7, resolutionY * 1, 0);
	  //scalarBarVec.at(currentVectorIndex)->GetPosition2Coordinate()->SetValue(resolutionX * 7.5, resolutionY * 7, 0);


      dataActorVec.at(currentVectorIndex)->SetMapper(mapperVec.at(currentVectorIndex));

	  rendererOutput.at(currentVectorIndex)->AddActor(dataActorVec.at(currentVectorIndex));
	  rendererOutput.at(currentVectorIndex)->AddActor2D(scalarBarVec.at(currentVectorIndex));
	  rendererOutput.at(currentVectorIndex)->SetBackground(0.44, 0.502, 0.565);
	  #ifdef CHRONO
		auto toc = std::chrono::steady_clock::now();
		std::cout << "The runtime of executing chunk " << fileIndex << " is "
			<< std::chrono::duration <double, std::milli>(toc - tic).count()
			<< " ms" << std::endl;
	  #endif

	  //#pragma omp ordered
		
	  //rendererOutput.at(currentVectorIndex) = ren;
      //renWin->AddRenderer(ren);
      //renWin->SetSize(400, 400);

      //iren->SetRenderWindow(renWin);
      //renWin->Render();
      //std::this_thread::sleep_for(std::chrono::milliseconds(16));
      //iren->Start();
	  
  }
  #ifdef CHRONO
	auto endTime = std::chrono::steady_clock::now();
	std::cout << "Total runtime is: "
		<< std::chrono::duration <double, std::milli>(endTime - startTime).count()
		<< " ms" << std::endl;
  #endif	
  return rendererOutput;
}



// MakeLUT: Adapted from
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
	  lut->SetHueRange(0, 1);
	  lut->SetSaturationRange(0, 1);
	  lut->SetValueRange(0, 1.0);
  };
}
}
