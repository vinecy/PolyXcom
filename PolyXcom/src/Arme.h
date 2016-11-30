/*
 * Arme.h
 *
 *  Created on: 29 nov. 2016
 *      Author: Vincent
 */

#ifndef ARME_H_
#define ARME_H_

class Arme
{
	private:
		int _tier;								//"niveau" de l'arme
		int _degats;							//degats max de l'arme
		int _portee;							//portee de l'arme

	public:
		Arme();									//Constructeur Arme "defaut"
		Arme(int tier,int degats,int portee);	//Constructeur d'Arme

		void display_info();					//Affichage info dans la console

		virtual ~Arme();						//destructeur
};





#endif /* ARME_H_ */
