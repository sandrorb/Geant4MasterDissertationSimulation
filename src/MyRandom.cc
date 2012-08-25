#include "MyRandom.hh"

double MyRandom::getRandomNumber(){
	//G4cout << "Numero aleatorio: " << G4UniformRand() << G4endl;
	return G4UniformRand();
}

MyRandom::MyRandom() {


}

MyRandom::~MyRandom() {

}
