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

#define DEBUG

int main (int argc, char *argv[]){
  if(argc < 2){
    std::cout << "Usage: " << argv[0] << " filename.vtk" << std::endl;
    return EXIT_FAILURE;
  }

  // Set the geometry
  int resolution = 20;
  vtkSmartPointer<vtkPlaneSource> idPlane =
    vtkSmartPointer<vtkPlaneSource>::New();
  idPlane->SetXResolution(resolution);
  idPlane->SetYResolution(resolution);

  vtkSmartPointer<vtkPlaneSource> temperaturePlane =
    vtkSmartPointer<vtkPlaneSource>::New();
  temperaturePlane->SetXResolution(resolution);
  temperaturePlane->SetYResolution(resolution);

  // Create the reader for the data.
  std::string filename = argv[1];
  std::cout << "Loading " << filename.c_str() << std::endl;
  vtkSmartPointer<vtkUnstructuredGridReader> reader =
    vtkSmartPointer<vtkUnstructuredGridReader>::New();
  reader->SetFileName(filename.c_str());
  reader->SetFieldDataName("attributes");
  reader->Update();

  // Achieving the Cell data
  vtkSmartPointer<vtkCellData> cellData =
    vtkSmartPointer<vtkCellData>::New();
  cellData = reader->GetOutput()->GetCellData();

  // Get the array using SafeDownCast()
  vtkSmartPointer<vtkIntArray> arrayID =
    vtkSmartPointer<vtkIntArray>::New();
  //vtkAbstractArray *arrayID;
  arrayID =
    vtkIntArray::SafeDownCast(cellData->GetAbstractArray("cellID"));
  arrayID->SetName("CellID");
  int arrayIDRange[2];
  arrayID->GetValueRange(arrayIDRange); // Note: This is not GetRange()!
  vtkSmartPointer<vtkFloatArray> arrayTemperature =
    vtkSmartPointer<vtkFloatArray>::New();

  //vtkAbstractArray *arrayTemperature;
  arrayTemperature =
    vtkFloatArray::SafeDownCast(cellData->GetAbstractArray("T"));
  arrayTemperature->SetName("Temperature");
  double arrayTemperatureRange[2];
  arrayTemperature->GetRange(arrayTemperatureRange);
  //int dimension = arrayID->GetNumberOfComponents();

  // Set up lookupTables
  vtkSmartPointer<vtkLookupTable> lutID =
    vtkSmartPointer<vtkLookupTable>::New();
  int tableSize = std::max(resolution*resolution + 1, 400);
  lutID->SetTableRange(arrayIDRange[0], arrayIDRange[1]);
  lutID->SetNumberOfTableValues(tableSize);
  lutID->Build();

  vtkSmartPointer<vtkLookupTable> lutTemperture =
    vtkSmartPointer<vtkLookupTable>::New();
  lutTemperture->SetNumberOfTableValues(tableSize);
  lutTemperture->SetTableRange(arrayTemperatureRange[0], arrayTemperatureRange[1]);
  lutTemperture->Build();

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  // lutTemperture->SetTableValue
  //   (arrayTemperatureRange[0], colors->GetColor4d("Tomato").GetData());
  // lutTemperture->SetTableValue
  //   (arrayTemperatureRange[1], colors->GetColor3d("MidnightBlue").GetData());

  idPlane->Update();
  idPlane->GetOutput()->GetCellData()->SetScalars(arrayID);

  temperaturePlane->Update();
  temperaturePlane->GetOutput()->GetCellData()->SetScalars(arrayTemperature);

  #ifdef DEBUG
    std::cout << "Hello!" << endl;
    std::cout << "Range of arrayID: " << arrayIDRange[0]
      << " " << arrayIDRange[1] << endl;
    std::cout << "Range of arrayTemperature: " << arrayTemperatureRange[0]
      << " " << arrayTemperatureRange[1] << endl;
    std::cout << "Values of the float array: " << endl;
    for(int i = 0; i < 400; i++){
      std::cout << arrayTemperature->GetVariantValue(i) << " ";
      if(i % 20 == 19){
        std::cout << "\n";
      }
    }
    std::cout << "Values of the int array: " << endl;
    for(int i = 0; i < 400; i++){
      std::cout << arrayID->GetVariantValue(i) << " ";
      if(i % 20 == 19){
        std::cout << "\n";
      }
    }

    double tableColor[3];
    lutTemperture->GetColor(arrayTemperatureRange[0], tableColor);
    std::cout << "The color of arrayTemperatureRange[0]: " <<
    tableColor[0] << " " << tableColor[1] << " " << tableColor[2] << std::endl;
    lutTemperture->GetColor(arrayTemperatureRange[1], tableColor);
    std::cout << "The color of arrayTemperatureRange[1]: " <<
    tableColor[0] << " " << tableColor[1] << " " << tableColor[2] << std::endl;
  #endif


  /////     Data manipulation ends here     /////

  // Connect with a Mapper
   // vtkSmartPointer<vtkDataSetMapper> dataMapper =
   //   vtkSmartPointer<vtkDataSetMapper>::New();
   // dataMapper->SetInputConnection(reader->GetOutputPort());
   vtkSmartPointer<vtkPolyDataMapper> mapper =
     vtkSmartPointer<vtkPolyDataMapper>::New();
   mapper->SetInputConnection(temperaturePlane->GetOutputPort());
   mapper->SetScalarRange(arrayTemperatureRange[0], arrayTemperatureRange[1]);
   mapper->SetLookupTable(lutTemperture);

   vtkSmartPointer<vtkActor> dataActor =
    vtkSmartPointer<vtkActor>::New();
  dataActor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  ren->AddActor(dataActor);
  ren->SetBackground(colors->GetColor3d("SlateGray").GetData());

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  //renWin->SetSize(300, 300);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  renWin->Render();
  iren->Start();

  // #ifdef DEBUG
  //   //std::cout << "Counter after for loop: " << counter << endl;
  //   std::cout << *cellData << endl;
  //   std::cout << *arrayID << endl;
  // #endif
  //arrayID->Delete();
  //arrayTemperature->Delete();
  return EXIT_SUCCESS;
}
