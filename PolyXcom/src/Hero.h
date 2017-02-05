/*
 * Hero.h
 *
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

#ifndef HERO_H_
#define HERO_H_
using namespace std;
#include <iostream>
#include "Personnage.h"

class Hero : public Personnage
{
	private:											//Attribut
		string _nom;									//Nom du hero

	public:
		Hero(int x,int y,int ID,int lev,int str,int acc,int agi,int end,int luck,Inventaire inv,string nom);//constructeur

		string get_name(void);							//getter
		void set_name(string);							//setter
		/*
		list<Personnage*> near(list<Personnage*> team);	//revoie la liste des ennemis adjacents
		void close_combat(list<Personnage*> list);		//combat au corps a corps
		void shoot(list<Personnage*> list);				//combat a distance
		*/
		void display_info();							//Affiche les attributs en console

		virtual ~Hero();								//destructeur
};

#endif /* HERO_H_ */
