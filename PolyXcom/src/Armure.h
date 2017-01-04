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
		int _tier;			//nombre representatif du niveau de l armure
		int _protection;	//nombre de degat que protege l armure

	public:
		Armure();			//construteur par defaut
		Armure(int tier);
		Armure(int tier,int protection);

		int get_protection();
		void display_info();

		~Armure();			//destructeur
};



#endif /* ARMURE_H_ */
