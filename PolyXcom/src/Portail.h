/*
 * Portail.h
 *
 *  Created on: 14 déc. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef PORTAIL_H_
#define PORTAIL_H_

#include <iostream>
#include "Affichable.h"

using namespace std;

class Portail : public Affichable{
private:							// ATTRIBUTS
	int _newX;
	int _newY;
	string _nameNextMap;
public:								// CONSTRUCTEUR
	Portail(int coordX, int coordY, int ID, int newX, int newY, string nextMap);

	int get_newX( void );			// GETTER
	int get_newY( void );
	string get_nameNextMap( void );

	void display( void );

	virtual ~Portail();				// DESTRUCTEUR
};

#endif /* PORTAIL_H_ */
