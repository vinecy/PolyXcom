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
	protected:										//attributs
		int _pvMax;									//Points de Vie maximums
		int _paMax;									//Points d'Action maximums
		int _pvCurrent;								//Points de Vie actuels
		int _paCurrent;								//Points d'Action actuels
		int _rotation;								//position du personnage par rapport au 4 points cardinaux.

public:
	Personnage(void);								//constructeur par defaut
	Personnage(int,int);							//construteur surchargé

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
