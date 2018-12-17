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
int main(int argc, char const *argv[]) {
	vector<double> Prv, Rav;
	string dummy;
	int m;
	double nn;
	int Prn, Ran;
	double Beta, Nu, TFloor, Pr, Ra, deltaT;
	double g = 9.81, h = .5, TCeil = 280;
	string command, save_loc;

	cout << "Please enter the number of values of Pr to be used." << endl;
	while(true)
	{
	cin >> dummy;
	m = 0;
	for(int i = 0; i < dummy.length(); i++)
	{
	if(isalpha(dummy[i]))
	{
	       if (dummy[i] != '.')
	{
		m++;
	}
	}
	}
	if(m > 0)
	{
		cout << "Input Invalid. Please try again." << endl;
	} else
	{
		nn = stoi(dummy);
		if((nn < 0)||(fmod(nn,1)> 1e-6))
		{
		cout << "Input Invalid. Please try again." << endl;
		}
		else
		{
			Prn = stoi(dummy);
			break;
		}
	}
	}
		
	for(int i = 0; i < Prn; i++)
	{
	cout << "Please enter the desired value for Pr[" << i << "]." << endl;;
	while(true)
	{
	cin >> dummy;
	m = 0;
	for(int i = 0; i < dummy.length(); i++)
	{
	if(isalpha(dummy[i]))
	{
	       if (dummy[i] != '.')
	{
		m++;
	}
	}
	}

	if(m > 0)
	{
		cout << "Input Invalid. Please try again." << endl;
	} else
	{

		nn = stoi(dummy);
		if(nn <= 0)
		{
		cout << "Input Invalid. Please try again." << endl;
		}
		else
		{
			Prv.push_back(stoi(dummy));
			break;
		}
	}
	}
	}
	
	cout << "Please enter the number of values of Ra to be used." << endl;
	while(true)
	{
	cin >> dummy;
	m = 0;
	for(int i = 0; i < dummy.length(); i++)
	{
	if(isalpha(dummy[i]))
	{
	       if (dummy[i] != '.')
	{
		m++;
	}
	}
	}

	if(m > 0)
	{
		cout << "Input Invalid. Please try again." << endl;
	} else
	{

		nn = stoi(dummy);
		if((nn < 0)||(fmod(nn,1)> 1e-6))
		{
		cout << "Input Invalid. Please try again." << endl;
		}
		else
		{
			Ran = stoi(dummy);
			break;
		}
	}
	}
		
	for(int i = 0; i < Ran; i++)
	{
	cout << "Please enter the desired value for Ra[" << i << "]." << endl;;
	while(true)
	{
	cin >> dummy;
	m = 0;
	for(int i = 0; i < dummy.length(); i++)
	{
	if(isalpha(dummy[i]))
	{
	       if (dummy[i] != '.')
	{
		m++;
	}
	}
	}

	if(m > 0)
	{
		cout << "Input Invalid. Please try again." << endl;
	} else
	{
		nn = stoi(dummy);
		if(nn <= 0)
		{
		cout << "Input Invalid. Please try again." << endl;
		}
		else
		{
			Rav.push_back(stoi(dummy));
			break;
		}
	}
	}
	}


	cout << "Instantiate Simulation Object (automatically checks setters)" << endl;
	RBConvSim test;
	cout << "Instantiation Successful" << endl;
        command = "cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection && blockMesh";
	system(command.c_str());

	for(int i = 0; i < Prn; i++) //Pr
	{
		Pr = Prv[i];
	       	test.setPr(Pr);
	    for(int j = 0; j < Ran; j++) //Ra
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
	       	command = "cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection && cp -R -rf VTK "+ save_loc + "RBC_Pr"+to_string(Pr)+"_Ra"+ to_string(Ra);
		system(command.c_str());
	    }
	}
	return EXIT_SUCCESS;
}
