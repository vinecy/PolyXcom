/*
 * Grenade.h
 *
 *  Created on: 15 déc. 2016
 *      Author: Vincent
 */

#ifndef GRENADE_H_
#define GRENADE_H_

class Grenade
{
private:
	int _dammage;
	int _number;
	int _range;
public:
	Grenade();

	int get_dammage();
	int get_number();

	void display_info();

	void add_number(int quantity);

	~Grenade();
};


#endif /* GRENADE_H_ */
