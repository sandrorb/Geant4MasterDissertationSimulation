#ifndef SIMULATIONCASE_HH_
#define SIMULATIONCASE_HH_

#include "globals.hh"
#include "G4Material.hh"


class SimulationCase {

	public:

		SimulationCase();
		~SimulationCase();

		G4Material* getMaterial();
		G4double getEnergy();
		G4double getCSDA();

	    std::vector<SimulationCase*> getSimulationCases();

		G4Material* material;
		G4double energy;
		G4double csda;
//		G4int numberOfEvents;

		std::vector<SimulationCase*> mySimCases;
		std::vector<SimulationCase*> getCases();

		SimulationCase(G4Material* material, G4double energy, G4double csda);

};


#endif /* SIMULATIONCASE_HH_ */

