/*
 * Affichable.h
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

#ifndef AFFICHABLE_H_
#define AFFICHABLE_H_

class Affichable
{
	protected:								//Attributs
		int _coordX;						//Abscisse
		int _coordY;						//Ordonnée
		int _ID;							//Identifiant

	public:
		Affichable();						//Construteur par defaut
		Affichable(int,int,int);			//Constructeur surchagé

		int get_x(void);					//getters
		int get_y(void);
		int get_ID(void);

		void set_x(int);					//setters
		void set_y(int);

		void display_info();				//Affiche les attributs en console

		virtual ~Affichable();				//Destructor
};

#endif /* AFFICHABLE_H_ */

