/*
 * Personnage.h
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

#ifndef PERSONNAGE_H_
#define PERSONNAGE_H_
#include <iostream>
using namespace std;

class Personnage
{
	protected:					//atributs
		int _coordX;
		int _coordY;
		int _pvMax;
		int _paMax;
		int _pvCurrent;
		int _paCurrent;

public:
	Personnage(void);			//constructeurs
	Personnage(int x,int y,int pv,int pa);

	int get_x(void);			//getter
	int get_y(void);
	int get_pvMax(void);
	int get_paMax(void);
	int get_pvCurrent(void);
	int get_paCurrent(void);

	void set_x(int x);			//setter
	void set_y(int y);
	void set_pvMax(int pv);
	void set_paMAx(int pa);
	void set_pvCurrent(int pv);
	void set_paCurrent(int pa);

	void display_info(void);	//afichage debug


	virtual ~Personnage(void);			//destructeur

};//Fin de la classe Personnage



#endif /* PERSONNAGE_H_ */
