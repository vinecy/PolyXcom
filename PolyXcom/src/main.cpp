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
#define CC 3
#define NORTH 11
#define EAST 12
#define SOUTH 13
#define WEST 14

int main_switch ( void ){
	int reponse ;
	do {
		cout << "\nQue voulez-vous faire : \n " << DEPLACER << " - Se deplacer " << endl;
		cout << " " << TIRER  << " - Tirer " << endl;
		cout << " " << CC << " - Corps à Corps " << endl;
		cout << " Tapez 0 pour passer votre tour \n> ";

		cin >> reponse ;
		//clean_stdin();
	}
	while ( reponse < 0 || reponse > CC ) ;
	return( reponse ) ;
}

int moove_switch ( void ){
	int reponse ;
	do {
		cout << "\n\t\t\t\t\tOu voullez vous allez : \n\t\t\t\t\t" << NORTH << " - au Nord " << endl;
		cout << "\t\t\t\t\t" << EAST  << " - a l'Est " << endl;
		cout << "\t\t\t\t\t" << SOUTH << " - au Sud " << endl;
		cout << "\t\t\t\t\t" << WEST << " - a l'Ouest " << endl;
		cout << "\t\t\t\t\tTapez 10 pour quitter le jeu \n> ";

		cin >> reponse ;
		//clean_stdin();
	}
	while ( reponse < 10 || reponse > WEST ) ;
	return( reponse ) ;
}

int fin_tour(list<Hero>)
{
	cout<<"ENTREE DANS LA FONCTION"<<endl;
	list<Hero>::iterator ite;
	/*
	for(&ite=l.begin();&ite!=l.end();ite++)
	{
		(*ite).display_info();
		cout<<(*ite).get_paCurrent()<<endl;
		if((*ite).get_paCurrent()<0)
		{
			cout<<"FINI"<<endl;
			return(0);
		}
	}
	*/
	cout<<"ENCORE"<<endl;
	return(1);
}


int main() {
	int choix;
	int choix2;

	//system("cls");

	Carte Luminy( (int)4 , (int)4 );			//creatin de la carte

	list<Hero> team_hero;						//creation des listes d'equipes
	list<Ennemi> team_ennemi;

	Hero val(0,0,2,10,1,Arme(),"Valentin");		//creation des perso
	//Hero vin(1,1,2,10,1,Arme(),"Vincent");
	Ennemi pro(2,2,3,10,1,Arme());

	team_hero.push_front(val);					// maj liste equipe
	//team_hero.push_front(vin);
	team_ennemi.push_front(pro);

	Luminy.addItem(val);						//ajoute des perso
	Luminy.addItem(pro);

	int token;
	token=3;
	while(token>0)			//TANT QUE Ennemis detruit ou Hero detruits
	{
		token--;
		cout<<"Nouveau tour"<<endl;
		while(val.get_paCurrent()>0)		//TANT QUE pa!=0 pour tous les hero
		{
			cout<<"Tour de val "<<endl;
			do {
				//cout << "-------------------------------------------------------------------------------- \n";
				cout<<"\t\t\t\t\tPA restants= "<<val.get_paCurrent()<<endl;
				Luminy.display();
				cout<<fin_tour(team_hero)<<endl;
				choix = main_switch() ;
				switch ( choix ){
				case DEPLACER :
					do
					{
						choix2 = moove_switch();
						switch(choix2)
						{
						case NORTH:
							val.move_up(Luminy);
							choix2=10;
							break;
						case EAST:
							val.move_right(Luminy);
							choix2=10;
							break;
						case SOUTH:
							val.move_down(Luminy);
							choix2=10;
							break;
						case WEST:
							val.move_left(Luminy);
							choix2=10;
							break;
						}
					}while (choix2 != 10 ) ;
					break;
				case TIRER:
					cout<<"peace man!"<<endl;
					break;
				case CC:
					cout<<"peace man!"<<endl;
					break;
				}
			} while ( choix != 0 ) ;
		}
		val.set_paCurrent(val.get_paMax());			//TANT QUE pa!=0 pour tous les ennemis
		while(pro.get_paCurrent()>0)
		{
			cout<<"Tour de pro"<<endl;
			Luminy.display();
			/*
			pro.move_up(Luminy);
			if(pro.get_paCurrent()>0)
			{
				pro.move_left(Luminy);
				if(pro.get_paCurrent()>0)
				{
					pro.move_right(Luminy);
					if(pro.get_paCurrent()>0)
					{
						pro.move_down(Luminy);
					}
				}
			}
			 */
			pro.set_paCurrent(0);
		}
		pro.set_paCurrent(pro.get_paMax());
	}
}






