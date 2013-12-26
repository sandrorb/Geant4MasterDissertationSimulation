#ifndef MYUTILS_HH_
#define MYUTILS_HH_

#include "globals.hh"
#include "G4UserLimits.hh"
#include "G4Material.hh"
//#include "MyMaterial.hh"
#include "SimulationCase.hh"

class MyUtils {

	public:

		inline ~MyUtils(){}

/* ++++++++   Singleton	begin ++++++++ */
		static MyUtils* getInstance();
/* ++++++++   Singleton	end ++++++++ */

		G4double getEnergy();
		G4double getDeltaZ();
		G4double getMaxStep();
		G4double calculateCSDA(G4double Ro, G4double density);
		G4UserLimits* getMyMaxStepLimit();
		G4Material*   getPhantomMaterial();
		G4double      getCSDA();
		void          printInfo();
		G4int		getCaseNumber();
		void	setCaseNumber(G4int);
		int	getSimulationNumber();
		void	setSimulationNumber(int);
		int	getNumberOfSimulations();
		void	setNumberOfSimulations(int);

	private:

/* ++++++++   Singleton	begin ++++++++ */
		MyUtils();							 // Private constructor to be singleton
		// Don't write bodies
		MyUtils(const MyUtils&);             // Prevent copy-construction
		MyUtils& operator=(const MyUtils&);  // Prevent assignment

		static MyUtils* instance;
/* ++++++++   Singleton	end ++++++++ */

		void setup();

//		G4Material* beryllium;
//		G4Material* molybdenum;
//
//		G4double berylliumDensity;
//		G4double molybdenumDensity;
//
//		G4double RoBerylliumElecton0521MeV;
//		G4double RoBerylliumElecton1033MeV;
//
//		G4double RoMolybdenumElecton05MeV;
//		G4double RoMolybdenumElecton10MeV;

		G4double energy;
		G4double deltaZ;
		G4double maxStep;

		G4Material* phantomMaterial;

		G4UserLimits* myMaxStepLimit;

		G4double csda;

		SimulationCase * cases;
		std::vector<SimulationCase*> mySimCases;
		G4int caseNumber;
		int simulationNumber;
		int numberOfSimulations;

};

#endif /* MYUTILS_HH_ */
