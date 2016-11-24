/*
 * Affichable.h
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

#ifndef AFFICHABLE_H_
#define AFFICHABLE_H_

class Affichable
{
	protected:
		int _coordX;
		int _coordY;
		int _ID;

	public:
		Affichable();
		Affichable(int x, int y);
		int get_x(void);
		int get_y(void);
		void set_x(int);
		void set_y(int);
};



#endif /* AFFICHABLE_H_ */
