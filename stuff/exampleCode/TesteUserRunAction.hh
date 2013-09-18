
#ifndef TESTEUSERRUNACTION_HH_
#define TESTEUSERRUNACTION_HH_

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class TesteUserRunAction : public G4UserRunAction {

	public:
		TesteUserRunAction();
		virtual ~TesteUserRunAction();

		 virtual G4Run* GenerateRun();
		 void BeginOfRunAction(const G4Run*);
		 void EndOfRunAction(const G4Run*);
};

#endif /* TESTEUSERRUNACTION_HH_ */
