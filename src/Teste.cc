/*
 * Teste.cc
 *
 *  Created on: Aug 30, 2012
 *      Author: sandro
 */

#include "Teste.hh"

Teste::Teste() {
	teste++;
	myInt = 83;
}

Teste::~Teste() {

}

int Teste::getTestInt() {
	return this->myInt;
}

int Teste::teste = 0;

