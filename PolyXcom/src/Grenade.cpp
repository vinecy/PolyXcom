/*
 * Grenade.cpp
 *
 *  Created on: 15 d�c. 2016
 *      Author: Vincent
 */

#include"Grenade.h"
using namespace std;


Grenade::Grenade(int power,int range):Bonus(power)
{
	_range=range;
}

void Grenade::use()
{

}

Grenade::~Grenade()
{

}
