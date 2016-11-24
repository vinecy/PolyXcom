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
	protected:
		string _nom;

	public:
		Hero(string);
		string get_name(void);
		void display_info();

		virtual ~Hero();
};

#endif /* HERO_H_ */
