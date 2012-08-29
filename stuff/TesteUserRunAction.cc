/*
 * TesteUserRunAction.cc
 *
 *  Created on: Apr 7, 2011
 *      Author: sandro
 */

#include <iostream>
#include "TesteUserRunAction.hh"

//#include "BeamTestRun.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include <assert.h>

TesteUserRunAction::TesteUserRunAction() {}

TesteUserRunAction::~TesteUserRunAction() {}

void TesteUserRunAction::BeginOfRunAction(const G4Run*) {}

//G4Run*  TesteUserRunAction::GenerateRun()
//{
//  G4cout << "Creating user define run class TesteUserRunAction" << G4endl;
//  return new TesteUserRunAction("MyDetector");
//}

void TesteUserRunAction::EndOfRunAction(const G4Run* aRun) {

	G4cout << "Teste" << G4endl;

//  G4cout <<"Number of Events Processed:" <<aRun->GetNumberOfEvent() << " events. " <<G4endl;
//  const BeamTestRun* theRun = dynamic_cast<const BeamTestRun*>(aRun);
//  assert (0 != theRun);
//  theRun->DumpData();
}

