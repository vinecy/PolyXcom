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
#include <stdio.h>
#include <stdlib.h>
#include "Hero.h"
#include "Carte.h"
#include "Arme.h"
#include "Graphe.h"
#include "Ennemi.h"
#include "Obstacle.h"
using namespace std;

#define DEPLACER 1
#define TIRER 2
#define RECHARGER 3

int choisir ( void ){
    int reponse ;
    do {
		cout << "\nQue voulez-vous faire : \n " << DEPLACER << " - Se deplacer " << endl;
		cout << " " << TIRER  << " - Tirer " << endl;
		cout << " " << RECHARGER << " - Recharger son arme " << endl;
		cout << " Tapez 0 pour quitter le jeu \n> ";

		cin >> reponse ;
		//clean_stdin();
    }
    while ( reponse < 0 || reponse > RECHARGER ) ;
    return( reponse ) ;
}


int main() {

	Carte luminy(6,6);
	Hero val(1,1,2,10,10,Arme(),"Valentin");
	Ennemi pros(4,2,3,10,10,Arme());
	Obstacle mur1(3,0,1);
	Obstacle mur2(3,1,1);
	Obstacle mur3(3,2,1);
	Obstacle mur4(3,3,1);
	Obstacle mur5(3,4,1);
	Obstacle mur6(2,3,1);

	luminy.addItem(val);
	luminy.addItem(pros);
	luminy.addItem(mur1);
	luminy.addItem(mur2);
	luminy.addItem(mur3);
	luminy.addItem(mur4);
	luminy.addItem(mur5);
	luminy.addItem(mur6);

	luminy.display();

	luminy.pathfinding(1, 1, 4, 3);

	/*int choix;

	//system("cls");
	do {
		cout << "-------------------------------------------------------------------------------- \n";
		choix = choisir() ;
		switch ( choix ){
			case DEPLACER :




				break ;
			case TIRER :
				cout << "rien à faire" << endl;
				break ;
			case RECHARGER :
				cout << "rien à faire" << endl;
				break ;
		}
	} while ( choix != 0 ) ;
	cout << "Bye ! "<< endl;
	cout << "------------------------------------------------------------------------" << endl;*/

}





