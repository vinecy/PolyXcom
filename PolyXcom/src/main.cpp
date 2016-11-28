/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'élèves de Polytech Marseille. Il ne peut être
 * reproduit, utilisé ou modifié sans l'avis express de ses auteurs.
 */

/**
 * @author BARTHOLOMEAU Vincent <vincent.bartholomeau@etu.univ-amu.fr>
 * @author BISSUEL Valentin <valentin.bissuel@etu.univ-amu.fr>
 *
 * @version 0.0.1 / 24/11/2016
 *
 */

/**
 * @file main.c
 * @brief Le main permet de lancer le jeu.
 */

#include <iostream>
#include "Hero.h"
#include "Carte.h"
#include "Graphe.h"
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	/*Affichable val(0,0,2);
	Affichable e1(0,2,3);
	Affichable e2(3,0,3);
	Affichable m1(0,1,1);
	Affichable m2(2,0,1);

	Carte Luminy( (int)4 , (int)4 );

	Luminy.display();
	*/
	cout << "Création Carte de Luminy..." << endl;
	Carte Luminy( (int)6 , (int)6 );
	cout << "Carte de Luminy crée" << endl;

	Luminy.display();

	Hero val(0,0,2,10, 10,"Valentin");
	Hero ennemi(4,4,3,10, 10,"Valentin");
	Affichable mur1(2,3,1);
	Affichable mur2(3,4,1);
	Affichable mur3(3,3,1);
	Affichable mur4(3,2,1);
	Affichable mur5(3,1,1);

	Luminy.addItem(val);
	Luminy.addItem(ennemi);
	Luminy.addItem(mur1);
	Luminy.addItem(mur2);
	Luminy.addItem(mur3);
	Luminy.addItem(mur4);
	Luminy.addItem(mur5);

	Luminy.display();
	cout << " *** debut pathfinding " << endl;
	Luminy.pathfinding(Luminy, 0, 0, 4, 3);

/*
 *
 *
	Graphe test(Luminy);
	test.display();
*/


	return 0;
}
