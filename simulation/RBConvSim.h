#include <iostream>
#include <string>
#include <ios>


typedef std::tuple<vectorField, scalarField, scalarField> resultsContainer;
// stores
// vectorField -> velocity Field
// scalarField -> pressure field
// scalarField -> temperature field


using namespace std;

class RBConvSim {
  public:
    RBConvSim() {}
    void setThermalConductivity(double alpha)
	{
		alpha_ = alpha;
		simulationResults_.clear();
    		setRaPr();
	}
    void setKViscosity(double nu)
	{
		nu_ = nu;
		simulationResults_.clear();
   		setRaPr();
	}
    void setDensity(double rho)
	{
		rho_ = rho;
		simulationResults_.clear();
    		setRaPr();
	}
    void setLowTemperature(double T1)
	{
		T1_ = T1;
		deltaT_ = T2_ - T1_;    
		simulationResults_.clear();
    		setRaPr();
	}
    void setHighTemperature(double T2)
	{
		T2_ = T2;
	    	deltaT_ = T2_ - T1_;    
		simulationResults_.clear();
		setRaPr();
	}
    void runSimulation()
    {
	    //OpenFOAM code here
	    
    }
	
    vector<resultsContainer> getResults()
    {
	return simulationResults_;    
    }
	
    double getRayleigh()
    {
	return Ra_;    
    }
	
    double getPrandtl()
    {
	return Pr_;
    }

  private:
    double L_; //simulation box width
    double h_; //simulation box height
    double tend_; //simulation end time
    double deltat_; // simulation time step
    
    double nu_; //kinematic viscosity
    double rho_; //density
    double T1_; //temperature at z = h
    double T2_; //temperature at z = 0
    double deltaT_; //temperature difference
    double alpha_; //volumetric coefficient of thermal expansion
    double kappa_; //thermal diffusivity
    double g = 9.81; //acceleration of gravity
    double Ra_; //Rayleigh Number
    double Pr_; //Prandtl Number
    vector<resultsContainer> simulationResults_; //results of simulation, each vector element is a time
	
    setRaPr()
    {
	Ra_ = alpha_*g*deltaT_*exp(h_,3)/(nu_*kappa_);
	Pr_ = nu_/kappa_;
    }
};
