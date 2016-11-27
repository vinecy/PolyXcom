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
	int _isObstacle;
	int _costFromBegin;
	int _costFromEnd;
	int _heuristic;
public:
	Noeud(int x, int y, bool isObstacle);
	Noeud(int x, int y, bool isObstacle, int F, int G, int H);
	void set_costFromBegin(int value);
	void set_costFromEnd(int value);
	void set_heuristic(int value);
	int get_costFromBegin(void);
	int get_costFromEnd(void);
	int get_heuristic(void);

	virtual ~Noeud();
};

#endif /* NOEUD_H_ */
