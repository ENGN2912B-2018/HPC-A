#pragma once
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
#include <vtkScalarBarActor.h>
#include <vtkScalarsToColors.h>
#include <vtkVariant.h>
#include <vtkVariantArray.h>

#include <vtkActor.h>
#include <vtkActor2D.h>
#ifdef _WIN32
#include <vtkAVIWriter.h>
#endif
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

#include <vtkDirectory.h>
#include <vtkPSystemTools.h>

#include <string>
#include <chrono>
#include <thread>
#include <time.h> 


typedef std::vector<vtkSmartPointer<vtkPlaneSource>>				PlaneSourceVector;
typedef std::vector<vtkSmartPointer<vtkUnstructuredGridReader>>		UnstructuredGridReaderVector;
typedef std::vector<vtkSmartPointer<vtkCellData>>					CellDataVector;
typedef std::vector<vtkSmartPointer<vtkFloatArray>>					FloatArrayVector;
typedef std::vector<vtkSmartPointer<vtkLookupTable>>				LookupTableVector;
typedef std::vector<vtkSmartPointer<vtkNamedColors>>				NamedColorsVector;
typedef std::vector<vtkSmartPointer<vtkPolyDataMapper>>				PolyDataMapperVector;
typedef std::vector<vtkSmartPointer<vtkActor>>						ActorVector;
typedef std::vector<vtkSmartPointer<vtkRenderer>>					RendererVector;
typedef std::vector<vtkSmartPointer<vtkScalarBarActor>>				ScalarBarActorVector;
typedef std::vector<vtkSmartPointer<vtkRenderWindow>>				RenderWindowVector;

class RBVisualizer{
  public:
    // Constructors
    RBVisualizer();
    RBVisualizer(int colorScheme, int resolutionX, int resolutionY,
       std::string path, std::string parameter, int timeStep, int timeMax);

    // Destrcutor
    ~RBVisualizer();



    // Getters
    int getColorScheme() const;
    int getResolutionX() const;
    int getResolutionY() const;
    int getTimeStep() const;
    int getTimeMax() const;
    double getParameterMin() const;
    double getParameterMax() const;
#ifdef _WIN32
	std::string getSavePath() const;
	std::string getSaveName() const;
#endif

    // Setters
    void setColorScheme(int colors);
    void setResolutionX(int resoX);
    void setResolutionY(int resoY);
    void setParameterMin(double min);
    void setParameterMax(double max);
#ifdef _WIN32
	void setSavePath(std::string savePath);
	void setSaveName(std::string saveName);
	void  setSaveNameDefault();
#endif

    // Member methods
    void readParameterMinMax();
	template <typename T>
	void vectorInitalizer(std::vector<vtkSmartPointer<T>>& pointerVector);
    RendererVector mainVisualizer();
	//void mainVideoSaver();
    // Methods for debugging
    //void coutDebugger(int debugMode);

  private:
    int				_colorScheme = 0;
    int				_resolutionX = 0;
    int				_resolutionY = 0;
    int				_timeStep = 0;
    int				_timeMax = 0;
	int				_vectorSize;
    std::string		_filePath;
#ifdef _WIN32
	std::string		_savePath;
	std::string		_saveName;
#endif
    //double        parameterMinMax[2] = {0};
    double			_parameterMin;
    double			_parameterMax;
    std::string		_parameterCode;
	//RendererVector	rendererOutput;


	

};

// Structs for error handling
struct fileNotExistError : public std::exception {
	const char * what() const throw() {
		return "File not exist.";
	}
};

struct pathNotExistError : public std::exception {
	const char * what() const throw() {
		return "Path not exist.";
	}
};