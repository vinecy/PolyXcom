/*
 * Obstacle.h
 *
 *  Created on: 27 nov. 2016
 *      Author: Vincent
 */

#ifndef OBSTACLE_H_
#define OBSTACLE_H_
#include "Affichable.h"
class Obstacle : public Affichable
{
	protected:										//Attributs
		bool _destrutible;							//destructible ou pas

	public:
		Obstacle(int x,int y,int ID);				//Constructeur

		void display_info();						//Affichable debug

		virtual ~Obstacle();						//Destructeur
};



#endif /* OBSTACLE_H_ */
