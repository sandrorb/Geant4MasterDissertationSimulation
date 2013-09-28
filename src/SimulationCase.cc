//#include "globals.hh"
#include "G4Material.hh"
#include "SimulationCase.hh"

//std::vector<SimulationCase*> SimulationCase::mySimCases(4);

//bool SimulationCase::setup(){
//	SimulationCase::mySimCases.push_back(new SimulationCase(new G4Material("Beryllium", 4.0, 9.012182*g/mole, 1.8480*g/cm3), 0.521*MeV,  0.224*g/cm2));
//	SimulationCase::mySimCases.push_back(new SimulationCase(new G4Material("Beryllium", 4.0, 9.012182*g/mole, 1.8480*g/cm3), 1.033*MeV, 0.554*g/cm2));
//	SimulationCase::mySimCases.push_back(new SimulationCase(new G4Material("Molybdenum", 42.0, 95.96*g/mole, 10.28*g/cm3), 0.5*MeV, 0.281*g/cm2));
//	SimulationCase::mySimCases.push_back(new SimulationCase(new G4Material("Molybdenum", 42.0, 95.96*g/mole, 10.28*g/cm3), 1.0*MeV, 0.673*g/cm2));
//	G4cout << "\n\n\n\nDentro de setup()\n\n\n\n";
//	return true;
//}



SimulationCase::SimulationCase(){
	mySimCases.push_back(new SimulationCase(new G4Material("Beryllium",   4.0,  9.012182*g/mole,  1.8480*g/cm3), 0.521*MeV, 0.224*g/cm2));
	mySimCases.push_back(new SimulationCase(new G4Material("Beryllium",   4.0,  9.012182*g/mole,  1.8480*g/cm3), 1.033*MeV, 0.554*g/cm2));
	mySimCases.push_back(new SimulationCase(new G4Material("Molybdenum", 42.0, 95.960000*g/mole, 10.2800*g/cm3), 0.500*MeV, 0.281*g/cm2));
	mySimCases.push_back(new SimulationCase(new G4Material("Molybdenum", 42.0, 95.960000*g/mole, 10.2800*g/cm3), 1.000*MeV, 0.673*g/cm2));
//	numberOfEvents = 1000000;
}

SimulationCase::SimulationCase(G4Material* material, G4double energy, G4double csda){
	this->material = material;
	this->energy = energy;
	this->csda = csda;
}

std::vector<SimulationCase*> SimulationCase::getCases(){
	return this->mySimCases;
}

G4Material* SimulationCase::getMaterial(){
	return this->material;
}

G4double SimulationCase::getEnergy(){
	return this->energy;
}

G4double SimulationCase::getCSDA(){
	return this->csda;
}


