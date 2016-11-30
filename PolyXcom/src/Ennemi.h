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
		Ennemi(int,int,int,int,int,Arme);							//Constructeur

		void display_info();						//Affichable debug

		void begin_IA();							//fonction qui commence le choix de l'AI

		virtual ~Ennemi();							//Destucteur

};



#endif /* ENNEMI_H_ */
