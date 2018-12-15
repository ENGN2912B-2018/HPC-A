#include "VTKReader.h"
//#define MULTI
int main(int argc, char const *argv[]) {
  int colorScheme = 1;
  int resolutionX = 100;
  int resolutionY = 50;
  std::string filePath = "C:\\Users\\Angio\\Documents\\Github-Repo\\HPC-A\\RBConvection\\VTK";
  std::string parameterCode = "T";
  int timeStep = 20;
  int timeMax = 2000;
  RBVisualizer testReader(colorScheme, resolutionX, resolutionY, filePath, parameterCode,
            timeStep, timeMax);
  testReader.readParameterMinMax();
  testReader.setParameterMin(280);
  //testReader.mainVisualizer();
  RendererVector rendererOutput = testReader.mainVisualizer();
  vtkSmartPointer<vtkRenderWindow> renWin =
	  vtkSmartPointer<vtkRenderWindow>::New();
  for (auto it = rendererOutput.cbegin(); it != rendererOutput.cend(); it++) {
#ifdef MULTI
	  std::cout << "Current ren: " << *it << std::endl;
#endif
	  renWin->AddRenderer(*it);
	  renWin->SetSize(400, 400);
	  renWin->Render();
	  std::this_thread::sleep_for(std::chrono::milliseconds(40));
  }
  return EXIT_SUCCESS;
}
