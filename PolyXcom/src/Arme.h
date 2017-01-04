/*
 * Arme.h
 *
 *
 *  Created on: 29 nov. 2016
 *      Author: Vincent
 */

#ifndef ARME_H_
#define ARME_H_

class Arme
{
	private:
		int _tier;								//"niveau" de l arme
		int _degats;							//degats max de l arme
		int _portee;							//portee de l arme
		int _munMax;							//nombre de munitions max de l arme
		int _munCurrent;						//nombre de munitions actuelle de l arme

	public:
		Arme();									//Constructeur Arme "defaut"
		Arme(int tier,int degats,int portee,int mun);//Constructeur d'Arme

		int get_tier();							//getter
		int get_degats();
		int get_portee();
		int get_munCurrent();
		int get_munMax();

		void set_munCurrent(int i);				//setter

		void display_info();					//Affichage info dans la console

		virtual ~Arme();						//destructeur
};

#endif /* ARME_H_ */
