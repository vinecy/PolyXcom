/*
 * Arme.h
 *
 *  Created on: 29 nov. 2016
 *      Author: Vincent
 */

#ifndef ARME_H_
#define ARME_H_

class Arme
{
	private:
		int _tier;
		int _degats;
		int _portee;

	public:
		Arme();
		Arme(int,int,int);

		void display_info();

		virtual ~Arme();
};





#endif /* ARME_H_ */
