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

inline bool operator== (Portail p1, Portail p2)
{
	if((p1.get_nameNextMap()==p2.get_nameNextMap())&&
			(p1.get_x()==p2.get_x())&& (p1.get_y()==p2.get_y()))
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

#endif /* PORTAIL_H_ */
