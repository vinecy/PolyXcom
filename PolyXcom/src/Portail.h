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
private:
	int _newX;
	int _newY;
	string _nameNextMap;
public:
	Portail(int coordX, int coordY, int ID, int newX, int newY, string nextMap);


	virtual ~Portail();
};

#endif /* PORTAIL_H_ */
