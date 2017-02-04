/*
 * Soin.h
 *
 *  Created on: 15 déc. 2016
 *      Author: Vincent
 */

#ifndef SOIN_H_
#define SOIN_H_


class Soin
{
private:
	int _heal;	//nombre de point de vie soigne par un medkit
	int _uses;	// utilisation de medkit restants

public:
	Soin();		//constructeur
	Soin(int s1, int s2);
	int get_heal();
	int get_uses();

	void display_info();			//affichage d'info dans la console

	void add_uses(int quantity);	//modifie la quantite de medkit disponible

	~Soin();	//destructeur
};


#endif /* SOIN_H_ */
