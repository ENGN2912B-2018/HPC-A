#include <string>
#include <ios>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <cmath>

using namespace std;

class RBConvSim {
  public:
    //Constructors
    RBConvSim()
    {
	system("cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection");
	//set parameters in simulation based on default
        //setNu(10e-6);
	//setBeta(1);
	//setTFloor(340);
	//setTCeil(280);
	//setPr(1);
    }
    //Destructor
    ~RBConvSim() {};
	
    //Setters
    void setBeta(double beta)
	{
		beta_ = beta;
	    //modify file
		update();
	        return;
	}
    
    void setNu(double nu)
	{
		nu_ = nu;
		string command;
		command = "cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection/constant && set 1 " + to_string(nu);
		system(command.c_str());
		system("cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection/constant && rm transportProperties && mv transportProperties0 transportProperties");
		update();
	        return;
	}
    void setTFloor(double TFloor)
	{
		TFloor_ = TFloor;
	    //modify file
		update();
	        return;
	}
    void setPr(double Pr)
	{
		Pr_ = Pr;
	    //modify file
		update();
	        return;
	}
	
    //Getters
     double getBeta()
	{
		return beta_;
	}
     double getNu()
	{
		return nu_;
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
	    system("buoyantBoussinesqPimpleFoam");
	    simRun_ = true;
        }
	
    vector<vector<double> > getTfield();
    vector<vector<vector<double> > > getUfield();

  private:
    //DO NOT CHANGE
    double L_ = 1; //simulation box width
    double h_ = 1; //simulation box height
    double TCeil_ = 280; // temperature at y = h;
    double horzmesh_ = 20;
    double vertmesh_ = 20;
    double meshsize_ = 400;
    double tend_ = 2000; //simulation end time
    double deltat_ = 20; // simulation time step
    double g = 9.81; // acceleration of gravity

    //CHANGED BY PROGRAM
    double Ra_; //Rayleigh Number
    double deltaT_; //temperature difference
    vector<vector<double> > Tfield_; //scalar x space x time
    vector<vector<vector<double> > > Ufield_; //3D vector x space x time
    bool simRun_ = false;

    //CHANGED DIRECTLY BY USER
    double nu_; //kinematic viscosity
    double TFloor_; //temperature at y = 0   
    double beta_; //thermal expansion coefficient
    double Pr_; //Prandtl Number

    void update()
	{
	    Ra_ = Pr_*beta_*g*deltaT_*pow(h_,3)/pow(nu_,2);
	    deltaT_ = TFloor_ - TCeil_;
	    system("cd $FOAM_RUN/tutorials/heatTransfer/buoyantBoussinesqPimpleFoam/RBConvection");
	    system("foamListTimes -rm");
	    Tfield_.clear();
	    Ufield_.clear();
	    simRun_ = false;
	}
};
/*
    vector<vector<double> > RBConvSim::getTfield()
        {
	if (!simRun_)
	    {
		//some kind of exception
	    }
	if Tfield_.empty()
	    {
	        //get data from file
	    }
	return Tfield;
        }

    vector<vector<vector<double> > > RBConvSim::getUfield()
        {
 	
        if (!simRun_)
	    {
		//some kind of exception
	    }
	if Ufield_.empty()
	    {
	        //get data from file
	    }
	return Ufield;
        }
        }
*/
