/*
 * Affichable.h
 *
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

#ifndef AFFICHABLE_H_
#define AFFICHABLE_H_

#include <SFML/Graphics.hpp>

using namespace sf;

class Affichable
{
	protected:								//Attributs
		int _coordX;						//Abscisse
		int _coordY;						//Ordonnée
		int _ID;							//Identifiant
		int _rotation;
	public:
		Sprite _sprite;
		int _coordIHMx;
		int _coordIHMy;

	public:
		Affichable();						//Construteur par defaut
		Affichable(int x,int y,int ID);		//Constructeur surchagé

		int distance(Affichable);			//retourne la 1-distance entre 2 Affichables
		int distance(int x, int y);			//retourne la 1-distance avec une position
		void display_info(void);			//Affiche les attributs en console

		int get_x(void);					//getters
		int get_y(void);
		int get_ID(void);
		int get_rotation(){ return (_rotation); }
		void set_x(int);					//setters
		void set_y(int);
		void set_rotation(int r){ _rotation = r; }

		Sprite get_sprite();
		void set_sprite(Texture &spriteSheet);

		virtual ~Affichable();				//Destructeur
};

#endif /* AFFICHABLE_H_ */

