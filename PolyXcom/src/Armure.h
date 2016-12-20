/*
 * Armure.h
 *
 *  Created on: 15 déc. 2016
 *      Author: Vincent
 */

#ifndef ARMURE_H_
#define ARMURE_H_

class Armure
{
	private:
		int _tier;
		int _protection;
	public:
		Armure();
		Armure(int tier);
		Armure(int tier,int protection);

		int get_protection();
		void display_info();

		~Armure();
};



#endif /* ARMURE_H_ */
