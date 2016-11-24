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
		int sizeX;
		int sizeY;
		int **map;

	// Methodes
	public:
		Carte();				// Constructeur

		void display(void);

		virtual ~Carte();		// Destructeur
};

#endif /* CARTE_H_ */
