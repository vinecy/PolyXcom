<<<<<<< HEAD
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
		bool moveIsPossible( int x , int y );						// Affirme si Déplacement possible à (x,y)
		void addItem( Affichable &a);								// Ajoute un objet affichable sur la carte
		void moveItemTo( int oldX , int oldY , int newX , int newY);// Déplace l'affichable de la case (x,y) à la nouvelle case
		void pathfinding( int xA , int yA , int xB , int yB );		// Recherche le meilleur chemin vers xB,yB et renvoie le chemin à faire
		list <Affichable*> list_cc(int X,int Y);

		int get_sizeX(void);
		int get_sizeY(void);
		int get_IDin(int x, int y);

		virtual ~Carte();										// Destructeur
};

#endif /* CARTE_H_ */
=======
/*
 * Carte.h
 *
 *  Created on: 24 nov. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef CARTE_H_
#define CARTE_H_


#include <list>
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

		void display(void);										// Permet d'afficher la carte
		bool moveIsPossible( int x , int y );					// affirme si Déplacement possible à (x,y)
		void addItem( Affichable &a);							// Ajoute un objet affichable sur la carte
		void moveItemTo( int oldX , int oldY , int newX , int newY);  // déplace l"affichable de la case (x,y) à la nouvelle case
		void pathfinding( int xA , int yA , int xB , int yB );
		//list <Affichable*> list_cc(int,int);

		//void get_Item(list<Affichable*>,int,int);

		int get_sizeX(void);
		int get_sizeY(void);
		int get_IDin(int x, int y);

		virtual ~Carte();										// Destructeur
};

#endif /* CARTE_H_ */
>>>>>>> refs/remotes/origin/PolyXcom
