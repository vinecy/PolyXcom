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
#include <map>
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

int move_switch ( void ){
	int reponse ;
	do {
		cout << "\n\t\t\t\t\tOu voulez vous allez : \n\t\t\t\t\t" << NORTH << " - au Nord " << endl;
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

int main() {
	int choix;
	int choix2;

	//system("cls");

	Carte Luminy( (int)4 , (int)4 );			//creation de la carte
	Carte Luminy2( "Luminy" );
	Luminy2.display();

	map<int,Personnage> team_hero;
	map<int,Personnage> team_ennemi;

	//list<Personnage*> team_hero;				//creation des listes d'equipes
	//list<Personnage*> team_ennemi;

	Hero val(0,0,2,10,8,Arme(),"Valentin");		//creation des perso
	Ennemi pro(1,0,3,2,1,Arme());
	//Ennemi gen(0,1,3,3,2,Arme());

	team_hero[0] = val;
	team_ennemi[0] = pro;
	//team_ennemi[1] = gen;

	/*team_hero.push_front(&val);					// maj liste equipe
	team_ennemi.push_front(&pro);
	team_ennemi.push_front(&gen);*/

	Luminy.addItem(team_hero[0]);						//ajoute des perso
	Luminy.addItem(team_ennemi[0]);
	Luminy.addItem(team_ennemi[1]);

	/*
	Luminy.addItem(val);						//ajoute des perso
	Luminy.addItem(pro);
	Luminy.addItem(gen);*/
	//Luminy.removeItem(pro);
	list<Personnage*>::iterator ite;

	int token;
	token=10;
	while(token>0)			//TANT QUE Ennemis detruit ou Hero detruits
	{
		token--;
		cout<<"Nouveau tour"<<endl;
		while(val.get_paCurrent()>0)		//TANT QUE pa!=0 pour tous les hero
		{
			cout<<"Tour de val "<<endl;
			do
			{
				cout<<"\t\t\t\t\tPA restants= "<<val.get_paCurrent()<<endl;
				Luminy.display();
				choix = main_switch() ;
				switch ( choix ){
				case DEPLACER :
					if(val.get_paCurrent()>=1)
					{
						do
						{
							choix2 = move_switch();
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
					}
					else
					{
						cout<<"Pas assez de PA"<<endl;;
					}
					break;
				case TIRER:
					cout<<"tirer"<<endl;
					break;
				case CC:
					if(val.get_paCurrent()>=3)
					{
						list<Personnage*> proch = val.near(Luminy,team_ennemi);
						val.close_combat(proch);
						list<Personnage*>::iterator ite;
						for(ite=proch.begin();ite!=proch.end();ite++)
						{
							if((*ite)->get_pvCurrent()==0)
							{
								Luminy.removeItem(*(*ite));//TODO tout seul
							}
						}
						break;
					}
					else
					{
						cout<<"Pas assez de PA"<<endl;
					}

				}
			}while ( choix != 0 ) ;
			val.set_paCurrent(0);
		}
		val.set_paCurrent(val.get_paMax());			//TANT QUE pa!=0 pour tous les ennemis
		while(pro.get_paCurrent()>0)
		{
			cout<<"Tour de pro"<<endl;
			Luminy.display();
			pro.set_paCurrent(0);
		}
		pro.set_paCurrent(pro.get_paMax());
	}

}






