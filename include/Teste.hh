/*
 * Teste.hh
 *
 *  Created on: Aug 30, 2012
 *      Author: sandro
 */

#ifndef TESTE_HH_
#define TESTE_HH_

class Teste {
	public:
		Teste();
		virtual ~Teste();
		static int teste;
		int getTestInt();
	private:
		int myInt;
};

#endif /* TESTE_HH_ */
