#include <iostream>
#include <string>
#include <ios>
#include <stdlib.h>
#include <exception>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include "RBConvSim.h"

using namespace std;

// main function
int main() {
	double Prv [3] = {1e-1, 1, 10};
        double Rav [3] = {1e7, 1e9, 1e11};
	double Beta, Nu, TFloor, Pr, Ra, deltaT;
	double g = 9.81, h = .5, TCeil = 280;
	string command, save_loc;

	cout << "Instantiate Simulation Object (automatically checks setters)" << endl;
	RBConvSim test;
	cout << "Instantiation Successful" << endl;
        command = "cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection && blockMesh";
	system(command.c_str());

	for(int i = 0; i < 3; i++) //Pr
	{
		Pr = Prv[i];
	       	test.setPr(Pr);
	    for(int j = 0; j < 3; j++) //Ra
	    {
	        //set parameters
		Ra = Rav[j];
		Beta = test.getBeta();
		Nu = test.getNu();
	        deltaT = Ra * pow(Nu,2) / (Pr * Beta * g * pow(h,3));
		TFloor = TCeil + deltaT;
		test.setTFloor(TFloor);
		cout << "Delta T = " << test.getdeltaT() << " = " << deltaT << endl;
		cout << "Ra = " << test.getRa() << endl;

		//run simulation
		cout << "Run Simulation" << endl;
	        test.runSimulation();
	        cout << "Simulation Successful" << endl;
		//save files
		save_loc = "~/scratch/project/HPC-A/data/";
	       	command = "cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection && cp -R -rf VTK"+ save_loc + "RBC_Pr"+to_string(Pr)+"_Ra"+ to_string(Ra);
		system(command.c_str());
	    }
	}
	return 0;
}
