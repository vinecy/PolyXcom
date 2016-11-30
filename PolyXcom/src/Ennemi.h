/*
 * Ennemi.h
 *
 *  Created on: 27 nov. 2016
 *      Author: Vincent
 */

#ifndef ENNEMI_H_
#define ENNEMI_H_
#include"Personnage.h"
class Ennemi : public Personnage
{
	public:
		Ennemi(int x,int y ,int ID ,int pv,int pa,Arme arme);	//Constructeur

		void display_info();									//Affichable debug

		void begin_IA();										//fonction qui commence le choix de l'AI

		virtual ~Ennemi();										//Destucteur

};



#endif /* ENNEMI_H_ */
