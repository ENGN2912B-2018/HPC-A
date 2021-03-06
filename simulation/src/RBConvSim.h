#include <string>
#include <ios>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class RBConvSim {
  public:
    //Constructors
    RBConvSim()
    {
        // default values
	setNu(.000001);
	setBeta(.000214);
	setTFloor(340);
	setPr(7.56);
    }
    //Destructor
    ~RBConvSim() {};
	
    //Setters
        
    void setNu(double nu)
	{
		nu_ = nu;

		string command;
		command = "cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection/constant && ./set 1 " + to_string(nu);
		system(command.c_str());
		system("cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection/constant && mv transportProperties0 transportProperties");
		
		update();
		return;
	}
    
    void setBeta(double beta)
	{
		beta_ = beta;
		
		string command;
		command = "cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection/constant && ./set 2 " + to_string(beta);
		system(command.c_str());
		system("cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection/constant && mv transportProperties0 transportProperties");

		update();
	        return;
	}

    void setTFloor(double TFloor)
	{
		TFloor_ = TFloor;

                string command;
		command = "cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection/0 && ./set 3 " + to_string(TFloor);
		system(command.c_str());
		system("cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection/0 && mv T0 T");

		update();
	        return;
	}
    void setPr(double Pr)
	{
		Pr_ = Pr;

                string command;
		command = "cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection/constant && ./set 4 " + to_string(Pr);
		system(command.c_str());
		system("cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection/constant && mv transportProperties0 transportProperties");

		update();
	        return;
	}
	
    //Getters
     double getNu()
	{
		return nu_;
	}
     double getBeta()
	{
		return beta_;
	}

     double getTFloor()
	{
		return TFloor_;
	}
    double getTCeil()
	{
		return TCeil_;
	}
    double getPr()
        {
	       return Pr_;
        }
    double getdeltaT()
	{
	       return deltaT_;
	}
    double getRa()
        {
	       return Ra_;
        }

    void runSimulation()
        {
	    //system("cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection && blockMesh");
	    system("cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection && buoyantBoussinesqPimpleFoam");
	    simRun_ = true;
        }	

  private:
    //DO NOT CHANGE
    double L_ = 1; //simulation box width
    double h_ = .50; //simulation box height
    double TCeil_ = 280; // temperature at y = h;
    double horzmesh_ = 100;
    double vertmesh_ = 50;
    double meshsize_ = 5000;
    double tend_ = 2000; //simulation end time
    double deltat_ = 2; // simulation time step
    double g = 9.81; // acceleration of gravity

    //CHANGED BY PROGRAM
    double Ra_; //Rayleigh Number
    double deltaT_; //temperature difference
    bool simRun_ = false;

    //CHANGED DIRECTLY BY USER
    double nu_; //kinematic viscosity
    double TFloor_; //temperature at y = 0   
    double beta_; //thermal expansion coefficient
    double Pr_; //Prandtl Number

    void update()
	{
	    deltaT_ = TFloor_ - TCeil_;
	    Ra_ = Pr_*beta_*g*deltaT_*pow(h_,3)/pow(nu_,2);
	    system("cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection && foamListTimes -rm");
	    system("cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection && rm -rf VTK");
	    simRun_ = false;
	}
};

