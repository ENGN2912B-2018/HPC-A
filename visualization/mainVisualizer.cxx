#include "VTKReader.h"
#ifdef _WIN32
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>
#endif

//#define MULTI
#define DEBUG
#ifdef _WIN32
void visualizerScript(RBVisualizer& testReader, bool isVideoSave);
#else
void visualizerScript(RBVisualizer& testReader);
#endif
int main(int argc, char const *argv[]) {

	int colorScheme = 2;
	std::string filePath = "C:\\Users\\Angio\\Documents\\Github-Repo\\RBC_Pr0.100000_Ra100000000000.000000";
	std::string parameterCode = "T";
	int timeStep = 2;
	int timeMax = 2000;
#ifdef _WIN32
	bool isVideoSave = true;
#endif
	std::cout << "=====		2D Rayleigh-B¨¦nard Convection Visualizer	=====" << std::endl;
	std::cout << "Developed by Yang Jiao, Yiming Li and Kit Sum Wu" << std::endl;
	std::cout << "\n\nEnter 0 to use the default parameter set." << std::endl;
	std::cout << "(The default set is only used in debugging, will NOT work on other systems): ";
	int parameterSet;
	std::cin >> parameterSet;
	if (parameterSet == 0) {
		// Do nothing
	}
	else {
		std::cout << "Enter the path of your .vtk files: ";
		std::cin >> filePath;
		std::cout << "Enter the parameter code. " << std::endl;
		std::cout << "0 for temperature, and others for velocity magnitude: ";
		int paraCode = 0;
		std::cin >> paraCode;
		if (paraCode == 0)
			parameterCode = "T";
		else
			parameterCode = "mag(U)";
		std::cout << "Enter the time step: ";
		std::cin >> timeStep;
		std::cout << "Enter the maximal time of simulation: ";
		std::cin >> timeMax;
#ifdef _WIN32
		std::cout << "Do you want to save the video?" << std::endl;
		std::cout << "Enter 0 to save, others not to save: ";
		int isSave;
		std::cin >> isSave;
		if (isSave == 0)
			isVideoSave = true;
		else
			isVideoSave = false;
#endif
	}


	int resolutionX = 100;
	int resolutionY = 50;
 
  
  try {
	  RBVisualizer testReader(colorScheme, resolutionX, resolutionY, filePath, parameterCode,
		  timeStep, timeMax);
	  testReader.readParameterMinMax();
#ifdef _WIN32
	  visualizerScript(testReader, isVideoSave);
#else
	  visualizerScript(testReader);
#endif
  }
  catch(const fileNotExistError &eFNE){
	  std::cerr << "fileNotExistError caught in " << filePath << " : "
		  << eFNE.what() << std::endl;
	  std::cerr << "The file we tried to access does not exist. "
		  "This may happen when you entered a wrong timeStep or timeMax. " << std::endl;
	  std::cerr << "The timeStep could be the multiple of the actual time step." << std::endl;
	  std::cerr << "Current timeStep: " << timeStep << std::endl;
	  std::cerr << "Current timeMax: " << timeMax << std::endl;
	  return EXIT_FAILURE;
  }
  catch (const pathNotExistError &ePNE) {
	  std::cerr << "pathNotExistError caught in " << filePath << " : "
		  << ePNE.what() << std::endl;
	  std::cerr << "The path you entered does not exist. "
		  "Make sure you have downloaded and unzipped the results." << std::endl;
	  return EXIT_FAILURE;
  }
  catch (...) {
	  std::cerr << "Execption thrown while visualizing the results." << std::endl;
	  std::cerr << "This may happen when your computation resources are "
		  "exhausted, or system platform is incompatible." << std::endl;
	  std::cerr << "Try it again later, or contact us at our Github Issues page: "
		  << std::endl;
	  std::cerr << "https://github.com/ENGN2912B-2018/HPC-A/issues" << std::endl;
	  return EXIT_FAILURE;
  }
 
  return EXIT_SUCCESS;
}
#ifdef _WIN32
void visualizerScript(RBVisualizer& testReader, bool isViedoSave) {
	if (isViedoSave ==  true) {
		RendererVector rendererOutput = testReader.mainVisualizer();
		vtkSmartPointer<vtkRenderWindow> renWin =
			vtkSmartPointer<vtkRenderWindow>::New();
		// Set up the filter
		vtkSmartPointer<vtkWindowToImageFilter> w2i =
			vtkSmartPointer<vtkWindowToImageFilter>::New();
		// The AVI writer to make a video from the render window
		// Note that the AVI writer is not supported by Linux
		vtkSmartPointer<vtkAVIWriter> writer =
			vtkSmartPointer<vtkAVIWriter>::New();
		renWin->AddRenderer(*rendererOutput.cbegin());
		renWin->SetSize(testReader.getResolutionX() * 8, 
			testReader.getResolutionY() * 8);
		// Render the first frame before the for loop
		// Or the AVI writer cannot acquire a compressor for the data
		renWin->Render();
		w2i->SetInput(renWin);
		w2i->Update();
		std::string saveName = testReader.getSavePath() + testReader.getSaveName();
		writer->SetFileName(saveName.c_str());
		writer->SetInputConnection(w2i->GetOutputPort());
		writer->SetRate(50);
		writer->SetQuality(2);
		writer->SetCompressorFourCC("MSVC");
		writer->Start();
		int frameCounter = 2;
		for (auto it = rendererOutput.cbegin() + 1; it != rendererOutput.cend(); it++) {
			renWin->AddRenderer(*it);
			renWin->SetSize(testReader.getResolutionX() * 8, 
				testReader.getResolutionY() * 8);
#ifdef DEBUG
			std::cout << "Attempting to write the video frame: " 
				<< frameCounter << std::endl;
#endif
			renWin->Render();
			w2i->Modified();
			writer->Write();


			std::this_thread::sleep_for(std::chrono::milliseconds(20));
			frameCounter++;
		}
	}
	else {
		RendererVector rendererOutput = testReader.mainVisualizer();
		vtkSmartPointer<vtkRenderWindow> renWin =
			vtkSmartPointer<vtkRenderWindow>::New();
		int frameCounter = 1;
		for (auto it = rendererOutput.cbegin() + 1; it != rendererOutput.cend(); it++) {
			renWin->AddRenderer(*it);
			renWin->SetSize(testReader.getResolutionX() * 8,
				testReader.getResolutionY() * 8);
#ifdef DEBUG
			std::cout << "Rendering the frame: "
				<< frameCounter << std::endl;
#endif
			renWin->Render();

			std::this_thread::sleep_for(std::chrono::milliseconds(20));
			frameCounter++;
		}
	}
}
#else
// Linux version
void visualizerScript(RBVisualizer& testReader) {
	RendererVector rendererOutput = testReader.mainVisualizer();
	vtkSmartPointer<vtkRenderWindow> renWin =
		vtkSmartPointer<vtkRenderWindow>::New();
	int frameCounter = 1;
	for (auto it = rendererOutput.cbegin() + 1; it != rendererOutput.cend(); it++) {
		renWin->AddRenderer(*it);
		renWin->SetSize(testReader.getResolutionX() * 8,
			testReader.getResolutionY() * 8);
#ifdef DEBUG
		std::cout << "Rendering the frame: "
			<< frameCounter << std::endl;
#endif
		renWin->Render();

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		frameCounter++;
	}
}
#endif
