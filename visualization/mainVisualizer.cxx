#include "VTKReader.h"
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>

//#define MULTI
#define DEBUG
void visualizerScript(RBVisualizer& testReader, bool isVideoSave);
int main(int argc, char const *argv[]) {
  int colorScheme = 2;
  int resolutionX = 100;
  int resolutionY = 50;
  std::string filePath = "C:\\Users\\Angio\\Documents\\Github-Repo\\RBC_Pr0.100000_Ra100000000000.000000";
  //RBC_Pr0.100000_Ra10000000.000000
  std::string parameterCode = "T";
  int timeStep = 2;	
  int timeMax = 2000;
  bool isVideoSave = true;
  
  try {
	  RBVisualizer testReader(colorScheme, resolutionX, resolutionY, filePath, parameterCode,
		  timeStep, timeMax);
	  testReader.readParameterMinMax();
	  visualizerScript(testReader, isVideoSave);
  }
  catch(const fileNotExistError &eFNE){
	  std::cerr << "fileNotExistError caught in " << filePath << " : "
		  << eFNE.what() << std::endl;
	  std::cerr << "The file we tried to access does not exist. "
		  "This may happen when you entered a wrong timeStep. " << std::endl;
	  std::cerr << "The timeStep could be the multiple of the actual time step." << std::endl;
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

void visualizerScript(RBVisualizer& testReader, bool isViedoSave) {
	if (isViedoSave ==  true) {
		RendererVector rendererOutput = testReader.mainVisualizer();
		vtkSmartPointer<vtkRenderWindow> renWin =
			vtkSmartPointer<vtkRenderWindow>::New();
		vtkSmartPointer<vtkWindowToImageFilter> w2i =
			vtkSmartPointer<vtkWindowToImageFilter>::New();
		vtkSmartPointer<vtkAVIWriter> writer =
			vtkSmartPointer<vtkAVIWriter>::New();
		renWin->AddRenderer(*rendererOutput.cbegin());
		renWin->SetSize(testReader.getResolutionX() * 8, 
			testReader.getResolutionY() * 8);
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

