/*
 * Carte.h
 *
 *
 *  Created on: 24 nov. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef CARTE_H_
#define CARTE_H_

#include <SFML/Graphics.hpp>	// Utilise la biblioth�que Graphique SFML
#include <list>					// Carte utilise des listes
#include "Personnage.h"			// Carte pointe sur des affichables

using namespace std;

class Carte {
	private:					// ATTRIBUTS
		int _sizeX;					// Longueur MAX de la carte
		int _sizeY;					// Largeur MAX de la carte
		Affichable ***_map;			// Matrice de pointeur d'objets affichables
		string _nameMap;			// nom de la carte
		bool _dangerZone;			// bool�en indiquant si c'est une zone de danger

	public:						// Composants graphique de l'IHM li�e � la classe Carte
		Sprite BackgroundMap;		// Sprite correspondant � la carte
		int _origXmap = 0;			// Origine X de la carte sur l'�cran
		int _origYmap = 0;			// Origine Y de la carte sur l'�cran
		int _widthMap;				// Longueur de la carte en pixels
		int _heightMap;				// Hauteur de la carte en pixels
		float _zoom = 1.0;			// Zoom sur l'�cran
		list<RectangleShape> _listSquareMap; // Collection de Carre repr�senant une case de la carte

	public:						// CONSTRUCTEUR
		Carte();					// constructeur par d�faut
		Carte(int,int);				// constructeur avec taille pr�defini
		Carte(string,int,int,bool);	// constructeur avec nom, taille, �tat du combat d�fini
											// METHODES
		void updatePosition();					// Remet � jour la position de la carte sur l'�cran
		void loadMap(string const);				// Permet de charger la carte avec le nom du fichier en argument
		int moveIsPossible(int,int,bool);		// Affirme si D�placement possible � (x,y)
		int move_up(Personnage &,bool);			// deplacement au Nord
		int move_down(Personnage &,bool);		// deplacement au Sud
		int move_left(Personnage &,bool);		// deplacement a l'Ouest
		int move_right(Personnage &,bool);		// deplacement a l'Est
		void addItem(Affichable &);				// Ajoute un objet affichable sur la carte
		void removeItem(Affichable &);			// Enleve un objet affichable sur la carte (ne supprime pas lobjet)
		void removeAllItem();					// Enl�ve tous les objets de la carte
		void moveItemTo(int,int,int,int);		// D�place l'affichable de la case (x,y) � la nouvelle case
		void moveItemToWithMoveAnim(int,int,int,int);		// Comme pr�cedement mais avec l'animation du d�placement
		list<pair<int,int> > pathfinding(int,int,int,int);	// Recherche le meilleur chemin vers xB,yB et renvoie le chemin � faire
		list<pair<int,int> > drawPath(int,int,int,int);		// trace la trajectoire entre le point xA,yA et le point xB,yB
		bool pathIsPossible(int,int,int,int);				// determine si le segment entre le point xA,yA et le point xB,yB ne pr�sente pas d'obstacle
		list<pair<int,int> > seekSpawnPoint(int,int,int); 	// determine les cases o� les personnages peuvent se d�placer en x,y
		//list<Personnage*> near(list<Personnage*> team);
		void display(void);									// Permet d'afficher la carte
											// GETTERS
		string get_nameMap(void);				// Retourne le nom de la carte
		int get_sizeX(void);					// Retourne la longueur de la carte
		int get_sizeY(void);					// Retourne la largeur de la carte
		bool get_dangerZone(void);				// Retourne le bool�en qui indique une zone de combat ou non
		int get_IDin(int x, int y);  			// Retourne l'ID de l'objet dans la carte
											// SETTERS
		void set_sizeX(int value);				// Modifie la longueur de la carte
		void set_sizeY(int value);				// Modifie la largeur de la carte

		virtual ~Carte();					// DESTRUCTEUR
};

#endif /* CARTE_H_ */
