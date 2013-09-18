/*
 * MyMaterial.hh
 *
 * @author Sandro Boschetti, August 30, 2012
 */

#ifndef MYMATERIAL_HH_
#define MYMATERIAL_HH_

class G4Material;

class MyMaterial {

	public:
		MyMaterial();
		virtual ~MyMaterial();
		G4Material* getAir();
		G4Material* getArgonGas();
		G4Material* getPb();
		G4Material* getWater();
		G4Material* getBeryllium();
		G4Material* getMolybdenum();

	private:
		G4Material* air;
		G4Material* argonGas;
		G4Material* pb;
		G4Material* water;
		G4Material* beryllium;
		G4Material* molybdenum;
};



#endif /* MYMATERIAL_HH_ */
