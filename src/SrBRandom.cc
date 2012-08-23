/*
 * SrBRandom.cpp
 *
 *  Created on: Apr 5, 2011
 *      Author: sandro
 */

#include "SrBRandom.hh"

double SrBRandom::getRandomNumber(){
	//G4cout << "Numero aleatorio: " << G4UniformRand() << G4endl;
	return G4UniformRand();
}

SrBRandom::SrBRandom() {


}

SrBRandom::~SrBRandom() {
	// TODO Auto-generated destructor stub
}
