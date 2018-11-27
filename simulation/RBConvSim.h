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
    RBConvSim() {}
    void setBeta(double beta)
	{
		beta_ = beta;
		simulationResults_.clear();
    		setRaPr();
	}
    void setNu(double nu)
	{
		nu_ = nu;
		simulationResults_.clear();
   		setRaPr();
	}
    void setTFloor(double TFloor)
	{
		TFloor_ = TFloor;
		deltaT_ = TFloor_ - TCeil_;    
		simulationResults_.clear();
    		setRaPr();
	}
    void setTCeil(double TCeil)
	{
		TCeil_ = TCeil;
	    	deltaT_ = TFloor_ - TCeil_;    
		simulationResults_.clear();
		setRaPr();
	}
	
    void getBeta()
	{
		beta_ = beta;
		simulationResults_.clear();
    		setRaPr();
	}
    void getNu()
	{
		nu_ = nu;
		simulationResults_.clear();
   		setRaPr();
	}
    void getTFloor()
	{
		TFloor_ = TFloor;
		deltaT_ = TFloor_ - TCeil_;    
		simulationResults_.clear();
    		setRaPr();
	}
    void getTCeil()
	{
		TCeil_ = TCeil;
	    	deltaT_ = TFloor_ - TCeil_;    
		simulationResults_.clear();
		setRaPr();
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
	    system("bouyantBoussinesqPimpleFoam -case $FOAM_RUN/tutorials/heatTransfer/bouyantBoussinesqPimpleFoam/RBConvection");
	    
    }
	
    vector<resultsContainer> getResults()
    {
	return simulationResults_;
    }
	


  private:
    double L_; //simulation box width
    double h_; //simulation box height
    double tend_; //simulation end time
    double deltat_; // simulation time step
    
    double nu_; //kinematic viscosity
    double T1_; //temperature at z = h
    double T2_; //temperature at z = 0
    double deltaT_; //temperature difference
    double beta_; //thermal expansion coefficient
    double Pr_; //Prandtl Number
    double Ra_; //Rayleigh Number
    vector<resultsContainer> simulationResults_; //results of simulation, each vector element is a time
	
    setRaPr()
    {
	Ra_ = alpha_*g*deltaT_*exp(h_,3)/(nu_*kappa_);
	Pr_ = nu_/kappa_;
    }
};
