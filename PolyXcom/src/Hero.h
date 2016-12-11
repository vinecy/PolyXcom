/*
 * Hero.h
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
	protected:											//Attribut
		string _nom;									//Nom du hero

	public:
		Hero(int x,int y,int ID,int pv,int pa,Arme arme,string nom);//constructeur

		string get_name(void);							//getter
		void set_name(string);							//setter

		list<Personnage*> near(Carte &map,list<Personnage*> &team);
		void close_combat(list<Personnage*> &team);

		void display_info();							//Affiche les attributs en console

		virtual ~Hero();								//destructor
};

#endif /* HERO_H_ */
