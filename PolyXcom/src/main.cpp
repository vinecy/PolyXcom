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





