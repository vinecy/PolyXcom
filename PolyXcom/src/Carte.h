/*
 * Carte.h
 *
 *  Created on: 24 nov. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef CARTE_H_
#define CARTE_H_


#include <list>
#include <map>
#include "Affichable.h"

using namespace std;

class Carte {

	// Attributs
	private:
		int _sizeX;												// Longueur MAX de la carte
		int _sizeY;												// Largeur MAX de la carte
		Affichable ***_map;										// Matrice de pointeur d'objets affichables

	// Methodes
	public:
		Carte( int x , int y );									// Constructeur

		void display(void);											// Permet d'afficher la carte
		bool moveIsPossible( int x , int y );						// Affirme si D�placement possible � (x,y)
		void addItem( Affichable &a);								// Ajoute un objet affichable sur la carte
		void moveItemTo( int oldX , int oldY , int newX , int newY);// D�place l'affichable de la case (x,y) � la nouvelle case
		void pathfinding( int xA , int yA , int xB , int yB );		// Recherche le meilleur chemin vers xB,yB et renvoie le chemin � faire
		list <Affichable*> list_cc(int X,int Y);

		int get_sizeX(void);
		int get_sizeY(void);
		int get_IDin(int x, int y);

		virtual ~Carte();										// Destructeur
};

#endif /* CARTE_H_ */
