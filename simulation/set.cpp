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
	
	switch (param) {
	case 1: //Nu
		{
		cout << "setting nu" << endl;
		char str[100];
		ifstream filein("transportProperties");
		ofstream fileout("transportProperties0");
		while(filein)
		{
		    filein.getline(str, 100,'\n');
		    if (str[0] == 'n')
		    {
		        fileout << "nu [0 2 -1 0 0 0 0] " << argv[2] << ";" << endl;
		    } else { 
		        fileout << str << endl;
	      	    }
		}
		fileout.close();
		}
		break;
	case 2: //Beta
		{
		cout << "setting beta" << endl;
		char str[100];
		ifstream filein("transportProperties");
		ofstream fileout("transportProperties0");
		while(filein)
		{
		    filein.getline(str, 100,'\n');
		    if (str[0] == 'b')
		    {
		        fileout << "beta [0 0 0 -1 0 0 0] " << argv[2] << ";" << endl;
		    } else { 
		        fileout << str << endl;
	      	    }
		}
		fileout.close();
		}
		break;
	case 3: //TFloor
		{
		cout << "setting TFloor" << endl;
		char str[100];
		ifstream filein("T");
		ofstream fileout("T0");
		while(filein)
		{
		    filein.getline(str, 100,'\n');
		    if ((str[4] == 'f') && (str[5] == 'l'))
		    {
		        fileout << str << endl; //floor
			
			filein.getline(str, 100,'\n');
			fileout << str << endl; // {
			
			filein.getline(str, 100,'\n');
                        fileout << str << endl; // type

			filein.getline(str,100,'\n');
			fileout << "        value           uniform ";
			fileout	<< argv[2] << ";" << endl; //value
		    } else { 
		        fileout << str << endl;
	      	    }
		}
		fileout.close();
		}
		break;
	case 4: //Pr:
		{
		cout << "setting Pr" << endl;
		char str[100];
		ifstream filein("transportProperties");
		ofstream fileout("transportProperties0");
		while(filein)
		{
		    filein.getline(str, 100,'\n');
		    if ((str[0] == 'P')  && (str[2] == ' ')) {
		        fileout << "Pr [0 0 0 0 0 0 0] " << argv[2] << ";" << endl;
		    } else { 
		        fileout << str << endl;
	      	    }
		}
		fileout.close();
		}
		break;
}
	cout << "set successful" << endl;
	return 0;
}
