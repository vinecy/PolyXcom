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

class Hero : Personnage
{
	protected:
		string _nom;


	public:
		Hero(int,int,int,int,int,string);
};




#endif /* HERO_H_ */

