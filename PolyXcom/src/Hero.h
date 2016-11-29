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
		Hero(int,int,int,int,int,list<Arme>,string);				//constructeur

		string get_name(void);							//getter
		void set_name(string);							//setter

		void display_info();							//Affiche les attributs en console

		virtual ~Hero();								//destructor
};

#endif /* HERO_H_ */
