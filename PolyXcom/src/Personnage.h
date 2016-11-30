/*
 * Personnage.h
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

#ifndef PERSONNAGE_H_
#define PERSONNAGE_H_
#include <iostream>
#include <list>
#include "Affichable.h"
#include "Carte.h"
#include "Arme.h"
using namespace std;

class Personnage : public Affichable
{
	protected:										//Attributs
		int _pvMax;									//Points de Vie maximums
		int _paMax;									//Points d'Action maximums
		int _pvCurrent;								//Points de Vie actuels
		int _paCurrent;								//Points d'Action actuels
		int _rotation;								//position du personnage par rapport au 4 points cardinaux.
		Arme _inv_armes;							//Arme du perso


public:
	Personnage(int,int,int,int,int,Arme);		//construteur

	int get_pvMax(void);							//getters
	int get_paMax(void);
	int get_pvCurrent(void);
	int get_paCurrent(void);

	void set_pvMax(int pv);							//setters
	void set_paMAx(int pa);
	void set_pvCurrent(int pv);
	void set_paCurrent(int pa);

	void move_up(Carte &);							//deplacement au Nord
	void move_down(Carte &);						//deplacement au Sud
	void move_left(Carte &);						//deplacement a l'Ouest
	void move_right(Carte &);						//deplacement a l'Est

	void display_info(void);						//affichage des attributs en console

	virtual ~Personnage(void);						//destructor

};//Fin de la classe Personnage

#endif /* PERSONNAGE_H_ */
