/*
 * Grenade.h
 *
 *  Created on: 15 déc. 2016
 *      Author: Vincent
 */

#ifndef GRENADE_H_
#define GRENADE_H_

#include"Bonus.h"

class Grenade : public Bonus
{
	private:
		int _range;
	public:
		Grenade(int pwr, int range);
		void use();
		~Grenade();
};


#endif /* GRENADE_H_ */
