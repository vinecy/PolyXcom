/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'�l�ves de Polytech Marseille. Il ne peut �tre
 * reproduit, utilis� ou modifi� sans l'avis express de ses auteurs.
 */

/**
 * @author BARTHOLOMEAU Vincent <vincent.bartholomeau@etu.univ-amu.fr>
 * @author BISSUEL Valentin <valentin.bissuel@etu.univ-amu.fr>
 *
 * @version 0.0.1 / 24/11/2016
 *
 * @todo -
 *
 * @bug -
 */

/**
 * @file main.c
 * @brief Le main permet de lancer le jeu.
 */

#include <iostream>
#include "Hero.h"
#include "Carte.h"
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

	Carte Luminy( (int)4 , (int)4 );
	Luminy.display();





	Hero test(2,3,5,11,7,"sergio");
	test.display_info();

	return 0;
}





