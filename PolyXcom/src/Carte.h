/*
 * Carte.h
 *
 *
 *  Created on: 24 nov. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef CARTE_H_
#define CARTE_H_


#include <list>					// Carte utilise des listes
#include "Affichable.h"			// Carte pointe sur des affichables

using namespace std;

class Carte {
	private:					// Attributs
		int _sizeX;					// Longueur MAX de la carte
		int _sizeY;					// Largeur MAX de la carte
		Affichable ***_map;			// Matrice de pointeur d'objets affichables

	// Methodes
	public:
		Carte( int x , int y );									// Constructeur
		Carte( string name );

		void loadMap(string const name);

		bool moveIsPossible(int x , int y);	// Affirme si Déplacement possible à (x,y)

		void move_up(Affichable &perso);						//deplacement au Nord
		void move_down(Personnage &perso);						//deplacement au Sud
		void move_left(Personnage &perso);						//deplacement a l'Ouest
		void move_right(Personnage &perso);					//deplacement a l'Est

		void addItem(Affichable &a);		// Ajoute un objet affichable sur la carte
		void removeItem(Affichable &a);		// Enleve un objet affichable sur la carte (ne supprime pas lobjet)
		void moveItemTo( int oldX , int oldY , int newX , int newY);// Déplace l'affichable de la case (x,y) à la nouvelle case
		list <pair<int , int>> pathfinding( int xA , int yA , int xB , int yB );// Recherche le meilleur chemin vers xB,yB et renvoie le chemin à faire
		list <pair<int , int>> drawPath( int xA, int yA, int xB, int yB );
		bool pathIsPossible( int xA, int yA, int xB, int yB );
		void display(void);					// Permet d'afficher la carte

		int get_sizeX(void);				// Retourne la longueur de la carte
		int get_sizeY(void);				// Retourne la largeur de la carte
		int get_IDin(int x, int y);  		// Retourne l'ID de l'objet dans la carte
		void set_sizeX(int value);			// Modifie la longueur de la carte
		void set_sizeY(int value);			// Modifie la largeur de la carte

		virtual ~Carte();										// Destructeur
};

#endif /* CARTE_H_ */
