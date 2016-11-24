/*
 * Carte.h
 *
 *  Created on: 24 nov. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef CARTE_H_
#define CARTE_H_

class Carte {

	// Attributs
	private:
		int _sizeX;
		int _sizeY;
		int **_map;

	// Methodes
	public:
		Carte( int x , int y );				// Constructeur

		void display(void);		// Permet d'afficher la carte

		virtual ~Carte();		// Destructeur
};

#endif /* CARTE_H_ */
