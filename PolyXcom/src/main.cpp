/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 *
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
#include <cstdlib>
#include "Obstacle.h"
#include "Hero.h"
#include "Carte.h"
#include "Arme.h"
#include "Graphe.h"
#include "Ennemi.h"
#include "Fichier.h"

using namespace std;

#define DEPLACER 1
#define TIRER 2
#define CC 3
#define CHANGER 4
#define NORTH 11
#define EAST 12
#define SOUTH 13
#define WEST 14

int main_switch();
int move_switch();
bool end_team(list<Personnage*>team);

int main()
{
	int choix;							//variables pour les switch
	int choix2;

	list<Ennemi> 		tank_ennemi;	//conteneurs pour
	list<Hero>			tank_hero;		//le chargement a partir d'un fichier
	list<Obstacle>  	tank_obstacle;
	list<Carte>  		collec_carte;

	list<Personnage*>	team_hero;		//equipes de personnages
	list<Personnage*>	team_ennemi;

	list<Personnage*>::iterator ite_l;	//itérateur de personnage qui agit
	list<Personnage*>::iterator ite;	//iterateur divers
	list<Ennemi>::iterator ite_e;		//iterateur ennemi
	list<Hero>::iterator ite_h;			//iterateur hero
	list<Obstacle>::iterator ite_o;		//iterateur obstacle
	list<Carte>::iterator ite_c;		//iterateur carte11

	Fichier pathMap("World");
	//collec_carte.push_back(Carte("Luminy"));
	Carte Luminy("Luminy",5,5);

	pathMap.loadMap("Luminy",collec_carte,tank_ennemi,tank_hero,tank_obstacle);

	for(ite_e=tank_ennemi.begin();ite_e!=tank_ennemi.end();ite_e++)	//chargement ennemis
	{
		Luminy.addItem((*ite_e));
		team_ennemi.push_front(&(*ite_e));
	}
	for(ite_h=tank_hero.begin();ite_h!=tank_hero.end();ite_h++)		//chargement heros
	{
		Luminy.addItem((*ite_h));
		team_hero.push_front(&(*ite_h));
	}
	for(ite_o=tank_obstacle.begin();ite_o!=tank_obstacle.end();ite_o++)	//chargement obstacles
	{
		Luminy.addItem((*ite_o));
	}

	bool cont=1;
	while(cont)
	{
		cout<<"\t\t\t\t\t\t\t\tNouveau tour"<<endl;
		ite_l=team_hero.begin();
		while(end_team(team_hero))		//TANT QUE pa!=0 pour tous les hero
		{
			cout<<"\t\t\t\t\t\t\t\tTour allié"<<endl;
			do
			{
				cout<<"\t\t\t\t\t\t\t\tPerso "<<(*ite_l)->get_x()<<"/"<<(*ite_l)->get_y()<<endl;
				cout<<"\t\t\t\t\t\t\t\tPA restants= "<<(*ite_l)->get_paCurrent()<<endl;
				Luminy.display();
				choix = main_switch() ;
				switch (choix)
				{
				case DEPLACER :
					do
					{
						choix2 = move_switch();
						switch(choix2)
						{
						case NORTH:
							Luminy.move_up(*(*ite_l));
							choix2=10;
							break;
						case EAST:
							Luminy.move_right(*(*ite_l));
							choix2=10;
							break;
						case SOUTH:
							Luminy.move_down(*(*ite_l));
							choix2=10;
							break;
						case WEST:
							Luminy.move_left(*(*ite_l));
							choix2=10;
							break;
						}
					}while (choix2!=10);
					break;
				case TIRER:
					if((*ite_l)->get_paCurrent()>=4)
					{
						list<Personnage*> in_range;
						for(ite=team_ennemi.begin();ite!=team_ennemi.end();ite++)
						{
							if(Luminy.pathIsPossible((*ite_l)->get_x(),(*ite_l)->get_y(),(*ite)->get_x(),(*ite)->get_y()))
							{
								in_range.push_front((*ite));
							}
						}
						(*ite_l)->shoot(in_range);
						list<Personnage*> temp;
						for(ite=team_ennemi.begin();ite!=team_ennemi.end();ite++)
						{
							if((*ite)->get_pvCurrent()>=1)
							{
								temp.push_front(*ite);
							}
							else
							{
								Luminy.removeItem(*(*ite));
							}
						}
						team_ennemi=temp;
						if(team_ennemi.size()==0)
						{
							cont=0;
						}
					}
					break;
				case CC:
					if((*ite_l)->get_paCurrent()>=3)
					{
						list<Personnage*> proch = (*ite_l)->near(team_ennemi);
						(*ite_l)->close_combat(proch);
						list<Personnage*> temp;
						for(ite=team_ennemi.begin();ite!=team_ennemi.end();ite++)
						{
							if((*ite)->get_pvCurrent()>=1)
							{
								temp.push_front(*ite);
							}
							else
							{
								Luminy.removeItem(*(*ite));
							}
						}
						team_ennemi=temp;
						if(team_ennemi.size()==0)
						{
							cont=0;
						}
					}
					else
					{
						cout<<"Pas assez de PA!"<<endl;
					}
				case CHANGER:
					if(team_hero.size()==1)
					{
						cout<<"Vous n'avez qu'un seul perso!";
					}
					else if((*ite_l)==team_hero.back())
					{
						ite_l=team_hero.begin();
					}
					else
					{
						ite_l++;
					}
				}
			}while(choix!=0);
			for(ite=team_hero.begin();ite!=team_hero.end();ite++)
			{
				(*ite)->set_paCurrent(0);
			}
		}
		for(ite=team_hero.begin();ite!=team_hero.end();ite++)
		{
			(*ite)->set_paCurrent((*ite)->get_paMax());
		}
		ite_l=team_ennemi.begin();
		while(end_team(team_ennemi))
		{
			cout<<"\t\t\t\t\t\t\t\tTour ennemi"<<endl;
			//Luminy.display();
			for(ite=team_ennemi.begin();ite!=team_ennemi.end();ite++)
			{
				(*ite)->set_paCurrent(0);
			}
		}
		for(ite=team_ennemi.begin();ite!=team_ennemi.end();ite++)
		{
			(*ite)->set_paCurrent((*ite)->get_paMax());
		}

	}
}

int main_switch ( void ){
	int reponse ;
	do {
		cout << "\nQue voulez-vous faire : \n " << DEPLACER << " - Se deplacer " << endl;
		cout << " " << TIRER  << " - Tirer " << endl;
		cout << " " << CC << " - Corps à Corps " << endl;
		cout << " " << CHANGER << " - Changer de Personnage " << endl;
		cout << " Tapez 0 pour passer votre tour \n> ";

		cin >> reponse ;

	}
	while ( reponse < 0 || reponse > CHANGER ) ;
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
	if(team.size()==0)
	{
		return(0);
	}
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
