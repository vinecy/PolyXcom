/*
 * Noeud.h
 *
 *  Created on: 27 nov. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef NOEUD_H_
#define NOEUD_H_

class Noeud {
private:
	int _x;
	int _y;
	int _G;
	int _H;
	int _F;
public:
	Noeud();
	Noeud(int x, int y);

	bool sameCoord(Noeud const&a);

	void set_costFromBegin(int value);
	void set_costFromEnd(int value);
	int get_costFromBegin(void);
	int get_costFromEnd(void);
	int get_heuristic(void);
	int get_X(void);
	int get_Y(void);

	virtual ~Noeud();
};

#endif /* NOEUD_H_ */
