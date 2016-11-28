/*
 * Carte.h
 *
 *  Created on: 24 nov. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef CARTE_H_
#define CARTE_H_

#include "Affichable.h"
class Carte {

	// Attributs
	private:
		int _sizeX;												// Longueur MAX de la carte
		int _sizeY;												// Largeur MAX de la carte
		Affichable ***_map;										// Matrice de pointeur d'objets affichables

	// Methodes
	public:
		Carte( int x , int y );									// Constructeur

		void display(void);										// Permet d'afficher la carte
		bool moveIsPossible( int x , int y );					// affirme si Déplacement possible à (x,y)
		void addItem( Affichable &a);							// Ajoute un objet affichable sur la carte
		void moveItemTo( int oldX , int oldY , int newX , int newY);  // déplace l"affichable de la case (x,y) à la nouvelle case
		void pathfinding( Carte &map, int xA , int yA , int xB , int yB );

		int get_sizeX(void);
		int get_sizeY(void);
		int get_IDin(int x, int y);

		virtual ~Carte();										// Destructeur
};

#endif /* CARTE_H_ */
