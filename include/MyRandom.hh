#ifndef MYRANDOM_HH_
#define MYRANDOM_HH_

#ifndef randomize_h
#define randomize_h 1

	#include <CLHEP/Random/Randomize.h>
/*
	#include <CLHEP/Random/RandGaussQ.h>
	#include <CLHEP/Random/RandGaussT.h>
	#include <CLHEP/Random/RandPoissonQ.h>
	#include <CLHEP/Random/RandPoissonT.h>
	#include <CLHEP/Random/RandLandau.h>
	#include <CLHEP/Random/RandBit.h>
*/

	#define G4RandGauss RandGaussQ
	//#define G4UniformRand() HepRandom::getTheEngine()->flat()
	#define 	G4UniformRand()   CLHEP::HepRandom::getTheEngine()->flat()
#endif // randomize_h

class MyRandom {

public:
	double getRandomNumber();
	MyRandom();
	virtual ~MyRandom();
};

#endif /* MYRANDOM_H_ */
