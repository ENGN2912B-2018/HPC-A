#include "VTKReader.h"

int main(int argc, char const *argv[]) {
  int colorScheme = 1;
  int resolutionX = 40;
  int resolutionY = 40;
  std::string filePath = "../../RBConvection/VTK";
  std::string parameterCode = "T";
  int timeStep = 100;
  int timeMax = 2000;
  RBVisualizer testReader(colorScheme, resolutionX, resolutionY, filePath, parameterCode,
            timeStep, timeMax);
  testReader.readParameterMinMax();
  testReader.setParameterMin(280);
  testReader.mainVisualizer();
  return EXIT_SUCCESS;
}
