/*
 * Noeud.cpp
 *
 *
 *  Created on: 27 nov. 2016
 *      Author: Valentin BISSUEL
 */

#include <iostream>
#include "Noeud.h"

using namespace std;

/** Le constructeur par défaut Noeud initialise le noeud et ses couts
 * */
Noeud::Noeud(){
	_x = 0;
	_y = 0;
	_G = 0;
	_H = 0;
	_F = _G + _H;
	cout << " + noeud créé " << endl;
}

/** Le constructeur Noeud initialise le noeud et ses couts
	 * @param x,y - pointeur sur la carte à analyser
	 * */
Noeud::Noeud(int x, int y) {
	_x = x;
	_y = y;
	_G = 0;
	_H = 0;
	_F = _G + _H;
	cout << " + noeud " << _x << "," << _y << " créé " << endl;
}

/** Modifie le cout depuis le debut
 * */
void Noeud::set_costFromBegin(int value){
	_G = value;
	_F = _G + _H;
}

/** Modifie le cout depuis la fin
 * */
void Noeud::set_costFromEnd(int value){
	_H = value;
	_F = _G + _H;
}

/** Retourne le cout depuis le debut
 * */
int Noeud::get_costFromBegin(void){
	return (_G);
}

/** Retourne le cout depuis la fin
 * */
int Noeud::get_costFromEnd(void){
	return (_H);
}

/** Retourne le cout final
 * */
int Noeud::get_costFinal(void){
	return (_F);
}

/** Retourne X
 * */
int Noeud::get_X(void){
	return (_x);
}

/** Retourne Y
 * */
int Noeud::get_Y(void){
	return (_y);
}

/** Méthode pour la redef de <<
 * */
void Noeud::display(ostream &flux) const {
	flux << "("<< _x << "," << _y << ") avec _G:"
	     << _G << ", _H:" << _H << ", _F:" << _F ;
}

/** La méthode display affiche le noeud et ses valeurs
 * */
void Noeud::display( void ) {
	cout << "(" << _x << "," << _y << ") avec _G:"
		 << _G << ", _H:" << _H << ", _F:" << _F ;
}

/** Redefinition de << pour le Noeud
 * */
ostream& operator<<( ostream &flux, Noeud const& noeud )
{
	noeud.display(flux);
    return (flux);
}

/** Le destructeur de Noeud
 * */
Noeud::~Noeud() {
	cout << " - noeud " << _x << "," <<  _y << " détruit " << endl;
}
