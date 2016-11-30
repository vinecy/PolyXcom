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
#include "Hero.h"
#include "Carte.h"
#include "Graphe.h"
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

	int choix;

	//system("cls");
	do {
		cout << "-------------------------------------------------------------------------------- \n";
		choix = choisir() ;
		switch ( choix ){
			case DEPLACER :

				break ;
			case TIRER :

				break ;
			case RECHARGER :

				break ;
		}
	} while ( choix != 0 ) ;
	cout << "Bye ! "<< endl;
	cout << "------------------------------------------------------------------------" << endl;
	return( 0 ) ;
}
/*
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

	system("cls");
	system("cls");
	system("cls");
	system("cls");
	//Luminy.pathfinding(Luminy, 0, 0, 4, 3);


 *
 *
	Graphe test(Luminy);
	test.display();



	return 0;
}
*/





