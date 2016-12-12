/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 *
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
 */

/**
 * @file main.c
 * @brief Le main permet de lancer le jeu.
 */

#include <iostream>
#include "Obstacle.h"
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

int main_switch();

int move_switch();

bool end_team(list<Personnage*> team);

int main() {
	int choix;
	int choix2;

	Carte Luminy( (int)4 , (int)4 );

	list<Ennemi> 		tank_ennemi;
	list<Hero>			tank_hero;
	list<Obstacle>  	tank_obstacle;

	list<Personnage*>	team_hero;
	list<Personnage*>	team_ennemi;

	list<Personnage*>::iterator ite_l;
	list<Ennemi>::iterator ite_e;
	list<Hero>::iterator ite_h;
	list<Obstacle>::iterator ite_o;

	//////////////////job de chargement a partir d'un fichier
	tank_hero.push_front(Hero(0,0,2,10,8,Arme(),"Vincent"));
	tank_ennemi.push_front(Ennemi(1,0,3,4,1,Arme()));
	tank_ennemi.push_front(Ennemi(0,1,3,5,2,Arme()));
	/////////////////

	for(ite_e=tank_ennemi.begin();ite_e!=tank_ennemi.end();ite_e++)
	{
		Luminy.addItem((*ite_e));
		team_ennemi.push_front(&(*ite_e));
	}
	for(ite_h=tank_hero.begin();ite_h!=tank_hero.end();ite_h++)
	{
		Luminy.addItem((*ite_h));
		team_hero.push_front(&(*ite_h));
	}
	for(ite_o=tank_obstacle.begin();ite_o!=tank_obstacle.end();ite_o++)
	{
		Luminy.addItem((*ite_o));
	}


	int token;
	token=10;
	while(token>0)			//TANT QUE Ennemis detruit ou Hero detruits
	{
		token--;
		cout<<"Nouveau tour"<<endl;
		ite_l=team_hero.begin();
		while((*ite_l)->get_paCurrent()>0)		//TANT QUE pa!=0 pour tous les hero
		{
			cout<<"Tour de val "<<endl;
			do
			{
				cout<<"\t\t\t\t\tPA restants= "<<(*ite_l)->get_paCurrent()<<endl;
				Luminy.display();
				choix = main_switch() ;
				switch ( choix ){
				case DEPLACER :
					if((*ite_l)->get_paCurrent()>=1)
					{
						do
						{
							choix2 = move_switch();
							switch(choix2)
							{
							case NORTH:
								(*ite_l)->move_up(Luminy);
								choix2=10;
								break;
							case EAST:
								(*ite_l)->move_right(Luminy);
								choix2=10;
								break;
							case SOUTH:
								(*ite_l)->move_down(Luminy);
								choix2=10;
								break;
							case WEST:
								(*ite_l)->move_left(Luminy);
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
					if((*ite_l)->get_paCurrent()>=3)
					{
						list<Personnage*> proch = (*ite_l)->near(Luminy,team_ennemi);
						(*ite_l)->close_combat(proch);
						list<Personnage*>::iterator ite;
						for(ite=proch.begin();ite!=proch.end();ite++)
						{
							if((*ite)->get_pvCurrent()<=0)
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
			(*ite_l)->set_paCurrent(0);
		}
		(*ite_l)->set_paCurrent((*ite_l)->get_paMax());			//TANT QUE pa!=0 pour tous les ennemis
		ite_l=team_ennemi.begin();
		while((*ite_l)->get_paCurrent()>0)
		{
			cout<<"Tour de pro"<<endl;
			Luminy.display();
			(*ite_l)->set_paCurrent(0);
		}
		(*ite_l)->set_paCurrent((*ite_l)->get_paMax());
	}
}



int main_switch ( void ){
	int reponse ;
	do {
		cout << "\nQue voulez-vous faire : \n " << DEPLACER << " - Se deplacer " << endl;
		cout << " " << TIRER  << " - Tirer " << endl;
		cout << " " << CC << " - Corps � Corps " << endl;
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
	}
	while ( reponse < 10 || reponse > WEST ) ;
	return( reponse ) ;
}

bool end_team(list<Personnage*> team)
{
	list<Personnage*>::iterator ite;
	for(ite=team.begin();ite!=team.end();ite++)
	{
		if((*ite)->get_paCurrent()==0)
		{
			return(0);
		}
	}
	return(1);
}
