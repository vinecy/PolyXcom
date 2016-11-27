/*
 * Ennemi.h
 *
 *  Created on: 27 nov. 2016
 *      Author: Vincent
 */

#ifndef ENNEMI_H_
#define ENNEMI_H_
#include"Personnage.h"
class Ennemi : Personnage
{
	public:
		Ennemi(int,int,int,int,int);

		void display_info();

		void begin_IA();

		virtual ~Ennemi();

};



#endif /* ENNEMI_H_ */
