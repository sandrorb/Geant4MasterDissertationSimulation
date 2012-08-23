//
// $Id: ExN01PhysicsList.cc,v 1.6 2006/06/29 17:47:21 gunter Exp $
// GEANT4 tag $Name: geant4-09-03-patch-02 $
//
// 

#include "SrBPhysicsList.hh"
#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"

#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"

//#include "G4Gamma.hh"



SrBPhysicsList::SrBPhysicsList()
{;}

SrBPhysicsList::~SrBPhysicsList()
{;}

void SrBPhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  G4Geantino::GeantinoDefinition();

  G4Gamma::GammaDefinition();

}

void SrBPhysicsList::ConstructProcess()
{
  // Define transportation process

  AddTransportation();

  G4ParticleDefinition* particle = G4Gamma::Gamma();
  G4ProcessManager* pmanager = particle->GetProcessManager();

  pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
  pmanager->AddDiscreteProcess(new G4ComptonScattering);
  pmanager->AddDiscreteProcess(new G4GammaConversion);

}

void SrBPhysicsList::SetCuts()
{
  // uppress error messages even in case e/gamma/proton do not exist
  G4int temp = GetVerboseLevel();                                                SetVerboseLevel(0);
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets
  //   the default cut value for all particle types
  SetCutsWithDefault();

  // Retrieve verbose level
  SetVerboseLevel(temp);
}

