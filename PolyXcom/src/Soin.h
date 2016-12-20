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

	int _heal;//TODO pourcentage de vie du hero ?
	int _uses;

public:
	Soin();

	int get_heal();
	int get_uses();

	void display_info();

	void add_uses(int quantity);

	~Soin();
};


#endif /* SOIN_H_ */
