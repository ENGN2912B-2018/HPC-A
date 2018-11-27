#include <iostream>
#include <string>
#include <ios>
#include <stdlib.h> 

typedef std::tuple<vectorField, scalarField, scalarField> resultsContainer;
// stores
// vectorField -> velocity Field
// scalarField -> pressure field
// scalarField -> temperature field


using namespace std;

class RBConvSim {
  public:
    //Constructors
    RBConvSim() {}
    void setBeta(double beta)
	{
		beta_ = beta;
		simulationResults_.clear();
    		setRaPr();
	}
    //Setters
    void setNu(double nu)
	{
		nu_ = nu;
		update();
	}
    void setTFloor(double TFloor)
	{
		TFloor_ = TFloor;
    		update();
	}
    void setTCeil(double TCeil)
	{
		TCeil_ = TCeil;
		update();
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
		return TCeil_'
	}
    double getRayleigh()
        {
	       return Ra_;
        }
	
    double getPrandtl()
        {
	       return Pr_;
        }
	
    void runSimulation()
        {
	    system("cd "+ casedir_);
	    system("bouyantBoussinesqPimpleFoam");
	    system("cd -");
	    simRun_ = true;
        }
	
    vector<vector<double> > getTfield()
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

    vector<vector<vector<double> > > get Ufield()
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
    fs::path casedir_;
	
    //CHANGED BY PROGRAM
    double Ra_; //Rayleigh Number
    double deltaT_; //temperature difference
    vector<vector<double> > Tfield_; //scalar x space x time
    vector<vector<vector<double> > > Ufield_; //3D vector x space x time
    bool simRun_ = false;
	
    //CHANGED DIRECTLY BY USER
    double nu_; //kinematic viscosity
    double TCeil_; //temperature at z = h
    double TFloor_; //temperature at z = 0
    double beta_; //thermal expansion coefficient
    double Pr_; //Prandtl Number

    void update();
	{
	    Ra_ = Pr_*alpha_*g*deltaT_*exp(h_,3)/exp(nu_,2);
	    deltaT_ = TFloor_ - TCeil_;
	    system("cd "+ casedir_);
	    system("foamListTimes -rm");
	    system("cd -");
	    Tfield_.clear();
	    Ufield_.clear();
	    simRun_ = false
	}
};
