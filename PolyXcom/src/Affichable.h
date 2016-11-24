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
	protected:					//Attributs
		int _coordX;
		int _coordY;
		int _ID;

	public:
		Affichable();			//Construtors
		Affichable(int,int,int);

		int get_x(void);		//getters
		int get_y(void);
		int get_ID(void);

		void set_x(int);		//setters
		void set_y(int);

		void display_info();

		virtual ~Affichable();	//Destructor

};

#endif /* AFFICHABLE_H_ */
