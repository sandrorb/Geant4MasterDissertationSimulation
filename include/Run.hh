
#ifndef Run_h
#define Run_h 1

#include "globals.hh"
#include "G4Run.hh"

#include "G4THitsMap.hh"

class G4Event;

class Run : public G4Run
{
  public:
    Run();
    virtual ~Run();

  public:
    virtual void RecordEvent(const G4Event*);

//    inline G4double GetTotalEnergyDeposited() const {
//    	return GetTotal(energySum);
//    }

    inline G4double GetMyTotalEnergyDeposited(G4int i) const {
    	return GetTotal(mapSum[i]);
    }

  private:
    //G4THitsMap<G4double> energySum;
    G4THitsMap<G4double> energySum[50];
    G4THitsMap<G4double> mapSum[50];
    G4double myEnergy[50];
    //G4int ID;
    G4int myID[50];
    G4double GetTotal(const G4THitsMap<G4double> &map) const;
};

#endif

