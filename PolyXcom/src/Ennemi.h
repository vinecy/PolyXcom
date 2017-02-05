/*
 * Ennemi.h
 *
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
		Ennemi();
		Ennemi(int x,int y,int ID,int lev,int str,int acc,int agi,int end,int luck,Inventaire inv);	//Constructeur

		void display_info();									//Affichable debug
		/*
		list<Personnage*> near(list<Personnage*> team);			//retourne une liste d'ennemi sur laquelle taper
		void close_combat(list<Personnage*> list);				//taper sur des ennemis
		void shoot(list<Personnage*> list);						//tirer sur des ennemis
		*/
		void begin_IA();										//fonction qui commence le choix de l'AI

		virtual ~Ennemi();										//Destucteur

};



#endif /* ENNEMI_H_ */
