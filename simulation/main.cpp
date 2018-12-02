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
	cout << "Instantiate Simulation Object (automatically checks setters)" << endl;
	RBConvSim test;
	cout << "Instantiation Successful" << endl;	

	cout << "Run Simulation" << endl;
	test.runSimulation();
	cout << "Simulation Successful" << endl;
	return 0;
}
