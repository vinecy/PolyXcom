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
	Carte Luminy( (int)4 , (int)4 );
	cout << "Carte de Luminy crée" << endl;

	Luminy.display();

	Hero val(0,0,2,10, 10,"Valentin");
	cout << "Valentin est apparu" << endl;
	cout << &val << endl;

	cout << "Ajout de val sur la carte" << endl;
	Luminy.addItem(val);
	cout << "Valentin est sur la carte " << endl;


	Luminy.display();

	cout << "Deplacement en haut" << endl;
	val.move_up(Luminy);
	Luminy.display();
	val.move_up(Luminy);
	Luminy.display();

	return 0;
}
