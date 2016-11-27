/*
 * Obstacle.cpp
 *
 *  Created on: 27 nov. 2016
 *      Author: Vincent
 */

#include "Obstacle.h"
#include <iostream>
using namespace std;

Obstacle::Obstacle(int x,int y,int ID)
{
	_coordX=0;
	_coordY=0;
	_ID=00;
}

Obstacle::~Obstacle()				//destructor
{
	cout << "Obstacle detruit" << endl;
}
