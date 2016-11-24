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
	protected:								//Attribut
		string _nom;

	public:
		Hero(string);						//constructors
		Hero(int,int,int,int,int,string);

		string get_name(void);				//getter
		void set_name(string);				//setter

		void display_info();

		virtual ~Hero();					//destructor
};

#endif /* HERO_H_ */
