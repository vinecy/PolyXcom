/*
 * Armure.cpp
 *
 *  Created on: 15 déc. 2016
 *      Author: Vincent
 */

#include"Armure.h"
using namespace std;

Armure::Armure()
{
	_tier=0;
	_protection=0;
}

Armure::Armure(int tier)
{
	_tier=tier;
	_protection=2*tier;
}

Armure::Armure(int tier,int prot)
{
	_tier=tier;
	_protection=prot;
}

Armure::~Armure()
{

}


