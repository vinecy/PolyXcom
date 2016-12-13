/*
 * Affichable.h
 *
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
		Affichable(int x,int y,int ID);		//Constructeur surchagé

		int distance(Affichable);			//retourne le distance entre 2 Affichables
		void display_info(void);				//Affiche les attributs en console

		int get_x(void);					//getters
		int get_y(void);
		int get_ID(void);
		void set_x(int);					//setters
		void set_y(int);

		virtual ~Affichable();				//Destructor
};

#endif /* AFFICHABLE_H_ */

