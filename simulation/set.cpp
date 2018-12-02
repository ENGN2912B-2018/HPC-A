#include <iostream>
#include <string>
#include <ios>
#include <stdlib.h>
#include <vector>
#include <regex>
#include <cmath>
#include <cctype>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	
	int param = atoi(argv[1]);
	double value = atof(argv[2]); 
	switch (param) {
	case 1: //Nu
		{
		char str[100];
		ifstream filein("transportProperties");
		ofstream fileout("transportProperties0");
		while(filein)
		{
		filein.getline(str, 100,'\n');
		cout << str << endl;
	      	}

		fileout.close();
		}
		break;
	case 2: //Beta
		{}
		break;
	case 3: //TFloor
		{}
		break;
	case 4: //Pr:
		{}
		break;
}
	return 0;
}
