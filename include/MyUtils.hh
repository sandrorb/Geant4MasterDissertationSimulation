#ifndef MYUTILS_HH_
#define MYUTILS_HH_

#include "G4UserLimits.hh"
#include "G4Material.hh"
#include "MyMaterial.hh"

//class G4Material;
//class G4UserLimits;

class MyUtils {

	public:
		virtual ~MyUtils();
		G4double calculateCSDA(G4double Ro, G4double density);
		G4UserLimits* getMyMaxStepLimit();
		G4Material* getPhantomMaterial();
		G4double getCSDA();
		G4double getDeltaZ();
		G4double getEnergy();
		G4double getMaxStep();
		void printInfo();

/* ++++++++   Singleton	begin ++++++++ */
		static MyUtils* getInstance();
/* ++++++++   Singleton	end ++++++++ */

	private:

/* ++++++++   Singleton	begin ++++++++ */
		MyUtils();							 // Private constructor to be singleton
		// Don't write bodies
		MyUtils(const MyUtils&);             // Prevent copy-construction
		MyUtils& operator=(const MyUtils&);  // Prevent assignment

		static MyUtils* instance;
/* ++++++++   Singleton	end ++++++++ */


		G4Material* beryllium;
		G4Material* molybdenum;

		G4double berylliumDensity;
		G4double molybdenumDensity;

		G4double energy;

		G4double RoBerylliumElecton0521MeV;
		G4double RoBerylliumElecton1033MeV;

		G4double RoMolybdenumElecton05MeV;
		G4double RoMolybdenumElecton10MeV;

		G4double deltaZ;
		G4double maxStep;

		G4Material* phantomMaterial;

		G4UserLimits* myMaxStepLimit;

		G4double csda;

};

#endif /* MYUTILS_HH_ */
