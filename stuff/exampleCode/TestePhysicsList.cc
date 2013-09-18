//
// $Id: ExN01PhysicsList.cc,v 1.6 2006/06/29 17:47:21 gunter Exp $
// GEANT4 tag $Name: geant4-09-03-patch-02 $
//
// 

#include "TestePhysicsList.hh"
#include "G4ParticleTypes.hh"


TestePhysicsList::TestePhysicsList()
{;}

TestePhysicsList::~TestePhysicsList()
{;}

void TestePhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  G4Geantino::GeantinoDefinition();
}

void TestePhysicsList::ConstructProcess()
{
  // Define transportation process

  AddTransportation();
}

void TestePhysicsList::SetCuts()
{
  // uppress error messages even in case e/gamma/proton do not exist            
  G4int temp = GetVerboseLevel();                                                SetVerboseLevel(0);                                                           
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets 
  //   the default cut value for all particle types 
  SetCutsWithDefault();   

  // Retrieve verbose level
  SetVerboseLevel(temp);  
}

