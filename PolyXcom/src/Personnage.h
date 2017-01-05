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
#include "Inventaire.h"
using namespace std;

class Personnage : public Affichable
{
protected:					//Attributs
	int _level;				//Niveau
	int _pvMax;				//Points de Vie maximums
	int _paMax;				//Points d'Action maximums
	int _pvCurrent;			//Points de Vie actuels
	int _paCurrent;			//Points d'Action actuels
	int _strength;			//Force
	int _accuracy;			//Precision
	int _agility;			//Agilité
	int _endurance;			//Endurance
	int _luck;				//Chance
	int _rotation;			//position du personnage par rapport au 4 points cardinaux.
	Inventaire _inv;		//Inventaire du perso


public:
	Personnage();
	Personnage(int x,int y,int ID,int lev,int str,int acc,int agi,int end,int luck,Inventaire inventaire);//construteur

	int get_pvMax(void);	//getters
	int get_paMax(void);
	int get_pvCurrent(void);
	int get_paCurrent(void);
	int get_rotation(void);
	Inventaire get_inv(void);
	Arme get_weapon(void);
	Armure get_armor(void);
	Soin get_medkit(void);
	Grenade get_grenade(void);


	void set_pvMax(int pv);	//setters
	void set_paMAx(int pa);
	void set_pvCurrent(int pv);
	void set_paCurrent(int pa);

	void display_info(void);//affichage des attributs en console

	virtual list<Personnage*> near(list<Personnage*> team)=0;	//revoie la liste des ennemis au cc
	virtual void close_combat(list<Personnage*> list)=0;		//permet de frapper des ennemis au cc
	virtual void shoot(list<Personnage*> list)=0;				//permet de tirer sur des ennemis
	void use_medkit();											//permet de se soigner
	void use_grenade(list<Personnage*> list);					//permet de lancer une grenade


	void reload();			//rechargement de l'arme

	virtual ~Personnage(void);//destructor

};//Fin de la classe Personnage

#endif /* PERSONNAGE_H_ */
