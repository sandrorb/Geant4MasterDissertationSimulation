#include "MyUtils.hh"
#include "G4UserLimits.hh"


/* ++++++++   Singleton	begin ++++++++ */
MyUtils* MyUtils::instance = NULL;

MyUtils* MyUtils::getInstance() {
	if (!instance) {
		instance = new MyUtils();
	};
	return instance;
}
/* ++++++++   Singleton	end ++++++++ */



MyUtils::MyUtils() {

}

void MyUtils::setup(){

//		if (caseNumber == NULL) {
//			caseNumber = 0;
//			G4cout << "\n\n\n\nCase Number is 0\n\n\n\n";
//		}

		cases = new SimulationCase();
		mySimCases = cases->getCases();
		G4cout << "\n\n\n\nCase Number is 0\n\n\n\n";
	//	MyMaterial * myMat = new MyMaterial;
	//	beryllium = myMat->getBeryllium();
	//	molybdenum = myMat->getMolybdenum();
	//	berylliumDensity = beryllium->GetDensity();   // 1.848*g/cm3;
	//	molybdenumDensity = molybdenum->GetDensity(); //10.28*g/cm3;
	//
	//	RoBerylliumElecton0521MeV = 0.224*g/cm2;
	//	RoBerylliumElecton1033MeV = 0.554*g/cm2;
	//
	//	RoMolybdenumElecton05MeV = 0.281*g/cm2;
	//	RoMolybdenumElecton10MeV = 0.673*g/cm2;

	//	energy = 1.0*MeV;
	//	energy = 0.5*MeV;
		energy = mySimCases[caseNumber]->getEnergy();

	//	energy = mySimCases[caseNumber]->getEnergy();
		deltaZ = 0.02;				// = divide the CSDA in 50 slices
		maxStep = 0.2 * deltaZ;		// = 20% of the slice thickness

	//	phantomMaterial = myMat->getMolybdenum();
		phantomMaterial = mySimCases[caseNumber]->getMaterial();
		csda =  calculateCSDA( mySimCases[caseNumber]->getCSDA(), mySimCases[caseNumber]->getMaterial()->GetDensity() );

	//	if (phantomMaterial->GetName() == "Molybdenum") {
	//		if (energy == 0.5*MeV) {
	//			csda = calculateCSDA(RoMolybdenumElecton05MeV, molybdenumDensity);
	//		} else {
	//			if (energy == 1.0*MeV) {
	//				csda = calculateCSDA(RoMolybdenumElecton10MeV, molybdenumDensity);
	//			} else {
	//				G4cout << "\n\n\nNOT == Known energy!!!\n\n\n";
	//			}
	//		}
	//
	//	} else {
	//		if (phantomMaterial->GetName() == "Beryllium") {
	//				if (energy == 0.521*MeV) {
	//					csda = calculateCSDA(RoBerylliumElecton0521MeV, berylliumDensity);
	//				} else {
	//					if (energy == 1.033*MeV) {
	//						csda = calculateCSDA(RoBerylliumElecton1033MeV, berylliumDensity);
	//					} else {
	//						G4cout << "\n\n\nNOT - Known energy!!!\n\n\n";
	//					}
	//				}
	//
	//		} else {
	//			G4cout << "\n\n\nNOT Known Material!!!\n\n\n";
	//		}
	//	}

		// 0.2 * 0.02 = 0.004
		myMaxStepLimit = new G4UserLimits(maxStep * csda);

}


G4double MyUtils::calculateCSDA(G4double Ro, G4double density){
	return (Ro / density);
}

G4UserLimits* MyUtils::getMyMaxStepLimit(){
	return this->myMaxStepLimit;
}

G4Material* MyUtils::getPhantomMaterial(){
	return this->phantomMaterial;
}

G4double MyUtils::getCSDA(){
	return this->csda;
}

G4double MyUtils::getEnergy(){
	return this->energy;
}

G4double MyUtils::getDeltaZ(){
	return this->deltaZ;
}

G4double MyUtils::getMaxStep(){
	return this->maxStep;
}

void MyUtils::printInfo(){
	MyUtils* myUtils = MyUtils::getInstance();
	G4cout << "\n\n\n\n\n";
	G4cout << "         Material : " << myUtils->getPhantomMaterial()->GetName() << G4endl;
	G4cout << "           Energy : " << myUtils->getEnergy()/MeV << " MeV"<< G4endl;
	G4cout << "        CSDA (Ro) : " << myUtils->getCSDA()/cm << " cm" << G4endl;
	G4cout << "  Max Step Length : " << (myUtils->getMaxStep() * myUtils->getCSDA())/cm << " cm" << G4endl;
	G4cout << "\n\n\n\n\n";
}

G4int MyUtils::getCaseNumber(){
	return this->caseNumber;
}

void MyUtils::setCaseNumber(G4int caseNumber){
	this->caseNumber = caseNumber;
	setup();
}



