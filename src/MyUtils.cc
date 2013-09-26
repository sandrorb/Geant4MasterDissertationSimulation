#include "MyUtils.hh"
#include "MyMaterial.hh"
#include "G4UserLimits.hh"

MyUtils::MyUtils() {
	MyMaterial * myMat = new MyMaterial;
	beryllium = myMat->getBeryllium();
	molybdenum = myMat->getMolybdenum();

	berylliumDensity = beryllium->GetDensity();   // 1.848*g/cm3;
	molybdenumDensity = molybdenum->GetDensity(); //10.28*g/cm3;

	RoBerylliumElecton0521MeV = 0.224*g/cm2;
	RoBerylliumElecton1033MeV = 0.554*g/cm2;

	RoMolybdenumElecton05MeV = 0.281*g/cm2;
	RoMolybdenumElecton10MeV = 0.673*g/cm2;

	deltaZ = 0.02;				// = divide the CSDA in 50 slices
	maxStep = 0.2 * deltaZ;		// = 20% of the slice thickness
	csda = calculateCSDA(RoMolybdenumElecton10MeV, molybdenumDensity);
	// 0.2 * 0.02 = 0.004
	myMaxStepLimit = new G4UserLimits(maxStep * csda);

	phantomMaterial = getPhantomMaterial(new MyMaterial);

}

G4double MyUtils::calculateCSDA(G4double Ro, G4double density){
	return (Ro / density);
}

G4Material* MyUtils::getPhantomMaterial(MyMaterial* myMaterial){
	//return myMaterial->getBeryllium();
	return myMaterial->getMolybdenum();
}

G4Material* MyUtils::getPhantomMaterial(){;
	return this->phantomMaterial;
}

G4UserLimits* MyUtils::getMyMaxStepLimit(){
	return this->myMaxStepLimit;
}

G4double MyUtils::getDeltaZ(){
	return this->deltaZ;
}

G4double MyUtils::getCSDA(){
	return this->csda;
}

MyUtils::~MyUtils() {
   //G4cout << "Destrutor de MyUtils" << G4endl;
}


