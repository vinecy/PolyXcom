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

		list<Personnage*> near(list<Personnage*> team);
		void close_combat(list<Personnage*> list);
		void shoot(list<Personnage*> list);

		void display_info();							//Affiche les attributs en console

		virtual ~Hero();								//destructor
};

#endif /* HERO_H_ */
