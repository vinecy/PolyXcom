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
#include "Personnage.h"			// Carte pointe sur des affichables

using namespace std;

class Carte {
	private:					// Attributs
		int _sizeX;					// Longueur MAX de la carte
		int _sizeY;					// Largeur MAX de la carte
		Affichable ***_map;			// Matrice de pointeur d'objets affichables
		string _nameMap;
		bool _dangerZone;
	// Methodes
	public:
		Carte();
		Carte( int x , int y );									// Constructeur
		Carte( string name , int x , int y , bool dZ);

		void loadMap(string const name);

		int moveIsPossible(int x , int y , bool canCrossMap);	// Affirme si Déplacement possible à (x,y)

		int move_up(Personnage &perso, bool withUsePA);						// deplacement au Nord
		int move_down(Personnage &perso, bool withUsePA);						// deplacement au Sud
		int move_left(Personnage &perso, bool withUsePA);						// deplacement a l'Ouest
		int move_right(Personnage &perso, bool withUsePA);						// deplacement a l'Est

		void addItem(Affichable &a);		// Ajoute un objet affichable sur la carte
		void removeItem(Affichable &a);		// Enleve un objet affichable sur la carte (ne supprime pas lobjet)
		void removeAllItem( void );			// Enlève tous les objets de la carte
		void moveItemTo( int oldX , int oldY , int newX , int newY);			// Déplace l'affichable de la case (x,y) à la nouvelle case
		void moveItemToWithMoveAnim( int oldX , int oldY , int newX , int newY);// Comme précedement mais l'animation du déplacement
		list <pair<int , int>> pathfinding( int xA , int yA , int xB , int yB );// Recherche le meilleur chemin vers xB,yB et renvoie le chemin à faire
		list <pair<int , int>> drawPath( int xA, int yA, int xB, int yB );
		bool pathIsPossible( int xA, int yA, int xB, int yB );
		list <pair<int , int>> seekSpawnPoint(int x, int y, int nb);
		//list<Personnage*> near(list<Personnage*> team);

		void display(void);					// Permet d'afficher la carte

		string get_nameMap(void);
		int get_sizeX(void);				// Retourne la longueur de la carte
		int get_sizeY(void);				// Retourne la largeur de la carte
		bool get_dangerZone(void);
		int get_IDin(int x, int y);  		// Retourne l'ID de l'objet dans la carte
		void set_sizeX(int value);			// Modifie la longueur de la carte
		void set_sizeY(int value);			// Modifie la largeur de la carte

		virtual ~Carte();										// Destructeur
};

#endif /* CARTE_H_ */
