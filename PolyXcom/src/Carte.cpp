/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'élèves de Polytech Marseille. Il ne peut être
 * reproduit, utilisé ou modifié sans l'avis express de ses auteurs.
 */

/**
 * @author BARTHOLOMEAU Vincent <vincent.bartholomeau@etu.univ-amu.fr>
 * @author BISSUEL Valentin <valentin.bissuel@etu.univ-amu.fr>
 *
 * @version 0.0.1 / 24/11/2016
 *
 */

/**
 * @file Carte.cpp
 * @brief La classe Carte permet de gérer les objets dans le monde
 */

#include <iostream>
#include "Carte.h"
#include "Affichable.h"

using namespace std;

static Affichable vide;


/** Le constructeur Carte initialise le tableau contenant les objets affichables
	 * @param x - la longueur de la carte
	 * @param y - la largeur de la carte
	 * */
Carte::Carte( int x , int y ) {
	_sizeX = x ;
	_sizeY = y ;
	_map = new Affichable **[_sizeY];

	// initialisation de la carte
	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X
	for( i = 0 ; i < _sizeY ; i++ ){
		_map[i] = new Affichable*[_sizeX];
		for( j = 0 ; j < _sizeX ; j++ ){
			_map[i][j] = &vide;
		}
	}
	cout << " + carte de taille "<< _sizeX << "*" << _sizeY << " crée" << endl;
	cout << " + adresse de vide "<< &vide << endl;
}

/** La méthode display permet d'afficher la carte sur la console */
void Carte::display( void ) {
	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X

	cout << " *** affichage de la carte *** " << endl;
	cout << " ----------------- " << endl;
	for( i = _sizeY-1 ; i >= 0 ; i-- ){
		for( j = 0 ; j < _sizeX ; j++ ){
			cout << " | " << _map[j][i]->get_ID() ;
		}
		cout << " | "<< endl << " ----------------- " << endl;
	}
	cout << " *** _map avec l'adresse sur laquelle chaque case pointe *** " << endl;
	for( i = _sizeY-1 ; i >= 0 ; i-- ){
		for( j = 0 ; j < _sizeX ; j++ ){
			cout << _map[j][i] << " ";
		}
		cout << " \n "<< endl;
	}
	cout << " *** fin affichage *** " << endl;
}

/** La méthode moveIsPossible permet de vérifier si la case (x,y) est franchissable ou pas
 	 * @param x,y - couple de coordonnées à verifier
 	 * @return - il retourne 1 et le deplacement est possible ou 0 sinon.
 	 * */
bool Carte::moveIsPossible( int x , int y ){
	bool rep = true ;

	if( !(_map[x][y] == &vide) ){
		// si obstacle sur la case destination
		rep = false;
		cout << " obstacle détectée sur " << x << "," << y << endl;
	} else if( !( ( x>=0 && x<_sizeX ) && ( y>=0 && y<_sizeY ) ) ) {
		// si case destination en dehors de la carte
		rep = false;
		cout << " on sort de la carte! sur " << x << "," << y << endl;
	} else {
		cout << " aucun obstacle détectée" << endl;
	}
	return rep;
}

/** La méthode addItem permet d'ajouter un affichable sur la carte
 	 * @param &a - adresse de l'affichable à ajouter
 	 * */
void Carte::addItem( Affichable &a ){
	cout << " la case " << a.get_x() << "," << a.get_y() << " pointe sur l'adresse " << _map[ a.get_x() ][ a.get_y() ] << endl;
	cout << " addresse de l'affichable " << &a << endl;
	_map[ a.get_x() ][ a.get_y() ] = &a;
	cout << " la case " << a.get_x() << "," << a.get_y() << " pointe sur l'adresse " << _map[ a.get_x() ][ a.get_y() ] << endl;
}

/** La méthode moveItemTo permet de deplacer un affichable à un point sur la carte
 	 * @param *a - pointeur sur l'affichable à déplacer sur la carte
 	 * @param newX,newY - nouvelle coordonnées de l'objet à déplacer
 	 * */
void Carte::moveItemTo( int oldX, int oldY , int newX , int newY ){
	cout << "màj des coordonnes" << endl;

	cout << "adresse de l'objet à deplacer " <<_map[ oldX ][ oldY ] << endl;
	cout << "coordonnes de l'objet : "<< oldX << " " << oldX << endl;
	cout << "coordonnes de l'objet : "<< _map[ oldX ][ oldY ]->get_x() << " " << _map[ oldX ][ oldY ]->get_y() << endl;

	_map[ newX ][ newY ] = _map[ oldX ][ oldY ];
	_map[ oldX ][ oldY ] = &vide;

	_map[ newX ][ newY ]->set_x(newX);
	_map[ newX ][ newY ]->set_y(newY);

	cout << "adresse de l'objet à la nvlle position "<< _map[ oldX ][ oldY ] << endl;
	cout << "adresse de l'objet à l'ancienne position "<< _map[ oldX ][ oldY ] << endl;
	cout << "coordonnes de l'objet : "<< _map[ newX ][ newY ]->get_x() << " " << _map[ newX ][ newY ]->get_y() << endl;
}

void Carte::pathfinding( int xA , int yA , int xB , int yB ){



}

int Carte::get_sizeX(void){
	return _sizeX;
}

int Carte::get_sizeY(void){
	return _sizeY;
}

int Carte::get_IDin(int x, int y){
	return _map[x][y]->get_ID();
}

/** Le destructeur Carte */
Carte::~Carte() {
	delete _map;

	cout << " - carte de taille "<< _sizeX << "*" << _sizeY << " detruit" << endl;
}
