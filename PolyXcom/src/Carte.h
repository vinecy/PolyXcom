/*
 * Carte.h
 *
 *
 *  Created on: 24 nov. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef CARTE_H_
#define CARTE_H_

#include <SFML/Graphics.hpp>	// Utilise la bibliothèque Graphique SFML
#include <list>					// Carte utilise des listes
#include "Personnage.h"			// Carte pointe sur des affichables

using namespace std;

class Carte {
	private:					// ATTRIBUTS
		int _sizeX;					// Longueur MAX de la carte
		int _sizeY;					// Largeur MAX de la carte
		Affichable ***_map;			// Matrice de pointeur d'objets affichables
		string _nameMap;			// nom de la carte
		bool _dangerZone;			// booléen indiquant si c'est une zone de danger

	public:						// Composants graphique de l'IHM liée à la classe Carte
		Sprite BackgroundMap;		// Sprite correspondant à la carte
		int _origXmap = 0;			// Origine X de la carte sur l'écran
		int _origYmap = 0;			// Origine Y de la carte sur l'écran
		int _widthMap;				// Longueur de la carte en pixels
		int _heightMap;				// Hauteur de la carte en pixels
		float _zoom = 1.0;			// Zoom sur l'écran
		list<RectangleShape> _listSquareMap; // Collection de Carre représenant une case de la carte

	public:						// CONSTRUCTEUR
		Carte();					// constructeur par défaut
		Carte(int,int);				// constructeur avec taille prédefini
		Carte(string,int,int,bool);	// constructeur avec nom, taille, état du combat défini
											// METHODES
		void updatePosition();					// Remet à jour la position de la carte sur l'écran
		void loadMap(string const);				// Permet de charger la carte avec le nom du fichier en argument
		int moveIsPossible(int,int,bool);		// Affirme si Déplacement possible à (x,y)
		int move_up(Personnage &,bool);			// deplacement au Nord
		int move_down(Personnage &,bool);		// deplacement au Sud
		int move_left(Personnage &,bool);		// deplacement a l'Ouest
		int move_right(Personnage &,bool);		// deplacement a l'Est
		void addItem(Affichable &);				// Ajoute un objet affichable sur la carte
		void removeItem(Affichable &);			// Enleve un objet affichable sur la carte (ne supprime pas lobjet)
		void removeAllItem();					// Enlève tous les objets de la carte
		void moveItemTo(int,int,int,int);		// Déplace l'affichable de la case (x,y) à la nouvelle case
		void moveItemToWithMoveAnim(int,int,int,int);		// Comme précedement mais avec l'animation du déplacement
		list<pair<int,int> > pathfinding(int,int,int,int);	// Recherche le meilleur chemin vers xB,yB et renvoie le chemin à faire
		list<pair<int,int> > drawPath(int,int,int,int);		// trace la trajectoire entre le point xA,yA et le point xB,yB
		bool pathIsPossible(int,int,int,int);				// determine si le segment entre le point xA,yA et le point xB,yB ne présente pas d'obstacle
		list<pair<int,int> > seekSpawnPoint(int,int,int); 	// determine les cases où les personnages peuvent se déplacer en x,y
		//list<Personnage*> near(list<Personnage*> team);
		void display(void);									// Permet d'afficher la carte
											// GETTERS
		string get_nameMap(void);				// Retourne le nom de la carte
		int get_sizeX(void);					// Retourne la longueur de la carte
		int get_sizeY(void);					// Retourne la largeur de la carte
		bool get_dangerZone(void);				// Retourne le booléen qui indique une zone de combat ou non
		int get_IDin(int x, int y);  			// Retourne l'ID de l'objet dans la carte
											// SETTERS
		void set_sizeX(int value);				// Modifie la longueur de la carte
		void set_sizeY(int value);				// Modifie la largeur de la carte

		virtual ~Carte();					// DESTRUCTEUR
};

#endif /* CARTE_H_ */
