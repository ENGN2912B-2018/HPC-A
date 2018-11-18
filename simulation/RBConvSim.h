#include <iostream>
#include <string>
#include <ios>


typedef std::tuple<vectorField, scalarField> resultsContainer;
// stores
// vectorField 	-> velocity Field
// scalarField -> temperature field


using namespace std;

class RBConvSim {
  public:
    void setViscosity(double mu)
	{
		mu_ = mu;
		simulationResults_.clear();
	}

  private:
    double L_; //simulation box width
    double h_; //simulation box height
    double tend_; //simulation end time
    double deltat_; // simulation time step
    
    double mu_; //viscosity
    double rho_; //density
    double T1_; //temperature at z = 0
    double T2_; //temperature at x = h
    double deltaT_; //temperature difference
    
    vector<resultsContainer> simulationResults_; //results of simulation, each vector element is a time
};
