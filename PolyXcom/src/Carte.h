/*
 * Carte.h
 *
 *  Created on: 24 nov. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef CARTE_H_
#define CARTE_H_

#include "Affichable.h"
#include <cstddef>
class Carte {

	// Attributs
	private:
		int _sizeX;												// Longueur MAX de la carte
		int _sizeY;												// Largeur MAX de la carte
		Affichable ***_map;												// Matrice o� sont plac�s les objets
		//nullptr_t ***_map;


	// Methodes
	public:
		Carte( int x , int y );									// Constructeur

		void display(void);										// Permet d'afficher la carte
		bool moveIsPossible( int x , int y );					// affirme si D�placement possible � (x,y)
		void addItem( Affichable &a);							// Ajoute un objet affichable sur la carte
		void update( Affichable *a , int newX , int newY);	    // d�place l"affichable de la case (x,y) � la nouvelle case

		virtual ~Carte();										// Destructeur
};

#endif /* CARTE_H_ */
