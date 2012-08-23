/*
 * SrBRandom.h
 *
 *  Created on: Apr 5, 2011
 *      Author: sandro
 */

#ifndef SRBRANDOM_HH_
#define SRBRANDOM_HH_

#ifndef randomize_h
#define randomize_h 1

	#include <CLHEP/Random/Randomize.h>

	#include <CLHEP/Random/RandGaussQ.h>
	#include <CLHEP/Random/RandGaussT.h>
	#include <CLHEP/Random/RandPoissonQ.h>
	#include <CLHEP/Random/RandPoissonT.h>
	#include <CLHEP/Random/RandLandau.h>
	#include <CLHEP/Random/RandBit.h>

	#define G4RandGauss RandGaussQ
	//#define G4UniformRand() HepRandom::getTheEngine()->flat()
	#define 	G4UniformRand()   CLHEP::HepRandom::getTheEngine()->flat()
#endif // randomize_h

class SrBRandom {

public:
	double getRandomNumber();
	SrBRandom();
	virtual ~SrBRandom();
};

#endif /* SRBRANDOM_H_ */
