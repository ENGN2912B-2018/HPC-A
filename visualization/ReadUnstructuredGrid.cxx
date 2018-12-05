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

#define DEBUG
// TODO: 1. Set up the color schemes               (x)
//       2. Work on multiple files                 ()
//          2.0. Create a draft animation          ()
//          2.1. Set up the interactor             ()
//          2.2. Use a widget to control the frame ()
//       3. Work on other data types               ()
//       4. Funtionalize the project               ()
/////----     Ready to release      ----/////

/////  List of input parameters  (for future development)  /////
// colorScheme: int, specify the color schemes
// min, max:    double, setting the scale and range of visualization? (TBD)
// param:       string/char, indicates which parameter to be visualized
// path:        string, indicates the path of vtk files (TBD)
// resolution:  the resolution of the simulation results (TBD)

namespace
{
//! Create a lookup table.
/*!
@param lut - An indexed lookup table.
*/
void MakeLUT(int const& colorScheme, vtkLookupTable* lut);
}


int main (int argc, char *argv[]){
  if(argc < 3){
    std::cout << "Usage: " << argv[0] <<
      "<path> <time step> [colorSecheme]" << std::endl;
    std::cout
      << "<path>: The relative path of the folder where the .vtk files are stored"
      << std::endl;
    std::cout << "<time step>: The time step of simulation." << std::endl;
    std::cout << "[colorScheme]: (OPTIONAL): The colors scheme." << std::endl;
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

  // Parsing the commandline arguments
  std::string path = argv[1]; // The path of vtk files stored
  if(path.back() != '/'){
    path.push_back('/');
  }


  int colorScheme = 0;

  if (argc == 4)
  {
    colorScheme = std::abs(atoi(argv[3]));
    colorScheme = (colorScheme > 2) ? 0 : colorScheme;
  }



  ///   Data Structres   ///
  // Create the reader for the data
  vtkSmartPointer<vtkUnstructuredGridReader> reader =
    vtkSmartPointer<vtkUnstructuredGridReader>::New();

  vtkSmartPointer<vtkCellData> cellData =
    vtkSmartPointer<vtkCellData>::New();

  vtkSmartPointer<vtkIntArray> arrayID =
    vtkSmartPointer<vtkIntArray>::New();

  vtkSmartPointer<vtkFloatArray> arrayTemperature =
    vtkSmartPointer<vtkFloatArray>::New();

  vtkSmartPointer<vtkLookupTable> lutID =
    vtkSmartPointer<vtkLookupTable>::New();

  vtkSmartPointer<vtkLookupTable> lutTemperture =
    vtkSmartPointer<vtkLookupTable>::New();

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();

  vtkSmartPointer<vtkActor> dataActor =
    vtkSmartPointer<vtkActor>::New();

  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

    std::string filenum = argv[2]; // The "number" or time step of simulation
    int filemax = std::stoi(filenum);



  for(int fileindex = 10; fileindex <= filemax; fileindex += 10 ){
      std::string filename = path + "RBConvection_" +
        std::to_string(fileindex) + ".vtk";
      std::cout << "Loading " << filename.c_str() << std::endl;
      reader->SetFileName(filename.c_str());
      reader->SetFieldDataName("attributes");
      reader->Update();

      // Achieving the Cell data

      cellData = reader->GetOutput()->GetCellData();

      // Get the array using SafeDownCast()

      //vtkAbstractArray *arrayID;
      arrayID =
        vtkIntArray::SafeDownCast(cellData->GetAbstractArray("cellID"));
      arrayID->SetName("CellID");
      int arrayIDRange[2];
      arrayID->GetValueRange(arrayIDRange); // Note: This is not GetRange()!


      //vtkAbstractArray *arrayTemperature;
      arrayTemperature =
        vtkFloatArray::SafeDownCast(cellData->GetAbstractArray("T"));
      arrayTemperature->SetName("Temperature");
      double arrayTemperatureRange[2];
      arrayTemperature->GetRange(arrayTemperatureRange);
      //int dimension = arrayID->GetNumberOfComponents();

      // Set up lookupTables


      int tableSize = std::max(resolution*resolution + 1, 400);
      lutID->SetNumberOfTableValues(tableSize);
      lutID->SetTableRange(arrayIDRange[0], arrayIDRange[1]);
      lutID->Build();


      lutTemperture->SetNumberOfTableValues(tableSize);
      // Set up the color scheme
      MakeLUT(colorScheme, lutTemperture);
      lutTemperture->SetTableRange(arrayTemperatureRange[0], arrayTemperatureRange[1]);
      lutTemperture->Build();


      //  lutTemperture->SetTableValue
      //    (arrayTemperatureRange[0], colors->GetColor4d("Tomato").GetData());
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

       mapper->SetInputConnection(temperaturePlane->GetOutputPort());
       mapper->SetScalarRange(arrayTemperatureRange[0], arrayTemperatureRange[1]);
       mapper->SetLookupTable(lutTemperture);


      dataActor->SetMapper(mapper);


      ren->AddActor(dataActor);
      ren->SetBackground(colors->GetColor3d("SlateGray").GetData());


      renWin->AddRenderer(ren);
      renWin->SetSize(800, 800);


      iren->SetRenderWindow(renWin);
      renWin->Render();
      std::this_thread::sleep_for(std::chrono::seconds(1));
      //iren->Start();
    }
  // #ifdef DEBUG
  //   //std::cout << "Counter after for loop: " << counter << endl;
  //   std::cout << *cellData << endl;
  //   std::cout << *arrayID << endl;
  // #endif
  //arrayID->Delete();
  //arrayTemperature->Delete();
  return EXIT_SUCCESS;
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
