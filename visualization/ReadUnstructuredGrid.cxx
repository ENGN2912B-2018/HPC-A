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
#include <vtkScalarsToColors.h>
#include <vtkVariant.h>
#include <vtkVariantArray.h>

#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkNamedColors.h>
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
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

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

  // Get the array?
  vtkSmartPointer<vtkIntArray> arrayID =
    vtkSmartPointer<vtkIntArray>::New();
  //vtkAbstractArray *arrayID;
  arrayID =
    vtkIntArray::SafeDownCast(cellData->GetAbstractArray("cellID"));
  arrayID->SetName("CellID");
  int arrayIDRange[2];
  arrayID->GetValueRange(arrayIDRange);
  vtkSmartPointer<vtkFloatArray> arrayTemperature =
    vtkSmartPointer<vtkFloatArray>::New();

  //vtkAbstractArray *arrayTemperature;
  arrayTemperature =
    vtkFloatArray::SafeDownCast(cellData->GetAbstractArray("T"));
  arrayTemperature->SetName("Temperature");
  double arrayTemperatureRange[2];
  arrayTemperature->GetRange(arrayTemperatureRange);
  //int dimension = arrayID->GetNumberOfComponents();

  // Set up a lookupTable
  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();

  #ifdef DEBUG
    std::cout << "Hello!" << endl;
    std::cout << "Range of arrayID: " << arrayIDRange[0]
      << " " << arrayIDRange[1] << endl;
    std::cout << "Range of arrayTemperature: " << arrayTemperatureRange[0]
      << " " << arrayTemperatureRange[1] << endl;
  #endif


  /////     Data manipulation ends here     /////

  // Connect with a Mapper
   vtkSmartPointer<vtkDataSetMapper> dataMapper =
     vtkSmartPointer<vtkDataSetMapper>::New();
   dataMapper->SetInputConnection(reader->GetOutputPort());

   vtkSmartPointer<vtkActor> dataActor =
    vtkSmartPointer<vtkActor>::New();
  dataActor->SetMapper(dataMapper);

  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  ren->SetBackground(0, 1, 0);
  ren->AddActor(dataActor);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  renWin->SetSize(300, 300);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
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
