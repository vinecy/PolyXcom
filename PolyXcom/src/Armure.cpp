/*
 * Armure.cpp
 *
 *  Created on: 15 déc. 2016
 *      Author: Vincent
 */

#include"Armure.h"
#include<iostream>
using namespace std;

Armure::Armure()
{
	_tier=0;
	_protection=1;
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

int Armure::get_protection()
{
	return(_protection);
}

void Armure::display_info()
{
	cout<<"Armure ( Tier= "<<_tier<<" , protection= "<<_protection<<" )"<<endl;
}

Armure::~Armure()
{

}


