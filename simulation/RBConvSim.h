#include <iostream>
#include <string>
#include <ios>
#include <stdlib.h> 
#include <boost/filesystem.hpp>
#include <exception>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

namespace fs = boost::filesystem;
using namespace std;

class RBConvSim {
  public:
    //Constructors
    RBConvSim()
    {
    	system("source $FOAM_INST_DIR/OpenFOAM-4.1/etc/bashrc")
    	//set parameters in simulation based on defaults
        setNu();
	setBeta();
	setTFloor();
	setTCeil();
	setPr();
    }
    //Destructor
    ~RBConv() {};
	
    //Setters
    void setBeta(double beta = beta_)
	{
		beta_ = beta;
	    //modify file
		update();
	        return;
	}
    
    void setNu(double nu = nu_)
	{
		nu_ = nu;
	    // modify file
		update();
	        return;
	}
    void setTFloor(double TFloor = TFloor_)
	{
		TFloor_ = TFloor;
	    //modify file
    		update();
	        return;
	}
    void setTCeil(double TCeil = TCeil_)
	{
		TCeil_ = TCeil;
	    //modify file
		update();
	        return;
	}
    void setPr(double Pr = Pr_)
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
		return Nu_;
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
	    system("cd "+ casedir_);
	    system("bouyantBoussinesqPimpleFoam");
	    system("cd -");
	    simRun_ = true;
        }
	
    vector<vector<double> > getTfield();
    vector<vector<vector<double> > > getUfield();

  private:
    //DO NOT CHANGE
    double L_ = 1; //simulation box width
    double h_ = 1; //simulation box height
    double horzmesh_ = 20;
    double vertmesh_ = 20;
    double meshsize_ = 400;
    double tend_ = 2000; //simulation end time
    double deltat_ = 20; // simulation time step
    double g = 9.81; // acceleration of gravity
    string casedir_ = "$FOAM_RUN/tutorials/heatTransfer/bouyantBoussinesqPimpleFoam/RBConvection";

    //CHANGED BY PROGRAM
    double Ra_; //Rayleigh Number
    double deltaT_; //temperature difference
    vector<vector<double> > Tfield_; //scalar x space x time
    vector<vector<vector<double> > > Ufield_; //3D vector x space x time
    bool simRun_ = false;

    //CHANGED DIRECTLY BY USER
    //default values
    double nu_; //kinematic viscosity
    double TCeil_; //temperature at z = h
    double TFloor_; //temperature at z = 0
    double beta_; //thermal expansion coefficient
    double Pr_; //Prandtl Number

    void update()
	{
	    Ra_ = Pr_*alpha_*g*deltaT_*exp(h_,3)/exp(nu_,2);
	    deltaT_ = TFloor_ - TCeil_;
	    system("cd " + casedir_);
	    system("foamListTimes -rm");
	    system("cd -");
	    Tfield_.clear();
	    Ufield_.clear();
	    simRun_ = false;
	}
};

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
