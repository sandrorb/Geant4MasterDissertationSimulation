
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

    inline G4double GetTotalEnergyDeposited() const {
    	return GetTotal(energySum);
    }

//  private:
//    G4double GetTotal(const G4THitsMap<G4double> &map) const;
//    G4double FindMinimum(const G4THitsMap<G4double> &map) const;

  private:
    G4THitsMap<G4double> energySum;
    G4int ID;

    G4double GetTotal(const G4THitsMap<G4double> &map) const;

//  private:
//    // Maps for accumulation
//    // mapSum[i][j]
//    //  i = 0 : Calor-A_abs    j = 0 : total eDep
//    //  i = 1 : Calor-A_gap    j = 1 : number of gamma
//    //  i = 2 : Calor-B_abs    j = 2 : number of electron
//    //  i = 3 : Calor-B_gap    j = 3 : number of positron
//    //  i = 4 : Calor-C_abs    j = 4 : total step length for e+/e-
//    //  i = 5 : Calor-C_gap    j = 5 : total number of steps for e+/e-
//    G4THitsMap<G4double> mapSum[6][6];
//    G4int colIDSum[6][6];
//
//    // Maps for minimum value
//    //  i = 0 : Calor-A_abs    j = 0 : minimum kinE at generation for gamma
//    //  i = 1 : Calor-A_gap    j = 1 : minimum kinE at generation for electron
//    //  i = 2 : Calor-B_abs    j = 2 : minimum kinE at generation for positron
//    //  i = 3 : Calor-B_gap
//    //  i = 4 : Calor-C_abs
//    //  i = 5 : Calor-C_gap
//    G4THitsMap<G4double> mapMin[6][3];
//    G4int colIDMin[6][3];
//
//    // Maps for accumulation in parallel world
//    // mapPara[i][j]
//    //  i = 0 : Calor-AP_para    j = 0 : total eDep
//    //  i = 1 : Calor-BP_para    j = 1 : number of gamma
//    //  i = 2 : Calor-CP_para    j = 2 : number of electron
//    //                          j = 3 : number of positron
//    //                          j = 4 : total step length for e+/e-
//    //                          j = 5 : total number of steps for e+/e-
//    G4THitsMap<G4double> mapPara[3][6];
//    G4int colIDPara[3][6];

//  public:
//    inline G4double GetTotalE(G4int i) const
//    { return GetTotal(mapSum[i][0]); }
//    inline G4double GetNGamma(G4int i) const
//    { return GetTotal(mapSum[i][1]); }
//    inline G4double GetNElectron(G4int i) const
//    { return GetTotal(mapSum[i][2]); }
//    inline G4double GetNPositron(G4int i) const
//    { return GetTotal(mapSum[i][3]); }
//    inline G4double GetTotalL(G4int i) const
//    { return GetTotal(mapSum[i][4]); }
//    inline G4double GetNStep(G4int i) const
//    { return GetTotal(mapSum[i][5]); }
//
//    inline G4double GetEMinGamma(G4int i) const
//    { return FindMinimum(mapMin[i][0]); }
//    inline G4double GetEMinElectron(G4int i) const
//    { return FindMinimum(mapMin[i][1]); }
//    inline G4double GetEMinPositron(G4int i) const
//    { return FindMinimum(mapMin[i][2]); }
//
//    inline G4double GetParaValue(G4int i,G4int j,G4int k) const
//    {
//      G4double* p = mapPara[i][j][k];
//      if(p) return *p;
//      return 0.;
//    }
};

#endif

