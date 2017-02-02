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
 * @file Affichable.cpp
 * @brief La classe Affichable est la classe mere de tous les objets affichables
 *
 */

#include <iostream>
#include <cstdlib>
#include "Affichable.h"

using namespace std;

#define NORD 1
#define OUEST 2
#define EST 3
#define SUD 4

#define COLUMN_PLAYER_SPRITE 1
#define COLUMN_ENNEMY_SPRITE 521
#define ROW_NORTH_PXL 1
#define ROW_SOUTH_PXL 66
#define ROW_EAST_PXL 131
#define ROW_WEST_PXL 196

/** Le constructeur Affichable construit un Affichable par defaut*/
Affichable::Affichable(void)
{
	_coordX=0;
	_coordY=0;
	_ID=00;
	_rotation = SUD;
	cout << " + Affichable créé avec les attributs " << _coordX <<  _coordY << _ID << endl;
	cout << " + adresse : "<< &_coordX  << endl;
}

/** Le constructeur Affichable construit un Affichable avec initialisation des attributs
	 * @param x - abscisse de l'Affichable
	 * @param y - Ordonnée de l'Affichable
	 * @param ID - nombre qui identifie l'Affichable*/
Affichable::Affichable(int x, int y, int ID)	//Construteur surchargé
{
	_coordX=x;
	_coordY=y;
	_ID=ID;
	_rotation = SUD;
	cout << " + Affichable créé avec les attributs " << _coordX <<  _coordY << _ID << endl;
	cout << " + adresse : "<< &_coordX  << endl;
}

/** La methode distance retourne la 1-distance entre 2 Affichables
 	* @param A - Affichable avec la quelle la 1-distance est calculée*/
int Affichable::distance(Affichable A)
{
	return(abs(this->_coordX-A._coordX)+abs(this->_coordY-A._coordY));
}


/** La methode distance retourne la 1-distance avec une position
 	* @param x - abcisse avec la quelle la 1-distance est calculée
 	* @param y - ordonnée avec la quelle la 1-distance est calculée*/
int Affichable::distance(int x, int y)
{
	return(abs(this->_coordX-x)+abs(this->_coordY-y));
}

/** La methode display_info permet d'afficher les attributs de celui qui l'invoque la console */
void Affichable::display_info(void)		//debug display
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"///////////////"<<endl;
}

int Affichable::get_x( void )
{
	return (_coordX ) ;
}
int Affichable::get_y(void)
{
	return(_coordY );
}
int Affichable::get_ID(void)
{
	return(_ID );
}

void Affichable::set_x(int x)			//setters
{
	_coordX=x;
}
void Affichable::set_y(int y)
{
	_coordY=y;
}

Sprite Affichable::get_sprite(){
	return _sprite;
}

void Affichable::set_sprite(Texture &spriteSheet){
	_sprite.setTexture(spriteSheet);
	if(_ID == 2){
		switch(_rotation){
			case NORD : _sprite.setTextureRect(IntRect(COLUMN_PLAYER_SPRITE,ROW_NORTH_PXL,64,64)); break;
			case OUEST: _sprite.setTextureRect(IntRect(COLUMN_PLAYER_SPRITE,ROW_WEST_PXL,64,64)); break;
			case EST :	_sprite.setTextureRect(IntRect(COLUMN_PLAYER_SPRITE,ROW_EAST_PXL,64,64)); break;
			case SUD : 	_sprite.setTextureRect(IntRect(COLUMN_PLAYER_SPRITE,ROW_SOUTH_PXL,64,64)); break;
		}
	} else if(_ID == 3){
		switch(_rotation){
			case NORD : _sprite.setTextureRect(IntRect(COLUMN_ENNEMY_SPRITE,ROW_NORTH_PXL,64,64)); break;
			case OUEST: _sprite.setTextureRect(IntRect(COLUMN_ENNEMY_SPRITE,ROW_WEST_PXL,64,64)); break;
			case EST :	_sprite.setTextureRect(IntRect(COLUMN_ENNEMY_SPRITE,ROW_EAST_PXL,64,64)); break;
			case SUD : 	_sprite.setTextureRect(IntRect(COLUMN_ENNEMY_SPRITE,ROW_SOUTH_PXL,64,64)); break;
		}
	}
}

/** Le destructeur Affichable */
Affichable::~Affichable()				//destructeur
{
	cout << " - Affichable avec les attributs " << _coordX << " " <<  _coordY << " " << _ID << " detruit " << endl;
}
