/*
 * MyMaterial.cc
 *
 *  Created on: Aug 30, 2012
 *      Author: sandro
 */

#include "MyMaterial.hh"
#include "G4Material.hh"
#include "G4NistManager.hh" // Useful for getting registered materials

MyMaterial::MyMaterial() {

	G4double a;  // atomic mass
	G4double z;  // atomic number
	G4double density;

	// Build Argon Gas
	argonGas = new G4Material("ArgonGas", z= 18., a= 39.95*g/mole, density= 1.782*mg/cm3);

	// Build Air
	G4Element*  elN = new G4Element("Nitrogen", "N", 7., 14.01*g/mole);
	G4Element*  elO = new G4Element("Oxygen", "O", 8., 16.00*g/mole);
	density = 1.290*mg/cm3;
	air = new G4Material("Air", density, 2);
	air->AddElement(elN, 70*perCent);
	air->AddElement(elO, 30*perCent);

	// Build Lead
	pb = new G4Material("Lead", z= 82., a= 207.19*g/mole, density= 11.35*g/cm3);

	// Build Water
	a = 1.01*g/mole;
	z = 1.;
	G4Element*  elH = new G4Element("Hydrogen", "H", z, a);
//	G4Element*  elO = new G4Element("Oxygen", "O", 8., 16.00*g/mole);
	density = 1.000*g/cm3;
	water = new G4Material("Water", density, 2);
	water->AddElement(elH, 2);
	water->AddElement(elO, 1);

	// build Beryllium
	beryllium = new G4Material("Beryllium", 4.0, 9.012182*g/mole, 1.8480*g/cm3);
	G4cout << "Berilio construido: " << beryllium->GetName() << G4endl;

	G4NistManager* man = G4NistManager::Instance();
	man->SetVerbose(1);
	vacuum = man->FindOrBuildMaterial("G4_Galactic");

	// Define materials not in NIST

	G4Element* C  = man->FindOrBuildElement("C");
	G4Element* Si = man->FindOrBuildElement("Si");
	G4Element* Cr = man->FindOrBuildElement("Cr");
	G4Element* Mn = man->FindOrBuildElement("Mn");
	G4Element* Fe = man->FindOrBuildElement("Fe");
	G4Element* Ni = man->FindOrBuildElement("Ni");

	G4double densityStainlessSteel;
	G4int ncomponents;
	G4double fractionmass;
	G4Material* stainlessSteel = new G4Material("StainlessSteel", densityStainlessSteel= 8.06*g/cm3, ncomponents=6);
	stainlessSteel->AddElement(C, fractionmass=0.001);
	stainlessSteel->AddElement(Si, fractionmass=0.007);
	stainlessSteel->AddElement(Cr, fractionmass=0.18);
	stainlessSteel->AddElement(Mn, fractionmass=0.01);
	stainlessSteel->AddElement(Fe, fractionmass=0.712);
	stainlessSteel->AddElement(Ni, fractionmass=0.09);
}

MyMaterial::~MyMaterial() {

}

G4Material* MyMaterial::getAir() {
	return this->air;
}

G4Material* MyMaterial::getArgonGas() {
	return this->argonGas;
}

G4Material* MyMaterial::getPb() {
	return this->pb;
}

G4Material* MyMaterial::getWater() {
	return this->water;
}

G4Material* MyMaterial::getBeryllium() {
	return this->beryllium;
}

G4Material* MyMaterial::getVacuum() {
	return this->vacuum;
}

G4Material* MyMaterial::getStainlessSteel() {
	return this->stainlessSteel;
}


// Outra forma de se obter alguns outros materiais
// G4NistManager* nistMan = G4NistManager::Instance();
// G4Material* H2O = nistMan->FindOrBuildMaterial("G4_WATER");
// G4Material* Air = nistMan->FindOrBuildMaterial("G4_AIR");
