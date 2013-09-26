/*
 * MyMaterial.cc
 *
 *  Created on: Aug 30, 2012
 *      Author: sandro
 */

#include "G4Material.hh"
#include "MyMaterial.hh"


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

	beryllium  = new G4Material("Beryllium", 4.0, 9.012182*g/mole, 1.8480*g/cm3);

	//a = 95.94*g/mole;
	//G4Element* elMo = new G4Element(name="Molybdenum", symbol="Mo", z=42., a);
	//G4Element* elMo = new G4Element("Molybdenum", "Mo", 42., a);
	//Element: Molybdenum (Mo)   Z = 42.0   N =  96.0   A =  95.96 g/mole

	//molybdenum  = new G4Material("Molybdenum", z= 42.0, a= 95.96*g/mole, density= 10.28*g/cm3);
	molybdenum  = new G4Material("Molybdenum", 42.0, 95.96*g/mole, 10.28*g/cm3);
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

G4Material* MyMaterial::getMolybdenum() {
	return this->molybdenum;
}


// Outra forma de se obter alguns outros materiais
// G4NistManager* nistMan = G4NistManager::Instance();
// G4Material* H2O = nistMan->FindOrBuildMaterial("G4_WATER");
// G4Material* Air = nistMan->FindOrBuildMaterial("G4_AIR");
