/*
 * Personnage.h
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

#ifndef PERSONNAGE_H_
#define PERSONNAGE_H_
#include <iostream>
#include "Affichable.h"
#include "Carte.h"
using namespace std;

class Personnage : public Affichable
{
	protected:					//attributs
		int _pvMax;
		int _paMax;
		int _pvCurrent;
		int _paCurrent;
		int _rotation;

public:
	Personnage(void);			//constructeurs
	Personnage(int,int);

	int get_pvMax(void);		//getters
	int get_paMax(void);
	int get_pvCurrent(void);
	int get_paCurrent(void);

	void set_pvMax(int pv);		//setters
	void set_paMAx(int pa);
	void set_pvCurrent(int pv);
	void set_paCurrent(int pa);

	void move_up(Carte);		//deplacement
	void move_down(Carte);
	void move_left(Carte);
	void move_right(Carte);

	void display_info(void);	//afichage debug


	virtual ~Personnage(void);	//destructor

};//Fin de la classe Personnage



#endif /* PERSONNAGE_H_ */
