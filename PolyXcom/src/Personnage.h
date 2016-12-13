/*
 * Personnage.h
 *
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
	Personnage();
	Personnage(int x,int y,int ID,int pv,int pa,Arme arme);//construteur

	int get_pvMax(void);							//getters
	int get_paMax(void);
	int get_pvCurrent(void);
	int get_paCurrent(void);
	int get_rotation(void);
	Arme get_inv_armes(void);

	void set_pvMax(int pv);							//setters
	void set_paMAx(int pa);
	void set_pvCurrent(int pv);
	void set_paCurrent(int pa);

	void move_up(Carte &map);						//deplacement au Nord
	void move_down(Carte &map);						//deplacement au Sud
	void move_left(Carte &map);						//deplacement a l'Ouest
	void move_right(Carte &map);					//deplacement a l'Est


	void display_info(void);						//affichage des attributs en console

	virtual list<Personnage*> near(Carte &map, list<Personnage*> team)=0; //revoit une liste d'ennemi sur laquelle taper
	virtual void close_combat(list<Personnage*> list)=0;				  //taper sur des ennemis
	virtual void shoot(list<Personnage*> list)=0;						  //tirer sur des ennemis

	void reload();									//rechargement de l'arme

	virtual ~Personnage(void);						//destructor

};//Fin de la classe Personnage

#endif /* PERSONNAGE_H_ */
