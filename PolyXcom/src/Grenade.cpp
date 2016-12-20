/*
 * Grenade.cpp
 *
 *  Created on: 15 déc. 2016
 *      Author: Vincent
 */

#include"Grenade.h"
#include<iostream>
using namespace std;


Grenade::Grenade()
{
	_range=4;
	_number=0;
	_dammage=4;
}

void Grenade::add_number(int q)
{
	_number=_number+q;
}

int Grenade::get_dammage()
{
	return(_dammage);
}

void Grenade::display_info()
{
	cout<<"Grenade( damage= "<<_dammage<<" , range= "<<_range<<" , number= "<<_number<<" )"<<endl;
}

int Grenade::get_number()
{
	return(_number);
}

Grenade::~Grenade()
{

}
